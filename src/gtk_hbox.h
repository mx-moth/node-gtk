#ifndef NGTK_HBOX_H_
#define NGTK_HBOX_H_

#include "gtk_box.h"

namespace nodeGtk {

	class NodeGtkHBox: public NodeGtkBox {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			/**
			 * Constructor. Creates a new HBox, which will wrap a new GtkHBox
			 */
			NodeGtkHBox(gboolean homogeneous, gint spacing);

			/**
			 * Checks to see if a v8::Object is a HBox in disguise
			 *
			 * Parameters:
			 *   obj - The object to check for HBoxness
			 *
			 * Returns:
			 * True if the object is a hbox, false otherwise
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
			 * GtkHBox *hbox = HBox::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkHBox contained in this HBox
			 */
			static inline GtkHBox* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_HBOX(ObjectWrap::Unwrap<NodeGtkHBox>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkHBox that holds the reference
			 */
			static NodeGtkHBox* From(GtkHBox *object) {
				return (NodeGtkHBox*)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};

} // namespace ngtk

#endif
