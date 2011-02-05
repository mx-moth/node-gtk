NodeGTK
========

Node.js bindings for GTK 2.6.

Using NodeGTK, you can create fully functional GUI applications in Node.js.

Awesome advantages over C++ etc.
--------------------------------

Well, you are using JavaScript, which is pretty sweet. It allows you to do things like

    var button = gtk.button_new("Click me!")
    gtk.signal_connect(button, 'click', function() {
		console.log("Clicked the button");
	});

	var window = gtk.window_new(gtk.WINDOW_TYPE);
	gtk.window_set_title(window, "Welcome to NodeGTK");
	gtk.container_add(window, button);
	gtk.widget_show_all(window);

Anonymous function signal callbacks. Life has never been sweeter.

Todo
----

Quite a bit. This is an initial work in progress release. Many things work, but many things are yet to be implemented.

* Implement all GTK classes
* Implement all GTK signals
* Create an object oriented set up:

		var button = new gtk.Button({label: "Click me!"});
		button.signalConnect('click', function() {
		   console.log("Clicked the button");
		});

		var window = new gtk.Window({type: gtk.WINDOW_TYPE});
		window.set('title', 'Welcome to NodeGTK');
		window.add(button);
		window.showAll();

See the [TODO][] list for more details

[TODO]: https://github.com/maelstrom/node-gtk/blob/master/TODO.md
