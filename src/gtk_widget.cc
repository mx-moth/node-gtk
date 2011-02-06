#include "gtk_widget.h"
#include <node.h>
#include <string.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * Adds a reference to this widget, and sets it up for destruction later.
	 */
	void NodeGtkWidget::addRef() {
		// Listen for desruction so we can call ev_unref later
		g_signal_connect(G_OBJECT(widget), "destroy", G_CALLBACK(NodeGtkWidget::onDestroy), (gpointer) this);

		// Bump up the ev ref count
		ev_ref(EV_DEFAULT_UC_);
	}

	/**
	 * Unrefs the widget, destroying the JavaScript object
	 */
	void NodeGtkWidget::onDestroy (GtkWidget *gtkWidget, NodeGtkWidget *widget) {
		HandleScope scope;
		ev_unref(EV_DEFAULT_UC_);
	}

	// Add signal handler.
	Handle<Value> signal_connect (const Arguments &args) {
		HandleScope scope;
		guint id = 0;

		if (args[1]->IsString() && args[2]->IsFunction()) {
			GtkWidget *widget = NodeGtkWidget::Data(args[0]->ToObject());
			GObject *object = G_OBJECT(widget);

			Persistent<Function> *callback = new Persistent<Function>();
			*callback = Persistent<Function>::New(Handle<Function>::Cast(args[2]));
			gpointer callback_ptr = (gpointer) callback;
			String::AsciiValue signalName(args[1]->ToString());

			for (std::vector<SignalCallback>::iterator it = NodeGtkWidget::callbacks->begin(); it != NodeGtkWidget::callbacks->end(); ++it) {
				if (strcmp(it->name, *signalName) == 0) {
					id = g_signal_connect(object, it->name, it->callback, callback_ptr);
					break;
				}
			}

			return scope.Close(v8::Number::New(id));
		}

		return scope.Close(v8::Boolean::New(false));
	}

	Handle<Value> signal_handler_disconnect (const Arguments &args) {
		HandleScope scope;
		if (args[1]->IsNumber()) {

			GtkWidget *instance = NodeGtkWidget::Data(args[0]->ToObject());
			int id = (int)(args[1]->NumberValue());

			if (g_signal_handler_is_connected (instance, id)) {
				g_signal_handler_disconnect (instance, id);
			}
		}

		return Undefined();
	}

	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_destroy)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_unparent)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_is_focus)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_show)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_show_now)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_show_all)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_hide)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_hide_all)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_map)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_unmap)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_realize)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_unrealize)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_queue_draw)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_queue_resize)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_queue_resize_no_redraw)

	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_grab_focus)
	GTK_NOARG_FUNCTION(NodeGtkWidget, GtkWidget, gtk_widget_grab_default)

	Handle<Value> gtk_widget_set_can_default (const Arguments &args) {
		HandleScope scope;
		
		GtkWidget *widget = NodeGtkWidget::Data(args[0]->ToObject());
		bool canDefault = args[1]->ToBoolean()->Value();
		
		gtk_widget_set_can_default(widget, canDefault);

		return Undefined();
	}

	/**
	 * Focus signal. Used as the intermediate callback for focus signals.
	 * Register a focus listener using @widget.on('focus', callback);@
	 *
	 * Parameter:
	 *   widget - The widget that triggered the signal
	 *   dir - Tab forward, tab backwards, etc. See <GtkDirectionType> enum
	 *   callback_ptr - The user data, which is the JavaScript function to call
	 */
	gboolean signal_focus(GtkWidget *widget, GtkDirectionType dir, gpointer callback_ptr) {
		Persistent<Function> *callback = reinterpret_cast<Persistent<Function>*>(callback_ptr);
		TryCatch try_catch;

		Local<Value> argv[1] = { v8::Number::New(dir) };

		Local<Value> ret = (*callback)->Call(Context::GetCurrent()->Global(), 1, argv);

		if (try_catch.HasCaught()) {
			FatalException(try_catch);
		}

		if (ret.IsEmpty()) {
			printf("Bad return");
		}

		return (*ret)->IsTrue();
	}


	/**
	 * Attach all widget methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkWidget::SetupMethods (Handle<Object> target) {
		HandleScope scope;
		GTK_ATTACH_FUNCTION(target, "widget_destroy", gtk_widget_destroy);
		GTK_ATTACH_FUNCTION(target, "widget_destroy", gtk_widget_destroy);
		GTK_ATTACH_FUNCTION(target, "widget_unparent", gtk_widget_unparent);
		GTK_ATTACH_FUNCTION(target, "widget_is_focus", gtk_widget_is_focus);
		GTK_ATTACH_FUNCTION(target, "widget_show", gtk_widget_show);
		GTK_ATTACH_FUNCTION(target, "widget_show_now", gtk_widget_show_now);
		GTK_ATTACH_FUNCTION(target, "widget_show_all", gtk_widget_show_all);
		GTK_ATTACH_FUNCTION(target, "widget_hide", gtk_widget_hide);
		GTK_ATTACH_FUNCTION(target, "widget_hide_all", gtk_widget_hide_all);
		GTK_ATTACH_FUNCTION(target, "widget_map", gtk_widget_map);
		GTK_ATTACH_FUNCTION(target, "widget_unmap", gtk_widget_unmap);
		GTK_ATTACH_FUNCTION(target, "widget_realize", gtk_widget_realize);
		GTK_ATTACH_FUNCTION(target, "widget_unrealize", gtk_widget_unrealize);
		GTK_ATTACH_FUNCTION(target, "widget_queue_draw", gtk_widget_queue_draw);
		GTK_ATTACH_FUNCTION(target, "widget_queue_resize", gtk_widget_queue_resize);
		GTK_ATTACH_FUNCTION(target, "widget_queue_resize_no_redraw", gtk_widget_queue_resize_no_redraw);

		GTK_ATTACH_FUNCTION(target, "widget_grab_focus", gtk_widget_grab_focus);
		GTK_ATTACH_FUNCTION(target, "widget_grab_default", gtk_widget_grab_default);
		GTK_ATTACH_FUNCTION(target, "widget_set_can_default", gtk_widget_set_can_default);

		GTK_ATTACH_FUNCTION(target, "signal_connect", signal_connect);
		GTK_ATTACH_FUNCTION(target, "signal_handler_disconnect", signal_handler_disconnect);
	}

	void NodeGtkWidget::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		(*callbacks).push_back(SignalCallback("focus", G_CALLBACK(signal_focus)));

		(*callbacks).push_back(SignalCallback("grab-focus", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("hide", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("map", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("show", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("realize", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("unmap", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("unrealize", G_CALLBACK(signal_bare)));

		(*callbacks).push_back(SignalCallback("popup-menu", G_CALLBACK(signal_boolean)));
		(*callbacks).push_back(SignalCallback("destroy", G_CALLBACK(signal_boolean)));
	}

	/**
	 * Sets up the environment with all things widgety
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkWidget::Initialize (Handle<Object> target) {
		HandleScope scope;
		NodeGtkWidget::SetupMethods(target);

		NodeGtkWidget::SetupCallbacks(callbacks);
	}


} // namespace ngtk
