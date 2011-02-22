#include "gtk_cell_renderer_text.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for CellRenderers
	 */
	Persistent<FunctionTemplate> NodeGtkCellRendererText::constructor_template;

	/**
	 * Creates a new Cell Renderer for Text
	 *
	 * Parameters:
	 *   cellRendererText - An instance of a GtkCellRendererText to wrap
	 */
	NodeGtkCellRendererText::NodeGtkCellRendererText(GtkCellRenderer *cellRendererText) {
		this->cellRenderer = cellRendererText;
		NODE_GTK_SET_REF_WITH_GETTER(this, NodeGtkCellRendererText, getCellRenderer);
		newJavaScriptInstance(constructor_template);
	}

	/**
	 * Creates a new GtkCellRendererText and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkButtonTypes
	 *
	 * Returns:
	 * A new instance of the Button class
	 */
	Handle<Value> node_gtk_cell_renderer_text_new (const Arguments &args) {
		HandleScope scope;

		GtkCellRenderer *cellRendererText = gtk_cell_renderer_text_new();
		NodeGtkCellRendererText *nodeCellRendererText = new NodeGtkCellRendererText(cellRendererText);

		return nodeCellRendererText->obj;
	}
	/**
	 * Attach all text cell renderer methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkCellRendererText::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("cell_renderer_text_new"), v8::FunctionTemplate::New(node_gtk_cell_renderer_text_new)->GetFunction());
	}

	void NodeGtkCellRendererText::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		NodeGtkWidget::SetupCallbacks(callbacks);
	}

	void NodeGtkCellRendererText::SetupConstants (Handle<Object> target) { }

	/**
	 * Sets up the environment with all things cell rendery
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkCellRendererText::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> cellRendererTextTemplate = FunctionTemplate::New();
		cellRendererTextTemplate->SetClassName(String::New("CellRendererText"));
		constructor_template = Persistent<FunctionTemplate>::New(cellRendererTextTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> cellRendererTextInstance = cellRendererTextTemplate->InstanceTemplate();
		cellRendererTextInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		NodeGtkCellRendererText::SetupMethods(target);
		NodeGtkCellRendererText::SetupConstants(target);
		NodeGtkCellRendererText::SetupCallbacks(callbacks);

	}
}
