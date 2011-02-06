#include "gtk_hbox.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for HBoxs
	 */
	Persistent<FunctionTemplate> NodeGtkHBox::constructor_template;

	/**
	 * Creates a new HBox
	 *
	 * Parameters:
	 *   type - One of the GtkHBoxTypes
	 */
	NodeGtkHBox::NodeGtkHBox (gboolean homogeneous, gint spacing) {
		widget = gtk_hbox_new(homogeneous, spacing);
		addRef();
	}

	/**
	 * Creates a new HBox and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkHBoxTypes
	 *
	 * Returns:
	 * A new instance of the HBox class
	 */
	Handle<Value> gtk_hbox_new (const Arguments &args) {
		HandleScope scope;

		bool homogeneous = args[0]->ToBoolean()->Value();
		int spacing = (int)args[1]->ToNumber()->Value();

		NodeGtkHBox *hbox = new NodeGtkHBox((gboolean)homogeneous, (gint)spacing);

		// Make a new JavaScript object and return it
		Local<Object> obj = NodeGtkHBox::constructor_template->GetFunction()->NewInstance();
		obj->SetInternalField(0, External::New(hbox));
		return obj;
	}

	/**
	 * Attach all hbox methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkHBox::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("hbox_new"), v8::FunctionTemplate::New(gtk_hbox_new)->GetFunction());
	}

	void NodeGtkHBox::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		NodeGtkBox::SetupCallbacks(callbacks);
	}

	/**
	 * Sets up the environment with all things hboxish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkHBox::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> hboxTemplate = FunctionTemplate::New();
		hboxTemplate->SetClassName(String::New("HBox"));
		constructor_template = Persistent<FunctionTemplate>::New(hboxTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> hboxInstance = hboxTemplate->InstanceTemplate();
		hboxInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		NodeGtkHBox::SetupMethods(target);
		NodeGtkHBox::SetupCallbacks(callbacks);
	}
}
