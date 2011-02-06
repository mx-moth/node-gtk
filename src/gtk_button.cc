#include "gtk_button.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for Buttons
	 */
	Persistent<FunctionTemplate> NodeGtkButton::constructor_template;

	/**
	 * Creates a new Button
	 *
	 * Parameters:
	 *   type - One of the GtkButtonTypes
	 */
	NodeGtkButton::NodeGtkButton () {
		widget = gtk_button_new();
		addRef();

		// Make a new JavaScript object and return it
		obj = NodeGtkButton::constructor_template->GetFunction()->NewInstance();
		obj->SetInternalField(0, External::New(this));
	}

	/**
	 * Creates a new Button and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkButtonTypes
	 *
	 * Returns:
	 * A new instance of the Button class
	 */
	Handle<Value> gtk_button_new (const Arguments &args) {
		HandleScope scope;

		NodeGtkButton *button = new NodeGtkButton();

		return button->obj;
	}

	/*
GtkWidget*  gtk_button_new_with_label       (const gchar *label);
GtkWidget*  gtk_button_new_with_mnemonic    (const gchar *label);
GtkWidget*  gtk_button_new_from_stock       (const gchar *stock_id);
*/

	Handle<Value> gtk_button_pressed(const Arguments &args) {
		HandleScope scope;
		GtkButton *button = NodeGtkButton::Data(args[0]->ToObject());
		gtk_button_pressed(button);
		return Undefined();
	}
	Handle<Value> gtk_button_released(const Arguments &args) {
		HandleScope scope;
		GtkButton *button = NodeGtkButton::Data(args[0]->ToObject());
		gtk_button_released(button);
		return Undefined();
	}
	Handle<Value> gtk_button_clicked(const Arguments &args) {
		HandleScope scope;
		GtkButton *button = NodeGtkButton::Data(args[0]->ToObject());
		gtk_button_clicked(button);
		return Undefined();
	}
	Handle<Value> gtk_button_enter(const Arguments &args) {
		HandleScope scope;
		GtkButton *button = NodeGtkButton::Data(args[0]->ToObject());
		gtk_button_enter(button);
		return Undefined();
	}
	Handle<Value> gtk_button_leave(const Arguments &args) {
		HandleScope scope;
		GtkButton *button = NodeGtkButton::Data(args[0]->ToObject());
		gtk_button_leave(button);
		return Undefined();
	}

	/*
	void        gtk_button_set_relief           (GtkButton *button, GtkReliefStyle newstyle);
	GtkReliefStyle gtk_button_get_relief        (GtkButton *button);
	*/

	Handle<Value> gtk_button_get_label(const Arguments &args) {
		HandleScope scope;
		GtkButton *button = NodeGtkButton::Data(args[0]->ToObject());
		const gchar *label = gtk_button_get_label(button);
		return scope.Close(String::New(label));
	}

	Handle<Value> gtk_button_set_label(const Arguments &args) {
		HandleScope scope;

		GtkButton *button = NodeGtkButton::Data(args[0]->ToObject());
		String::AsciiValue label(args[1]->ToString());

		gtk_button_set_label(button, *label);
		return Undefined();
	}

	/*
	gboolean    gtk_button_get_use_stock        (GtkButton *button);
	void        gtk_button_set_use_stock        (GtkButton *button, gboolean use_stock);
	gboolean    gtk_button_get_use_underline    (GtkButton *button);
	void        gtk_button_set_use_underline    (GtkButton *button, gboolean use_underline);
	void        gtk_button_set_focus_on_click   (GtkButton *button, gboolean focus_on_click);
	gboolean    gtk_button_get_focus_on_click   (GtkButton *button);
	void        gtk_button_set_alignment        (GtkButton *button, gfloat xalign, gfloat yalign);
	void        gtk_button_get_alignment        (GtkButton *button, gfloat *xalign, gfloat *yalign);
	*/

	/**
	 * Attach all button methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkButton::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("button_new"), v8::FunctionTemplate::New(gtk_button_new)->GetFunction());
		target->Set(v8::String::NewSymbol("button_pressed"), v8::FunctionTemplate::New(gtk_button_pressed)->GetFunction());
		target->Set(v8::String::NewSymbol("button_released"), v8::FunctionTemplate::New(gtk_button_released)->GetFunction());
		target->Set(v8::String::NewSymbol("button_clicked"), v8::FunctionTemplate::New(gtk_button_clicked)->GetFunction());
		target->Set(v8::String::NewSymbol("button_enter"), v8::FunctionTemplate::New(gtk_button_enter)->GetFunction());
		target->Set(v8::String::NewSymbol("button_leave"), v8::FunctionTemplate::New(gtk_button_leave)->GetFunction());
		target->Set(v8::String::NewSymbol("button_set_label"), v8::FunctionTemplate::New(gtk_button_set_label)->GetFunction());
		target->Set(v8::String::NewSymbol("button_get_label"), v8::FunctionTemplate::New(gtk_button_get_label)->GetFunction());
	}

	void NodeGtkButton::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		NodeGtkBin::SetupCallbacks(callbacks);
		(*callbacks).push_back(SignalCallback("activate", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("clicked", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("enter", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("leave", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("pressed", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("released", G_CALLBACK(signal_bare)));
	}

	/**
	 * Sets up the environment with all things buttonish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkButton::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> buttonTemplate = FunctionTemplate::New();
		buttonTemplate->SetClassName(String::New("Button"));
		constructor_template = Persistent<FunctionTemplate>::New(buttonTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> buttonInstance = buttonTemplate->InstanceTemplate();
		buttonInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		NodeGtkButton::SetupMethods(target);

		NodeGtkButton::SetupCallbacks(callbacks);
	}
}
