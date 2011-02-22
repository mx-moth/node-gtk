#include "gtk_tree_view_column.h"
#include "gtk_cell_renderer.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for TreeViewColumns
	 */
	Persistent<FunctionTemplate> NodeGtkTreeViewColumn::constructor_template;

	/**
	 * Creates a new TreeViewColumn
	 */
	NodeGtkTreeViewColumn::NodeGtkTreeViewColumn (GtkTreeViewColumn *treeViewColumn) {
		this->treeViewColumn = treeViewColumn;
		NODE_GTK_SET_REF_WITH_GETTER(this, NodeGtkWindow, getTreeViewColumn);
		newJavaScriptInstance(constructor_template);
	}

	/**
	 * Creates a new TreeViewColumn and attaches it to a JavaScript object
	 *
	 * Returns:
	 * A new instance of the TreeViewColumn class
	 */
	Handle<Value> node_gtk_tree_view_column_new (const Arguments &args) {
		HandleScope scope;

		GtkTreeViewColumn *treeViewColumn = gtk_tree_view_column_new();
		NodeGtkTreeViewColumn *nodeGtkTreeViewColumn = new NodeGtkTreeViewColumn(treeViewColumn);

		return nodeGtkTreeViewColumn->obj;
	}

	/**
	 * Creates a new TreeViewColumn and attaches it to a JavaScript object
	 *
	 * Returns:
	 * A new instance of the TreeViewColumn class
	 */
	Handle<Value> node_gtk_tree_view_column_new_with_attributes (const Arguments &args) {
		HandleScope scope;

		String::AsciiValue title(args[0]->ToString());
		GtkCellRenderer *cellRenderer = NodeGtkCellRenderer::Data(args[1]->ToObject());

		GtkTreeViewColumn *treeViewColumn = gtk_tree_view_column_new_with_attributes(*title, cellRenderer, NULL);

		int i;
		for (i = 2; i < args.Length(); i = i + 2) {
			String::AsciiValue attribute(args[i]->ToString());
			int column = args[i + 1]->ToNumber()->Value();

			gtk_tree_view_column_add_attribute(treeViewColumn, cellRenderer, *attribute, column);
		}

		NodeGtkTreeViewColumn *nodeGtkTreeViewColumn = new NodeGtkTreeViewColumn(treeViewColumn);

		return nodeGtkTreeViewColumn->obj;
	}

	Handle<Value> node_gtk_tree_view_column_set_attributes(const Arguments &args) {
		HandleScope scope;

		GtkTreeViewColumn *treeViewColumn = NodeGtkTreeViewColumn::Data(args[0]->ToObject());
		GtkCellRenderer *cellRenderer = NodeGtkCellRenderer::Data(args[1]->ToObject());

		int i;
		for (i = 2; i < args.Length(); i = i + 2) {
			String::AsciiValue attribute(args[i]->ToString());
			int column = args[i + 1]->ToNumber()->Value();

			gtk_tree_view_column_add_attribute(treeViewColumn, cellRenderer, *attribute, column);
		}

		return Undefined();
	}

	Handle<Value> node_gtk_tree_view_column_add_attribute(const Arguments &args) {
		HandleScope scope;

		GtkTreeViewColumn *treeViewColumn = NodeGtkTreeViewColumn::Data(args[0]->ToObject());
		GtkCellRenderer *cellRenderer = NodeGtkCellRenderer::Data(args[1]->ToObject());

		String::AsciiValue attribute(args[2]->ToString());
		int column = args[3]->ToNumber()->Value();

		gtk_tree_view_column_add_attribute(treeViewColumn, cellRenderer, *attribute, column);

		return Undefined();
	}

	/*
	Handle<Value> node_gtk_tree_view_column_pressed(const Arguments &args) {
		HandleScope scope;
		GtkTreeViewColumn *treeViewColumn = NodeGtkTreeViewColumn::Data(args[0]->ToObject());
		gtk_tree_view_column_pressed(treeViewColumn);
		return Undefined();
	}
	Handle<Value> node_gtk_button_released(const Arguments &args) {
		HandleScope scope;
		GtkTreeViewColumn *treeViewColumn = NodeGtkTreeViewColumn::Data(args[0]->ToObject());
		gtk_button_released(treeViewColumn);
		return Undefined();
	}
	*/

	/**
	 * Attach all tree view methods methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeViewColumn::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("tree_view_column_new"), v8::FunctionTemplate::New(node_gtk_tree_view_column_new)->GetFunction());
		target->Set(v8::String::NewSymbol("tree_view_column_new_with_attributes"), v8::FunctionTemplate::New(node_gtk_tree_view_column_new_with_attributes)->GetFunction());
		target->Set(v8::String::NewSymbol("tree_view_column_set_attributes"), v8::FunctionTemplate::New(node_gtk_tree_view_column_set_attributes)->GetFunction());
		target->Set(v8::String::NewSymbol("tree_view_column_add_attribute"), v8::FunctionTemplate::New(node_gtk_tree_view_column_add_attribute)->GetFunction());
	}

	void NodeGtkTreeViewColumn::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		NodeGtkObject::SetupCallbacks(callbacks);
	}

	void NodeGtkTreeViewColumn::SetupConstants (Handle<Object> target) { }

	/**
	 * Sets up the environment with all things tree view columnish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeViewColumn::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> treeViewColumnTemplate = FunctionTemplate::New();
		treeViewColumnTemplate->SetClassName(String::New("TreeViewColumn"));
		constructor_template = Persistent<FunctionTemplate>::New(treeViewColumnTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> treeViewColumnInstance = treeViewColumnTemplate->InstanceTemplate();
		treeViewColumnInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		NodeGtkTreeViewColumn::SetupMethods(target);
		NodeGtkTreeViewColumn::SetupConstants(target);
		NodeGtkTreeViewColumn::SetupCallbacks(callbacks);

	}
}
