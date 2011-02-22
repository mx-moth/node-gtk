#ifndef NGTK_TREE_MODEL_H_
#define NGTK_TREE_MODEL_H_

#include "g_interface.h"

namespace nodeGtk {

	class NodeGtkTreeModel: public NodeGInterface {

		public:
			virtual ~NodeGtkTreeModel() {}
			GtkTreeModel *model;
			// virtual void OverrideMe() = 0;

			static inline GtkTreeModel* Data(v8::Handle<v8::Object> obj) {
				v8::HandleScope scope;
				return ObjectWrap::Unwrap<NodeGtkTreeModel>(obj)->getModel();
			}

			virtual GtkTreeModel* getModel() {
				return model;
			}
			virtual void setModel(GtkTreeModel *model) {
				this->model = model;
			}

	};

}

#endif
