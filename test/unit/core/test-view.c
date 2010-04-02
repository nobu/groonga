/* -*- c-basic-offset: 2; coding: utf-8 -*- */
/*
  Copyright (C) 2010  Kouhei Sutou <kou@clear-code.com>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License version 2.1 as published by the Free Software Foundation.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <gcutter.h>
#include <glib/gstdio.h>

#include "../lib/grn-assertions.h"

void data_create(void);
void test_create(gconstpointer data);

static grn_logger_info *logger;
static grn_ctx context;
static grn_obj *database, *view;

static gchar *tmp_directory;
static gchar *database_path;

void
cut_startup(void)
{
  tmp_directory = g_build_filename(grn_test_get_base_dir(),
                                   "tmp",
                                   "test-database",
                                   NULL);
  database_path = g_build_filename(tmp_directory, "database.groonga", NULL);
}

void
cut_shutdown(void)
{
  g_free(database_path);
  g_free(tmp_directory);
}

static void
remove_tmp_directory(void)
{
  cut_remove_path(tmp_directory, NULL);
}

void
cut_setup(void)
{
  view = NULL;

  logger = setup_grn_logger();
  grn_ctx_init(&context, 0);

  remove_tmp_directory();
  g_mkdir_with_parents(tmp_directory, 0700);

  database = grn_db_create(&context, database_path, NULL);
  grn_test_assert_context(&context);
}

void
cut_teardown(void)
{
  if (view) {
    grn_obj_unlink(&context, view);
  }

  if (database) {
    grn_obj_unlink(&context, database);
  }

  grn_ctx_fin(&context);
  teardown_grn_logger(logger);

  remove_tmp_directory();
}

void
data_create(void)
{
#define ADD_DATA(label, name, path)             \
  gcut_add_datum(label,                         \
                 "name", G_TYPE_STRING, name,   \
                 "path", G_TYPE_STRING, path,   \
                 NULL)

  ADD_DATA("anonymous", NULL, NULL);
  ADD_DATA("named", "Entries", NULL);
  ADD_DATA("named - explicit path", "Entries",
           cut_build_path(tmp_directory, "view.db", NULL));

#undef ADD_DATA
}

void
test_create(gconstpointer data)
{
  const gchar *name, *path;
  grn_obj_flags flags = GRN_OBJ_TABLE_VIEW;

  name = gcut_data_get_string(data, "name");
  path = gcut_data_get_string(data, "path");

  if (name || path) {
    flags |= GRN_OBJ_PERSISTENT;
  }

  view = grn_table_create(&context,
                          name, name ? strlen(name) : 0,
                          path,
                          flags,
                          NULL, NULL);
  grn_test_assert_not_null(&context, view);
}