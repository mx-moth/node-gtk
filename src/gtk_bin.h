#ifndef NGTK_BIN_H_
#define NGTK_BIN_H_

#include "gtk_container.h"

namespace nodeGtk {
	class Bin : public Container {

		public: 

			// For getting the underlying GtkWidget
			static inline GtkBin* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_BIN(ObjectWrap::Unwrap<Bin>(obj)->widget);
			}

	};
}

#endif
