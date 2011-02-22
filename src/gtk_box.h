#ifndef NGTK_BOX_H_
#define NGTK_BOX_H_

#include "gtk_container.h"

namespace nodeGtk {
	class NodeGtkBox : public NodeGtkContainer {

		public: 

			// For getting the underlying GtkBox
			static inline GtkBox* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return GTK_BOX(ObjectWrap::Unwrap<NodeGtkBox>(obj)->getWidget());
			}

			static void SetupMethods (v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize (v8::Handle<v8::Object> target);

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkBox that holds the reference
			 */
			static GtkBox* From(GtkBox *object) {
				return (GtkBox*)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};
}

#endif
