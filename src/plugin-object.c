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

/**
 * SECTION: plugin-object
 * @short_description: A wrapper for plug-ins.
 * @see_also: #manager
 * @stability: Development
 * 
 * A wrapper for plug-ins. 
 * That provide a interface to call interfaces in other plug-ins.
 */

#include "plugin-object.h"
#include "manager.h"

#define GKIU_PLUGIN_GET_PRIVATE(o) (G_TYPE_INSTANCE_GET_PRIVATE((o), GKIU_PLUGIN_TYPE, GkiuPluginPrivate))

struct _GkiuPluginPrivate
{
    PeasEngine *engine;
};

G_DEFINE_TYPE (GkiuPlugin, gkiu_plugin, G_TYPE_OBJECT);

static void
gkiu_plugin_dispose (GObject *gobject)
{
    //GkiuPlugin *self = GKIU_PLUGIN (gobject);

    /* in dispose, unref all the gobject class */
    G_OBJECT_CLASS (gkiu_plugin_parent_class)->dispose (gobject);
}

static void
gkiu_plugin_finalize (GObject *gobject)
{
    /* in finalize, free all the data */
    //GkiuPlugin *self = GKIU_PLUGIN (gobject);

    G_OBJECT_CLASS (gkiu_plugin_parent_class)->finalize (gobject);
}


static void
gkiu_plugin_init (GkiuPlugin *self)
{
    /* set priv pointer of self if there is a priv struct for GkiuPlugin. */
    self->priv = GKIU_PLUGIN_GET_PRIVATE (self);

    self->priv->engine = get_engine ();
    self->call_plugin  = manager_call_function;

    if (self->call_plugin("keyring","keyring_delpwd", "test") == FALSE)
        g_print ("hai shi shi bai le...");
    else
        g_print ("pass...\n");

    /* initialize*/
}

static void
gkiu_plugin_class_init (GkiuPluginClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

    gobject_class->dispose = gkiu_plugin_dispose;
    gobject_class->finalize = gkiu_plugin_finalize;

    /* set set_property & get_property function pointers
       and install defualt property */
}
