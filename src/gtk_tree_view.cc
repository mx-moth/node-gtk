#include "gtk_tree_view.h"
#include "gtk_tree_view_column.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for TreeViews
	 */
	Persistent<FunctionTemplate> NodeGtkTreeView::constructor_template;

	/**
	 * Creates a new NodeGtkTreeView
	 *
	 * Parameters:
	 *   type - One of the GtkTreeViewTypes
	 */
	NodeGtkTreeView::NodeGtkTreeView (GtkWidget *treeView) {
		widget = treeView;
		addRef();
		NODE_GTK_SET_REF(this, NodeGtkTreeView);
		newJavaScriptInstance(constructor_template);
	}
	Handle<Value> node_gtk_tree_view_new_with_model (const Arguments &args) {
		HandleScope scope;

		GtkTreeModel *model = ObjectWrap::Unwrap<NodeGtkTreeModel>(args[0]->ToObject())->getModel();

		GtkWidget *treeView = gtk_tree_view_new_with_model(model);
		NodeGtkTreeView *nodeTreeView = new NodeGtkTreeView(treeView);

		return nodeTreeView->obj;
	}
	Handle<Value> node_gtk_tree_view_append_column (const Arguments &args) {
		HandleScope scope;

		GtkTreeView *treeView = GTK_TREE_VIEW(NodeGtkTreeView::Data(args[0]->ToObject()));
		GtkTreeViewColumn *treeViewColumn = NodeGtkTreeViewColumn::Data(args[1]->ToObject());
		gtk_tree_view_append_column(treeView, treeViewColumn);

		return Undefined();
	}

	/**
	 * Attach all treeView methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeView::SetupMethods (Handle<Object> target) {
		target->Set(v8::String::NewSymbol("tree_view_new_with_model"), v8::FunctionTemplate::New(node_gtk_tree_view_new_with_model)->GetFunction());
		target->Set(v8::String::NewSymbol("tree_view_append_column"), v8::FunctionTemplate::New(node_gtk_tree_view_append_column)->GetFunction());
	}

	void NodeGtkTreeView::SetupCallbacks(std::vector<SignalCallback> *callbacks) { }

	void NodeGtkTreeView::SetupConstants(Handle<Object> target) { }

	/**
	 * Sets up the environment with all things treeViewish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeView::Initialize (Handle<Object> target) {
		HandleScope scope;

		SetupCallbacks(callbacks);
		SetupConstants(target);
		SetupMethods(target);

		NODE_GTK_NEW_CLASS(constructor_template, "TreeView");
	}
}
