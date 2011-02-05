#ifndef NGTK_BOX_H_
#define NGTK_BOX_H_

#include "gtk_container.h"

namespace nodeGtk {
	class Box : public Container {

		public: 

			// For getting the underlying GtkWidget
			static inline GtkBox* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_BOX(ObjectWrap::Unwrap<Box>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

	};
}

#endif
