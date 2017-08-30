#include <gtk/gtk.h>

#include "presentationmodeapp.h"
#include "presentationmodeappwin.h"
#include "pm-save-restore.h"

struct _PresentationModeAppWindow
{
  GtkApplicationWindow   parent;
  GtkLabel              *time_label;
  GtkAdjustment         *adjustment;
  GtkStack              *stack;
  guint                  seconds;
};

G_DEFINE_TYPE(PresentationModeAppWindow, presentation_mode_app_window, GTK_TYPE_APPLICATION_WINDOW);

static void
presentation_mode_app_window_init (PresentationModeAppWindow *self)
{
    gtk_widget_init_template (GTK_WIDGET (self));
    self->seconds = 0;
}

gboolean
decrease_countdown_seconds (void *selfv)
{
    guint hours;
    guint minutes;
    guint seconds;
    PresentationModeAppWindow *self;
    char *time_string;
    
    self = PRESENTATION_MODE_APP_WINDOW (selfv);

    hours = self->seconds / (60 * 60);
    minutes = (self->seconds / 60) % 60;
    seconds = self->seconds % 60;

    time_string = g_strdup_printf ("%02u:%02u:%02u", hours, minutes, seconds);
    gtk_label_set_label (self->time_label, time_string);
    g_free(time_string);

    if (self->seconds == 0)
      {
        gtk_stack_set_visible_child_name(self->stack, "start");
        pm_restore();
        return FALSE;
      }
    self->seconds--;

    return TRUE;
}

static void
on_start_clicked (GtkButton *button)
{
    GtkWidget *toplevel;
    PresentationModeAppWindow *win;
    guint minutes;

    toplevel = gtk_widget_get_toplevel (GTK_WIDGET (button));
    win = PRESENTATION_MODE_APP_WINDOW (toplevel);

    gtk_stack_set_visible_child_name(win->stack, "countdown");

    minutes = (guint) gtk_adjustment_get_value (win->adjustment);
    win->seconds = minutes * 60;

    decrease_countdown_seconds (win);
    pm_save();
    pm_enable_presentation();
    g_timeout_add_seconds (1, &decrease_countdown_seconds, win);
}

static void
on_stop_clicked (GtkButton *button)
{
    GtkWidget *toplevel;
    PresentationModeAppWindow *win;

    toplevel = gtk_widget_get_toplevel (GTK_WIDGET (button));
    win = PRESENTATION_MODE_APP_WINDOW (toplevel);

    gtk_stack_set_visible_child_name (win->stack, "start");
    // resets the timeout in the next step
    win->seconds = 0;
}

static gboolean
on_delete (GtkWidget *self,
           GdkEvent  *event)
{
    PresentationModeAppWindow *win;

    win = PRESENTATION_MODE_APP_WINDOW (self);
    if (win->seconds != 0)
        pm_restore();

    return FALSE;
}

static void
presentation_mode_app_window_class_init (PresentationModeAppWindowClass *klass)
{
    GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/de/flump/presentation-mode/window.ui");
    gtk_widget_class_bind_template_child (widget_class, PresentationModeAppWindow, time_label);
    gtk_widget_class_bind_template_child (widget_class, PresentationModeAppWindow, adjustment);
    gtk_widget_class_bind_template_child (widget_class, PresentationModeAppWindow, stack);

    gtk_widget_class_bind_template_callback (widget_class, on_start_clicked);
    gtk_widget_class_bind_template_callback (widget_class, on_stop_clicked);
    gtk_widget_class_bind_template_callback (widget_class, on_delete);
}

PresentationModeAppWindow *
presentation_mode_app_window_new (PresentationModeApp *app)
{
  return g_object_new (PRESENTATION_MODE_APP_WINDOW_TYPE, "application", app, NULL);
}
