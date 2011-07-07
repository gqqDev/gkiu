/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * chatlog.c
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

#include <time.h>

#include <glib.h>
#include <gdbm.h> /* database */
#include "i18n.h"
#include "config.h"
#include "debug.h"
#include "chatlog.h"

GString *cht_dir=NULL;
GDBM_FILE cht_file;
gboolean success=FALSE;

static GMutex *mutex = NULL;/* lock gdbm object */

/* TODO: 测试这些函数 */

/**
   cht_chkdir:
  
   Looking for current user's chatlog directory.
 */
void
cht_chkdir ()
{
	/* copy */
	cht_dir = g_string_new (cfg_getusrdir()->str);
	g_string_append (cht_dir, "/chatlog");
}

/**
   cht_getdir:
   
   Get current user's chatlog directory.
   
   Return value: The directory in GString pointer.
 */
GString *
cht_getdir ()
{
	return cht_dir;
}

/**
   cht_open:
   @to: The message has sent to. It needed by filename.   
   Open the database.
   Warning: Only #cht_add() can call it. You shouldn't call it.
 */
void 
cht_open (const char *to)
{
	GString *filename=g_string_new ("");
	g_string_printf (filename, "%s/chat_with_%s", cht_dir->str, to);
	if ((cht_file = gdbm_open(filename->str, -1, GDBM_WRCREAT, 0777, NULL)) == NULL)
	{
		g_warning (_("Cannot open database"));
		success = FALSE;
	}

	g_string_free (filename, TRUE);
}

/**
   cht_getdbobj:
   Get database object.
   
   Return Value: A GDBM object.
*/
GDBM_FILE
cht_getdbobj ()
{
	return cht_file;
}


/**
   add_callback_handler:
   @s_data: a dbdb pointer.
   WARNING!! You should not call this by yourself.
 */
static gpointer /* NULL: successful */
add_callback_handler (void *s_data)
{
	struct dbdb *data = (struct dbdb *)s_data;

    g_mutex_lock (mutex); /* LOCK!! If this mutex has been lock, wait for unlock */
	/* write */
	cht_open (data->to);
	if (!success)
	{
		dbg_print("DBG: failed to open chatlog file.");
		return (gpointer) !NULL;
	}
	
	/* if this key already exist, replace it */
	if (gdbm_store (cht_file, data->key, data->context, GDBM_REPLACE))
	{
		dbg_print ("DBG: failed to save message.");
		return (gpointer)!NULL;
	}
	cht_close (FALSE); /* just kill current action. */
	g_mutex_unlock (mutex);

	/* free memory, but not useful. */
	/*g_mutex_free (mutex);
	mutex = NULL;*/
	
	return NULL;
}
/**
   cht_add:
   @from: the writer of this message.
   @to: this message has sent to.
   @msg: the context of this message.
   Add a message to database.
   It'll call #cht_open() and #cht_close(), so you needn't call it by yourself.
*/
void
cht_add (char *from,
		 char *to,
         char *msg)
{
	GString *tmstr = g_string_new ("");
	datum key, context;
	time_t timeval;
	struct tm *tmbuf;
	struct dbdb data;
	
	time (&timeval);
	tmbuf = localtime (&timeval);

	/* format */
	g_string_printf (tmstr, _("Month %d Day %d, %d. %d:%d:%d from %s to %s"), 
					 tmbuf->tm_mon + 1,
					 tmbuf->tm_mday,
					 tmbuf->tm_year + 1900,
					 tmbuf->tm_hour,
					 tmbuf->tm_min,
					 tmbuf->tm_sec,
					 from, to);

	key.dptr = tmstr->str;
	key.dsize = tmstr->len;

	context.dptr = msg;
	context.dsize = strlen (msg);

	g_string_free (tmstr, TRUE);

	/* Thread */
	data.key     = key;
	data.context = context;
	data.from    = from;
	data.to      = to;
   
	if (!mutex) mutex = g_mutex_new ();
	g_thread_create (&add_callback_handler, (void *)&data, FALSE, NULL);
}

/**
   cht_fetchall:
   @callback: if get any message, call it.
   Search all messages.
*/
void 
cht_fetchall(void (*callback)(gchar *info, gchar *msg))
{
	datum key, context;
	key = gdbm_firstkey (cht_file);
	while (key.dptr)
	{
		context = gdbm_fetch(cht_file, key);
		(*callback)(key.dptr, context.dptr);

		key = gdbm_nextkey (cht_file, key);
	}
}

/**
   cht_del:
   @pkey:The string of the key.
   Delete a message from database.
*/
void 
cht_del(gchar *pkey)
{
	struct datum keys;
	g_return_if_fail (pkey != NULL);
	keys.dptr = pkey;
	keys.dptr = strlen (pkey);
	if (gdbm_delete (cht_file, keys))
		dbg_print ("Failed to delete the chatlog entry.");
}

/**
   cht_close:
   @block: if set to TRUE, free all allocated memories, and close database completely, should use if app will end. if set to FALSE, only close database object.
   Close current action and free memory.
*/
void
cht_close (gboolean block)
{
	if (block)
		g_string_free (cht_dir, TRUE);
	if (cht_file)
		gdbm_close (cht_file);
	cht_file = NULL; /* 结束，置0 */
}
