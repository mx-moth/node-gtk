#include "gtk_cell_renderer.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for CellRenderers
	 */
	Persistent<FunctionTemplate> NodeGtkCellRenderer::constructor_template;

	/**
	 * Attach all cell renderer methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkCellRenderer::SetupMethods (Handle<Object> target) {
		HandleScope scope;
	}
	void NodeGtkCellRenderer::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		NodeGtkWidget::SetupCallbacks(callbacks);
	}

	/**
	 * Sets up the environment with all things cell rendery
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkCellRenderer::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Attach methods to the target
		NodeGtkCellRenderer::SetupMethods(target);
		NodeGtkCellRenderer::SetupConstants(target);
		NodeGtkCellRenderer::SetupCallbacks(callbacks);

	}
}
