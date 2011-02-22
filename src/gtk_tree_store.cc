#include "gtk_tree_store.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for TreeStores
	 */
	Persistent<FunctionTemplate> NodeGtkTreeStore::constructor_template;

	NodeGtkTreeStore::NodeGtkTreeStore (GtkTreeStore *store) {
		model = GTK_TREE_MODEL(store);
		newJavaScriptInstance(constructor_template);
	}

	Handle<Value> node_gtk_tree_store_new (const Arguments &args) {
		HandleScope scope;

		int length = args.Length();
		GType *columns = new GType[length];
		for (int i = 0; i < length; i++) {
			GType type = (int)(args[i]->ToNumber()->Value());
			columns[i] = type;
		}

		GtkTreeStore *treeStore = gtk_tree_store_newv((gint)length, columns);
		NodeGtkTreeStore *nodeTreeStore = new NodeGtkTreeStore(treeStore);

		return nodeTreeStore->obj;
	}

	Handle<Value> node_gtk_tree_store_append(const Arguments &args) {
		HandleScope scope;

		GtkTreeStore *treeStore = GTK_TREE_STORE(NodeGtkTreeStore::Data(args[0]->ToObject()));
		GtkTreeIter iter;
		GtkTreeIter *parent = NULL;
		if (args.Length() > 1) {
			GtkTreeIter parentIter = NodeGtkTreeIter::Data(args[1]->ToObject());
			parent = &parentIter;
		}

		gtk_tree_store_append(treeStore, &iter, parent);
		NodeGtkTreeIter *node_iter = new NodeGtkTreeIter(iter);

		return node_iter->obj;
	}

	Handle<Value> node_gtk_tree_store_set(const Arguments &args) {
		HandleScope scope;

		GtkTreeStore *treeStore = GTK_TREE_STORE(NodeGtkTreeStore::Data(args[0]->ToObject()));
		NodeGtkTreeIter *nodeTreeIter= ObjectWrap::Unwrap<NodeGtkTreeIter>(args[1]->ToObject());

		int n_values = (args.Length() - 2) / 2;
		int i;
		gint *columns = new gint[n_values];
		GValue *values = new GValue[n_values];

		for (i = 0; i < n_values; i++) {
			columns[i] = args[(i * 2) + 2]->ToNumber()->Value();
			Local<Value> arg = args[(i * 2) + 3];
			values[i] = {0};
			if (arg->IsString()) {
				g_value_init(&values[i], G_TYPE_STRING);
				String::AsciiValue contents(arg->ToString());
				g_value_set_string(&values[i], *contents);
			} else if (arg->IsBoolean()) {
				g_value_init(&values[i], G_TYPE_BOOLEAN);
				g_value_set_boolean(&values[i], arg->ToBoolean()->Value());
			} else if (arg->IsNumber()) {
				g_value_init(&values[i], G_TYPE_DOUBLE);
				g_value_set_double(&values[i], arg->ToNumber()->Value());
			} else {
				printf("  Unknown column!\n");
				return Undefined();
			}

		}

		GtkTreeIter iter = nodeTreeIter->getTreeIter();

		gtk_tree_store_set_valuesv(treeStore, &iter, columns, values, n_values);

		return Undefined();
	}


	/**
	 * Attach all treeStore methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeStore::SetupMethods (Handle<Object> target) {
		target->Set(v8::String::NewSymbol("tree_store_new"), v8::FunctionTemplate::New(node_gtk_tree_store_new)->GetFunction());
		target->Set(v8::String::NewSymbol("tree_store_append"), v8::FunctionTemplate::New(node_gtk_tree_store_append)->GetFunction());
		target->Set(v8::String::NewSymbol("tree_store_set"), v8::FunctionTemplate::New(node_gtk_tree_store_set)->GetFunction());
	}

	void NodeGtkTreeStore::SetupCallbacks(std::vector<SignalCallback> *callbacks) { }

	void NodeGtkTreeStore::SetupConstants(Handle<Object> target) { }

	/**
	 * Sets up the environment with all things treeStoreish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeStore::Initialize (Handle<Object> target) {
		HandleScope scope;

		SetupCallbacks(callbacks);
		SetupConstants(target);
		SetupMethods(target);

		NODE_GTK_NEW_CLASS(constructor_template, "TreeStore");
	}
}
