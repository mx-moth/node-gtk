#ifndef GTK_OBJECT_H_
#define GTK_OBJECT_H_

#include "g_object.h"


namespace nodeGtk {

	class NodeGtkObject : public NodeGObject {
		public:

			/**
			 * Retrieves a reference to this instance from the widget
			 *
			 * Parameters:
			 *   object - The GtkObject that holds the reference
			 */
			static NodeGtkObject* From(GObject *object) {
				return (NodeGtkObject *)(g_object_get_data(object, "NodeGTK-ref"));
			}
	};

} // namespace ngtk

#endif
