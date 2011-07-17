/*
 * GKiu
 *
 * Copyright (C) GQQ Team
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
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <glib.h>
#include <glib/gi18n.h>
#include <glib/gstdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include "config.h"
#include "../config.h"

static GKeyFile *config = NULL;

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
    sprintf (CFG_DIR, "%s/.%s", g_get_home_dir (),PACKAGE_NAME);
    sprintf (CFG_KEY_FILE, "%s/%s", CFG_DIR, "config.ini");
    
    /* mkdir */
    if (g_mkdir (CFG_DIR, 0777))
    {
        if (errno != EEXIST)
            g_error (_("Couldn't make directory to save configurations: %s"), strerror (errno));
        else errno = 0;
    }

    /* test key file & create */
    int fd = open (CFG_KEY_FILE, O_RDWR|O_CREAT);
    if (!fd)
    {
        g_error (_("Couldn't create key file: %s"), strerror (errno));
        exit (EXIT_FAILURE);
    }
    struct stat buf;
    fstat (fd, &buf);
    if (buf.st_size == 0)
    {
        lseek (fd, 0L, SEEK_SET);
        write (fd, "#\n", 2);/* it's really 2 */
    }
    close (fd);

    /* open key file */
    config = g_key_file_new ();
    GError *err = NULL;
    if (!g_key_file_load_from_file (config, CFG_KEY_FILE, G_KEY_FILE_NONE, &err))
    {
        g_error (_("Couldn't load configurations file!"));
        exit (EXIT_FAILURE);
    }
}

/**
 * cfg_check:
 * @group: a group
 * @key: a key
 *
 * Check if group or key can be found.
 *
 * Return Value: CFG_OK is returned if group and key can be found,
 *               CFG_KEY_NOT_FOUND is returned if key can't be found,
 *               CFG_GROUP_NOT_FOUND is returned if group can't be found.
 */
enum CFG_CHECK_MODE
cfg_check (const gchar *group, 
           const gchar *key)
{
    if (!g_key_file_has_group (config, group))
        return CFG_GROUP_NOT_FOUND;
    if (!g_key_file_has_key (config, group, key, NULL))
        return CFG_KEY_NOT_FOUND;
    return CFG_OK;
}

/**
 * cfg_get_int:
 * @group: a group
 * @key: a key
 * @pint: a pointer to integer
 *
 * get a integer.
 *
 * Since: 2.9.9
 */
gboolean 
cfg_get_int (const char *group,
             const char *key,
             int        *pint)
{
    if (cfg_check (group, key) != CFG_OK)
        return FALSE;

    *pint = g_key_file_get_integer (config, group, key, NULL);

    return TRUE;
}

/**
 * cfg_get_strv:
 * @group: a group
 * @key: a key
 * @lenght: a pointer to get the number of strings
 *
 * Get a list of strings in a key.
 *
 * Return Value: a NULL-terminated string array 
 *               or NULL if key can't be found.
 */
gchar **
cfg_get_strv (const char *group,
              const char *key,
              gsize      *lenght)
{
    if (cfg_check (group, key) != CFG_OK)
        return NULL;
    return g_key_file_get_string_list (config, group, key, lenght, NULL);
}

/**
 * cfg_set_int:
 * @group: a group
 * @key: a key
 * @i: a integer number
 *
 * Set a integer for key.
 *
 * Since: 2.9.9
 */
void
cfg_set_int (const char *group,
             const char *key,
             int i)
{
    g_key_file_set_integer (config, group, key, i);
}

/**
 * cfg_set_strv:
 * @group_name: a group
 * @key: a key
 * @list: a array that contain strings.
 * @lenght: the number of strings.
 *
 * Set a string list for key.
 * 
 * Since: 2.9.9
 */
void
cfg_set_strv (const gchar *group_name,
              const gchar *key,
              const gchar **list,
              gsize lenght)
{
    g_key_file_set_string_list (config, group_name, key, list, lenght);
}

/**
 * cfg_save:
 *
 * Save the configurations.
 *
 * Since: 2.9.9
 */
void
cfg_save ()
{
    gsize len;
    const gchar *p = g_key_file_to_data (config, &len, NULL);

    FILE *fp = fopen (CFG_KEY_FILE, "w+");
    if (!fp)
    {
        g_warning (_("Couldn't save configurations."));
        return;
    }
    fwrite (p, len, 1, fp);
    fclose (fp);
}

/**
 * cfg_free:
 *
 * close key file.
 *
 * Since: 2.9.9
 */
void
cfg_free ()
{
    g_key_file_free (config);
}

