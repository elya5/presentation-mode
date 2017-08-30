#ifndef __PRESENTATIONMODEAPPWIN_H
#define __PRESENTATIONMODEAPPWIN_H

#include <gtk/gtk.h>
#include "presentationmodeapp.h"


#define PRESENTATION_MODE_APP_WINDOW_TYPE (presentation_mode_app_window_get_type ())
G_DECLARE_FINAL_TYPE (PresentationModeAppWindow, presentation_mode_app_window, PRESENTATION_MODE, APP_WINDOW, GtkApplicationWindow)


PresentationModeAppWindow       *presentation_mode_app_window_new          (PresentationModeApp *app);

#endif /* __PRESENTATIONMODEAPPWIN_H */


