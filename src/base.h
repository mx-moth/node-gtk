#ifndef BASE_H_
#define BASE_H_

#include <node_object_wrap.h>
#include "gtk.h"
#include <vector>
#include <ev.h>
#include <node.h>
#include <string.h>

namespace nodeGtk {

	class NodeBase : public node::ObjectWrap {
		public:

			v8::Local<v8::Object> obj;

            /**
             * Makes the external reference to be returned to JavaScript
			 */
			void newJavaScriptInstance(v8::Persistent<v8::FunctionTemplate> constructor) {
				obj = constructor->GetFunction()->NewInstance();
				obj->SetInternalField(0, v8::External::New(this));
			}

			static void SetupConstants(v8::Handle<v8::Object> target);
			static void SetupMethods(v8::Handle<v8::Object> target);
			static void Initialize(v8::Handle<v8::Object> target); 

	};


} // namespace ngtk

#endif
