/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * uilogin.c
 * Copyright (C) GQQ Team <gqq@freelists.org>
 * 
 * gkiu is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gkiu is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Login Window UI */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <glib.h>
#include <gtk/gtk.h>

#include "i18n.h"
#include "keyring.h"
#include "config.h"
#include "debug.h"
#include "uilogin.h"

#ifdef DEBUG
#  define UI_FILE "src/uilogin.glade"
#else
#  define UI_FILE PACKAGE_DATA_DIR"/gkiu/ui/uilogin.glade"
#endif


static GtkWidget* window = NULL;	/*GtkWindow*/
GtkWidget* ety_pwd = NULL;		/*GtkEntry*/
GtkWidget* cbb_usr = NULL;		/*GtkComboBoxEntry*/
GtkWidget* chb_svpwd = NULL;		/*GtkCheckButton*/
GtkWidget* chb_apoffline=NULL;  	/*GtkCheckButton*/

/**
   get_usrlist_cb:
   @usr: The user name.
 */
static void
get_usrlist_cb(gchar *usr)
{
	gtk_combo_box_append_text (GTK_COMBO_BOX (cbb_usr), usr);
}

/**
   on_btn_login_clicked: 
   @widget: The widget.
   @data: user data.
   btn_login (signal) clicked callback
 */
static void
on_btn_login_clicked(GtkWidget *widget,
                     gpointer data)
{
	/* Add the current user to list */
	cfg_add_user_to_list (gtk_combo_box_get_active_text (GTK_COMBO_BOX (cbb_usr)));
	
	/* TODO: 这里暂未考虑已存储的密码 */
	gboolean save_pwd = FALSE;
	GString *user = g_string_new (gtk_combo_box_get_active_text (GTK_COMBO_BOX (cbb_usr)));
	
	cfg_chkusrdir (user->str);
	
	save_pwd = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (chb_svpwd));
	if (save_pwd == TRUE)
	{
	  //dbg_print ("DBG: Will save the password.");
		keyring_savepwd (user->str,gtk_entry_get_text (GTK_ENTRY (ety_pwd)));
	}
	/* WILL BE MOVE *//*
	keyring_findpwd (user->str,&pwd);

	keyring_delpwd (user->str);
	g_string_free (user, TRUE);*/
}

/**
   on_btn_cancel_clicked:
   @widget: the widget.
   @data: user data.
   btn_cancel (Signal) clicked callback
 */
static void
on_btn_cancel_clicked(GtkWidget *widget,
                      gpointer data)
{
	_exit(0);
}

/**
   lw_destory:
   @widget: the widget.
   @data: user data.
   login window (Signal) Destroy callback.
 */
static void
lw_destroy(GtkWidget *widget,
           gpointer data)
{
	gtk_main_quit();
}

/**
   lw_create:
   create login window.
   Return value: The widget pointer of login window.
 */
GtkWidget*
lw_create(void)
{
	GtkBuilder *builder;
	GError* error = NULL;

	builder = gtk_builder_new ();
	if (!gtk_builder_add_from_file (builder, UI_FILE, &error))
	{
		g_error (_("Couldn't load builder file: %s"), error->message);
		g_error_free (error);
		_exit(1);
	}

	/* This is important */
	gtk_builder_connect_signals (builder, NULL);
	/* get gtk widget from builder */
	window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
	ety_pwd = GTK_WIDGET (gtk_builder_get_object (builder, "ety_pwd"));
	cbb_usr = GTK_WIDGET (gtk_builder_get_object (builder, "cbb_usr"));
	chb_svpwd=GTK_WIDGET (gtk_builder_get_object (builder, "chb_svpwd"));
	chb_apoffline=GTK_WIDGET (gtk_builder_get_object (builder,"chb_apoffline"));

	/* set up window */
	gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);

	/* set up password entry  */
	gtk_entry_set_visibility (GTK_ENTRY(ety_pwd), FALSE);

	/* set up user combo box */
	GtkListStore *usr_lst = gtk_list_store_new (1, G_TYPE_STRING);
	gtk_combo_box_set_model (GTK_COMBO_BOX (cbb_usr), GTK_TREE_MODEL (usr_lst));
	gtk_combo_box_entry_set_text_column(GTK_COMBO_BOX_ENTRY(cbb_usr), 0); 
	cfg_get_lists_usrlist (&get_usrlist_cb);
	
	g_object_unref (builder);

	//dbg_print("DBG: Login Window is created.");
	return window;
}
