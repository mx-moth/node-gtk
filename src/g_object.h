#ifndef G_OBJECT_H_
#define G_OBJECT_H_

#include <node_object_wrap.h> // node::ObjectWrap
#include "gtk.h"
#include <vector>
#include <ev.h>
#include <node.h>
#include <string.h>

namespace nodeGtk {

	struct SignalCallback {

		const char *name;
		GCallback callback;

		SignalCallback (const char *name, GCallback callback) {
			this->name = name;
			this->callback = callback;
		}

	};

	class NodeGObject : public node::ObjectWrap {
		public:

			static std::vector<SignalCallback> *callbacks;
			GObject *widget;
			v8::Local<v8::Object> obj;

			/**
			 * Stores a reference to this instance in the widget
			 */
			void storeSelfInWidget() {
				g_object_set_data(G_OBJECT(this->widget), "NodeGTK-ref", (void *)this);
			}

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GObject that holds the reference
			 */
			static NodeGObject* From(GObject *object) {
				return (NodeGObject *)(g_object_get_data(object, "NodeGTK-ref"));
			}

	};

	void signal_bare(GtkWidget *widget, gpointer callback_ptr);
	gboolean signal_boolean(GtkWidget *widget, gpointer callback_ptr);

} // namespace ngtk

#endif
