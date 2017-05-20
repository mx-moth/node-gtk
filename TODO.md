TODO
====

This is only an alpha release, and as such there is still plenty of things to do.

Classes to implement
--------------------

Instead of listing all of the classes left to implement, the currently implemented classes are:

* GtkButton
* GtkWindow
* GtkLabel
* GtkInput
* GtkBox
* GtkBin
* GtkContainer
* GtkWidget
* GtkObject
* GObject

These classes are not yet fully implemented, but there is enough functionality to create a basic 'log in' style window with inputs. See [login.coffee][] for an example.

[login.coffee]: https://github.com/maelstrom/node-gtk/blog/master/examples/login.coffee

Signals to implement
--------------------

Because each different signal potentially has a unique callback signature, a new C++ callback needs to be created for each unique function signature required. This is not a difficult process as such, just a really tedious one. As such, many of the more obscure signals are not yet implemented. They are being implemented as someone requires them. If you require a signal to be connected, but do not have the requisite C++ skills to accomplish this, please create an issue and someone will do it at when they get a chance.

Object oriented approach
------------------------

Unsurprisingly, the GTK library functions are designed to work in C++, and not so much in JavaScript. There are much better ways of implementing all of the classes in JavaScript. The final goal of this project is to create wrapper classes for the GTK classes and their associated functions. This will allow code such as the following:

```js
var button = new gtk.Button({label: "Click me!"});
button.signalConnect('click', function() {
   console.log("Clicked the button");
});

var window = new gtk.Window({type: gtk.WINDOW_TYPE});
window.set('title', 'Welcome to NodeGTK');
window.add(button);
window.showAll();
```
