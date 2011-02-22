#ifndef NGTK_TREE_ITER_H_
#define NGTK_TREE_ITER_H_

#include "g_object.h"

namespace nodeGtk {

	class NodeGtkTreeIter: public NodeGObject {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			GtkTreeIter treeIter;

			/**
			 * Constructor. Creates a new NodeGtkTreeIter, which will wrap a new GtkTreeIter
			 */
			NodeGtkTreeIter(GtkTreeIter treeIter);

			/**
			 * For getting the underlying GtkTreeIter.
			 *
			 * Returns:
			 * The pointer to the GtkTreeIter contained in this NodeGtkTreeIter
			 */
			static inline GtkTreeIter Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return ObjectWrap::Unwrap<NodeGtkTreeIter>(obj)->getTreeIter();
			}

			virtual inline GtkTreeIter getTreeIter() {
				return treeIter;
			}
			virtual inline void setTreeIter(GtkTreeIter treeIter) {
				this->treeIter = GtkTreeIter(treeIter);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void SetupConstants(v8::Handle<v8::Object> target);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkTreeIter that holds the reference
			 */
			static NodeGtkTreeIter* From(GtkTreeIter *object) {
				NodeGtkTreeIter *button;
				NODE_GTK_GET_REF(object, button, NodeGtkTreeIter);
				return button;
			}

	};

} // namespace ngtk

#endif

