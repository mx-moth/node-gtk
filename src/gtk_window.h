#ifndef NGTK_WINDOW_H_
#define NGTK_WINDOW_H_

#include "gtk_bin.h"

#define NGTK_WINDOW_DEFAULT_WIDTH  640
#define NGTK_WINDOW_DEFAULT_HEIGHT 480

namespace nodeGtk {

	class NodeGtkWindow: public nodeGtk::NodeGtkBin {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			/**
			 * Constructor. Creates a new Window, which will wrap a new GtkWindow
			 *
			 * Parameters:
			 *   type - The window type
			 */
			NodeGtkWindow(GtkWindowType type);

			/**
			 * Checks to see if a v8::Object is a Window in disguise
			 *
			 * Parameters:
			 *   obj - The object to check for Windowness
			 *
			 * Returns:
			 * True if the object is a window, false otherwise
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
			 * GtkWindow *window = Window::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkWindow contained in this Window
			 */
			static inline GtkWindow* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				assert(NodeGtkWindow::HasInstance(obj));
				return GTK_WINDOW(ObjectWrap::Unwrap<NodeGtkWindow>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkWindow that holds the reference
			 */
			static NodeGtkWindow* From(GtkWindow *object) {
				return (NodeGtkWindow *)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};

} // namespace ngtk

#endif
