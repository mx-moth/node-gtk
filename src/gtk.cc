#include "gtk.h"

#include <ev.h>
#include <stdlib.h> // malloc, free

#include "g_object.h"
#include "gtk_object.h"
#include "gtk_widget.h"
#include "gtk_bin.h"
#include "gtk_container.h"
#include "gtk_window.h"
#include "gtk_box.h"
#include "gtk_hbox.h"
#include "gtk_vbox.h"
#include "gtk_button.h"
#include "gtk_entry.h"
#include "gtk_misc.h"
#include "gtk_label.h"
#include "gtk_tree_store.h"

namespace nodeGtk {

using namespace v8;

struct econtext {
  GPollFD *pfd;
  ev_io *iow;
  int nfd, afd;
  gint maxpri;

  ev_prepare pw;
  ev_check cw;
  ev_timer tw;

  GMainContext *gc;
};

static void timer_cb (EV_P_ ev_timer *w, int revents) {
  /* nop */
}

static void io_cb (EV_P_ ev_io *w, int revents) {
  /* nop */
}

static void prepare_cb (EV_P_ ev_prepare *w, int revents) {
  struct econtext *ctx = (struct econtext *)(((char *)w) - offsetof (struct econtext, pw));
  gint timeout;
  int i;

  g_main_context_dispatch (ctx->gc);

  g_main_context_prepare (ctx->gc, &ctx->maxpri);

  while (ctx->afd < (ctx->nfd = g_main_context_query  (
          ctx->gc,
          ctx->maxpri,
          &timeout,
          ctx->pfd,
          ctx->afd))
      )
  {
    free (ctx->pfd);
    free (ctx->iow);

    ctx->afd = 1;
    while (ctx->afd < ctx->nfd)
      ctx->afd <<= 1;

    ctx->pfd = (GPollFD*) malloc (ctx->afd * sizeof (GPollFD));
    ctx->iow = (ev_io*) malloc (ctx->afd * sizeof (ev_io));
  }

  for (i = 0; i < ctx->nfd; ++i)
  {
    GPollFD *pfd = ctx->pfd + i;
    ev_io *iow = ctx->iow + i;

    pfd->revents = 0;

    ev_io_init (
        iow,
        io_cb,
        pfd->fd,
        (pfd->events & G_IO_IN ? EV_READ : 0)
        | (pfd->events & G_IO_OUT ? EV_WRITE : 0)
        );
    iow->data = (void *)pfd;
    ev_set_priority (iow, EV_MINPRI);
    ev_io_start (EV_A iow);
  }

  if (timeout >= 0)
  {
    ev_timer_set (&ctx->tw, timeout * 1e-3, 0.);
    ev_timer_start (EV_A &ctx->tw);
  }
}

static void check_cb (EV_P_ ev_check *w, int revents) {
  struct econtext *ctx = (struct econtext *)(((char *)w) - offsetof (struct econtext, cw));
  int i;

  for (i = 0; i < ctx->nfd; ++i)
  {
    ev_io *iow = ctx->iow + i;

    if (ev_is_pending (iow))
    {
      GPollFD *pfd = ctx->pfd + i;
      int revents = ev_clear_pending (EV_A iow);

      pfd->revents |= pfd->events &
        ((revents & EV_READ ? G_IO_IN : 0)
         | (revents & EV_WRITE ? G_IO_OUT : 0));
    }

    ev_io_stop (EV_A iow);
  }

  if (ev_is_active (&ctx->tw))
    ev_timer_stop (EV_A &ctx->tw);

  g_main_context_check (ctx->gc, ctx->maxpri, ctx->pfd, ctx->nfd);
}

static struct econtext default_context;

static Handle<Value> GtkInit (const Arguments &args) {
  HandleScope scope;
  gtk_init(NULL, NULL);
  return Undefined();
}

static Handle<Value> GtkMain (const Arguments &args) {
  HandleScope scope;
  gtk_main();
  return Undefined();
}

static Handle<Value> GtkMainQuit (const Arguments &args) {
  HandleScope scope;
  gtk_main_quit();
  return Undefined();
}

extern "C" void init(Handle<Object> target) {
  HandleScope scope;

  // We can't init here.
  //gtk_init(NULL, NULL);

  // User has to init inside a nextTick etc.
  GTK_ATTACH_FUNCTION(target, "init", GtkInit);
  GTK_ATTACH_FUNCTION(target, "main", GtkMain);
  GTK_ATTACH_FUNCTION(target, "main_quit", GtkMainQuit);

  // Position constants.
  GTK_DEFINE_CONSTANT(target, "WIN_POS_NONE",             GTK_WIN_POS_NONE);
  GTK_DEFINE_CONSTANT(target, "WIN_POS_CENTER",           GTK_WIN_POS_CENTER);
  GTK_DEFINE_CONSTANT(target, "WIN_POS_MOUSE",            GTK_WIN_POS_MOUSE);
  GTK_DEFINE_CONSTANT(target, "WIN_POS_CENTER_ALWAYS",    GTK_WIN_POS_CENTER_ALWAYS);
  GTK_DEFINE_CONSTANT(target, "WIN_POS_CENTER_ON_PARENT", GTK_WIN_POS_CENTER_ON_PARENT);

  // MessageDialog constants
  GTK_DEFINE_CONSTANT(target, "DIALOG_MODAL",               GTK_DIALOG_MODAL);
  GTK_DEFINE_CONSTANT(target, "DIALOG_DESTROY_WITH_PARENT", GTK_DIALOG_DESTROY_WITH_PARENT);
  GTK_DEFINE_CONSTANT(target, "DIALOG_NO_SEPARATOR",        GTK_DIALOG_NO_SEPARATOR);

  // Message types.
  GTK_DEFINE_CONSTANT(target, "MESSAGE_INFO",     GTK_MESSAGE_INFO);
  GTK_DEFINE_CONSTANT(target, "MESSAGE_WARNING",  GTK_MESSAGE_WARNING);
  GTK_DEFINE_CONSTANT(target, "MESSAGE_QUESTION", GTK_MESSAGE_QUESTION);
  GTK_DEFINE_CONSTANT(target, "MESSAGE_ERROR",    GTK_MESSAGE_ERROR);
  GTK_DEFINE_CONSTANT(target, "MESSAGE_OTHER",    GTK_MESSAGE_OTHER);

  // Buttons.
  GTK_DEFINE_CONSTANT(target, "BUTTONS_NONE",      GTK_BUTTONS_NONE);
  GTK_DEFINE_CONSTANT(target, "BUTTONS_OK",        GTK_BUTTONS_OK);
  GTK_DEFINE_CONSTANT(target, "BUTTONS_CLOSE",     GTK_BUTTONS_CLOSE);
  GTK_DEFINE_CONSTANT(target, "BUTTONS_CANCEL",    GTK_BUTTONS_CANCEL);
  GTK_DEFINE_CONSTANT(target, "BUTTONS_YES_NO",    GTK_BUTTONS_YES_NO);
  GTK_DEFINE_CONSTANT(target, "BUTTONS_OK_CANCEL", GTK_BUTTONS_OK_CANCEL);

  // Position
  GTK_DEFINE_CONSTANT(target, "POS_TOP", GTK_POS_TOP);
  GTK_DEFINE_CONSTANT(target, "POS_RIGHT", GTK_POS_RIGHT);
  GTK_DEFINE_CONSTANT(target, "POS_BOTTOM", GTK_POS_BOTTOM);
  GTK_DEFINE_CONSTANT(target, "POS_LEFT", GTK_POS_LEFT);

  // Response constants
  GTK_DEFINE_CONSTANT(target, "RESPONSE_NONE",         GTK_RESPONSE_NONE);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_REJECT",       GTK_RESPONSE_REJECT);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_ACCEPT",       GTK_RESPONSE_ACCEPT);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_DELETE_EVENT", GTK_RESPONSE_DELETE_EVENT);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_OK",           GTK_RESPONSE_OK);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_CANCEL",       GTK_RESPONSE_CANCEL);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_CLOSE",        GTK_RESPONSE_CLOSE);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_YES",          GTK_RESPONSE_YES);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_NO",           GTK_RESPONSE_NO);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_APPLY",        GTK_RESPONSE_APPLY);
  GTK_DEFINE_CONSTANT(target, "RESPONSE_HELP",         GTK_RESPONSE_HELP);

  // Direction type constants
  GTK_DEFINE_CONSTANT(target, "DIR_TAB_FORWARD",       GTK_DIR_TAB_FORWARD);
  GTK_DEFINE_CONSTANT(target, "DIR_TAB_BACKWARD",      GTK_DIR_TAB_BACKWARD);
  GTK_DEFINE_CONSTANT(target, "DIR_UP",                GTK_DIR_UP);
  GTK_DEFINE_CONSTANT(target, "DIR_DOWN",              GTK_DIR_DOWN);
  GTK_DEFINE_CONSTANT(target, "DIR_LEFT",              GTK_DIR_LEFT);
  GTK_DEFINE_CONSTANT(target, "DIR_RIGHT",             GTK_DIR_RIGHT);

  GMainContext *gc     = g_main_context_default();
  struct econtext *ctx = &default_context;

  NodeGtkWidget::Initialize(target);
  NodeGtkContainer::Initialize(target);
  NodeGtkBin::Initialize(target);
  NodeGtkBox::Initialize(target);
  NodeGtkHBox::Initialize(target);
  NodeGtkVBox::Initialize(target);
  NodeGtkWindow::Initialize(target);
  NodeGtkEntry::Initialize(target);
  NodeGtkButton::Initialize(target);
  NodeGtkMisc::Initialize(target);
  NodeGtkLabel::Initialize(target);
  NodeGtkTreeStore::Initialize(target);

  ctx->gc  = g_main_context_ref(gc);
  ctx->nfd = 0;
  ctx->afd = 0;
  ctx->iow = 0;
  ctx->pfd = 0;

  ev_prepare_init (&ctx->pw, prepare_cb);
  ev_set_priority (&ctx->pw, EV_MINPRI);
  ev_prepare_start (EV_DEFAULT_UC_ &ctx->pw);
  ev_unref(EV_DEFAULT_UC_);

  ev_check_init (&ctx->cw, check_cb);
  ev_set_priority (&ctx->cw, EV_MAXPRI);
  ev_check_start (EV_DEFAULT_UC_ &ctx->cw);
  ev_unref(EV_DEFAULT_UC_);

  ev_init (&ctx->tw, timer_cb);
  ev_set_priority (&ctx->tw, EV_MINPRI);
}

} // namespace ngtk
