#include "gtk_label.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for Labels
	 */
	Persistent<FunctionTemplate> NodeGtkLabel::constructor_template;

	/**
	 * Creates a new Label
	 *
	 * Parameters:
	 *   type - One of the GtkLabelTypes
	 */
	NodeGtkLabel::NodeGtkLabel (gchar *text) {
		widget = gtk_label_new(text);
		addRef();
		obj = NodeGtkLabel::constructor_template->GetFunction()->NewInstance();
		obj->SetInternalField(0, External::New(this));
	}

	/**
	 * Creates a new Label and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   text - The text to put in the label
	 *
	 * Returns:
	 * A new instance of the Label class
	 */
	Handle<Value> gtk_label_new (const Arguments &args) {
		HandleScope scope;

		String::AsciiValue text(args[0]->ToString());
		NodeGtkLabel *label = new NodeGtkLabel((gchar*)*text);

		// Make a new JavaScript object and return it
		return label->obj;
	}

	/**
	 * Sets the text of a label
	 *
	 * Parameters:
	 *   label - The Label to set the text of
	 *   text - The text to put in the label
	 */
	Handle<Value> gtk_label_set_text(const Arguments &args) {
		HandleScope scope;

		GtkLabel *label = NodeGtkLabel::Data(args[0]->ToObject());
		String::AsciiValue text(args[1]->ToString());

		gtk_label_set_text(label, *text);

		return Undefined();
	}

	/**
	 * Gets the text of a label
	 *
	 * Parameters:
	 *   label - The Label to get the text from
	 *
	 * Returns:
	 * The text from the Label
	 */
	Handle<Value> gtk_label_get_text(const Arguments &args) {
		HandleScope scope;

		GtkLabel *label = NodeGtkLabel::Data(args[0]->ToObject());

		return scope.Close(String::New(gtk_label_get_text(label)));
	}

	/**
	 * Attach all label methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkLabel::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("label_new"), v8::FunctionTemplate::New(gtk_label_new)->GetFunction());
		target->Set(v8::String::NewSymbol("label_set_text"), v8::FunctionTemplate::New(gtk_label_set_text)->GetFunction());
		target->Set(v8::String::NewSymbol("label_get_text"), v8::FunctionTemplate::New(gtk_label_get_text)->GetFunction());
	}

	void NodeGtkLabel::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		NodeGtkMisc::SetupCallbacks(callbacks);
		//TODO Callbacks for this
	}

	/**
	 * Sets up the environment with all things labelish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkLabel::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> labelTemplate = FunctionTemplate::New();
		labelTemplate->SetClassName(String::New("Label"));
		constructor_template = Persistent<FunctionTemplate>::New(labelTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> labelInstance = labelTemplate->InstanceTemplate();
		labelInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		NodeGtkLabel::SetupMethods(target);

		NodeGtkLabel::SetupCallbacks(callbacks);
	}
}
