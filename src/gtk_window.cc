#include "gtk_window.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for Windows
	 */
	Persistent<FunctionTemplate> NodeGtkWindow::constructor_template;

	/**
	 * Creates a new Window
	 *
	 * Parameters:
	 *   type - One of the GtkWindowTypes
	 */
	NodeGtkWindow::NodeGtkWindow (GtkWindowType type) {
		// Make a new widget
		widget = gtk_window_new(type);
		// Add references to this
		addRef();
		// Wrap this in a JavaScript object
		obj = NodeGtkWindow::constructor_template->GetFunction()->NewInstance();
		obj->SetInternalField(0, External::New(this));
	}

	/**
	 * Creates a new Window and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkWindowTypes
	 *
	 * Returns:
	 * A new instance of the Window class
	 */
	Handle<Value> gtk_window_new (const Arguments &args) {
		HandleScope scope;

		assert(args[0]->IsNumber());

		GtkWindowType type = (GtkWindowType)args[0]->ToNumber()->IntegerValue();
		NodeGtkWindow *window = new NodeGtkWindow(type);

		return window->obj;
	}

	/**
	 * Sets the title of a Window
	 *
	 * Parameters:
	 *   title - The title of the window
	 */
	Handle<Value> gtk_window_set_title (const Arguments &args) {
		HandleScope scope;

		assert(NodeGtkWindow::HasInstance(args[0]->ToObject()));
		assert(args[1]->IsString());

		GtkWindow *window = NodeGtkWindow::Data(args[0]->ToObject());
		String::AsciiValue title(args[1]->ToString());
		gtk_window_set_title(window, *title);

		return Undefined();
	}


	/**
	 * Attach all window methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkWindow::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("window_new"), v8::FunctionTemplate::New(gtk_window_new)->GetFunction());
		target->Set(v8::String::NewSymbol("window_set_title"), v8::FunctionTemplate::New(gtk_window_set_title)->GetFunction());
	}

	/**
	 * Sets up the environment with all things windowy
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkWindow::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> windowTemplate = FunctionTemplate::New();
		windowTemplate->SetClassName(String::New("Window"));
		constructor_template = Persistent<FunctionTemplate>::New(windowTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> windowInstance = windowTemplate->InstanceTemplate();
		windowInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		NodeGtkWindow::SetupMethods(target);

	}
}
