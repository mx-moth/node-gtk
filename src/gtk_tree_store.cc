#include "gtk_tree_store.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for TreeStores
	 */
	Persistent<FunctionTemplate> NodeGtkTreeStore::constructor_template;

	/**
	 * Creates a new NodeGtkTreeStore
	 *
	 * Parameters:
	 *   type - One of the GtkTreeStoreTypes
	 */
	NodeGtkTreeStore::NodeGtkTreeStore (gint n_columns, GType *columns) {
		widget = gtk_tree_store_new(n_columns, columns);

		obj = NodeGtkTreeStore::constructor_template->GetFunction()->NewInstance();
		obj->SetInternalField(0, External::New(this));
	}

	/**
	 * Creates a new NodeGtkTreeStore and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkTreeStoreTypes
	 *
	 * Returns:
	 * A new instance of the NodeGtkTreeStore class
	 */
	Handle<Value> gtk_tree_store_new (const Arguments &args) {
		HandleScope scope;

		int length = args.Length();
		GType *columns = new GType[length];
		for (int i = 0; i < length; i++) {
			columns[i] = (int)(args[i]->ToNumber()->Value());
		}

		NodeGtkTreeStore *treeStore = new NodeGtkTreeStore((gint)length, columns);

		return treeStore->obj;
	}

	/**
	 * Sets the text of an treeStore
	 *
	 * Parameters:
	 *   treeStore - The NodeGtkTreeStore to set the text of
	 *   text - The text to put in the treeStore
	Handle<Value> gtk_tree_store_set_text(const Arguments &args) {
		HandleScope scope;

		GtkTreeStore *treeStore = NodeGtkTreeStore::Data(args[0]->ToObject());
		String::AsciiValue text(args[1]->ToString());

		gtk_tree_store_set_text(treeStore, *text);

		return Undefined();
	}
	 */


	/**
	 * Attach all treeStore methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeStore::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("tree_store_new"), v8::FunctionTemplate::New(gtk_tree_store_new)->GetFunction());
		//target->Set(v8::String::NewSymbol("tree_store_set_text"), v8::FunctionTemplate::New(gtk_tree_store_set_text)->GetFunction());
	}

	void NodeGtkTreeStore::SetupCallbacks(std::vector<SignalCallback> *callbacks) { }

	/**
	 * Sets up the environment with all things treeStoreish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkTreeStore::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> treeStoreTemplate = FunctionTemplate::New();
		treeStoreTemplate->SetClassName(String::New("TreeStore"));
		constructor_template = Persistent<FunctionTemplate>::New(treeStoreTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> treeStoreInstance = treeStoreTemplate->InstanceTemplate();
		treeStoreInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		NodeGtkTreeStore::SetupMethods(target);

		NodeGtkTreeStore::SetupCallbacks(callbacks);
	}
}
