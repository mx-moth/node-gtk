#ifndef NGTK_TREE_STORE_H_
#define NGTK_TREE_STORE_H_

#include "g_object.h"
#include "gtk_tree_iter.h"
#include "gtk_tree_model.h"

namespace nodeGtk {

	class NodeGtkTreeStore: public NodeGObject, public NodeGtkTreeModel {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			GtkTreeModel *model;

			/**
			 * Constructor. Creates a new NodeGtkTreeStore, which will wrap a new GtkTreeStore
			 */
			NodeGtkTreeStore(GtkTreeStore *treeStore);

			/**
			 * For getting the underlying GtkTreeStore.
			 *
			 * Returns:
			 * The pointer to the GtkTreeStore contained in this NodeGtkTreeStore
			 */
			static inline GtkTreeModel* Data(v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return ObjectWrap::Unwrap<NodeGtkTreeStore>(obj)->getModel();
			}

			virtual GtkTreeModel* getModel() {
				return model;
			}

			virtual void setModel(GtkTreeModel *model) {
				this->model = model;
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void SetupConstants(v8::Handle<v8::Object> target);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkTreeStore that holds the reference
			 */
			static NodeGtkTreeStore* From(GtkTreeStore *object) {
				NodeGtkTreeStore *button;
				NODE_GTK_GET_REF(object, button, NodeGtkTreeStore);
				return button;
			}

	};

} // namespace ngtk

#endif

