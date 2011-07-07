/*
 * config.c
 *
 * Copyright (C) gqq team 2011 <gqq@freelists.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib.h>
#include <gio/gio.h>
#include <stdlib.h>
#include "config.h"


/* If you wanna use this variable in other files, just extern it. */
GSettings *settings = NULL;

/**
 * cfg_init:
 *
 * Init configure.
 *
 * Since: GKiu 0.0 UI Preview A
*/
void
cfg_init (void)
{
    if ((settings = g_settings_new ("org.gkiu")) == NULL)
    {
        g_error ("Oops! Couldn't read configurations!");
        exit (EXIT_FAILURE);
    }
}
