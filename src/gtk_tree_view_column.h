#ifndef NGTK_TREE_VIEW_COLUMN_H_
#define NGTK_TREE_VIEW_COLUMN_H_

#include "gtk_object.h"

namespace nodeGtk {

	class NodeGtkTreeViewColumn: public NodeGtkObject {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			GtkTreeViewColumn *treeViewColumn;

			/**
			 * Constructor. Creates a new NodeGtkTreeViewColumn, which will wrap a new GtkTreeViewColumn
			 */
			NodeGtkTreeViewColumn(GtkTreeViewColumn *treeViewColumn);

			/**
			 * Checks to see if a v8::Object is a TreeViewColumn in disguise
			 *
			 * Parameters:
			 *   obj - The object to check for TreeViewColumnness
			 *
			 * Returns:
			 * True if the object is a tree view column, false otherwise
			 */
			static inline bool HasInstance(v8::Handle<v8::Object> val) {
				v8::HandleScope scope;

				if (val->IsObject()) {
					v8::Local<v8::Object> obj = val->ToObject();

					if (constructor_template->HasInstance(obj)) {
						return true;
					}
				}
				return false;
			}

			/**
			 * For getting the underlying GtkWidget.
			 *
			 * Usage:
			 * (code)
			 * GtkTreeViewColumn *treeViewColumn = TreeViewColumn::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkTreeViewColumn contained in this TreeViewColumn
			 */
			static inline GtkTreeViewColumn* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_TREE_VIEW_COLUMN(ObjectWrap::Unwrap<NodeGtkTreeViewColumn>(obj)->getTreeViewColumn());
			}

			virtual inline GtkTreeViewColumn* getTreeViewColumn() {
				return treeViewColumn;
			}
			virtual inline void setTreeViewColumn(GtkTreeViewColumn *widget) {
				this->treeViewColumn = treeViewColumn;
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupConstants (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkTreeViewColumn that holds the reference
			 */
			static NodeGtkTreeViewColumn* From(GtkTreeViewColumn *object) {
				NodeGtkTreeViewColumn *treeViewColumn;
				NODE_GTK_GET_REF(object, treeViewColumn, NodeGtkTreeViewColumn);
				return treeViewColumn;
			}

	};

} // namespace ngtk

#endif
