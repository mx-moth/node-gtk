#ifndef NGTK_WIDGET_H_
#define NGTK_WIDGET_H_

#include "gtk_object.h"

namespace nodeGtk {

	struct SignalCallback {

		const char *name;
		GCallback callback;

		SignalCallback (const char *name, GCallback callback) {
			this->name = name;
			this->callback = callback;
		}

	};

	class Widget: public GtkObject {

		public:

			static std::vector<SignalCallback> *callbacks;

			// For getting the underlying GtkWidget
			static inline GtkWidget* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return ObjectWrap::Unwrap<Widget>(obj)->widget;
			}

			static void SetupMethods(v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize(v8::Handle<v8::Object> target);

			static void onDestroy (GtkWidget *gktWidget, Widget *widget);

			void addRef();

	};

	void signal_bare(GtkWidget *widget, gpointer callback_ptr);
	gboolean signal_boolean(GtkWidget *widget, gpointer callback_ptr);


} // namespace ngtk

#endif
