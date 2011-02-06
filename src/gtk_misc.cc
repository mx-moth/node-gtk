#include "gtk_misc.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	Handle<Value> gtk_misc_set_alignment (const Arguments &args) {
		HandleScope scope;

		GtkMisc *misc = NodeGtkMisc::Data(args[0]->ToObject());
		float xalign = args[1]->ToNumber()->Value();
		float yalign = args[2]->ToNumber()->Value();

		gtk_misc_set_alignment(misc, (gfloat)(xalign), (gfloat)(yalign));

		return Undefined();
	}

	Handle<Value> gtk_misc_set_padding (const Arguments &args) {
		HandleScope scope;

		GtkMisc *misc = NodeGtkMisc::Data(args[0]->ToObject());
		int xpad = (int)args[1]->ToNumber()->Value();
		int ypad = (int)args[2]->ToNumber()->Value();

		gtk_misc_set_padding(misc, (gint)(xpad), (gint)(ypad));

		return Undefined();
	}

	Handle<Value> gtk_misc_get_alignment (const Arguments &args) {
		HandleScope scope;

		GtkMisc *misc = NodeGtkMisc::Data(args[0]->ToObject());
		gfloat xalign = 0;
		gfloat yalign = 0;

		gtk_misc_get_alignment(misc, &xalign, &yalign);

		Handle<Object> c = Object::New();
		c->Set(String::New("x"), v8::Number::New(xalign), None);
		c->Set(String::New("y"), v8::Number::New(xalign), None);
		return scope.Close(c);
	}

	Handle<Value> gtk_misc_get_padding (const Arguments &args) {
		HandleScope scope;

		GtkMisc *misc = NodeGtkMisc::Data(args[0]->ToObject());
		gint xpad = 0;
		gint ypad = 0;

		gtk_misc_get_padding(misc, &xpad, &ypad);

		Handle<Object> c = Object::New();
		c->Set(String::New("x"), v8::Number::New(xpad), None);
		c->Set(String::New("y"), v8::Number::New(ypad), None);
		return scope.Close(c);
	}


	/**
	 * Attach all misc methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkMisc::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("misc_set_padding"),   v8::FunctionTemplate::New(gtk_misc_set_padding)->GetFunction());
		target->Set(v8::String::NewSymbol("misc_set_alignment"), v8::FunctionTemplate::New(gtk_misc_set_alignment)->GetFunction());
		target->Set(v8::String::NewSymbol("misc_get_padding"),   v8::FunctionTemplate::New(gtk_misc_get_padding)->GetFunction());
		target->Set(v8::String::NewSymbol("misc_get_alignment"), v8::FunctionTemplate::New(gtk_misc_get_alignment)->GetFunction());
	}

	/**
	 * Attach all misc signals
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkMisc::SetupCallbacks (std::vector<SignalCallback> *callbacks) {
		NodeGtkWidget::SetupCallbacks(callbacks);
	}

	/**
	 * Sets up the environment with all things entryish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkMisc::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Attach methods to the target
		NodeGtkMisc::SetupMethods(target);
		NodeGtkMisc::SetupCallbacks(callbacks);
	}

}
