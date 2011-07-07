/*
 * GKiu
 * Copyright (C) 2011 the GQQ Team
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <libpeas/peas.h>
#include <libpeas-gtk/peas-gtk.h>

#include "manager.h"

static PeasEngine *engine = NULL;

/**
 * get_engine:
 *
 * Get the pointer to the default
 * Peas Engine of GKiu. [read-only]
 *
 * Return Value: The pointer to the default PeasEngine.
 * Since: 0.0
 */
PeasEngine *
get_engine()
{
    return engine;
}

/**
 * manager_init:
 * Get ready for loading modules.
 *
 * Return Value: void
 * Since: 2.9.9
 */
void
manager_init (gboolean on_dev)
{
    if ((engine = peas_engine_get_default ())==NULL)
    {
        g_error (_("Could not load modules"));
        exit (1);
    }

    if (on_dev)
    {
        g_debug ("Now search plug-ins from build directory.");
        peas_engine_add_search_path (engine, DEV_MODULES_DIR, NULL);
    }
    else
    {
        peas_engine_add_search_path (engine, 
                                     PACKAGE_LIB_DIR  "/modules",
                                     PACKAGE_DATA_DIR "/modules");
    }
    peas_engine_enable_loader (engine, "gjs");
    peas_engine_enable_loader (engine, "seed");
    peas_engine_enable_loader (engine, "python");
}

/**
 * manager_show_manager_window:
 *
 * Open the Core Manager Window.
 * You can call it with argument '--show-manager'
 * before it starts
 *
 * Return Value: the pointer to Window. (GtkWidget *)
 * Since: 2.9.9
 */
GtkWidget *
manager_show_manager_window ()
{
    GtkWidget *window     = NULL;
    GtkWidget *box        = NULL;
    GtkWidget *manager    = NULL;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (window, "delete-event", 
                      G_CALLBACK (gtk_main_quit), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 6);
    gtk_window_set_title (GTK_WINDOW (window), _("GKiu Manager"));
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

#if GTK_CHECK_VERSION(2,91,1)
    gtk_window_set_has_resize_grip (GTK_WINDOW (window), FALSE);
#endif

    box = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER (window), box);

    manager = peas_gtk_plugin_manager_new (get_engine ());
    gtk_box_pack_start (GTK_BOX (box), manager, TRUE, TRUE, 0);

    gtk_window_resize (GTK_WINDOW(window), 600, 500);

    return window;
}

/**
 * manager_auto_start:
 * @engine: Start the auto-star tmodules in that engine.
 *
 * Just start the auto-start modules.
 *
 * Return Value: 0 on success. The others are on error.
 */
int
manager_auto_start (PeasEngine *engine)
{
    
    return 0;
}


/**
 * manager_refresh_modules_list:
 * @engine: The engine will refresh.
 *
 * Just refresh the modules list.
 *
 * Return Value: 0 on success. The others are on error.
 * Since: 2.9.9
 */
int
manager_refresh_modules_list ()
{
    return 0;
}
