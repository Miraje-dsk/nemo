/* ---------------------------------------------------------------------------
 * nemo-trash-bar.c
 * ---------------------------------------------------------------------------
 * Modified to automatically close the Trash window after emptying,
 * respecting the GSettings key "auto-close-trash".
 * --------------------------------------------------------------------------- */

#include <gio/gio.h>               /* ← new include */
#include "nemo-trash-bar.h"

/* Existing includes … */

/* Helper: close the Trash window if the user enabled the option */
static void
maybe_close_trash_window (NemoWindow *window)
{
    GSettings *settings;
    gboolean   auto_close;

    settings = g_settings_new ("org.miraje.nemo");
    auto_close = g_settings_get_boolean (settings, "auto-close-trash");
    g_object_unref (settings);

    if (auto_close && window != NULL) {
        gtk_window_close (GTK_WINDOW (window));
    }
}

/* Original empty‑trash callback – extended */
static void
empty_trash_cb (GtkWidget *widget,
                gpointer   user_data)
{
    NemoWindow *window = NEMO_WINDOW (user_data);

    /* Existing logic that actually empties the trash */
    nemo_trash_empty (/* … */);

    /* After a successful empty, optionally close the window */
    maybe_close_trash_window (window);
}

/* The rest of the file remains unchanged */