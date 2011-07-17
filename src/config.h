/*
 * GKiu
 * Copyright (C) 2011 GQQ Team
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
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <limits.h>

char    CFG_DIR[PATH_MAX];
char    CFG_KEY_FILE[PATH_MAX];

enum CFG_CHECK_MODE
{
    CFG_OK,                /* group and key can both be found */
    CFG_GROUP_NOT_FOUND,   /* can't find group (so you can't find key) */
    CFG_KEY_NOT_FOUND      /* can't find key, but group can be found */
};

void    cfg_init     (void);

enum CFG_CHECK_MODE cfg_check    (const char *group, const char *key);

gchar  **cfg_get_strv (const char *group, const char *key, gsize *lenght);
gboolean cfg_get_int  (const char *group, const char *key, int *pint);

void     cfg_set_strv (const char *group, const char *key, const char **strv, gsize lenght);
void     cfg_set_int  (const char *group, const char *key, int i);

void     cfg_save     (void);
void     cfg_free     (void);

#endif /* __CONFIG_H__ */
