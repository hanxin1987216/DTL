/*
 * locales.cpp: Culture-sensitive handling
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *	Mohammad DAMT (mdamt@cdl2000.com)
 *
 * Revision: 
 *    	hanxin (han.xin@Datatom.com): port for DTL.
 *
 * (C) 2003 Ximian, Inc.
 * (C) 2003 PT Cakram Datalingga Duaribu  http://www.cdl2000.com
 */

/*
 * The following two methods are modified from the ICU source code. (http://oss.software.ibm.com/icu)
 * Copyright (c) 1995-2003 International Business Machines Corporation and others
 * All rights reserved.
 */

#include <strings.h>
#include <glib.h>
#include <locale.h>
#include <algorithm>
#include <functional>
#include <mono_base/localemap.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

typedef struct _GlobalLANGLocaleMap {
	const char* locale;	

	int lcid;	
} GlobalLANGLocaleMap;

#define GLLMAP_NUM		201

// The table defined the sub language for a locale.
static const GlobalLANGLocaleMap gllMap [GLLMAP_NUM + 1] = {
	{"af",			0x0036},	//南非荷兰语
	{"af-ZA",		0x0436},	//南非荷兰语 - 南非 
	{"ar",			0x0001},	//阿拉伯语
	{"ar-AE",		0x3801},	//阿拉伯语 - 阿拉伯联合酋长国 
	{"ar-BH",		0x3C01},	//阿拉伯语 - 巴林 
	{"ar-DZ",		0x1401},	//阿拉伯语 - 阿尔及利亚 
	{"ar-EG",		0x0C01},	//阿拉伯语 - 埃及 
	{"ar-IQ",		0x0801},	//阿拉伯语 - 伊拉克 
	{"ar-JO",		0x2C01},	//阿拉伯语 - 约旦 
	{"ar-KW",		0x3401},	//阿拉伯语 - 科威特 
	{"ar-LB",		0x3001},	//阿拉伯语 - 黎巴嫩 
	{"ar-LY",		0x1001},	//阿拉伯语 - 利比亚 
	{"ar-MA",		0x1801},	//阿拉伯语 - 摩洛哥 
	{"ar-OM",		0x2001},	//阿拉伯语 - 阿曼 
	{"ar-QA",		0x4001},	//阿拉伯语 - 卡塔尔 
	{"ar-SA",		0x0401},	//阿拉伯语 - 沙特阿拉伯 
	{"ar-SY",		0x2801},	//阿拉伯语 - 叙利亚 
	{"ar-TN",		0x1C01},	//阿拉伯语 - 突尼斯 
	{"ar-YE",		0x2401},	//阿拉伯语 - 也门 
	{"az",			0x002C},	//阿泽里语 
	{"az-AZ-Cyrl",	0x082C},	//阿泽里语（西里尔语）- 阿塞拜疆 
	{"az-AZ-Latn",	0x042C},	//阿泽里语（拉丁）- 阿塞拜疆 
	{"be",			0x0023},	//白俄罗斯语 
	{"be-BY",		0x0423},	//白俄罗斯语 - 白俄罗斯 
	{"bg",			0x0002},	//保加利亚语 
	{"bg-BG",		0x0402},	//保加利亚语 - 保加利亚 
	{"ca",			0x0003},	//加泰罗尼亚语 
	{"ca-ES",		0x0403},	//加泰罗尼亚语 - 加泰罗尼亚地区 
	{"cs",			0x0005},	//捷克语 
	{"cs-CZ",		0x0405},	//捷克语 - 捷克共和国 
	{"da",			0x0006},	//丹麦语 
	{"da-DK",		0x0406},	//丹麦语 - 丹麦 
	{"de",			0x0007},	//德语 
	{"de-AT",		0x0C07},	//德语 - 奥地利 
	{"de-CH",		0x0807},	//德语 - 瑞士 
	{"de-DE",		0x0407},	//德语 - 德国 
	{"de-LI",		0x1407},	//德语 - 列支敦士登 
	{"de-LU",		0x1007},	//德语 - 卢森堡 
	{"div",			0x0065},	//马尔代夫语 
	{"div-MV",		0x0465},	//马尔代夫语 - 马尔代夫 
	{"el",			0x0008},	//希腊语 
	{"el-GR",		0x0408},	//希腊语 - 希腊 
	{"en",			0x0009},	//英语 
	{"en-AU",		0x0C09},	//英语 - 澳大利亚 
	{"en-BZ",		0x2809},	//英语 - 伯利兹 
	{"en-CA",		0x1009},	//英语 - 加拿大 
	{"en-CB",		0x2409},	//英语 - 加勒比 
	{"en-GB",		0x0809},	//英语 - 英国 
	{"en-IE",		0x1809},	//英语 - 爱尔兰 
	{"en-JM",		0x2009},	//英语 - 牙买加 
	{"en-NZ",		0x1409},	//英语 - 新西兰
	{"en-PH",		0x3409},	//英语 - 菲律宾 
	{"en-TT",		0x2C09},	//英语 - 特立尼达和多巴哥 
	{"en-US",		0x0409},	//英语 - 美国 
	{"en-ZA",		0x1C09},	//英语 - 南非 
	{"en-ZW",		0x3009},	//英语 - 津巴布韦 
	{"es",			0x000A},	//西班牙语 
	{"es-AR",		0x2C0A},	//西班牙语 - 阿根廷 
	{"es-BO",		0x400A},	//西班牙语 - 玻利维亚 
	{"es-CL",		0x340A},	//西班牙语 - 智利 
	{"es-CO",		0x240A},	//西班牙语 - 哥伦比亚 
	{"es-CR",		0x140A},	//西班牙语 - 哥斯达黎加 
	{"es-DO",		0x1C0A},	//西班牙语 - 多米尼加共和国 
	{"es-EC",		0x300A},	//西班牙语 - 厄瓜多尔 
	{"es-ES",		0x0C0A},	//西班牙语 - 西班牙 
	{"es-GT",		0x100A},	//西班牙语 - 危地马拉 
	{"es-HN",		0x480A},	//西班牙语 - 洪都拉斯 
	{"es-MX",		0x080A},	//西班牙语 - 墨西哥 
	{"es-NI",		0x4C0A},	//西班牙语 - 尼加拉瓜 
	{"es-PA",		0x180A},	//西班牙语 - 巴拿马 
	{"es-PY",		0x3C0A},	//西班牙语 - 巴拉圭 
	{"es-PE",		0x280A},	//西班牙 - 秘鲁 
	{"es-PR",		0x500A},	//西班牙语 - 波多黎各 
	{"es-SV",		0x440A},	//西班牙语 - 萨尔瓦多 
	{"es-UY",		0x380A},	//西班牙语 - 乌拉圭 
	{"es-VE",		0x200A},	//西班牙语 - 委内瑞拉 
	{"eu",			0x002D},	//巴斯克语 
	{"eu-ES",		0x042D},	//巴斯克语 - 巴斯克地区 
	{"et",			0x0025},	//爱沙尼亚语 
	{"et-EE",		0x0425},	//爱沙尼亚语 - 爱沙尼亚 
	{"fa",			0x0029},	//波斯语 
	{"fa-IR",		0x0429},	//波斯语 - 伊朗 
	{"fi",			0x000B},	//芬兰语 
	{"fi-FI",		0x040B},	//芬兰语 - 芬兰 
	{"fo",			0x0038},	//法罗语 
	{"fo-FO",		0x0438},	//法罗语 - 法罗群岛 
	{"fr",			0x000C},	//法语 
	{"fr-BE",		0x080C},	//法语 - 比利时 
	{"fr-CA",		0x0C0C},	//法语 - 加拿大 
	{"fr-CH",		0x100C},	//法语 - 瑞士 
	{"fr-FR",		0x040C},	//法语 - 法国 
	{"fr-LU",		0x140C},	//法语 - 卢森堡 
	{"fr-MC",		0x180C},	//法语 - 摩纳哥 
	{"gl",			0x0056},	//加利西亚语 
	{"gl-ES",		0x0456},	//加利西亚语 - 加利西亚地区 
	{"gu",			0x0047},	//古吉拉特语 
	{"gu-IN",		0x0447},	//古吉拉特语 - 印度 
	{"he",			0x000D},	//希伯来语 
	{"he-IL",		0x040D},	//希伯来语 - 以色列 
	{"hi",			0x0039},	//印地语 
	{"hi-IN",		0x0439},	//印地语 - 印度 
	{"hr",			0x001A},	//克罗地亚语 
	{"hr-HR",		0x041A},	//克罗地亚语 - 克罗地亚 
	{"hu",			0x000E},	//匈牙利语 
	{"hu-HU",		0x040E},	//匈牙利语 - 匈牙利 
	{"hy",			0x002B},	//亚美尼亚语 
	{"hy-AM",		0x042B},	//亚美尼亚语 - 亚美尼亚 
	{"id",			0x0021},	//印度尼西亚语 
	{"id-ID",		0x0421},	//印度尼西亚语 - 印度尼西亚
	{"is",			0x000F},	//冰岛语 
	{"is-IS",		0x040F},	//冰岛语 - 冰岛 
	{"it",			0x0010},	//意大利语 
	{"it-IT",		0x0410},	//意大利语 - 意大利 
	{"it-CH",		0x0810},	//意大利语 - 瑞士 
	{"ja",			0x0011},	//日语 
	{"ja-JP",		0x0411},	//日语 - 日本 
	{"ka",			0x0037},	//格鲁吉亚语 
	{"ka-GE",		0x0437},	//格鲁吉亚语 - 格鲁吉亚 
	{"kk",			0x003F},	//哈萨克语 
	{"kk-KZ",		0x043F},	//哈萨克语 - 哈萨克斯坦 
	{"kn",			0x004B},	//卡纳达语 
	{"kn-IN",		0x044B},	//卡纳达语 - 印度 
	{"kok",			0x0057},	//贡根语 
	{"kok-IN",		0x0457},	//贡根语 - 印度 
	{"ko",			0x0012},	//朝鲜语 
	{"ko-KR",		0x0412},	//朝鲜语 - 韩国 
	{"ky",			0x0040},	//吉尔吉斯语 
	{"ky-KZ",		0x0440},	//吉尔吉斯语 - 吉尔吉斯坦 
	{"lt",			0x0027},	//立陶宛语 
	{"lt-LT",		0x0427},	//立陶宛语 - 立陶宛 
	{"lv",			0x0026},	//拉脱维亚语 
	{"lv-LV",		0x0426},	//拉脱维亚语 - 拉脱维亚 
	{"mk",			0x002F},	//马其顿语 
	{"mk-MK",		0x042F},	//马其顿语 - FYROM 
	{"mn",			0x0050},	//蒙古语 
	{"mn-MN",		0x0450},	//蒙古语 - 蒙古 
	{"mr",			0x004E},	//马拉地语 
	{"mr-IN",		0x044E},	//马拉地语 - 印度 
	{"ms",			0x003E},	//马来语 
	{"ms-BN",		0x083E},	//马来语 - 文莱 
	{"ms-MY",		0x043E},	//马来语 - 马来西亚 
	{"nb-NO",		0x0414},	//挪威语（博克马尔）- 挪威 
	{"nl",			0x0013},	//荷兰语 
	{"nl-BE",		0x0813},	//荷兰语 - 比利时 
	{"nl-NL",		0x0413},	//荷兰语 - 荷兰 
	{"nn-NO",		0x0814},	//挪威语（尼诺斯克）- 挪威 
	{"no",			0x0014},	//挪威语 
	{"pa",			0x0046},	//旁遮普语 
	{"pa-IN",		0x0446},	//旁遮普语 - 印度 
	{"pl",			0x0015},	//波兰语 
	{"pl-PL",		0x0415},	//波兰语 - 波兰 
	{"pt",			0x0016},	//葡萄牙语 
	{"pt-BR",		0x0416},	//葡萄牙语 - 巴西 
	{"pt-PT",		0x0816},	//葡萄牙语 - 葡萄牙 
	{"ro",			0x0018},	//罗马尼亚语 
	{"ro-RO",		0x0418},	//罗马尼亚语 - 罗马尼亚 
	{"ru",			0x0019},	//俄语 
	{"ru-RU",		0x0419},	//俄语 - 俄罗斯 
	{"sa",			0x004F},	//梵语 
	{"sa-IN",		0x044F},	//梵语 - 印度 
	{"sk",			0x001B},	//斯洛伐克语 
	{"sk-SK",		0x041B},	//斯洛伐克语 - 斯洛伐克 
	{"sl",			0x0024},	//斯洛文尼亚语 
	{"sl-SI",		0x0424},	//斯洛文尼亚语 - 斯洛文尼亚 
	{"sq",			0x001C},	//阿尔巴尼亚语
	{"sq-AL",		0x041C},	//阿尔巴尼亚语 - 阿尔巴尼亚 
	{"sr-SP-Cyrl",	0x0C1A},	//塞尔维亚语（西里尔语）- 塞尔维亚 
	{"sr-SP-Latn",	0x081A},	//塞尔维亚语（拉丁）- 塞尔维亚 
	{"sv",			0x001D},	//瑞典语 
	{"sv-FI",		0x081D},	//瑞典语 - 芬兰 
	{"sv-SE",		0x041D},	//瑞典语 - 瑞典 
	{"sw",			0x0041},	//斯瓦希里语 
	{"sw-KE",		0x0441},	//斯瓦希里语 - 肯尼亚 
	{"syr",			0x005A},	//叙利亚语 
	{"syr-SY",		0x045A},	//叙利亚语 - 叙利亚 
	{"ta",			0x0049},	//泰米尔语 
	{"ta-IN",		0x0449},	//泰米尔语 - 印度 
	{"te",			0x004A},	//泰卢固语 
	{"te-IN",		0x044A},	//泰卢固语 - 印度 
	{"th",			0x001E},	//泰语 
	{"th-TH",		0x041E},	//泰语 - 泰国 
	{"tr",			0x001F},	//土耳其语 
	{"tr-TR",		0x041F},	//土耳其语 - 土耳其 
	{"tt",			0x0044},	//鞑靼语 
	{"tt-RU",		0x0444},	//鞑靼语 - 俄罗斯 
	{"uk",			0x0022},	//乌克兰语 
	{"uk-UA",		0x0422},	//乌克兰语 - 乌克兰 
	{"ur",			0x0020},	//乌尔都语 
	{"ur-PK",		0x0420},	//乌尔都语 - 巴基斯坦 
	{"uz",			0x0043},	//乌兹别克语 
	{"uz-UZ-Cyrl",	0x0843},	//乌兹别克语（西里尔语）- 乌兹别克斯坦 
	{"uz-UZ-Latn",	0x0443},	//乌兹别克语（拉丁）- 乌兹别克斯坦 
	{"vi",			0x002A},	//越南语 
	{"vi-VN",		0x042A},	//越南语 - 越南 
	{"zh-CN",		0x0804},	//中文 - 中国 
	{"zh-CHS",		0x0004},	//中文（简体） 
	{"zh-CHT",		0x7C04},	//中文（繁体） 
	{"zh-HK",		0x0C04},	//中文 - 香港特别行政区 
	{"zh-MO",		0x1404},	//中文 - 澳门特别行政区 
	{"zh-SG",		0x1004},	//中文 - 新加坡 
	{"zh-TW",		0x0404},	//中文 - 台湾 
	{"",				0x007F},	//固定区域性
};

struct GLLComparator
{
	GLLComparator (const gchar * localeStr) : localStr (localeStr) { }
	bool operator () (const GlobalLANGLocaleMap & gllPtr)
	{
		return strcasecmp (localStr, gllPtr.locale) == 0 ? true : false;
	}

	const gchar * localStr;
};


int
getGlobalLangLCID (const gchar* localeStr)
{
	const GlobalLANGLocaleMap* gllMapEnd = gllMap + GLLMAP_NUM;
	const GlobalLANGLocaleMap* gllPtr = std::find_if (gllMap, 
																	  gllMapEnd, 
																	  GLLComparator (localeStr));

	return gllPtr->lcid;
}

gchar*
get_posix_locale (void)
{
	const gchar* posix_locale = NULL;

	posix_locale = g_getenv("LC_ALL");
	if (posix_locale == 0) {
		posix_locale = g_getenv("LANG");
		if (posix_locale == 0) {
			posix_locale = setlocale(LC_ALL, NULL);
		}
	}

	if (posix_locale == NULL)
		return NULL;

	if ((strcmp ("C", posix_locale) == 0) || (strchr (posix_locale, ' ') != NULL)
			|| (strchr (posix_locale, '/') != NULL)) {
		/*
		 * HPUX returns 'C C C C C C C'
		 * Solaris can return /en_US/C/C/C/C/C on the second try.
		 * Maybe we got some garbage.
		 */
		return NULL;
	}

	return g_strdup (posix_locale);
}

gchar*
get_current_locale_name (void)
{
	gchar *locale;
	gchar *corrected = NULL;
	const gchar *p;
        gchar *c;

	locale = get_posix_locale ();

	if (locale == NULL)
		return NULL;

	if ((p = strchr (locale, '.')) != NULL) {
		/* assume new locale can't be larger than old one? */
		corrected = (gchar*)malloc (strlen (locale));
		strncpy (corrected, locale, p - locale);
		corrected [p - locale] = 0;

		/* do not copy after the @ */
		if ((p = strchr (corrected, '@')) != NULL)
			corrected [p - corrected] = 0;
	}

	/* Note that we scan the *uncorrected* ID. */
	if ((p = strrchr (locale, '@')) != NULL) {

		/*
		 * In Mono we dont handle the '@' modifier because we do
		 * not have any cultures that use it. We just trim it
		 * off of the end of the name.
		 */

		if (corrected == NULL) {
			corrected = (gchar*)malloc (strlen (locale));
			strncpy (corrected, locale, p - locale);
			corrected [p - locale] = 0;
		}
	}

	if (corrected == NULL)
		corrected = locale;
	else
		g_free (locale);

	if ((c = strchr (corrected, '_')) != NULL)
		*c = '-';

	g_strdown (corrected);

	return corrected;
}	 

int GetUserDefaultLangID (void)
{
	gchar* localStr = get_current_locale_name ();

	int li;
	if (localStr == NULL) {
		li = getGlobalLangLCID ("en_US");
	}
	else 
		li = getGlobalLangLCID (localStr);
	
	g_free (localStr);

	return li;
}
