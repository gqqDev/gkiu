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

#ifndef __PLUGIN_OBJECT_H__
#define __PLUGIN_OBJECT_H__

#include <libpeas/peas.h>
#include <glib-object.h>

G_BEGIN_DECLS

#define GKIU_PLUGIN_TYPE            (gkiu_plugin_get_type ())
#define GKIU_PLUGIN(o)              (G_TYPE_CHECK_INSTANCE_CAST ((o), GKIU_PLUGIN_TYPE, GkiuPlugin))
#define GKIU_PLUGIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GKIU_PLUGIN_TYPE, GkiuPluginClass))
#define GKIU_IS_PLUGIN(o)           (G_TYPE_CHECK_INSTANCE_TYPE ((o), GKIU_PLUGIN_TYPE))
#define GKIU_IS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GKIU_PLUGIN_TYPE))
#define GKIU_GET_PLUGIN_CLASS(o)    (G_TYPE_INSTANCE_GET_CLASS ((o), GKIU_PLUGIN_TYPE, GkiuPluginClass))

typedef struct _GkiuPlugin GkiuPlugin;
typedef struct _GkiuPluginClass GkiuPluginClass;
typedef struct _GkiuPluginPrivate GkiuPluginPrivate;

struct _GkiuPlugin
{
    PeasActivatable *parent;

    /*< private >*/
    GkiuPluginPrivate *priv;

    /*< public >*/
    gboolean (*call_plugin)(const char *pname, const char *mname, ...);
};

struct _GkiuPluginClass
{
    PeasActivatable *parent_class;
};

GType gkiu_plugin_get_type (void);

GkiuPlugin *gkiu_plugin_new (void);

G_END_DECLS

#endif /* __PLUGIN_OBJECT_H__ */
