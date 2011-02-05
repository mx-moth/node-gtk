#ifndef NGTK_CONTAINER_H_
#define NGTK_CONTAINER_H_

#include "gtk_widget.h"

namespace nodeGtk {
	class Container : public Widget {

		public:

			// For getting the underlying GtkWidget
			static inline GtkContainer* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_CONTAINER(ObjectWrap::Unwrap<Container>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

	};
}

#endif
