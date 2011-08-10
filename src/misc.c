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

#include <glib.h>
#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include "misc.h"

/**
 * SECTION: misc
 * @Short_description: Miscellaneous functions
 * @Include: misc.h
 */


/**
 * misc_open_image:
 * @path: Where the image is.
 * 
 * This function will open the 
 *  image into a new GdkPixbuf.
 * 
 * Return Value: A newly created GdkPixbuf.
 * Since: 2.9.9
 */
GdkPixbuf *
misc_open_image (const gchar *path)
{
    GError *err = NULL;
    GdkPixbuf *buf = gdk_pixbuf_new_from_file (path, &err);
    if (!buf)
    {
        fprintf (stderr, _("Failed to open the picture: %s\n"), 
                 err->message);
        return NULL;
    }
    return buf;
}

