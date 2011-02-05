#include "gtk_box.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;


	/*
	Handle<Value> gtk_box* (const Arguments &args) {
		HandleScope scope;

		GtkContainer *container = Container::Data(args[0]->ToObject());
		GtkWidget *widget = Widget::Data(args[1]->ToObject());

		gtk_box_*(container, widget);

		return Undefined();
	}
	*/

	/**
	 * Attach all box methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void Box::SetupMethods (Handle<Object> target) {
		HandleScope scope;
	}

	/**
	 * Attach all signals
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void Box::SetupCallbacks (std::vector<SignalCallback> *callbacks) {
		Container::SetupCallbacks(callbacks);
	}

	/**
	 * Sets up the environment with all things entryish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void Box::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Attach methods to the target
		Box::SetupMethods(target);
		Box::SetupCallbacks(callbacks);

	}
}

