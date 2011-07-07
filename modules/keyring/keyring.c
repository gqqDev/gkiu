/*
 *
 * keyring.c
 *
 * Copyright (C) 2011 - GQQ Team
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

#include <string.h>

#include <glib.h>
#include <glib-object.h>
#include <glib/gi18n.h>

#include <gnome-keyring.h>

#include <libpeas/peas.h>

#include "keyring.h"

static void peas_activatable_iface_init (PeasActivatableInterface *);

G_DEFINE_DYNAMIC_TYPE_EXTENDED (GkmodKeyring,
                                gkmod_keyring,
                                PEAS_TYPE_EXTENSION_BASE,
                                0,
                                G_IMPLEMENT_INTERFACE_DYNAMIC (PEAS_TYPE_ACTIVATABLE,
                                                               peas_activatable_iface_init))

G_MODULE_EXPORT void
peas_register_types (PeasObjectModule *module)
{
    gkmod_keyring_register_type (G_TYPE_MODULE (module));
    
    peas_object_module_register_extension_type (module,
                                                PEAS_TYPE_ACTIVATABLE,
                                                GKMOD_TYPE_KEYRING);
}

static void
gkmod_keyring_class_init (GkmodKeyringClass *klass)
{
}

static void
gkmod_keyring_class_finalize (GkmodKeyringClass *klass)
{
}


static void
gkmod_keyring_init (GkmodKeyring *plugin)
{
    g_debug (G_STRFUNC);
}


static void
gkmod_keyring_activate (PeasActivatable *activatable)
{
    GkmodKeyring *plugin = GKMOD_KEYRING (activatable);
    g_debug (G_STRFUNC);
}

static void
gkmod_keyring_deactivate (PeasActivatable *activatable)
{
    GkmodKeyring *plugin = GKMOD_KEYRING (activatable);
    g_debug (G_STRFUNC);
}

static void
peas_activatable_iface_init (PeasActivatableInterface *iface)
{
    iface->activate = gkmod_keyring_activate;
    iface->deactivate = gkmod_keyring_deactivate;
}


/**
   keyring_savepwd:
   @usr: user name.
   @pwd: the password of the user.
   Save a password to default keyring.
 */
static void
save_callback (GnomeKeyringResult result,
               gpointer data)
{
	if (result != GNOME_KEYRING_RESULT_OK)
		g_warning (_("Couldn't save the password. %s"),
		           gnome_keyring_result_to_message (result));
}
void 
keyring_savepwd (const char *usr, 
                 const char *pwd)
{
	GString *des = g_string_new ("");
	g_string_sprintf (des, "GKiu_%s", usr);
	gnome_keyring_store_password (GNOME_KEYRING_NETWORK_PASSWORD,
	                              GNOME_KEYRING_DEFAULT,
	                              des->str, pwd, 
	                              &save_callback,
	                              NULL/*user data*/, NULL /*destory modify*/,
	                              /* User attributes */
	                              "user", usr,
	                              "server", "gkiu",
	                              NULL); /* End with NULL */
	g_string_free (des, TRUE);
}

/**
   keyring_findpwd:
   @usr: username.
   @pwd_buf: password buffer for getting password.
   Find the password of a user
 */
void
keyring_findpwd (const char *usr, 
                 char **pwd_buf)
{
	gnome_keyring_find_password_sync (GNOME_KEYRING_NETWORK_PASSWORD,
	                                  pwd_buf, 
	                                  "user", usr, 
	                                  "server", "gkiu",
	                                  NULL);
}

/**
   keyring_delpwd:
   @usr: the username
   Delete a password from default keyring
 */
void 
keyring_delpwd (const char *usr)
{
	int ret =
	gnome_keyring_delete_password_sync (GNOME_KEYRING_NETWORK_PASSWORD,
	                                    "user", usr,
	                                    "server", "gkiu",
	                                    NULL);
	if (ret != GNOME_KEYRING_RESULT_OK)
	{
		g_warning (_("Couldn't delete the password. %s"),
		           gnome_keyring_result_to_message (ret));
	}
}
