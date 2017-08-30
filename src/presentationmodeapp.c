#include <gtk/gtk.h>

#include "presentationmodeapp.h"
#include "presentationmodeappwin.h"

struct _PresentationModeApp
{
  GtkApplication parent;
};

G_DEFINE_TYPE(PresentationModeApp, presentation_mode_app, GTK_TYPE_APPLICATION);

static void
presentation_mode_app_init (PresentationModeApp *app)
{
}

static void
presentation_mode_app_activate (GApplication *app)
{
  PresentationModeAppWindow *win;

  win = presentation_mode_app_window_new (PRESENTATION_MODE_APP (app));
  gtk_window_present (GTK_WINDOW (win));
}

static void
presentation_mode_app_class_init (PresentationModeAppClass *class)
{
  G_APPLICATION_CLASS (class)->activate = presentation_mode_app_activate;
}

PresentationModeApp *
presentation_mode_app_new (void)
{
  return g_object_new (PRESENTATION_MODE_APP_TYPE,
                       "application-id", "de.flump.presentation-mode", NULL);
}
