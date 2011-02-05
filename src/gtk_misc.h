#ifndef NGTK_MISC_H_
#define NGTK_MISC_H_

#include "gtk_widget.h"

namespace nodeGtk {
	class Misc : public Widget {

		public: 

			// For getting the underlying GtkWidget
			static inline GtkMisc* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_MISC(ObjectWrap::Unwrap<Misc>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

	};
}

#endif
