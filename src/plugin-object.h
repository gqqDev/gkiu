#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define GKIU_PLUGIN_TYPE            (gkiu_plugin_get_type ())
#define GKIU_PLUGIN(o)              (G_TYPE_CHECK_INSTANCE_CAST ((o), GKIU_PLUGIN_TYPE, GkiuPlugin))
#define GKIU_PLUGIN_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GKIU_PLUGIN_TYPE, GkiuPluginClass))
#define GKIU_IS_PLUGIN(o)           (G_TYPE_CHECK_INSTANCE_TYPE ((o), GKIU_PLUGIN_TYPE))
#define GKIU_IS_PLUGIN_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GKIU_PLUGIN_TYPE))
#define GKIU_GET_PLUGIN_CLASS(o)    (G_TYPE_INSTANCE_GET_CLASS ((o), GKIU_PLUGIN_TYPE, GkiuPluginClass))

typedef struct _GkiuPlugin GkiuPlugin
typedef struct _GkiuPluginClass GkiuPlugin

struct _GkiuPlugin
{
    PeasActivatable parent;
};

struct _GkiuPluginClass
{
    PeasActivatable parent_class;
};

GType gkiu_plugin_get_type (void);

GkiuPlugin *gkiu_plugin_new (void);

G_END_DECLS

