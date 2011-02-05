gtk = require '../build/default/gtk'

showLogin = ->

	usernameHbox = gtk.hbox_new true, 5
	usernameLabel = gtk.label_new "Username"
	gtk.misc_set_alignment usernameLabel, 1.0, 0.5
	usernameEntry = gtk.entry_new()
	gtk.container_add usernameHbox, control for control in [usernameLabel, usernameEntry]

	passwordHbox = gtk.hbox_new true, 5
	passwordLabel = gtk.label_new "Password"
	gtk.misc_set_alignment passwordLabel, 1.0, 0.5
	passwordEntry = gtk.entry_new()
	gtk.entry_set_visibility passwordEntry, false
	gtk.container_add passwordHbox, control for control in [passwordLabel, passwordEntry]

	submit = gtk.button_new()
	gtk.button_set_label submit, "Submit"
	gtk.signal_connect submit, "clicked", ->
		console.log "Logging in with", (gtk.entry_get_text usernameEntry), ":", (gtk.entry_get_text passwordEntry)
		gtk.widget_destroy window
		setTimeout showLogin, 1000

	vbox = gtk.vbox_new false, 2
	gtk.container_add vbox, control for control in [usernameHbox, passwordHbox, submit]

	window = gtk.window_new 0
	gtk.window_set_title window, "Enter your log in details"
	gtk.container_add window, vbox

	gtk.signal_connect window, "destroy", gtk.main_quit

	gtk.widget_set_can_default submit, true
	gtk.widget_grab_default submit
	gtk.widget_show_all window
	gtk.main()

process.nextTick ->
	gtk.init()
	showLogin()
