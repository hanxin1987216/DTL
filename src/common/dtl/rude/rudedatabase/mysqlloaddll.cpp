/***************************************************************************************************
mysqlloaddll.cpp:
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	 libmySQL.dll module APIs definition.

Author:
	韩欣 (han.xin@datatom.com)
	
Creating Time:
	2012-03-10
***************************************************************************************************/

#include "../../prec.h"
#include "../../lang/string.h"
#include "../../sys/exception.h"
#include "../../sys/library.h"

#include "mysqlloaddll.h"

static bool is_mysql_load = false;

MYSQL_LIBRARY_INIT mysql_library_init_c = 0;
MYSQL_LIBRARY_END mysql_library_end_c = 0;
MYSQL_INIT mysql_init_c = 0;
MYSQL_SSL_SET mysql_ssl_set_c = 0;
MYSQL_CHANGE_USER mysql_change_user_c = 0;
MYSQL_REAL_CONNECT mysql_real_connect_c = 0;
MYSQL_SELECT_DB mysql_select_db_c = 0;
MYSQL_QUERY mysql_query_c = 0;
MYSQL_LIST_DBS mysql_list_dbs_c = 0;
MYSQL_NUM_ROWS mysql_num_rows_c = 0;
MYSQL_FETCH_ROW mysql_fetch_row_c = 0;
MYSQL_FREE_RESULT mysql_free_result_c = 0;
MYSQL_CLOSE mysql_close_c = 0;
MYSQL_LIST_TABLES mysql_list_tables_c = 0;
MYSQL_NUM_FIELDS mysql_num_fields_c = 0;
MYSQL_FETCH_FIELDS mysql_fetch_fields_c = 0;
MYSQL_STORE_RESULT mysql_store_result_c = 0;
MYSQL_USE_RESULT mysql_use_result_c = 0;
MYSQL_ERROR mysql_error_c = 0;
MYSQL_ESCAPE_STRING  mysql_escape_string_c = 0;
MYSQL_STAT mysql_stat_c = 0;
MYSQL_INSERT_ID mysql_insert_id_c = 0;


static void* g_mysqlInstance = 0;

bool is_load_mysql_module (void)
{
	return is_mysql_load;
}

bool load_mysql_module (void)
{
	if (is_mysql_load == true)
		return true;

	String dllname;

#ifdef __WINDOWS__
	/*dllname = _T("C:/Program Files/MySQL/MySQL Server 5.1/bin/libmySQL.dll");*/
	dllname = _T("libmySQL.dll");
#elif defined __LINUX__ 
	dllname = _T("libmysqlclient.so");
#endif

	try {

		g_mysqlInstance = Library::load (dllname);

		mysql_library_init_c = (MYSQL_LIBRARY_INIT) Library::loadSymbol (g_mysqlInstance, "mysql_server_init");

		mysql_library_end_c = (MYSQL_LIBRARY_END) Library::loadSymbol (g_mysqlInstance, "mysql_server_end");

		mysql_init_c = (MYSQL_INIT) Library::loadSymbol (g_mysqlInstance, "mysql_init");

		mysql_ssl_set_c = (MYSQL_SSL_SET) Library::loadSymbol (g_mysqlInstance, "mysql_ssl_set");

		mysql_change_user_c = (MYSQL_CHANGE_USER) Library::loadSymbol (g_mysqlInstance, "mysql_change_user");

		mysql_real_connect_c = (MYSQL_REAL_CONNECT) Library::loadSymbol (g_mysqlInstance, "mysql_real_connect");

		mysql_select_db_c = (MYSQL_SELECT_DB) Library::loadSymbol (g_mysqlInstance, "mysql_select_db");

		mysql_query_c = (MYSQL_QUERY) Library::loadSymbol (g_mysqlInstance, "mysql_query");

		mysql_list_dbs_c = (MYSQL_LIST_DBS) Library::loadSymbol (g_mysqlInstance, "mysql_list_dbs");

		mysql_num_rows_c = (MYSQL_NUM_ROWS) Library::loadSymbol (g_mysqlInstance, "mysql_num_rows");

		mysql_fetch_row_c = (MYSQL_FETCH_ROW) Library::loadSymbol (g_mysqlInstance, "mysql_fetch_row");

		mysql_free_result_c = (MYSQL_FREE_RESULT) Library::loadSymbol (g_mysqlInstance, "mysql_free_result");

		mysql_close_c = (MYSQL_CLOSE) Library::loadSymbol (g_mysqlInstance, "mysql_close");	

		mysql_list_tables_c = (MYSQL_LIST_TABLES) Library::loadSymbol (g_mysqlInstance, "mysql_list_tables");		
		
		mysql_num_fields_c = (MYSQL_NUM_FIELDS) Library::loadSymbol (g_mysqlInstance, "mysql_num_fields");		

		mysql_fetch_fields_c = (MYSQL_FETCH_FIELDS) Library::loadSymbol (g_mysqlInstance, "mysql_fetch_fields");

		mysql_store_result_c = (MYSQL_STORE_RESULT) Library::loadSymbol (g_mysqlInstance, "mysql_store_result");

		mysql_use_result_c = (MYSQL_USE_RESULT) Library::loadSymbol (g_mysqlInstance, "mysql_use_result");
	
		mysql_error_c = (MYSQL_ERROR) Library::loadSymbol (g_mysqlInstance, "mysql_error");

		mysql_escape_string_c = (MYSQL_ESCAPE_STRING) Library::loadSymbol (g_mysqlInstance, "mysql_escape_string");

		mysql_stat_c = (MYSQL_STAT) Library::loadSymbol (g_mysqlInstance, "mysql_stat");

		mysql_insert_id_c = (MYSQL_INSERT_ID) Library::loadSymbol (g_mysqlInstance, "mysql_insert_id");


		is_mysql_load = true;
		return true;
	}
	catch (Exception &e)
	{
		unload_mysql_module ();
		throw e;
	}
	catch (...) {
		unload_mysql_module ();		
	}

	return is_mysql_load;
}

/**
 * Delete libmySQL module
 */
void unload_mysql_module (void)
{
	if (g_mysqlInstance != NULL)
		Library::unload (g_mysqlInstance);

	is_mysql_load = false;
	g_mysqlInstance = 0;
}