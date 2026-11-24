/* ---------------------------------------------------------------------------
 * nemo-file-management-properties.c
 * ---------------------------------------------------------------------------
 * Added a checkbox to Preferences → Behavior that toggles the
 * "auto-close-trash" GSettings key.
 * --------------------------------------------------------------------------- */

#include <gio/gio.h>
#include "nemo-file-management-properties.h"

/* ---------------------------------------------------------------------------
 * Callback for the new checkbox
 * --------------------------------------------------------------------------- */
static void
on_auto_close_trash_toggled (GtkToggleButton *toggle,
                             GSettings       *settings)
{
    gboolean active = gtk_toggle_button_get_active (toggle);
    g_settings_set_boolean (settings, "auto-close-trash", active);
}

/* ---------------------------------------------------------------------------
 * Insert the checkbox into the Behavior page
 * --------------------------------------------------------------------------- */
static void
add_auto_close_trash_option (GtkBuilder *builder, GtkBox *parent)
{
    GSettings *settings;
    GtkWidget *check;

    settings = g_settings_new ("org.miraje.nemo");

    check = gtk_check_button_new_with_label (
                _("Automatically close the Trash window after emptying"));
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check),
                                  g_settings_get_boolean (settings,
                                                          "auto-close-trash"));
    g_signal_connect (check, "toggled",
                      G_CALLBACK (on_auto_close_trash_toggled),
                      settings);

    gtk_box_pack_start (parent, check, FALSE, FALSE, 0);
    gtk_widget_show (check);
}

/* ---------------------------------------------------------------------------
 * Wherever the Behavior page is built (e.g., build_behavior_page()), call:
 * --------------------------------------------------------------------------- */
    /* existing option widgets … */
    add_auto_close_trash_option (builder, GTK_BOX (behavior_vbox));
    /* continue with other options … */

/* Cleanup – unref settings when the preferences dialog is destroyed */
static void
preferences_dialog_destroy_cb (GtkWidget *dialog,
                               gpointer   user_data)
{
    GSettings *settings = G_SETTINGS (user_data);
    g_object_unref (settings);
}

/* The remainder of the file is unchanged */