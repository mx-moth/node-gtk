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

		GtkContainer *container = NodeGtkContainer::Data(args[0]->ToObject());
		GtkWidget *widget = NodeGtkWidget::Data(args[1]->ToObject());

		gtk_container_add(container, widget);

		return Undefined();
	}


	/**
	 * Attach all container methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkContainer::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("container_add"), v8::FunctionTemplate::New(gtk_container_add)->GetFunction());
	}

	/**
	 * Attach all container signals
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkContainer::SetupCallbacks (std::vector<SignalCallback> *callbacks) {
		NodeGtkWidget::SetupCallbacks(callbacks);
	}

	/**
	 * Sets up the environment with all things entryish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkContainer::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Attach methods to the target
		NodeGtkContainer::SetupMethods(target);
		NodeGtkContainer::SetupCallbacks(callbacks);

	}
}
