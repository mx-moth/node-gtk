#include "gtk_tree_iter.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for TreeIters
	 */
	Persistent<FunctionTemplate> NodeGtkTreeIter::constructor_template;

	/**
	 * Creates a new NodeGtkTreeIter
	 *
	 * Parameters:
	 *   type - One of the GtkTreeIterTypes
	 */
	NodeGtkTreeIter::NodeGtkTreeIter (GtkTreeIter iter) {
		treeIter = GtkTreeIter(iter);

		newJavaScriptInstance(constructor_template);
	}

	/**
	 * Creates a new NodeGtkTreeIter and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkTreeIterTypes
	 *
	 * Returns:
	 * A new instance of the NodeGtkTreeIter class
	Handle<Value> node_gtk_tree_iter (const Arguments &args) {
		HandleScope scope;

		int length = args.Length();
		GType *columns = new GType[length];
		for (int i = 0; i < length; i++) {
			GType type = (int)(args[i]->ToNumber()->Value());
			columns[i] = type;
		}

		NodeGtkTreeIter *treeIter = new NodeGtkTreeIter((gint)length, columns);

		return treeIter->obj;
	}

	Handle<Value> node_gtk_tree_iter_append(const Arguments &args) {
		HandleScope scope;

		GtkTreeIter *treeIter = NodeGtkTreeIter::Data(args[0]->ToObject());
		GtkTreeIter *parent = NodeGtkTreeIter::Data(args[1]->ToObject());

		GtkTreeIter iter;

		gtk_tree_iter_append(treeIter, &iter, parent);

		NodeGtkTreeIter *node_iter = new NodeGtkTreeIter(iter);

		return node_iter->obj;
	}
	 */


	/**
	 * Attach all treeIter methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeIter::SetupMethods (Handle<Object> target) {
		// target->Set(v8::String::NewSymbol("tree_iter_new"), v8::FunctionTemplate::New(node_gtk_tree_iter_new)->GetFunction());
		// target->Set(v8::String::NewSymbol("tree_iter_append"), v8::FunctionTemplate::New(node_gtk_tree_iter_append)->GetFunction());
	}

	void NodeGtkTreeIter::SetupCallbacks(std::vector<SignalCallback> *callbacks) { }

	void NodeGtkTreeIter::SetupConstants(Handle<Object> target) { }

	/**
	 * Sets up the environment with all things treeIterish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeIter::Initialize (Handle<Object> target) {
		HandleScope scope;

		SetupCallbacks(callbacks);
		SetupConstants(target);
		SetupMethods(target);

		NODE_GTK_NEW_CLASS(constructor_template, "TreeIter");
	}
}
