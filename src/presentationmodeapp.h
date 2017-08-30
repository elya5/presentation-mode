#ifndef __PRESENTATIONMODEAPP_H
#define __PRESENTATIONMODEAPP_H

#include <gtk/gtk.h>


#define PRESENTATION_MODE_APP_TYPE (presentation_mode_app_get_type ())
G_DECLARE_FINAL_TYPE (PresentationModeApp, presentation_mode_app, PRESENTATION_MODE, APP, GtkApplication)


PresentationModeApp     *presentation_mode_app_new         (void);


#endif /* __PRESENTATIONMODEAPP_H */


