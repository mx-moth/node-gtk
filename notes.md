Every class of NodeGtk widgets should have:

    /**
     * Create a new Foo, wrap it, and return its object
     */
    Handle<Object> gtk_foo_new(const Arguments &args) {
        GtkFoo widget = gtk_foo_new(arg1, arg2, ...);
        NodeGtkFoo node = NodeGtkFoo::From(widget);
        return node->jsObject;
    }

    /**
     * Get the NodeGtkFoo from a GtkFoo. If there is not one,
     * create a new one. This is the only way a new NodeGtkFoo is constructed
     */
    NodeGtkFoo* NodeGtkFoo::From(GtkFoo *foo) {
        NodeGtkFoo *ref = (NodeGtkFoo*)(g_object_get_data(G_OBJECT(foo), "NodeGtk-wrapper"));
        if (ref == NULL) {
            ref = new NodeGtkFoo(foo);
        }
        return ref;
    }

    /**
     * Construct a new NodeGtkFoo by wrapping a GtkFoo
     */
    NodeGtkFoo::NodeGtkFoo (GtkFoo *foo) {
        this->widget = GTK_WIDGET(foo);
        this->storeReference()
        this->makeExternal(NodeGtkFoo::constructor);
        this->addRef(); // If GtkWidget
    }

In this way, wrapping any Gtk object in a NodeGtk wrapper object will be simple, and does not have to be form the constructor.  `gtk_` functions will only ever be called from the intermediate functions, leaving the wrapper classes clean of any messy implementation details - and also very easy to write.

Problems I can see arising
==========================

If there was a function such as `gtk_container_get_child` which returned a `GtkWidget`, and this widget had not been wrapped with a NodeGtk wrapper, calling `NodeGtkWidget::From` upon this would create a new `NodeGtkWidget` isntance. Unfortunately, this widget probably isnt a widget, but would be something like a `NodeGtkEntry` or `NodeGtkLabel`. I know of no easy way of fixing this, besides having a massive series of `if` statements, working top down through the heirachy of classes checking for a match.
