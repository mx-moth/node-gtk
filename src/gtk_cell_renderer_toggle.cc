#include "gtk_cell_renderer_toggle.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for CellRenderers
	 */
	Persistent<FunctionTemplate> NodeGtkCellRendererToggle::constructor_template;

	/**
	 * Creates a new Cell Renderer for Toggle
	 *
	 * Parameters:
	 *   cellRendererToggle - An instance of a GtkCellRendererToggle to wrap
	 */
	NodeGtkCellRendererToggle::NodeGtkCellRendererToggle(GtkCellRenderer *cellRendererToggle) {
		this->cellRenderer = cellRendererToggle;
		NODE_GTK_SET_REF_WITH_GETTER(this, NodeGtkCellRendererToggle, getCellRenderer);
		newJavaScriptInstance(constructor_template);
	}

	/**
	 * Creates a new GtkCellRendererToggle and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkButtonTypes
	 *
	 * Returns:
	 * A new instance of the Button class
	 */
	Handle<Value> node_gtk_cell_renderer_toggle_new (const Arguments &args) {
		HandleScope scope;

		GtkCellRenderer *cellRendererToggle = gtk_cell_renderer_toggle_new();
		NodeGtkCellRendererToggle *nodeCellRendererToggle = new NodeGtkCellRendererToggle(cellRendererToggle);

		return nodeCellRendererToggle->obj;
	}
	/**
	 * Attach all toggle cell renderer methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkCellRendererToggle::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("cell_renderer_toggle_new"), v8::FunctionTemplate::New(node_gtk_cell_renderer_toggle_new)->GetFunction());
	}

	void NodeGtkCellRendererToggle::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		NodeGtkWidget::SetupCallbacks(callbacks);
	}

	void NodeGtkCellRendererToggle::SetupConstants (Handle<Object> target) { }

	/**
	 * Sets up the environment with all things cell rendery
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkCellRendererToggle::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> cellRendererToggleTemplate = FunctionTemplate::New();
		cellRendererToggleTemplate->SetClassName(String::New("CellRendererToggle"));
		constructor_template = Persistent<FunctionTemplate>::New(cellRendererToggleTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> cellRendererToggleInstance = cellRendererToggleTemplate->InstanceTemplate();
		cellRendererToggleInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		NodeGtkCellRendererToggle::SetupMethods(target);
		NodeGtkCellRendererToggle::SetupConstants(target);
		NodeGtkCellRendererToggle::SetupCallbacks(callbacks);

	}
}
