#ifndef GTK_H_
#define GTK_H_

#include <v8.h>
#include <glib.h>
#include <gtk/gtk.h>

namespace ngtk {

#define GTK_DEFINE_CONSTANT(target, name, constant)                      \
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

} // namespace ngtk

#endif
