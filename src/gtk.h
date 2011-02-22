#ifndef GTK_H_
#define GTK_H_

#include <v8.h>
#include <glib.h>
#include <gtk/gtk.h>

namespace ngtk {

#define GTK_DEFINE_CONSTANT(target, name, constant)                       \
  (target)->Set(v8::String::NewSymbol(name),                              \
                v8::Integer::New(constant),                               \
                static_cast<v8::PropertyAttribute>(v8::ReadOnly|v8::DontDelete))


#define GTK_NOARG_FUNCTION(target, type, function)                        \
	Handle<Value> function (const Arguments &args) {                      \
		HandleScope scope;                                                \
		type *widget = target::Data(args[0]->ToObject());                 \
		function(widget);                                                 \
		return Undefined();                                               \
	}

#define GTK_ATTACH_FUNCTION(target, name, function)                       \
	target->Set(                                                          \
			v8::String::NewSymbol(name),                                  \
			v8::FunctionTemplate::New(function)->GetFunction())

#define NODE_GTK_NEW_CLASS(target, name)                                  \
	do {                                                                  \
		/* Create a new JavaScript class */                               \
		Handle<FunctionTemplate> fnTemplate = FunctionTemplate::New();    \
		fnTemplate->SetClassName(String::New(name));                      \
		target = Persistent<FunctionTemplate>::New(fnTemplate);           \
                                                                          \
		/* Set up the class to point to a C++ class */                    \
		Handle<ObjectTemplate> instance = fnTemplate->InstanceTemplate(); \
		instance->SetInternalFieldCount(1);                      \
	} while (0)

#define NODE_GTK_SET_REF(object, Class) \
	g_object_set_data(G_OBJECT(object->getWidget()), "NodeGTK-"#Class, object);

#define NODE_GTK_SET_REF_WITH_GETTER(object, Class, getter) \
	g_object_set_data(G_OBJECT(object->getter()), "NodeGTK-"#Class, object);

#define NODE_GTK_GET_REF(object, ptr, Class)                              \
	printf("Getting ref to NodeGTK-"#Class"\n");                          \
	ptr = (Class *)(g_object_get_data(G_OBJECT(object), "NodeGTK-"#Class)); \
	printf("Got ref\n");


} // namespace ngtk

#endif
