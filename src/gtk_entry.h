#ifndef NGTK_ENTRY_H_
#define NGTK_ENTRY_H_

#include "gtk_widget.h"

namespace nodeGtk {

	class Entry: public nodeGtk::Widget {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			/**
			 * Constructor. Creates a new Entry, which will wrap a new GtkEntry
			 */
			Entry();

			/**
			 * Checks to see if a v8::Object is a Entry in disguise
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
			 * GtkEntry *entry = Entry::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkEntry contained in this Entry
			 */
			static inline GtkEntry* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_ENTRY(ObjectWrap::Unwrap<Entry>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

	};

} // namespace ngtk

#endif
