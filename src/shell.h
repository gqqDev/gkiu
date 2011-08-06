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

#ifndef SHELL_H
#define SHELL_H

G_BEGIN_DECLS

typedef struct _GKiuShell GKiuShell;
typedef struct _GKiuShellClass GKiuShellClass;

struct _GKiuShell
{
    GObject parent;
};

struct _GKiuShellClass
{
    GObjectClass parent;
};

#define GKIU_TYPE_SHELL (gkiu_shell_get_type())

GType    gkiu_shell_get_type      (void);
gboolean gkiu_shell_call_function (GKiuShell *shell, 
                                   const gchar *module, 
                                   const gchar *name, 
                                   gpointer data1,
                                   gpointer data2,
                                   gpointer data3,
                                   gpointer data4,
                                   GError **err);

#endif /* GKIU_DBUS_OBJECT_H */
