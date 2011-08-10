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

/**
 * SECTION: main
 * @Title: The entry point.
 * @Short_description: the main() function.
 * @See_also: the #main() function.
 * @Stability: Stable
 * 
 * This file include the main() function.
 */

#include <../config.h>
#include <stdlib.h>

#include <glib.h>
#include <glib/gi18n.h>
#include <girepository.h>

#include <gtk/gtk.h>
#include <libpeas/peas.h>

#include "about.h"
#include "config.h"
#include "dbus.h"
#include "main.h"
#include "manager.h"

gboolean showmanager;
gboolean about;

static GOptionEntry args [] = {
    { "show-manager", 'm', 0, G_OPTION_ARG_NONE, &showmanager,
            N_("Show the Modules Manager of GKiu Core."), NULL 
    },
    { "about", 'a', 0, G_OPTION_ARG_NONE, &about,
            N_("Show the About dialog."), NULL 
    },
    { NULL }
};

/**
 * main:
 * @argc: The number of arguments. From shell.
 * @argv: The char array of arguments. From shell.
 *
 * This function is the main() function.
 * It does:
 * 1, Init (parse args, i18n, config, gobject)
 * 2. Init DBus
 * 3, Call core manager.
 *
 * Return Value: The exitcode.
 * Since: 0.0
 */
int
main (int argc,
      char *argv[])
{
    /* init i18n */
    bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);
    
    
    /* init cfg */
    cfg_init ();

    /* init gobject */
    g_type_init ();
    
    /* init dbus */
    __dbus_init ();

    /* Parse arguments */
    GOptionContext *option_context;
    GError *error = NULL;

    option_context = g_option_context_new (_(" - GKiu Core Manager"));

    g_option_context_add_main_entries (option_context, args, PACKAGE_NAME);
    g_option_context_add_group (option_context, 
                                gtk_get_option_group (TRUE));

    g_option_context_add_group (option_context, 
                                g_irepository_get_option_group ());

    if (!g_option_context_parse (option_context, &argc, &argv, &error))
    {
        g_error (_("Error while parsing arguments: %s"), error->message);
        g_error_free (error);
        exit (EXIT_FAILURE);
    }
    g_option_context_free (option_context);
        
    /* check if about dialog will be shown */
    if (about)
    {
        about_show_dialog ();
        exit (EXIT_SUCCESS);
    }
    
    /* Call core manager */
    manager_init ();
    manager_load_modules_in_list ();
    
    if (showmanager)
    {
        gtk_widget_show_all (manager_show_manager_window ());
        gtk_main ();
    }

    /* Good night, GKiu. :-) */
    cfg_save ();
    cfg_free ();
    exit (EXIT_SUCCESS);
}
