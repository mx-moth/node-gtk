#ifndef NGTK_BUTTON_H_
#define NGTK_BUTTON_H_

#include "gtk_bin.h"

namespace nodeGtk {

	class Button: public nodeGtk::Bin {

		public:

			static v8::Persistent<v8::FunctionTemplate> constructor_template;

			/**
			 * Constructor. Creates a new Button, which will wrap a new GtkButton
			 */
			Button();

			/**
			 * Checks to see if a v8::Object is a Button in disguise
			 *
			 * Parameters:
			 *   obj - The object to check for Buttonness
			 *
			 * Returns:
			 * True if the object is a button, false otherwise
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
			 * GtkButton *button = Button::Data(args[n]->ToObject());
			 * (end)
			 *
			 * Returns:
			 * The pointer to the GtkButton contained in this Button
			 */
			static inline GtkButton* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_BUTTON(ObjectWrap::Unwrap<Button>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

	};

} // namespace ngtk

#endif
