#ifndef NGTK_TREE_VIEW_H_
#define NGTK_TREE_VIEW_H_

#include "gtk_container.h"
#include "gtk_tree_iter.h"
#include "gtk_tree_model.h"
#include "gtk_tree_store.h"

namespace nodeGtk {

	class NodeGtkTreeView: public NodeGtkContainer {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			/**
			 * Constructor. Creates a new NodeGtkTreeView, which will wrap a new GtkTreeView
			 */
			NodeGtkTreeView(GtkWidget *treeView);

			/**
			 * For getting the underlying GtkTreeView.
			 *
			 * Returns:
			 * The pointer to the GtkTreeView contained in this NodeGtkTreeView
			 */
			static inline GtkTreeView* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_TREE_VIEW(ObjectWrap::Unwrap<NodeGtkTreeView>(obj)->getWidget());
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void SetupConstants(v8::Handle<v8::Object> target);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkTreeView that holds the reference
			 */
			static NodeGtkTreeView* From(GtkTreeView *object) {
				NodeGtkTreeView *button;
				NODE_GTK_GET_REF(object, button, NodeGtkTreeView);
				return button;
			}

	};

} // namespace ngtk

#endif

