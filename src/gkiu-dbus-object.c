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

#include <dbus/dbus-glib.h>
#include "manager.h"
#include "gkiu-dbus-object.h"

/**
 * SECTION: gkiu-dbus-object
 * @Short_description: The shell object used in D-Bus communication.
 * @Title: GKiu D-Bus Object
 * @Include: gkiu-dbus-object.h
 * 
 * The shell object used in D-Bus communication.
 */

G_DEFINE_TYPE (GKiuDBusObject, gkiu_dbus_object, GKIU_TYPE_DBUS_OBJECT)

static void 
gkiu_dbus_object_init (GKiuDBusObject *obj)
{
}

static void
gkiu_dbus_object_class_init (GKiuDBusObjectClass *klass)
{
}

gboolean gkiu_dbus_object_call_function (GKiuDBusObject *obj, 
                                         const gchar *module,
                                         const gchar *function,
                                         gpointer data1,
                                         gpointer data2,
                                         gpointer data3,
                                         gpointer data4,
                                         GError **err)
{
    return manager_call_function (module, function, 
                                  data1, data2, 
                                  data3, data4);
}

