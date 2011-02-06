#ifndef NGTK_ENTRY_H_
#define NGTK_ENTRY_H_

#include "gtk_widget.h"

namespace nodeGtk {

	class NodeGtkEntry: public NodeGtkWidget {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			/**
			 * Constructor. Creates a new NodeGtkEntry, which will wrap a new GtkEntry
			 */
			NodeGtkEntry();

			/**
			 * Checks to see if a v8::Object is a NodeGtkEntry in disguise
			 *
			 * Parameters:
			 *   obj - The object to check for Entryness
			 *
			 * Returns:
			 * True if the object is a entry, false otherwise
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
			 * GtkEntry *entry = NodeGtkEntry::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkEntry contained in this NodeGtkEntry
			 */
			static inline GtkEntry* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_ENTRY(ObjectWrap::Unwrap<NodeGtkEntry>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkEntry that holds the reference
			 */
			static NodeGtkEntry* From(GtkEntry *object) {
				return (NodeGtkEntry*)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};

} // namespace ngtk

#endif
