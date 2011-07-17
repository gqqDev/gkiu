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

#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <gtk/gtk.h>

/* Macros */
#define DEV_MODULES_DIR "../modules"

/* Definations */
#define CFG_GRP_MANAGER        "Manager"
#define CFG_KEY_PLUGIN_LIST    "PluginList"
#define CFG_KEY_PLUGIN_LIST_NO "PluginListNumber"

/* Functions */
PeasEngine*   get_engine                   ();
void          manager_init                 (gboolean);
GtkWidget *   manager_show_manager_window  ();
void          manager_refresh_modules_list ();
void          manager_save_modules_list    ();
void          manager_load_modules_in_list ();
gboolean      manager_call_function        (const char*, const char *, ...);

#endif /* __MANAGER_H__ */
