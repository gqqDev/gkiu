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
 * @short_description: the main() function.
 * @see_also: the #main() function.
 * @stability: Stable
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

#include "config.h"
#include "main.h"
#include "manager.h"

gboolean development;
gboolean showmanager;


static GOptionEntry args [] = {
    { "development", 'd', 0, G_OPTION_ARG_NONE, &development,
      N_("Run on development."), NULL },
    { "show-manager", 'm', 0, G_OPTION_ARG_NONE, &showmanager,
      N_("Show the Modules Manager of GKiu Core."), NULL },
};


/**
 * main:
 * @argc: The number of arguments. From shell.
 * @argv: The char array of arguments. From shell.
 *
 * This function is the main() function.
 * It does:
 * 1, Init (parse args, i18n, config, gobject)
 * 3, Print application name and version to terminal.
 * 4, Call core manager.
 *
 * Return Value: The exitcode.
 * Since: 0.0
 */
int
main (int argc,
      char *argv[])
{
    GOptionContext *option_context;
    GError *error = NULL;

    /* init cfg */
    cfg_init ();

    /* init i18n */
    bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);

    /* Parse arguments */
    option_context = g_option_context_new (_(" - GKiu Core Manager"));

    g_option_context_add_main_entries (option_context, args, PACKAGE_NAME);
    g_option_context_add_group (option_context, gtk_get_option_group (TRUE));

    g_option_context_add_group (option_context, g_irepository_get_option_group ());

    if (!g_option_context_parse (option_context, &argc, &argv, &error))
    {
        g_error (_("Error while parsing arguments: %s"), error->message);
        g_error_free (error);
        exit (EXIT_FAILURE);
    }
    g_option_context_free (option_context);

    /* Load GIRepository Support */
    g_irepository_prepend_search_path (GIR_DIR);

    /* Print Some Informations */
    g_print (_("Welcome to %s\n"), PACKAGE_STRING);

    /* Call core manager */
    g_debug (_("Staring Core Manager."));
    manager_init (development);
    manager_load_modules_in_list ();

    if (manager_call_function("keyring","keyring_delpwd", "test") == FALSE)
        g_print ("hai shi shi bai le...");
    else
        g_print ("pass...\n");


    if (showmanager)
    {
        /* Show manager window. */
        gtk_widget_show_all (manager_show_manager_window ());
        gtk_main ();
    }

    /* Bye, GKiu. We'll miss you. :-) */
    cfg_save ();
    cfg_free ();
    exit (EXIT_SUCCESS);
}
