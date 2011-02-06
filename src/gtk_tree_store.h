#ifndef NGTK_TREE_VIEW_H_
#define NGTK_TREE_VIEW_H_

#include "g_object.h"

namespace nodeGtk {

	class NodeGtkTreeStore: public NodeGObject {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			GtkTreeStore *widget;

			/**
			 * Constructor. Creates a new NodeGtkTreeStore, which will wrap a new GtkTreeStore
			 */
			NodeGtkTreeStore(gint n_columns, GType *columns);

			/**
			 * For getting the underlying GtkTreeStore.
			 *
			 * Returns:
			 * The pointer to the GtkTreeStore contained in this NodeGtkTreeStore
			 */
			static inline GtkTreeStore* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_TREE_STORE(ObjectWrap::Unwrap<NodeGtkTreeStore>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkTreeStore that holds the reference
			 */
			static NodeGtkTreeStore* From(GtkTreeStore *object) {
				return (NodeGtkTreeStore*)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};

} // namespace ngtk

#endif

