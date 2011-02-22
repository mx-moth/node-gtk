gtk = require '../build/default/gtk'

columns =
   title: 0
   author: 1
   checked: 2

populateTreeModel = (store) ->
	#Acquire a top-level iterator
	iter1 = gtk.tree_store_append store

	gtk.tree_store_set store, iter1,
		columns.title, "The Art of Computer Programming",
		columns.author, "Donald E. Knuth",
		columns.checked, false

	# Acquire a child iterator
	iter2 = gtk.tree_store_append store, iter1
	gtk.tree_store_set store, iter2, columns.title, "Volume 1: Fundamental Algorithms"

	iter2 = gtk.tree_store_append store, iter1
	gtk.tree_store_set store, iter2, columns.title, "Volume 2: Seminumerical Algorithms"

	iter1 = gtk.tree_store_append store
	gtk.tree_store_set store, iter1,
		columns.title, "The Principle of Reason",
		columns.author, "Martin Heidegger",
		columns.checked, true
	
	return


makeTreeView = ->

	# Create a model.  We are using the store model for now, though we
	# could use any other GtkTreeModel
	store = gtk.tree_store_new gtk.G_TYPE_STRING, gtk.G_TYPE_STRING, gtk.G_TYPE_BOOLEAN

	# custom function to fill the model with data 
	populateTreeModel store

	# Create a view 
	tree = gtk.tree_view_new_with_model store

	# The view now holds a reference.  We can get rid of our own
	# reference 
	delete store

	# Create a cell render 
	renderer = gtk.cell_renderer_text_new()

	# TODO: arbitrarily make it red for demonstration purposes 
	# gtk.g_object_set renderer, "foreground", "red"

	# Create a column, associating the "text" attribute of the
	# cell_renderer to the first column of the model 
	column = gtk.tree_view_column_new_with_attributes "Author", renderer, "text", columns.author

	# Add the column to the view. 
	gtk.tree_view_append_column tree, column

	# Second column.. title of the book. 
	renderer = gtk.cell_renderer_text_new()
	column = gtk.tree_view_column_new_with_attributes "Title", renderer, "text", columns.title
	gtk.tree_view_append_column tree, column

	# Last column.. whether a book is checked out. 
	renderer = gtk.cell_renderer_toggle_new()
	column = gtk.tree_view_column_new_with_attributes "Checked out", renderer, "active", columns.checked
	gtk.tree_view_append_column tree, column

	return tree


showWindow = ->
	
	tree = makeTreeView()

	window = gtk.window_new 0
	gtk.window_set_title window, "Tree View"
	gtk.signal_connect window, 'destroy', gtk.main_quit

	vbox = gtk.vbox_new false, 1
	gtk.container_add vbox, tree
	gtk.container_add vbox, do ->
		button = do gtk.button_new
		gtk.button_set_label button, "Button"
		return button
	gtk.container_add window, vbox

	console.log tree.toString()
	gtk.widget_show_all window

	gtk.main()

process.nextTick ->
	gtk.init()
	showWindow()
