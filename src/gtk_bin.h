#ifndef NGTK_BIN_H_
#define NGTK_BIN_H_

#include "gtk_container.h"

namespace nodeGtk {
	class NodeGtkBin : public NodeGtkContainer {

		public: 

			// For getting the underlying GtkWidget
			static inline GtkBin* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_BIN(ObjectWrap::Unwrap<NodeGtkBin>(obj)->widget);
			}

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GObject that holds the reference
			 */
			static NodeGtkBin* From(GtkBin *object) {
				return (NodeGtkBin *)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};
}

#endif
