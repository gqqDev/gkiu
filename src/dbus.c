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
#include <dbus/dbus.h>
#include <dbus/dbus-glib.h>
#include <limits.h>

#include "dbus.h"
#include "gkiu-dbus-object.h"
#include "gkiu-dbus-object-glue.h"
#include "../config.h"

/**
 * SECTION: dbus
 * @Short_description: dbus proxy for calling modules
 * @Title: DBus Proxy
 * @Include: dbus.h
 * 
 * The dbus proxy for calling modules.
 * The functions here are internal. (So I add _ prefix.)
 */

static const char __DBUS_NAME[] = "org.gkiu";
static const char __DBUS_PATH_SHELL[] = "/org/gkiu/Shell";
static const char __DBUS_INTERFACE_SHELL[] = "org.gkiu.Shell";

/**
 * __dbus_init:
 * 
 * Initialize DBus support of GKiu.
 */
gboolean __dbus_init(void)
{
    DBusGConnection *session_bus = NULL;
    DBusGProxy      *shell_proxy = NULL;
    GError          *error       = NULL;
    GObject         *shell_info  = NULL;

    session_bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
    if (session_bus == NULL)
    {
        g_error (_("Failed to open DBus: %s"), error->message);
        g_error_free (error);
        return FALSE;
    }
    
    shell_proxy = dbus_g_proxy_new_for_name (session_bus,
                                             __DBUS_NAME,
                                             __DBUS_PATH_SHELL,
                                             __DBUS_INTERFACE_SHELL);
    if (!shell_proxy)
    {
        g_warning (_("Couldn't create proxy for DBus shell: %s"), 
                   error->message);
        g_error_free (error);
        return FALSE;
    }
    else
    {
        abort ();
        dbus_g_object_type_install_info (GKIU_TYPE_DBUS_OBJECT,
                                         &dbus_glib_gkiu_dbus_object_object_info);
        shell_info = g_object_new (GKIU_TYPE_DBUS_OBJECT, NULL);
        dbus_g_connection_register_g_object (session_bus,
                                             __DBUS_PATH_SHELL,
                                             G_OBJECT (shell_info));
    }
    g_object_unref (G_OBJECT (shell_proxy));
    
    return TRUE;
}
