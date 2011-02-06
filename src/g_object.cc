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

} // namespace ngtk
