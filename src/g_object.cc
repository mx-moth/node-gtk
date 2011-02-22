#include "g_object.h"

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * Bare signal. Used as the intermediate callback for various signals.
	 * Register a focus listener using @widget.on(signal, callback);@. Many signals
	 * are bare, this function handles all of them.
	 *
	 * Parameter:
	 *   widget - The widget that triggered the signal
	 *   callback_ptr - The user data, which is the JavaScript function to call
	 */
	void signal_bare(GtkWidget *widget, gpointer callback_ptr) {
		Persistent<Function> *callback = reinterpret_cast<Persistent<Function>*>(callback_ptr);
		TryCatch try_catch;

		(*callback)->Call(Context::GetCurrent()->Global(), 0, NULL);

		if (try_catch.HasCaught()) {
			FatalException(try_catch);
		}
	}


	/**
	 * Boolean signal. Used as the intermediate callback for various signals.
	 * Register a focus listener using @widget.on(signal, callback);@. Many signals
	 * are bare, but return a gboolean to indicate success/failure, or if the event
	 * should propagate. This function handles all of them.
	 *
	 * Parameter:
	 *   widget - The widget that triggered the signal
	 *   callback_ptr - The user data, which is the JavaScript function to call
	 *
	 * Returns:
	 * True or false, what ever the callback returns
	 */
	gboolean signal_boolean(GtkWidget *widget, gpointer callback_ptr) {
		Persistent<Function> *callback = reinterpret_cast<Persistent<Function>*>(callback_ptr);
		TryCatch try_catch;

		Local<Value> ret = (*callback)->Call(Context::GetCurrent()->Global(), 0, NULL);

		if (try_catch.HasCaught()) {
			FatalException(try_catch);
		}

		if (ret.IsEmpty()) {
			printf("Bad return");
		}

		return (*ret)->IsTrue();
	}

	std::vector<SignalCallback> *NodeGObject::callbacks = new std::vector<SignalCallback>;

	void NodeGObject::SetupCallbacks(std::vector<SignalCallback> *callbacks) {}
	void NodeGObject::SetupMethods(Handle<Object> target) {}
	void NodeGObject::SetupConstants(Handle<Object> target) {
		GTK_DEFINE_CONSTANT(target, "G_TYPE_INVALID", G_TYPE_INVALID);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_NONE", G_TYPE_NONE);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_INTERFACE", G_TYPE_INTERFACE);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_CHAR", G_TYPE_CHAR);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_UCHAR", G_TYPE_UCHAR);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_BOOLEAN", G_TYPE_BOOLEAN);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_INT", G_TYPE_INT);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_UINT", G_TYPE_UINT);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_LONG", G_TYPE_LONG);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_ULONG", G_TYPE_ULONG);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_INT64", G_TYPE_INT64);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_UINT64", G_TYPE_UINT64);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_ENUM", G_TYPE_ENUM);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_FLAGS", G_TYPE_FLAGS);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_FLOAT", G_TYPE_FLOAT);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_DOUBLE", G_TYPE_DOUBLE);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_STRING", G_TYPE_STRING);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_POINTER", G_TYPE_POINTER);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_BOXED", G_TYPE_BOXED);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_PARAM", G_TYPE_PARAM);
		GTK_DEFINE_CONSTANT(target, "G_TYPE_OBJECT", G_TYPE_OBJECT);


		// Position constants.
		GTK_DEFINE_CONSTANT(target, "WIN_POS_NONE",             GTK_WIN_POS_NONE);
		GTK_DEFINE_CONSTANT(target, "WIN_POS_CENTER",           GTK_WIN_POS_CENTER);
		GTK_DEFINE_CONSTANT(target, "WIN_POS_MOUSE",            GTK_WIN_POS_MOUSE);
		GTK_DEFINE_CONSTANT(target, "WIN_POS_CENTER_ALWAYS",    GTK_WIN_POS_CENTER_ALWAYS);
		GTK_DEFINE_CONSTANT(target, "WIN_POS_CENTER_ON_PARENT", GTK_WIN_POS_CENTER_ON_PARENT);

		// MessageDialog constants
		GTK_DEFINE_CONSTANT(target, "DIALOG_MODAL",               GTK_DIALOG_MODAL);
		GTK_DEFINE_CONSTANT(target, "DIALOG_DESTROY_WITH_PARENT", GTK_DIALOG_DESTROY_WITH_PARENT);
		GTK_DEFINE_CONSTANT(target, "DIALOG_NO_SEPARATOR",        GTK_DIALOG_NO_SEPARATOR);

		// Message types.
		GTK_DEFINE_CONSTANT(target, "MESSAGE_INFO",     GTK_MESSAGE_INFO);
		GTK_DEFINE_CONSTANT(target, "MESSAGE_WARNING",  GTK_MESSAGE_WARNING);
		GTK_DEFINE_CONSTANT(target, "MESSAGE_QUESTION", GTK_MESSAGE_QUESTION);
		GTK_DEFINE_CONSTANT(target, "MESSAGE_ERROR",    GTK_MESSAGE_ERROR);
		GTK_DEFINE_CONSTANT(target, "MESSAGE_OTHER",    GTK_MESSAGE_OTHER);

		// Buttons.
		GTK_DEFINE_CONSTANT(target, "BUTTONS_NONE",      GTK_BUTTONS_NONE);
		GTK_DEFINE_CONSTANT(target, "BUTTONS_OK",        GTK_BUTTONS_OK);
		GTK_DEFINE_CONSTANT(target, "BUTTONS_CLOSE",     GTK_BUTTONS_CLOSE);
		GTK_DEFINE_CONSTANT(target, "BUTTONS_CANCEL",    GTK_BUTTONS_CANCEL);
		GTK_DEFINE_CONSTANT(target, "BUTTONS_YES_NO",    GTK_BUTTONS_YES_NO);
		GTK_DEFINE_CONSTANT(target, "BUTTONS_OK_CANCEL", GTK_BUTTONS_OK_CANCEL);

		// Position
		GTK_DEFINE_CONSTANT(target, "POS_TOP", GTK_POS_TOP);
		GTK_DEFINE_CONSTANT(target, "POS_RIGHT", GTK_POS_RIGHT);
		GTK_DEFINE_CONSTANT(target, "POS_BOTTOM", GTK_POS_BOTTOM);
		GTK_DEFINE_CONSTANT(target, "POS_LEFT", GTK_POS_LEFT);

		// Response constants
		GTK_DEFINE_CONSTANT(target, "RESPONSE_NONE",         GTK_RESPONSE_NONE);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_REJECT",       GTK_RESPONSE_REJECT);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_ACCEPT",       GTK_RESPONSE_ACCEPT);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_DELETE_EVENT", GTK_RESPONSE_DELETE_EVENT);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_OK",           GTK_RESPONSE_OK);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_CANCEL",       GTK_RESPONSE_CANCEL);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_CLOSE",        GTK_RESPONSE_CLOSE);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_YES",          GTK_RESPONSE_YES);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_NO",           GTK_RESPONSE_NO);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_APPLY",        GTK_RESPONSE_APPLY);
		GTK_DEFINE_CONSTANT(target, "RESPONSE_HELP",         GTK_RESPONSE_HELP);

		// Direction type constants
		GTK_DEFINE_CONSTANT(target, "DIR_TAB_FORWARD",       GTK_DIR_TAB_FORWARD);
		GTK_DEFINE_CONSTANT(target, "DIR_TAB_BACKWARD",      GTK_DIR_TAB_BACKWARD);
		GTK_DEFINE_CONSTANT(target, "DIR_UP",                GTK_DIR_UP);
		GTK_DEFINE_CONSTANT(target, "DIR_DOWN",              GTK_DIR_DOWN);
		GTK_DEFINE_CONSTANT(target, "DIR_LEFT",              GTK_DIR_LEFT);
		GTK_DEFINE_CONSTANT(target, "DIR_RIGHT",             GTK_DIR_RIGHT);
	}

	void NodeGObject::Initialize(v8::Handle<v8::Object> target) {
		v8::HandleScope scope;

		SetupCallbacks(callbacks);
		SetupConstants(target);
		SetupMethods(target);
	}

} // namespace ngtk
