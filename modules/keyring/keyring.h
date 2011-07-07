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


#ifndef GKMOD_KEYRING_H
#define GKMOD_KEYRING_H

#define KEYRING_NAME "GKiu_Password"

G_BEGIN_DECLS

#define GKMOD_TYPE_KEYRING         (gkmod_keyring_get_type ())
#define GKMOD_KEYRING(o)           (G_TYPE_CHECK_INSTANCE_CAST ((o), GKMOD_TYPE_KEYRING, GkmodKeyring))
#define GKMOD_KEYRING_CLASS(k)     (G_TYPE_CHECK_CLASS_CAST((k), GKMOD_TYPE_KEYRING, GkmodKeyringClass))
#define GKMOD_IS_KEYRING(o)        (G_TYPE_CHECK_INSTANCE_TYPE ((o), GKMOD_TYPE_KEYRING))
#define GKMOD_IS_KEYRING_CLASS(k)  (G_TYPE_CHECK_CLASS_TYPE ((k), GKMOD_TYPE_KEYRING))
#define GKMOD_KEYRING_GET_CLASS(o) (G_TYPE_INSTANCE_GET_CLASS ((o), GKMOD_TYPE_KEYRING, GkmodKeyringClass))

typedef struct _GkmodKeyring       GkmodKeyring;
typedef struct _GkmodKeyringClass  GkmodKeyringClass;

/* Based on PeasExtensionBase */
struct _GkmodKeyring {
    PeasExtensionBase parent_instance;
};

struct _GkmodKeyringClass {
    PeasExtensionBaseClass parent_class;
};


GType                 gkmod_keyring_get_type        (void) G_GNUC_CONST;
G_MODULE_EXPORT void  peas_register_types                         (PeasObjectModule *module);

G_END_DECLS

void keyring_savepwd (const char *usr, const char *pwd);
void keyring_findpwd (const char *usr, char **pwd_buf);
void keyring_delpwd (const char *usr);

#endif /* GKMOD_KEYRING_H */
