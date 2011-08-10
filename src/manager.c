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

#include <stdarg.h>
#include <stdlib.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <libpeas/peas.h>
#include <libpeas-gtk/peas-gtk.h>

#include "config.h"
#include "main.h"
#include "misc.h"
#include "manager.h"

/**
 * SECTION: engine
 * @Short_description: Manage the Engine
 * @Title: Manager
 * @Include: manager.h
 */

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
 * Since: 2.9.9
 */
void
manager_init ()
{
    if ((engine = peas_engine_get_default ())==NULL)
    {
        g_error (_("Could not load modules"));
        exit (1);
    }

    peas_engine_add_search_path (engine, 
                                 PACKAGE_LIB_DIR  "/modules",
                                 PACKAGE_DATA_DIR "/modules");
    
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
static gboolean
manager_window_close_cb (GtkWidget *widget,
                         GdkEvent *event,
                         gpointer ptr)
{
    manager_save_modules_list ();
    gtk_main_quit ();
    return FALSE;
}

GtkWidget *
manager_show_manager_window ()
{
    GtkWidget *window     = NULL;
    GtkWidget *box        = NULL;
    GtkWidget *manager    = NULL;
    GtkWidget *rbutton    = NULL; /* refresh module list */
    GtkWidget *buttonbox  = NULL; /* add extra buttons to this */

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (window, "delete-event", 
                      G_CALLBACK (manager_window_close_cb), NULL);
    gtk_container_set_border_width (GTK_CONTAINER (window), 6);
    gtk_window_set_title (GTK_WINDOW (window), _("GKiu Manager"));
    gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_CENTER);

    /* set icon */
    GdkPixbuf *image = misc_open_image (WHERE_ICON);
    if (image)
    {
        gtk_window_set_default_icon (image);
        g_object_unref (image);
    }
    
    gtk_window_set_has_resize_grip (GTK_WINDOW (window), FALSE);

    box = gtk_vbox_new (FALSE, 6);
    gtk_container_add (GTK_CONTAINER (window), box);

    manager = peas_gtk_plugin_manager_new (get_engine ());
    gtk_box_pack_start (GTK_BOX (box), manager, TRUE, TRUE, 0);

    /* button box */
    buttonbox = gtk_hbutton_box_new ();
    gtk_button_box_set_layout (GTK_BUTTON_BOX(buttonbox),
                               GTK_BUTTONBOX_END);
    gtk_box_pack_end (GTK_BOX (box), buttonbox, FALSE, FALSE, 0);
    
    /* rbutton */
    rbutton = gtk_button_new_with_mnemonic (_("_Refresh"));
    g_signal_connect (rbutton, "clicked", 
                      G_CALLBACK (manager_refresh_modules_list), NULL);
    gtk_box_pack_end (GTK_BOX (buttonbox), rbutton, FALSE, FALSE, 0);

    gtk_window_resize (GTK_WINDOW(window), 600, 500);

    return window;
}

/**
 * manager_save_modules_list:
 *
 * Save the loaded modules into the config file.
 *
 * Since: 2.9.9
 */
void
manager_save_modules_list ()
{
    const GList *list = NULL;
    int          n    = 0;

    /* get number */
    list = peas_engine_get_plugin_list (get_engine ());
    while (g_list_next (list))
    {
        if (peas_plugin_info_is_loaded ((PeasPluginInfo *)list->data))
            n ++;
        list = g_list_next (list);
    }

    /* get list */
    gchar **strv;
    strv = peas_engine_get_loaded_plugins (get_engine ());

    /* save */
    cfg_set_strv (CFG_GRP_MANAGER, CFG_KEY_PLUGIN_LIST, (const char**)strv, n);
    cfg_set_int  (CFG_GRP_MANAGER, CFG_KEY_PLUGIN_LIST_NO, n);

    /* clean up */
    g_strfreev (strv);
}

/**
 * manager_load_modules_in_list:
 * 
 * Load the modules in list.
 *
 * Since: 2.9.9
 */
void
manager_load_modules_in_list ()
{
    gsize n;
    gchar **strv = cfg_get_strv (CFG_GRP_MANAGER, CFG_KEY_PLUGIN_LIST, &n);
    if (strv)
    {
        peas_engine_set_loaded_plugins (get_engine (), (const gchar**)strv);
    }
    g_strfreev (strv);
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
void
manager_refresh_modules_list ()
{
    peas_engine_rescan_plugins (get_engine ());
}

/**
 * manager_call_function:
 * @pname: The plugin name.
 * @mname: The function name.
 *
 * Call a function in a plugin.
 *
 * Return Value: TRUE on a successful call.
 * Since: 2.9.9
 */
gboolean
manager_call_function (const char *pname,
                       const char *mname,
                       ...)
{
    /* PeasExtensionSet */
    PeasExtensionSet *set = peas_extension_set_new (get_engine (),
                                                    PEAS_TYPE_ACTIVATABLE,
                                                    NULL);
    /* get plugin info */
    PeasPluginInfo *pinfo = peas_engine_get_plugin_info (get_engine (),
                                                         pname);
    
    /* PeasExtension */
    PeasExtension *ext = peas_extension_set_get_extension (set, pinfo);
    if (!ext)
        return FALSE;

    /* call it. */
    va_list pvar;
    va_start (pvar, mname);
    gboolean r = peas_extension_call_valist (ext, mname, pvar);
    va_end (pvar);

    return r;
}

