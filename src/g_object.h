#ifndef G_OBJECT_H_
#define G_OBJECT_H_

#include "base.h"

namespace nodeGtk {

	struct SignalCallback {

		const char *name;
		GCallback callback;

		SignalCallback (const char *name, GCallback callback) {
			this->name = name;
			this->callback = callback;
		}

	};

	class NodeGObject : public NodeBase {
		public:

			static std::vector<SignalCallback> *callbacks;
			GObject *widget;

			/**
			 * Stores a reference to this instance in the widget
			 */
			void storeReference() {
				g_object_set_data(G_OBJECT(this->widget), "NodeGTK-ref", (void *)this);
			}
                

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GObject that holds the reference
			 */
			static NodeGObject* From(GObject *object) {
                NodeGObject *ref = (NodeGObject*)(g_object_get_data(G_OBJECT(object), "NodeGtk-wrapper"));
				assert(ref != NULL);
                return ref;
			}

			static void SetupConstants(v8::Handle<v8::Object> target);
			static void SetupCallbacks(std::vector<SignalCallback> *callbacks);
			static void SetupMethods(v8::Handle<v8::Object> target);
			static void Initialize(v8::Handle<v8::Object> target); 

	};

	void signal_bare(GtkWidget *widget, gpointer callback_ptr);
	gboolean signal_boolean(GtkWidget *widget, gpointer callback_ptr);

} // namespace ngtk

#endif
