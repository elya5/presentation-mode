
#include "pm-save-restore.h"

void
pm_save ()
{
    GSettings *settings;
    gboolean show_banners;
    guint idle_delay;
    gboolean show_desktop_icons;
    gchar *path;
    GKeyFile *keyfile;
    GError *error = NULL;

    settings = g_settings_new ("org.gnome.desktop.notifications");
    show_banners = g_settings_get_boolean (settings, "show-banners");
    settings = g_settings_new ("org.gnome.desktop.session");
    idle_delay = g_settings_get_uint (settings, "idle-delay");
    settings = g_settings_new ("org.gnome.desktop.background");
    show_desktop_icons = g_settings_get_boolean (settings, "show-desktop-icons");

    path = g_build_path (G_DIR_SEPARATOR_S,
                         g_get_user_data_dir (),
                         "presentation-mode",
                         NULL);
    keyfile = g_key_file_new ();
    g_key_file_set_boolean (keyfile, "settings", "show-banners", show_banners);
    g_key_file_set_boolean (keyfile, "settings", "show-desktop-icons", show_desktop_icons);
    g_key_file_set_uint64 (keyfile, "settings", "idle-delay", idle_delay);

    g_mkdir_with_parents (path, 0750);
    path = g_build_path (G_DIR_SEPARATOR_S, path, "conf", NULL);
    if (!g_key_file_save_to_file (keyfile, path, &error))
      {
        g_warning ("Error saving keyfile: %s", error->message);
        g_error_free (error);
      }

    g_free (path);
    g_key_file_free (keyfile);
}

void
pm_enable_presentation ()
{
    GSettings *settings;

    settings = g_settings_new ("org.gnome.desktop.notifications");
    g_settings_set_boolean (settings, "show-banners", FALSE);
    settings = g_settings_new ("org.gnome.desktop.session");
    g_settings_set_uint (settings, "idle-delay", 0);
    settings = g_settings_new ("org.gnome.desktop.background");
    g_settings_set_boolean (settings, "show-desktop-icons", FALSE);
}


void
pm_restore ()
{
    GSettings *settings;
    gboolean show_banners;
    gboolean show_desktop_icons;
    guint idle_delay;
    gchar *path;
    GKeyFile *keyfile;
    GError *error = NULL;

    path = g_build_path (G_DIR_SEPARATOR_S,
                         g_get_user_data_dir (),
                         "presentation-mode",
                         "conf",
                         NULL);
    keyfile = g_key_file_new ();
    if (!g_key_file_load_from_file (keyfile, path, G_KEY_FILE_NONE, &error))
      {
        g_warning ("Error loading keyfile: %s", error->message);
        g_error_free (error);
        g_free (path);
        return;
      }

    show_banners = g_key_file_get_boolean (keyfile, "settings", "show-banners", NULL);
    show_desktop_icons = g_key_file_get_boolean (keyfile, "settings", "show-desktop-icons", NULL);
    idle_delay = g_key_file_get_integer (keyfile, "settings", "idle-delay", NULL);

    settings = g_settings_new ("org.gnome.desktop.notifications");
    g_settings_set_boolean (settings, "show-banners", show_banners);
    settings = g_settings_new ("org.gnome.desktop.background");
    g_settings_set_boolean (settings, "show-desktop-icons", show_desktop_icons);
    settings = g_settings_new ("org.gnome.desktop.session");
    g_settings_set_uint (settings, "idle-delay", idle_delay);

    g_free (path);
    g_key_file_free (keyfile);
}
