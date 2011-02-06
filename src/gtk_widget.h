#ifndef NGTK_WIDGET_H_
#define NGTK_WIDGET_H_

#include "gtk_object.h"

namespace nodeGtk {

	class NodeGtkWidget: public NodeGtkObject {

		public:

			GtkWidget *widget;

			// For getting the underlying GtkWidget
			static inline GtkWidget* Data (v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return ObjectWrap::Unwrap<NodeGtkWidget>(obj)->widget;
			}

			static void SetupMethods(v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void Initialize(v8::Handle<v8::Object> target);

			static void onDestroy (GtkWidget *gktWidget, NodeGtkWidget *widget);

			void addRef();

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkWidget that holds the reference
			 */
			static NodeGtkWidget* From(GObject *object) {
				return (NodeGtkWidget *)(g_object_get_data(G_OBJECT(object), "NodeGTK-ref"));
			}

	};


} // namespace ngtk

#endif
