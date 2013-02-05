/*
 * locales.h: Culture-sensitive handling
 *
 * Authors:
 *	Dick Porter (dick@ximian.com)
 *
 * Revision: 
 *    	hanxin (han.xin@Datatom.com): port for DTL.
 *
 * (C) 2003 Ximian, Inc.
 */

#ifndef _WAPI_LOCALES_H_
#define _WAPI_LOCALES_H_

int GetUserDefaultLangID (void);
gchar* get_posix_locale (void);
int getGlobalLangLCID (const gchar* localeStr);

#endif /* _WAPI_LOCALES_H_ */
