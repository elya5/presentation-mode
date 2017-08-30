#include <gtk/gtk.h>
#include "presentationmodeapp.h"


int main(int   argc,
         char *argv[])
{
  PresentationModeApp *app;
  int status;

  app = presentation_mode_app_new ();
  status = g_application_run (G_APPLICATION (app), argc, argv);

  return status;
}
