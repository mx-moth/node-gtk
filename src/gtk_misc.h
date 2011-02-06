#ifndef NGTK_MISC_H_
#define NGTK_MISC_H_

#include "gtk_widget.h"

namespace nodeGtk {
	class NodeGtkMisc : public NodeGtkWidget {

		public: 

			// For getting the underlying GtkWidget
			static inline GtkMisc* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_MISC(ObjectWrap::Unwrap<NodeGtkMisc>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkMisc that holds the reference
			 */
			static NodeGtkMisc* From(GtkMisc *object) {
				return (NodeGtkMisc*)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};
}

#endif
