#include "gtk_vbox.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for VBoxs
	 */
	Persistent<FunctionTemplate> VBox::constructor_template;

	/**
	 * Creates a new VBox
	 *
	 * Parameters:
	 *   type - One of the GtkVBoxTypes
	 */
	VBox::VBox (gboolean homogeneous, gint spacing) {
		widget = gtk_vbox_new(homogeneous, spacing);
		addRef();
	}

	/**
	 * Creates a new VBox and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkVBoxTypes
	 *
	 * Returns:
	 * A new instance of the VBox class
	 */
	Handle<Value> gtk_vbox_new (const Arguments &args) {
		HandleScope scope;

		bool homogeneous = args[0]->ToBoolean()->Value();
		int spacing = (int)args[1]->ToNumber()->Value();

		VBox *vbox = new VBox((gboolean)homogeneous, (gint)spacing);

		// Make a new JavaScript object and return it
		Local<Object> obj = VBox::constructor_template->GetFunction()->NewInstance();
		obj->SetInternalField(0, External::New(vbox));
		return obj;
	}

	/**
	 * Attach all vbox methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void VBox::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("vbox_new"), v8::FunctionTemplate::New(gtk_vbox_new)->GetFunction());
	}

	void VBox::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		Box::SetupCallbacks(callbacks);
	}

	/**
	 * Sets up the environment with all things vboxish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void VBox::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> vboxTemplate = FunctionTemplate::New();
		vboxTemplate->SetClassName(String::New("VBox"));
		constructor_template = Persistent<FunctionTemplate>::New(vboxTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> vboxInstance = vboxTemplate->InstanceTemplate();
		vboxInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		VBox::SetupMethods(target);
		VBox::SetupCallbacks(callbacks);
	}
}
