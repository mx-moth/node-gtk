#ifndef NGTK_LABEL_H_
#define NGTK_LABEL_H_

#include "gtk_misc.h"

namespace nodeGtk {

	class NodeGtkLabel: public NodeGtkMisc {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			/**
			 * Constructor. Creates a new Label, which will wrap a new GtkLabel
			 */
			NodeGtkLabel(gchar *text);

			/**
			 * Checks to see if a v8::Object is a Label in disguise
			 *
			 * Parameters:
			 *   obj - The object to check for Labelness
			 *
			 * Returns:
			 * True if the object is a label, false otherwise
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
			 * GtkLabel *label = Label::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkLabel contained in this Label
			 */
			static inline GtkLabel* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_LABEL(ObjectWrap::Unwrap<NodeGtkLabel>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkLabel that holds the reference
			 */
			static NodeGtkLabel* From(GtkLabel *object) {
				return (NodeGtkLabel*)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};

} // namespace ngtk

#endif
