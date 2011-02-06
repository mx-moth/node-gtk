#ifndef NGTK_CONTAINER_H_
#define NGTK_CONTAINER_H_

#include "gtk_widget.h"

namespace nodeGtk {
	class NodeGtkContainer : public NodeGtkWidget {

		public:

			// For getting the underlying GtkWidget
			static inline GtkContainer* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_CONTAINER(ObjectWrap::Unwrap<NodeGtkContainer>(obj)->widget);
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkContainer that holds the reference
			 */
			static NodeGtkContainer* From(GtkContainer *object) {
				return (NodeGtkContainer*)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};
}

#endif
