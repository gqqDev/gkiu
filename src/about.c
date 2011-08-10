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

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include "../config.h"
#include "main.h"
#include "misc.h"
#include "about.h"

/**
 * SECTION: about
 * @Short_descript: Show about dialog
 * @Include: about.h
 */

static gchar *_authors[] = {"Mike Ma <zhtx10@gmail.com>", NULL};

/**
 * about_show_dialog:
 * 
 * Show the About dialog of GKiu.
 * 
 * Since: 2.9.9
 */
void
about_show_dialog (void)
{
    GtkWidget *dialog = NULL;
    dialog = gtk_about_dialog_new ();
    gtk_about_dialog_set_program_name (GTK_ABOUT_DIALOG (dialog),
                                       _("GKiu Core"));
    gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (dialog), VERSION);
    gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG (dialog), 
                                   _("GKiu Core Manager"));
    gtk_about_dialog_set_license_type (GTK_ABOUT_DIALOG (dialog),
                                       GTK_LICENSE_GPL_3_0);
    gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (dialog),
                                  "http://github.com/gqqdev/gkiu");
    gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (dialog), 
                                  (const gchar **)_authors);
    gtk_about_dialog_set_artists (GTK_ABOUT_DIALOG (dialog), NULL);/* artworks are needed */
    gtk_about_dialog_set_documenters (GTK_ABOUT_DIALOG (dialog),
                                      NULL);
    gtk_about_dialog_set_translator_credits (GTK_ABOUT_DIALOG (dialog),
                                             _("translator-credits"));
    
    
    GdkPixbuf *buf = misc_open_image (WHERE_ICON);
    if (buf)
    {
        gtk_about_dialog_set_logo (GTK_ABOUT_DIALOG (dialog), buf);
        g_object_unref (buf);
    }
    
    gtk_dialog_run (GTK_DIALOG (dialog));
}
