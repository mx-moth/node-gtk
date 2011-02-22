#ifndef NGTK_CELL_RENDERER_H_
#define NGTK_CELL_RENDERER_H_

#include "gtk_widget.h"

namespace nodeGtk {

	class NodeGtkCellRenderer: public nodeGtk::NodeGtkObject {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			GtkCellRenderer *cellRenderer;

			/**
			 * Checks to see if a v8::Object is a CellRenderer in disguise
			 *
			 * Parameters:
			 *   obj - The object to check for CellRendererness
			 *
			 * Returns:
			 * True if the object is a cell renderer, false otherwise
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
			 * GtkCellRenderer *cellRenderer = CellRenderer::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkCellRenderer contained in this CellRenderer
			 */
			static inline GtkCellRenderer* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_CELL_RENDERER(ObjectWrap::Unwrap<NodeGtkCellRenderer>(obj)->getCellRenderer());
			}

			virtual inline GtkCellRenderer* getCellRenderer() {
				return cellRenderer;
			}
			virtual inline void setWidget(GtkCellRenderer *cellRenderer) {
				this->cellRenderer = cellRenderer;
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkCellRenderer that holds the reference
			 */
			static NodeGtkCellRenderer* From(GtkCellRenderer *object) {
				NodeGtkCellRenderer *button;
				NODE_GTK_GET_REF(object, button, NodeGtkCellRenderer);
				return button;
			}

	};

} // namespace ngtk

#endif
