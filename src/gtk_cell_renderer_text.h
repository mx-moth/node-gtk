#ifndef NGTK_CELL_RENDERER_TEXT_H_
#define NGTK_CELL_RENDERER_TEXT_H_

#include "gtk_cell_renderer.h"

namespace nodeGtk {

	class NodeGtkCellRendererText: public NodeGtkCellRenderer {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			NodeGtkCellRendererText(GtkCellRenderer *cellRendererText);

			/**
			 * Checks to see if a v8::Object is a CellRendererText in disguise
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
			 * GtkCellRendererText *cellRenderer = CellRendererText::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkCellRendererText contained in this CellRendererText
			 */
			static inline GtkCellRendererText* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				assert(NodeGtkCellRendererText::HasInstance(obj));
				return GTK_CELL_RENDERER_TEXT(ObjectWrap::Unwrap<NodeGtkCellRendererText>(obj)->getCellRenderer());
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupConstants (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkCellRendererText that holds the reference
			 */
			static NodeGtkCellRendererText* From(GtkCellRendererText *object) {
				NodeGtkCellRendererText *button;
				NODE_GTK_GET_REF(object, button, NodeGtkCellRendererText);
				return button;
			}

	};

} // namespace ngtk

#endif
