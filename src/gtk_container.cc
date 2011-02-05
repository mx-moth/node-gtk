#include "gtk_container.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;


	/**
	 * Creates a new Container and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkContainerTypes
	 *
	 * Returns:
	 * A new instance of the Container class
	 */
	Handle<Value> gtk_container_add (const Arguments &args) {
		HandleScope scope;

		GtkContainer *container = Container::Data(args[0]->ToObject());
		GtkWidget *widget = Widget::Data(args[1]->ToObject());

		gtk_container_add(container, widget);

		return Undefined();
	}


	/**
	 * Attach all container methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void Container::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("container_add"), v8::FunctionTemplate::New(gtk_container_add)->GetFunction());
	}

	/**
	 * Attach all container signals
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void Container::SetupCallbacks (std::vector<SignalCallback> *callbacks) {
		Widget::SetupCallbacks(callbacks);
	}

	/**
	 * Sets up the environment with all things entryish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void Container::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Attach methods to the target
		Container::SetupMethods(target);
		Container::SetupCallbacks(callbacks);

	}
}
