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
#include "shell.h"
#include "shell-glue.h"
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

static const char __DBUS_NAME[] = "org.gkiu.core";
static const char __DBUS_PATH_SHELL[] = "/org/gkiu/core/Shell";
static const char __DBUS_INTERFACE_SHELL[] = "org.gkiu.core.Shell";

/**
 * __dbus_init:
 * 
 * Initialize DBus support of GKiu.
 */
gboolean __dbus_init(void)
{
    DBusGConnection *bus;
    DBusGProxy *bus_proxy;
    GError *error = NULL;
    GKiuShell *obj;
    guint request_name_result;
    
    dbus_g_object_type_install_info (GKIU_TYPE_SHELL, 
                                     &dbus_glib_gkiu_shell_object_info);
    
    bus = dbus_g_bus_get (DBUS_BUS_SESSION, &error);
    if (!bus)
    {
        g_error (_("Couldn't connect to system bus: %s"), error->message);
        g_error_free (error);
        return FALSE;
    }
    
    bus_proxy = dbus_g_proxy_new_for_name (bus, "org.freedesktop.DBus",
                                           "/", "org.freedesktop.DBus");
    
    if (!dbus_g_proxy_call (bus_proxy, "RequestName", &error,
                            G_TYPE_STRING, __DBUS_NAME,
                            G_TYPE_UINT, 0,
                            G_TYPE_INVALID,
                            G_TYPE_UINT, &request_name_result,
                            G_TYPE_INVALID))
    {
        g_error (_("Failed to acquire %s: %s"), __DBUS_NAME, error->message);
        g_error_free (error);
        return FALSE;
    }
    
    obj = g_object_new (GKIU_TYPE_SHELL, NULL);
    dbus_g_connection_register_g_object (bus, __DBUS_PATH_SHELL, 
                                         G_OBJECT (obj));
    return TRUE;
}
