#ifndef G_OBJECT_H_
#define G_OBJECT_H_

#include <node_object_wrap.h> // node::ObjectWrap
#include "gtk.h"
#include <vector>

namespace nodeGtk {

	class GObject : public node::ObjectWrap {
		public:

			GtkWidget *widget;
			v8::Local<v8::Object> obj;

	};

} // namespace ngtk

#endif
