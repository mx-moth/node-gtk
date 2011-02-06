#include "gtk_entry.h"

#include <ev.h>

namespace nodeGtk {

	using namespace v8;
	using namespace node;

	/**
	 * The class constructor for Entrys
	 */
	Persistent<FunctionTemplate> NodeGtkEntry::constructor_template;

	/**
	 * Creates a new NodeGtkEntry
	 *
	 * Parameters:
	 *   type - One of the GtkEntryTypes
	 */
	NodeGtkEntry::NodeGtkEntry () {
		widget = gtk_entry_new();
		addRef();

		obj = NodeGtkEntry::constructor_template->GetFunction()->NewInstance();
		obj->SetInternalField(0, External::New(this));
	}

	/**
	 * Creates a new NodeGtkEntry and attaches it to a JavaScript object
	 *
	 * Parameters:
	 *   type - One of the GtkEntryTypes
	 *
	 * Returns:
	 * A new instance of the NodeGtkEntry class
	 */
	Handle<Value> gtk_entry_new (const Arguments &args) {
		HandleScope scope;

		NodeGtkEntry *entry = new NodeGtkEntry();

		return entry->obj;
	}

	/**
	 * Sets the text of an entry
	 *
	 * Parameters:
	 *   entry - The NodeGtkEntry to set the text of
	 *   text - The text to put in the entry
	 */
	Handle<Value> gtk_entry_set_text(const Arguments &args) {
		HandleScope scope;

		GtkEntry *entry = NodeGtkEntry::Data(args[0]->ToObject());
		String::AsciiValue text(args[1]->ToString());

		gtk_entry_set_text(entry, *text);

		return Undefined();
	}

	/**
	 * Gets the text of an entry
	 *
	 * Parameters:
	 *   entry - The NodeGtkEntry to get the text from
	 *
	 * Returns:
	 * The text from the NodeGtkEntry
	 */
	Handle<Value> gtk_entry_get_text(const Arguments &args) {
		HandleScope scope;

		GtkEntry *entry = NodeGtkEntry::Data(args[0]->ToObject());

		return scope.Close(String::New(gtk_entry_get_text(entry)));
	}

	/**
	 * Gets the lenght of the text of an entry
	 *
	 * Parameters:
	 *   entry - The NodeGtkEntry to get the text from
	 *
	 * Returns:
	 * The length of the text from the NodeGtkEntry
	 */
	Handle<Value> gtk_entry_get_text_length(const Arguments &args) {
		HandleScope scope;

		GtkEntry *entry = NodeGtkEntry::Data(args[0]->ToObject());

		return scope.Close(Number::New(gtk_entry_get_text_length(entry)));
	}

	/**
	 * Sets the visibility of the entry text. If set invisible, the text is
	 * replaced with the 'inivisible char'. In other words, this makes an
	 * entry field in to a password field.
	 *
	 * Parameters:
	 *   entry - The NodeGtkEntry to work with
	 *   visible - The visibility of the text
	 */
	Handle<Value> gtk_entry_set_visibility(const Arguments &args) {
		HandleScope scope;

		GtkEntry *entry = NodeGtkEntry::Data(args[0]->ToObject());
		bool visible = args[1]->ToBoolean()->Value();

		gtk_entry_set_visibility(entry, visible);
		return Undefined();
	}

	/**
	 * Attach all entry methods to the target
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkEntry::SetupMethods (Handle<Object> target) {
		HandleScope scope;

		target->Set(v8::String::NewSymbol("entry_new"), v8::FunctionTemplate::New(gtk_entry_new)->GetFunction());
		target->Set(v8::String::NewSymbol("entry_set_text"), v8::FunctionTemplate::New(gtk_entry_set_text)->GetFunction());
		target->Set(v8::String::NewSymbol("entry_get_text"), v8::FunctionTemplate::New(gtk_entry_get_text)->GetFunction());
		target->Set(v8::String::NewSymbol("entry_get_text_length"), v8::FunctionTemplate::New(gtk_entry_get_text_length)->GetFunction());
		target->Set(v8::String::NewSymbol("entry_set_visibility"), v8::FunctionTemplate::New(gtk_entry_set_visibility)->GetFunction());
	}

	void NodeGtkEntry::SetupCallbacks(std::vector<SignalCallback> *callbacks) {
		NodeGtkWidget::SetupCallbacks(callbacks);
		//TODO This should be part of the Editable class, but I've not made it yet
		(*callbacks).push_back(SignalCallback("changed", G_CALLBACK(signal_bare)));

		(*callbacks).push_back(SignalCallback("activate", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("backspace", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("copy-clipboard", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("cut-clipboard", G_CALLBACK(signal_bare)));
		(*callbacks).push_back(SignalCallback("toggle-overwrite", G_CALLBACK(signal_bare)));

		/*
		//TODO Unimplemented signals
		(*callbacks).push_back(SignalCallback("delete-from-cursor", G_CALLBACK(???)));
		(*callbacks).push_back(SignalCallback("icon-press", G_CALLBACK(???)));
		(*callbacks).push_back(SignalCallback("icon-release", G_CALLBACK(???)));
		(*callbacks).push_back(SignalCallback("insert-at-cursor", G_CALLBACK(???)));
		(*callbacks).push_back(SignalCallback("move-cursor", G_CALLBACK(???)));
		(*callbacks).push_back(SignalCallback("paste-clipboard", G_CALLBACK(???)));
		(*callbacks).push_back(SignalCallback("preedit-changed", G_CALLBACK(???)));
		*/
	}

	/**
	 * Sets up the environment with all things entryish
	 *
	 * Parameters:
	 *   target: The object to attach methods to
	 */
	void NodeGtkEntry::Initialize (Handle<Object> target) {
		HandleScope scope;

		// Create a new JavaScript class
		Handle<FunctionTemplate> entryTemplate = FunctionTemplate::New();
		entryTemplate->SetClassName(String::New("Entry"));
		constructor_template = Persistent<FunctionTemplate>::New(entryTemplate);

		// Set up the class to point to a C++ class
		Handle<ObjectTemplate> entryInstance = entryTemplate->InstanceTemplate();
		entryInstance->SetInternalFieldCount(1);

		// Attach methods to the target
		NodeGtkEntry::SetupMethods(target);

		NodeGtkEntry::SetupCallbacks(callbacks);
	}
}
