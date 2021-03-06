/* -*- c-basic-offset: 2; coding: utf-8 -*- */
/*
  Copyright (C) 2009  Kouhei Sutou <kou@clear-code.com>

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

#include <db.h>

#include <gcutter.h>
#include <glib/gstdio.h>

#include "../lib/grn-assertions.h"

void data_text_to_bool(void);
void test_text_to_bool(gconstpointer data);
void test_text_to_int8(void);
void test_text_to_uint8(void);
void test_text_to_int16(void);
void test_text_to_uint16(void);
void test_text_to_int32(void);
void test_text_to_uint32(void);
void test_text_to_int64(void);
void test_text_to_uint64(void);
void test_text_to_float(void);
void test_text_to_time(void);

void data_text_error(void);
void test_text_error(gconstpointer data);

void data_int32_to_bool(void);
void test_int32_to_bool(gconstpointer data);
void test_int32_to_int8(void);
void test_int32_to_uint8(void);
void test_int32_to_int16(void);
void test_int32_to_uint16(void);
void test_int32_to_int32(void);
void test_int32_to_uint32(void);
void test_int32_to_int64(void);
void test_int32_to_uint64(void);
void test_int32_to_float(void);
void test_int32_to_time(void);

void data_uint32_to_bool(void);
void test_uint32_to_bool(gconstpointer data);
void test_uint32_to_int8(void);
void test_uint32_to_uint8(void);
void test_uint32_to_int16(void);
void test_uint32_to_uint16(void);
void test_uint32_to_int32(void);
void test_uint32_to_uint32(void);
void test_uint32_to_int64(void);
void test_uint32_to_uint64(void);
void test_uint32_to_float(void);
void test_uint32_to_time(void);

void data_int64_to_bool(void);
void test_int64_to_bool(gconstpointer data);
void test_int64_to_int8(void);
void test_int64_to_uint8(void);
void test_int64_to_int16(void);
void test_int64_to_uint16(void);
void test_int64_to_int32(void);
void test_int64_to_uint32(void);
void test_int64_to_int64(void);
void test_int64_to_uint64(void);
void test_int64_to_float(void);
void test_int64_to_time(void);

void data_uint64_to_bool(void);
void test_uint64_to_bool(gconstpointer data);
void test_uint64_to_int8(void);
void test_uint64_to_uint8(void);
void test_uint64_to_int16(void);
void test_uint64_to_uint16(void);
void test_uint64_to_int32(void);
void test_uint64_to_uint32(void);
void test_uint64_to_int64(void);
void test_uint64_to_uint64(void);
void test_uint64_to_float(void);
void test_uint64_to_time(void);

static grn_logger_info *logger;
static grn_ctx context;
static grn_obj src, dest;

void
cut_setup(void)
{
  logger = setup_grn_logger();
  grn_ctx_init(&context, 0);
  GRN_VOID_INIT(&src);
  GRN_VOID_INIT(&dest);
}

void
cut_teardown(void)
{
  grn_obj_remove(&context, &src);
  grn_obj_remove(&context, &dest);
  grn_ctx_fin(&context);
  teardown_grn_logger(logger);
}

static void
cast_text(const gchar *text)
{
  grn_obj_reinit(&context, &src, GRN_DB_TEXT, 0);
  if (text) {
    GRN_TEXT_PUTS(&context, &src, text);
  }
  grn_test_assert(grn_obj_cast(&context, &src, &dest, GRN_FALSE));
}

void
data_text_to_bool(void)
{
#define ADD_DATA(label, expected, text)                 \
  gcut_add_datum(label,                                 \
                 "expected", G_TYPE_UINT, expected,     \
                 "text", G_TYPE_STRING, text,           \
                 NULL)

  ADD_DATA("empty", GRN_FALSE, "");
  ADD_DATA("NULL", GRN_FALSE, NULL);
  ADD_DATA("true", GRN_TRUE, "true");
  ADD_DATA("false", GRN_TRUE, "false");

#undef ADD_DATA
}

void
test_text_to_bool(gconstpointer data)
{
  grn_obj_reinit(&context, &dest, GRN_DB_BOOL, 0);
  cast_text(gcut_data_get_string(data, "text"));
  cut_assert_equal_boolean(gcut_data_get_uint(data, "expected"),
                           GRN_BOOL_VALUE(&dest));
}

void
test_text_to_int8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT8, 0);
  cast_text("-29");
  cut_assert_equal_int(-29, GRN_INT8_VALUE(&dest));
}

void
test_text_to_uint8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT8, 0);
  cast_text("29");
  cut_assert_equal_uint(29, GRN_UINT8_VALUE(&dest));
}

void
test_text_to_int16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT16, 0);
  cast_text("-2929");
  cut_assert_equal_int(-2929, GRN_INT16_VALUE(&dest));
}

void
test_text_to_uint16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT16, 0);
  cast_text("2929");
  cut_assert_equal_uint(2929, GRN_UINT16_VALUE(&dest));
}

void
test_text_to_int32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT32, 0);
  cast_text("-29292929");
  cut_assert_equal_int(-29292929, GRN_INT32_VALUE(&dest));
}

void
test_text_to_uint32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT32, 0);
  cast_text("29292929");
  cut_assert_equal_uint(29292929, GRN_UINT32_VALUE(&dest));
}

void
test_text_to_int64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT64, 0);
  cast_text("-2929292929292929");
  gcut_assert_equal_int64(G_GINT64_CONSTANT(-2929292929292929),
                          GRN_INT64_VALUE(&dest));
}

void
test_text_to_uint64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT64, 0);
  cast_text("2929292929292929");
  gcut_assert_equal_uint64(G_GUINT64_CONSTANT(2929292929292929),
                           GRN_UINT64_VALUE(&dest));
}

void
test_text_to_float(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_FLOAT, 0);
  cast_text("29.029");
  cut_assert_equal_double(29.029, 0.001, GRN_FLOAT_VALUE(&dest));
}

void
test_text_to_time(void)
{
  long long int sec, usec;

  grn_obj_reinit(&context, &dest, GRN_DB_TIME, 0);
  cast_text("2009/11/24 05:52:10.02929");
  GRN_TIME_UNPACK(GRN_TIME_VALUE(&dest), sec, usec);
  cut_assert_equal_int(1259009530, sec);
  cut_assert_equal_int(29290, usec);
}

void
data_text_error(void)
{
#define ADD_DATA(label, expected, type, text)           \
  gcut_add_datum(label,                                 \
                 "expected", G_TYPE_UINT, expected,     \
                 "type", G_TYPE_UINT, type,             \
                 "text", G_TYPE_STRING, text,           \
                 NULL)

  ADD_DATA("not numeric", GRN_INVALID_ARGUMENT, GRN_DB_INT32, "not-numeric");

#undef ADD_DATA
}

void
test_text_error(gconstpointer data)
{
  grn_obj_reinit(&context, &dest, gcut_data_get_uint(data, "type"), 0);
  grn_obj_reinit(&context, &src, GRN_DB_TEXT, 0);
  GRN_TEXT_PUTS(&context, &src, gcut_data_get_string(data, "text"));
  grn_test_assert_equal_rc(gcut_data_get_uint(data, "expected"),
                           grn_obj_cast(&context, &src, &dest, GRN_FALSE));
}

static void
cast_int32(gint32 number)
{
  grn_obj_reinit(&context, &src, GRN_DB_INT32, 0);
  GRN_INT32_SET(&context, &src, number);
  grn_test_assert(grn_obj_cast(&context, &src, &dest, GRN_FALSE));
}

void
data_int32_to_bool(void)
{
#define ADD_DATA(label, expected, number)               \
  gcut_add_datum(label,                                 \
                 "expected", G_TYPE_UINT, expected,     \
                 "number", G_TYPE_INT, number,          \
                 NULL)

  ADD_DATA("true", GRN_TRUE, 1);
  ADD_DATA("false", GRN_FALSE, 0);
  ADD_DATA("not zero", GRN_TRUE, 100);

#undef ADD_DATA
}

void
test_int32_to_bool(gconstpointer data)
{
  grn_obj_reinit(&context, &dest, GRN_DB_BOOL, 0);
  cast_int32(gcut_data_get_int(data, "number"));
  cut_assert_equal_boolean(gcut_data_get_uint(data, "expected"),
                           GRN_BOOL_VALUE(&dest));
}

void
test_int32_to_int8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT8, 0);
  cast_int32(-29);
  cut_assert_equal_int(-29, GRN_INT8_VALUE(&dest));
}

void
test_int32_to_uint8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT8, 0);
  cast_int32(29);
  cut_assert_equal_uint(29, GRN_UINT8_VALUE(&dest));
}

void
test_int32_to_int16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT16, 0);
  cast_int32(-2929);
  cut_assert_equal_int(-2929, GRN_INT16_VALUE(&dest));
}

void
test_int32_to_uint16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT16, 0);
  cast_int32(2929);
  cut_assert_equal_uint(2929, GRN_UINT16_VALUE(&dest));
}

void
test_int32_to_int32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT32, 0);
  cast_int32(-29292929);
  cut_assert_equal_int(-29292929, GRN_INT32_VALUE(&dest));
}

void
test_int32_to_uint32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT32, 0);
  cast_int32(29292929);
  cut_assert_equal_uint(29292929, GRN_UINT32_VALUE(&dest));
}

void
test_int32_to_int64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT64, 0);
  cast_int32(-29292929);
  gcut_assert_equal_int64(G_GINT64_CONSTANT(-29292929),
                          GRN_INT64_VALUE(&dest));
}

void
test_int32_to_uint64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT64, 0);
  cast_int32(29292929);
  gcut_assert_equal_uint64(G_GUINT64_CONSTANT(29292929),
                           GRN_UINT64_VALUE(&dest));
}

void
test_int32_to_float(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_FLOAT, 0);
  cast_int32(29);
  cut_assert_equal_double(29, 0.1, GRN_FLOAT_VALUE(&dest));
}

void
test_int32_to_time(void)
{
  long long int sec, usec;

  grn_obj_reinit(&context, &dest, GRN_DB_TIME, 0);
  cast_int32(1259009530);
  GRN_TIME_UNPACK(GRN_TIME_VALUE(&dest), sec, usec);
  cut_assert_equal_int(1259009530, sec);
  cut_assert_equal_int(0, usec);
}

void
test_int32_to_text(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_TEXT, 0);
  cast_int32(2929);
  cut_assert_equal_string("2929", GRN_TEXT_VALUE(&dest));
}

static void
cast_uint32(guint32 number)
{
  grn_obj_reinit(&context, &src, GRN_DB_UINT32, 0);
  GRN_UINT32_SET(&context, &src, number);
  grn_test_assert(grn_obj_cast(&context, &src, &dest, GRN_FALSE));
}

void
data_uint32_to_bool(void)
{
#define ADD_DATA(label, expected, number)               \
  gcut_add_datum(label,                                 \
                 "expected", G_TYPE_UINT, expected,     \
                 "number", G_TYPE_UINT, number,         \
                 NULL)

  ADD_DATA("true", GRN_TRUE, 1);
  ADD_DATA("false", GRN_FALSE, 0);
  ADD_DATA("not zero", GRN_TRUE, 100);

#undef ADD_DATA
}

void
test_uint32_to_bool(gconstpointer data)
{
  grn_obj_reinit(&context, &dest, GRN_DB_BOOL, 0);
  cast_uint32(gcut_data_get_uint(data, "number"));
  cut_assert_equal_boolean(gcut_data_get_uint(data, "expected"),
                           GRN_BOOL_VALUE(&dest));
}

void
test_uint32_to_int8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT8, 0);
  cast_uint32(29);
  cut_assert_equal_int(29, GRN_UINT8_VALUE(&dest));
}

void
test_uint32_to_uint8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT8, 0);
  cast_uint32(29);
  cut_assert_equal_uint(29, GRN_UINT8_VALUE(&dest));
}

void
test_uint32_to_int16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT16, 0);
  cast_uint32(2929);
  cut_assert_equal_int(2929, GRN_UINT16_VALUE(&dest));
}

void
test_uint32_to_uint16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT16, 0);
  cast_uint32(2929);
  cut_assert_equal_uint(2929, GRN_UINT16_VALUE(&dest));
}

void
test_uint32_to_int32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT32, 0);
  cast_uint32(29292929);
  cut_assert_equal_int(29292929, GRN_INT32_VALUE(&dest));
}

void
test_uint32_to_uint32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT32, 0);
  cast_uint32(29292929);
  cut_assert_equal_uint(29292929, GRN_UINT32_VALUE(&dest));
}

void
test_uint32_to_int64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT64, 0);
  cast_uint32(29292929);
  gcut_assert_equal_int64(G_GINT64_CONSTANT(29292929),
                          GRN_INT64_VALUE(&dest));
}

void
test_uint32_to_uint64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT64, 0);
  cast_uint32(29292929);
  gcut_assert_equal_uint64(G_GUINT64_CONSTANT(29292929),
                           GRN_UINT64_VALUE(&dest));
}

void
test_uint32_to_float(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_FLOAT, 0);
  cast_uint32(29);
  cut_assert_equal_double(29, 0.1, GRN_FLOAT_VALUE(&dest));
}

void
test_uint32_to_time(void)
{
  long long int sec, usec;

  grn_obj_reinit(&context, &dest, GRN_DB_TIME, 0);
  cast_uint32(1259009530);
  GRN_TIME_UNPACK(GRN_TIME_VALUE(&dest), sec, usec);
  cut_assert_equal_int(1259009530, sec);
  cut_assert_equal_int(0, usec);
}

void
test_uint32_to_text(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_TEXT, 0);
  cast_uint32(2929);
  cut_assert_equal_string("2929", GRN_TEXT_VALUE(&dest));
}

static void
cast_int64(gint64 number)
{
  grn_obj_reinit(&context, &src, GRN_DB_INT64, 0);
  GRN_INT64_SET(&context, &src, number);
  grn_test_assert(grn_obj_cast(&context, &src, &dest, GRN_FALSE));
}

void
data_int64_to_bool(void)
{
#define ADD_DATA(label, expected, number)               \
  gcut_add_datum(label,                                 \
                 "expected", G_TYPE_UINT, expected,     \
                 "number", G_TYPE_INT, number,          \
                 NULL)

  ADD_DATA("true", GRN_TRUE, 1);
  ADD_DATA("false", GRN_FALSE, 0);
  ADD_DATA("not zero", GRN_TRUE, 100);

#undef ADD_DATA
}

void
test_int64_to_bool(gconstpointer data)
{
  grn_obj_reinit(&context, &dest, GRN_DB_BOOL, 0);
  cast_int64(gcut_data_get_int(data, "number"));
  cut_assert_equal_boolean(gcut_data_get_uint(data, "expected"),
                           GRN_BOOL_VALUE(&dest));
}

void
test_int64_to_int8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT8, 0);
  cast_int64(-29);
  cut_assert_equal_int(-29, GRN_INT8_VALUE(&dest));
}

void
test_int64_to_uint8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT8, 0);
  cast_int64(29);
  cut_assert_equal_uint(29, GRN_UINT8_VALUE(&dest));
}

void
test_int64_to_int16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT16, 0);
  cast_int64(-2929);
  cut_assert_equal_int(-2929, GRN_INT16_VALUE(&dest));
}

void
test_int64_to_uint16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT16, 0);
  cast_int64(2929);
  cut_assert_equal_uint(2929, GRN_UINT16_VALUE(&dest));
}

void
test_int64_to_int32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT32, 0);
  cast_int64(-29292929);
  cut_assert_equal_int(-29292929, GRN_INT32_VALUE(&dest));
}

void
test_int64_to_uint32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT32, 0);
  cast_int64(29292929);
  cut_assert_equal_uint(29292929, GRN_UINT32_VALUE(&dest));
}

void
test_int64_to_int64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT64, 0);
  cast_int64(-29292929);
  gcut_assert_equal_int64(G_GINT64_CONSTANT(-29292929),
                          GRN_INT64_VALUE(&dest));
}

void
test_int64_to_uint64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT64, 0);
  cast_int64(G_GINT64_CONSTANT(2929292929));
  gcut_assert_equal_uint64(G_GUINT64_CONSTANT(2929292929),
                           GRN_UINT64_VALUE(&dest));
}

void
test_int64_to_float(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_FLOAT, 0);
  cast_int64(29);
  cut_assert_equal_double(29, 0.1, GRN_FLOAT_VALUE(&dest));
}

void
test_int64_to_time(void)
{
  long long int sec, usec;

  grn_obj_reinit(&context, &dest, GRN_DB_TIME, 0);
  cast_int64(1259009530);
  GRN_TIME_UNPACK(GRN_TIME_VALUE(&dest), sec, usec);
  cut_assert_equal_int(1259009530, sec);
  cut_assert_equal_int(0, usec);
}

void
test_int64_to_text(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_TEXT, 0);
  cast_int64(2929);
  cut_assert_equal_string("2929", GRN_TEXT_VALUE(&dest));
}

static void
cast_uint64(guint64 number)
{
  grn_obj_reinit(&context, &src, GRN_DB_UINT64, 0);
  GRN_UINT64_SET(&context, &src, number);
  grn_test_assert(grn_obj_cast(&context, &src, &dest, GRN_FALSE));
}

void
data_uint64_to_bool(void)
{
#define ADD_DATA(label, expected, number)               \
  gcut_add_datum(label,                                 \
                 "expected", G_TYPE_UINT, expected,     \
                 "number", G_TYPE_UINT, number,         \
                 NULL)

  ADD_DATA("true", GRN_TRUE, 1);
  ADD_DATA("false", GRN_FALSE, 0);
  ADD_DATA("not zero", GRN_TRUE, 100);

#undef ADD_DATA
}

void
test_uint64_to_bool(gconstpointer data)
{
  grn_obj_reinit(&context, &dest, GRN_DB_BOOL, 0);
  cast_uint64(gcut_data_get_uint(data, "number"));
  cut_assert_equal_boolean(gcut_data_get_uint(data, "expected"),
                           GRN_BOOL_VALUE(&dest));
}

void
test_uint64_to_int8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT8, 0);
  cast_uint64(29);
  cut_assert_equal_int(29, GRN_UINT8_VALUE(&dest));
}

void
test_uint64_to_uint8(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT8, 0);
  cast_uint64(29);
  cut_assert_equal_uint(29, GRN_UINT8_VALUE(&dest));
}

void
test_uint64_to_int16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT16, 0);
  cast_uint64(2929);
  cut_assert_equal_int(2929, GRN_UINT16_VALUE(&dest));
}

void
test_uint64_to_uint16(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT16, 0);
  cast_uint64(2929);
  cut_assert_equal_uint(2929, GRN_UINT16_VALUE(&dest));
}

void
test_uint64_to_int32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT32, 0);
  cast_uint64(29292929);
  cut_assert_equal_int(29292929, GRN_INT32_VALUE(&dest));
}

void
test_uint64_to_uint32(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT32, 0);
  cast_uint64(29292929);
  cut_assert_equal_uint(29292929, GRN_UINT32_VALUE(&dest));
}

void
test_uint64_to_int64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_INT64, 0);
  cast_uint64(G_GUINT64_CONSTANT(2929292929));
  gcut_assert_equal_int64(G_GINT64_CONSTANT(2929292929),
                          GRN_INT64_VALUE(&dest));
}

void
test_uint64_to_uint64(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_UINT64, 0);
  cast_uint64(G_GUINT64_CONSTANT(2929292929));
  gcut_assert_equal_uint64(G_GUINT64_CONSTANT(2929292929),
                           GRN_UINT64_VALUE(&dest));
}

void
test_uint64_to_float(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_FLOAT, 0);
  cast_uint64(29);
  cut_assert_equal_double(29, 0.1, GRN_FLOAT_VALUE(&dest));
}

void
test_uint64_to_time(void)
{
  long long int sec, usec;

  grn_obj_reinit(&context, &dest, GRN_DB_TIME, 0);
  cast_uint64(1259009530);
  GRN_TIME_UNPACK(GRN_TIME_VALUE(&dest), sec, usec);
  cut_assert_equal_int(1259009530, sec);
  cut_assert_equal_int(0, usec);
}

void
test_uint64_to_text(void)
{
  grn_obj_reinit(&context, &dest, GRN_DB_TEXT, 0);
  cast_uint64(2929);
  cut_assert_equal_string("2929", GRN_TEXT_VALUE(&dest));
}
