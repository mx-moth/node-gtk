#ifndef NGTK_VBOX_H_
#define NGTK_VBOX_H_

#include "gtk_box.h"

namespace nodeGtk {

	class NodeGtkVBox: public NodeGtkBox {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			/**
			 * Constructor. Creates a new VBox, which will wrap a new GtkVBox
			 */
			NodeGtkVBox(gboolean homogeneous, gint spacing);
			NodeGtkVBox(GtkVBox *vbox);

			/**
			 * Checks to see if a v8::Object is a VBox in disguise
			 *
			 * Parameters:
			 *   obj - The object to check for VBoxness
			 *
			 * Returns:
			 * True if the object is a vbox, false otherwise
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
			 * GtkVBox *vbox = VBox::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkVBox contained in this VBox
			 */
			static inline GtkVBox* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_VBOX(ObjectWrap::Unwrap<NodeGtkVBox>(obj)->getWidget());
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkVBox that holds the reference
			 */
			static NodeGtkVBox* From(GtkVBox *object) {
				NodeGtkVBox *button;
				NODE_GTK_GET_REF(object, button, NodeGtkVBox);
				return button;
			}

	};

} // namespace ngtk

#endif
