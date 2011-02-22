#ifndef NGTK_G_INTERFACE_H_
#define NGTK_G_INTERFACE_H_

#include <node_object_wrap.h>
#include "gtk.h"
#include <vector>
#include <ev.h>
#include <node.h>
#include <string.h>

namespace nodeGtk {

	class NodeGInterface: public node::ObjectWrap {

		public:
			virtual ~NodeGInterface() {};
			// virtual void OverrideMe() = 0;


	};

}

#endif
