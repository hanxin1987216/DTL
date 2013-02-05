/***************************************************************************************************
mysqlloaddll.h:	
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	libmySQL.dll module APIs definition.

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2012-03-10
***************************************************************************************************/

#ifndef __DTL_DB_MYSQL_LOADDLL_H__
#define __DTL_DB_MYSQL_LOADDLL_H__

#if AB_PRAGMA_ONCE
#pragma once
#endif

#include <mysql.h>

/**
 * Get current status of libmySQL module.
 * @return == true Read already, initiation.
 */
bool is_load_mysql_module (void);

/**
 * Load module of libmySQL, and return the status of libmySQL module.
 */
bool load_mysql_module (void);

/**
 * Delete libmySQL module.
 */
void unload_mysql_module (void);

/**
 * Initialize the MySQL C API library.
 * int STDCALL mysql_server_init(int argc, char **argv, char **groups).
 * #define mysql_library_init mysql_server_init.
 */
typedef int (STDCALL* MYSQL_LIBRARY_INIT) (int argc, char **argv, char **groups);
extern MYSQL_LIBRARY_INIT mysql_library_init_c;

/**
 * Finalize the MySQL C API library.
 * void STDCALL mysql_server_end(void).
 * #define mysql_library_end mysql_server_end.
 */
typedef void (STDCALL* MYSQL_LIBRARY_END) (void);
extern MYSQL_LIBRARY_END my_library_end_c;

/**
 * Gets or initializes a MYSQL structure.
 * MYSQL * STDCALL mysql_init(MYSQL *mysql).
 */
typedef MYSQL * (STDCALL* MYSQL_INIT) (MYSQL *mysql);
extern MYSQL_INIT mysql_init_c;
 
/**
 * Prepare to establish SSL connection to server.
 * my_bool STDCALL mysql_ssl_set(MYSQL *mysql, const char *key
 * 							, const char *cert, const char *ca
 *							, const char *capath, const char *cipher);
 */
typedef my_bool (STDCALL* MYSQL_SSL_SET) (MYSQL *mysql
							  , const char *key
			 				  , const char *cert
							  , const char *ca
							  , const char *capath
							  , const char *cipher);
extern MYSQL_SSL_SET mysql_ssl_set_c;



/**
* escape sql string
*/
typedef unsigned long (STDCALL* MYSQL_ESCAPE_STRING) (char *to,
													  const char *from,
													  unsigned long from_length);
extern MYSQL_ESCAPE_STRING mysql_escape_string_c;




/**
* xxx
*/
typedef const char * (STDCALL* MYSQL_STAT) (MYSQL *mysql);
extern MYSQL_STAT mysql_stat_c;


/**
* 
*/
typedef my_ulonglong (STDCALL* MYSQL_INSERT_ID) (MYSQL *mysql);
extern MYSQL_INSERT_ID mysql_insert_id_c;

/**
 * Changes user and database on an open connection.
 * my_bool STDCALL mysql_change_user(MYSQL *mysql, const char *user
 *								, const char *passwd, const char *db);
 */
typedef my_bool (STDCALL* MYSQL_CHANGE_USER) (MYSQL *mysql
								  , const char *user
								  , const char *passwd
								  , const char *db);
extern MYSQL_CHANGE_USER mysql_change_user_c;

/**
 * Connects to a MySQL server.
 * MYSQL * STDCALL mysql_real_connect(MYSQL *mysql
 *							, const char *host
 *							, const char *user
 *							, const char *passwd
 *							, const char *db
 *							, unsigned int port
 *							, const char *unix_socket
 *							, unsigned long clientflag);
 */
typedef MYSQL * (STDCALL* MYSQL_REAL_CONNECT) (MYSQL *mysql
							   , const char *host
							   , const char *user 
							   , const char *passwd
							   , const char *db
							   , unsigned int port
							   , const char *unix_socket
							   , unsigned long clientflag);
extern MYSQL_REAL_CONNECT mysql_real_connect_c;

/**
 * Selects a database.
 * int STDCALL mysql_select_db(MYSQL *mysql, const char *db).
 */
typedef int (STDCALL* MYSQL_SELECT_DB) (MYSQL *mysql, const char *db);
extern MYSQL_SELECT_DB mysql_select_db_c;

/**
 * Executes an SQL query specified as a null-terminated string.
 * int STDCALL mysql_query(MYSQL *mysql, const char *q).
 */
typedef int (STDCALL* MYSQL_QUERY) (MYSQL *mysql, const char *q);
extern MYSQL_QUERY mysql_query_c;

/**
 * Returns database names matching a simple regular expression.
 * MYSQL_RES *	STDCALL mysql_list_dbs(MYSQL *mysql,const char *wild).
 */
typedef MYSQL_RES * (STDCALL* MYSQL_LIST_DBS) (MYSQL *mysql,const char *wild);
extern MYSQL_LIST_DBS mysql_list_dbs_c;

/**
 * Returns the number of rows in a result set.
 * my_ulonglong STDCALL mysql_num_rows(MYSQL_RES *res).
 */
typedef my_ulonglong (STDCALL* MYSQL_NUM_ROWS) (MYSQL_RES *res);
extern MYSQL_NUM_ROWS mysql_num_rows_c;

/**
 * Fetches the next row from the result set.
 * MYSQL_ROW STDCALL mysql_fetch_row(MYSQL_RES *result).
 */
typedef MYSQL_ROW (STDCALL* MYSQL_FETCH_ROW) (MYSQL_RES *result);
extern MYSQL_FETCH_ROW mysql_fetch_row_c;

/**
 * Frees memory used by a result set.
 * void	STDCALL mysql_free_result(MYSQL_RES *result).
 */
typedef void (STDCALL* MYSQL_FREE_RESULT) (MYSQL_RES *result);
extern MYSQL_FREE_RESULT mysql_free_result_c;

/**
 * Closes a server connection.
 * void STDCALL mysql_close(MYSQL *sock).
 */
typedef void (STDCALL* MYSQL_CLOSE) (MYSQL *sock);
extern MYSQL_CLOSE mysql_close_c;

/**
 * Returns table names matching a simple regular expression.
 * MYSQL_RES * STDCALL mysql_list_tables(MYSQL *mysql,const char *wild).
 */
typedef MYSQL_RES * (STDCALL* MYSQL_LIST_TABLES) (MYSQL *mysql,const char *wild);
extern MYSQL_LIST_TABLES mysql_list_tables_c;

/**
 * Returns the number of columns in a result set.
 * unsigned int STDCALL mysql_num_fields(MYSQL_RES *res).
 */
typedef unsigned int (STDCALL* MYSQL_NUM_FIELDS) (MYSQL_RES *res);
extern MYSQL_NUM_FIELDS mysql_num_fields_c;

/**
 * Returns an array of all field structures.
 * MYSQL_FIELD * STDCALL mysql_fetch_fields(MYSQL_RES *res).
 */
typedef MYSQL_FIELD * (STDCALL* MYSQL_FETCH_FIELDS) (MYSQL_RES *res);
extern MYSQL_FETCH_FIELDS mysql_fetch_fields_c;

/**
 * Retrieves a complete result set to the client.
 * MYSQL_RES * STDCALL mysql_store_result(MYSQL *mysql).
 */
typedef MYSQL_RES * (STDCALL* MYSQL_STORE_RESULT) (MYSQL *mysql);
extern MYSQL_STORE_RESULT mysql_store_result_c;

/**
 * Initiates a row-by-row result set retrieval.
 * MYSQL_RES * STDCALL mysql_use_result(MYSQL *mysql).
 */
typedef MYSQL_RES * (STDCALL* MYSQL_USE_RESULT) (MYSQL *mysql);
extern MYSQL_USE_RESULT mysql_use_result_c;

/**
 * Returns the error message for the most recently invoked MySQL function.
 * const char * STDCALL mysql_error(MYSQL *mysql).
 */
typedef const char * (STDCALL* MYSQL_ERROR) (MYSQL *mysql);
extern MYSQL_ERROR mysql_error_c;

#endif // !__DTL_DB_MYSQL_LOADDLL_H__





 









