#include "gtk_box.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * Attach all box methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkBox::SetupMethods (Handle<Object> target) {
		HandleScope scope;
	}

	/**
	 * Attach all signals
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkBox::SetupCallbacks (std::vector<SignalCallback> *callbacks) {
		NodeGtkContainer::SetupCallbacks(callbacks);
	}

	/**
	 * Sets up the environment with all things entryish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkBox::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Attach methods to the target
		NodeGtkBox::SetupMethods(target);
		NodeGtkBox::SetupCallbacks(callbacks);

	}
}

