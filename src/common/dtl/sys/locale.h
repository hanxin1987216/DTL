/***************************************************************************************************
locale.h:	
	C++ Foundation Library header files
	Copyright (c) DateTome Software Inc.(2012)

Purpose:

Author:
	韩欣 (han.xin@datatom.com)

Creating Time:
	2012-02-07
	
	This library is free software; you can redistribute it and/or modify it under the terms of the 
 	GNU Lesser General Public License as published by the Free Software Foundation; either version 
 	2 of the License, or (at your option) any later version.  	
***************************************************************************************************/

#ifndef __DTL_SYS_LOCALE_H__
#define __DTL_SYS_LOCALE_H__

#if PRAGMA_ONCE
#pragma once
#endif

#include "../lang/string.h"
#include <vector>
	
	
/**
 * The country/region code defined by ISO-3166. You can get a full list of these
 * code at link http://www.davros.org/misc/iso3166.txt.
 */
enum LocaleCode
{
	AFGHANISTAN = 4,
	ALBANIA = 8,
	ANTARCTICA = 10,
	ALGERIA = 12,
	AMERICAN_SAMOA = 16,
	ANDORRA = 20,
	ANGOLA = 24,
	AZERBAIJAN = 31,
	ARGENTINA = 32,
	AUSTRALIA = 36,
	AUSTRIA = 40,
	BAHAMAS = 44,
	BAHRAIN = 48,
	BANGLADESH = 50,
	ARMENIA = 51,
	BARBADOS = 52,
	BELGIUM = 56,
	BERMUDA = 60,
	BHUTAN = 64, 
	BOLIVIA = 68,
	BOTSWANA = 72,
	BOUVETOYA = 74,
	BRAZIL = 76,
	BELIZE = 84,
	SOLOMON_ISLANDS = 90,
	BRUNEI = 96,
	BULGARIA = 100,
	MYANMAR = 104,
	BURUNDI = 108,		
	BYELORUSSIA = 112,
	CAMBODIA = 116,
	CAMEROON = 120,
	CANADA = 124,
	CAPE_VERDE = 132,
	CAYMAN_ISLANDS = 136,
	CENTRAL_AFRICAN = 140,
	SRI_LANKA = 144,
	CHAD = 148,
	CHILE = 152,
	CHINA = 156,
	TAIWAN = 158,
	CHRISTMAS_ISLAND = 162,
	COCOS_ISLANDS = 166,
	COLOMBIA = 170,
	COMOROS = 174,
	MAYOTTE = 175,
	CONGO_PRC = 178,
	CONGO_DRC = 180,
	COOK_ISLANDS = 184,
	COSTA_RICA = 188,
	CROATIA = 191,
	CUBA = 192,
	CYPRUS = 196,
	CZECH = 203,
	BENIN = 204,
	DENMARK = 208,
	DOMINICA = 212,
	DOMINICAN = 214,
	ECUADOR = 218,
	EL_SALVADOR = 222,
	EQUATORIAL_GUINEA = 226,
	ETHIOPIA = 231,
	ERITREA = 232,
	ESTONIA = 233,
	FAEROE_ISLANDS = 234,
	FALKLAND_ISLANDS = 238,
	SOUTH_GEORGIA_SOUTH_SANDWICH_ISLANDS = 239,
	FIJI = 242,
	FINLAND = 246,
	FRANCE = 250,
	FRENCH_GUIANA = 254,
	FRENCH_POLYNESIA = 258,
	FRENCH_SOUTHERN_TERRITORIES = 260,
	DJIBOUTI = 262,	
	GABON = 266,
	GEORGIA = 268,
	GAMBIA = 270,
	PALESTINIAN_TERRITORY = 275,
	GERMANY = 276,		
	GHANA = 288,
	GIBRALTAR = 292,
	KIRIBATI = 296,
	GREECE = 300,
	GREENLAND = 304,
	GRENADA = 308,
	GUADALOUPE = 312,
	GUAM = 316,
	GUATEMALA = 320,
	GUINEA = 324,
	GUYANA = 328,
	HAITI = 332,
	HEARD_MCDONALD_ISLANDS = 334,
	HOLY_SEE = 336,
	HONDURAS = 340,
	HONG_KONG = 344,
	HUNGARY = 348,
	ICELAND = 352,
	INDIA = 356,
	INDONESIA = 360,
	IRAN = 364,
	IRAQ = 368,
	IRELAND = 372,
	ISRAEL = 376,
	ITALY = 380,
	JAMAICA = 388,
	JAPAN = 392,
	KAZAKHSTAN = 398,
	JORDAN = 400,
	KENYA = 404,
	KOREA_DPR = 408,
	KOREA = 410,
	KUWAIT = 414,
	KYRGYZ = 417,
	LAO = 418,
	LEBANON = 422,
	LESOTHO = 426,
	LATVIA = 428,
	LIBERIA = 430,
	LIBYAN = 434,
	LIECHTENSTEIN = 438,
	LITHUANIA = 440,
	LUXEMBOURG = 442,
	MACAO = 446,
	MADAGASCAR = 450,
	MALAWI = 454,
	MALAYSIA = 458,
	MALDIVES = 462,
	MALI = 466,
	MALTA = 470, 
	MARTINIQUE = 474,
	MAURITANIA = 478,
	MAURITIUS = 480,
	MEXICO = 484,
	MONACO = 492,
	MONGOLIA = 496, 
	MOLDOVA = 498, 
	MONTSERRAT = 500,
	MOROCCO = 504,
	MOZAMBIQUE = 508,
	OMAN = 512,
	NAMIBIA = 516,
	NAURU = 520, 
	NEPAL = 524, 
	NETHERLANDS = 528,
	NETHERLANDS_ANTILLES = 530,
	NEW_CALEDONIA = 540,
	VANUATU = 548,
	ARUBA = 553,
	NEW_ZEALAND = 554,
	NICARAGUA = 558, 
	NIGER = 562, 
	NIGERIA = 566,
	NIUE = 570, 
	NORFOLK_ISLAND = 574,
	NORWAY = 578,
	NORTHERN_MARIANA_ISLANDS = 580,
	MICRONESIA = 583,
	MARSHALL_ISLANDS = 584,
	PAKISTAN = 586,
	PALAU = 585,
	PANAMA = 591,
	PAPUA_NEW_GUINEA = 598,
	PARAGUAY = 600,
	PERU = 604,
	PHILIPPINES = 608,
	PITCAIRN_ISLAND = 612,
	POLAND = 616,
	PORTUGAL = 620,
	GUINEA_BISSAU = 624,
	TIMOR_LESTE = 626,
	PUERTO_RICO = 630,
	QATAR = 634,
	REUNION = 638,
	ROMANIA = 642,
	RUSSIAN = 643,
	RWANDA = 646,
	ST_HELENA = 654,
	ST_KITTS_NEVIS = 659,
	ANGUILLA = 660,
	ST_LUCIA = 662,
	ST_PIERRE_MIQUELON = 666,
	ST_VINCENT_GRENADINES = 670,
	SAN_MARINO = 674,
	SAO_TOME_PRINCIPE = 678,
	SAUDI_ARABIA = 682,
	SENEGAL = 686, 
	SEYCHELLES = 690,
	SERBIA_MONTENEGRO = 691,
	SIERRA_LEONE = 694,
	SINGAPORE = 702,
	SLOVAKIA = 703,
	VIET_NAM = 704,
	SLOVENIA = 705,
	SOMALIA = 706,
	SOUTH_AFRICA = 710,
	ZIMBABWE = 716,
	SPAIN = 724,
	CATALONIAN = 726,
	WESTERN_SAHARA = 732,
	SUDAN = 736,
	SURINAME = 740,
	SVALBARD_JAN_MAYEN_ISLANDS = 744,
	SWAZILAND = 748,
	SWEDEN = 752,
	SWITZERLAND = 756,
	SYRIAN_ARAB_REPUBLIC = 760,
	TAJIKISTAN = 762,
	THAILAND = 764,
	TOGO = 768,
	TOKELAU = 772,
	TONGA = 776,
	TRINIDAD_TOBAGO = 780,
	UNITED_ARAB_EMIRATES = 784,
	TUNISIA = 788,
	TURKEY = 792,
	TURKMENISTAN = 795,
	TURKS_CAICOS_ISLANDS = 796,
	TUVALU = 798,
	UGANDA = 800,
	UKRAINE = 804,
	MACEDONIA = 807,
	EGYPT = 818,		
	UNITED_KINGDOM = 826,
	TANZANIA = 834,
	UNITED_STATES = 840,
	BURKINA_FASO = 854,
	URUGUAY = 858,
	UZBEKISTAN = 860,
	VENEZUELA = 862,
	WALLIS_FUTUNA_ISLANDS = 876,
	SAMOA = 882,
	YEMEN = 887,
	ZAMBIA = 894,
	
	LOCALE_CODE_MAX = 900,
};


class DTL_DLLEXPORT Locale
{
// Ctors and dtor
public:
	/**
	 * Constructs a locale object with specified locale code.
	 *	This constructor uses the official language of this locale to constructs
	 *	the language property of this object.
	 *
	 * @param code	The locale code for this Locale object.
	 *
	 * @throw Exception If the specified code doesn't not implemented by DTL.
	 */
	Locale (LocaleCode code);
	
	/**
	 * Constructs a locale object with specifed locale code and custom language (other than 
	 *	official language).
	 *
	 * @param code				The locale code for this Locale object.
	 * @param lang 				The language for this locale.
	 * @param isOfficialLang	Flag whether the lauage is official for the locale.
	 *
	 * @throw Exception If the specified code doesn't not implemented by DTL.
	 */
	Locale (LocaleCode code, const String& lang, bool isOfficalLang);
		
// Public methods
public:
	/**
	 * Returns a string of the entire locale, with the language, region, and country
	 * separated by underbars.
	 *
	 * For example, "zh_CN”...
	 */
	String toString (void) const;
	
	/**
	 * Returns the upper-case, two-letters country code for this locale.
	 */
	String getCountry (void) const
	{
		return _country;
	}

	/**
	 * Returns the lower-case, two-letters language code for this locale.
	 */
	String getLanguage (void) const
	{
		return _lang;
	}
	
	/**
	 * Returns the upper-case, two-letters region code for this locale.
	 */
	String getRegion (void) const
	{
		return _region;
	}
	
	/**
	 * Returns the locale code for this locale.
	 */
	LocaleCode getLocaleCode (void) const
	{
		return _code;
	}
	
	/**
	 * Returns a string of the entire locale with format like 
	 *	"full language ([full region, ]full country)". The string
	 * uses the langauage of this locale.
	 *
	 * For example: CHINA (简体中文(中华人民共和国)), TAIWAN (繁體中文(中國台灣))
	 *
	 * @throw InvalidOperationException If cannot get the native locale data.
	 */
	String getNativeName (void) const;
	
	/**
	 * Returns a string of the entire locale with format like 
	 *	"full language ([full region, ]full country)". The string
	 * uses the langauage of current locale.
	 *
	 * For example: CHINA (Simplied Chinese(PRC)), TAIWAN (Traditional Chinese(Taiwan, PRC))
	 */
	String getEnglishName (void) const;	
	
	/**
	 * Returns a string of the entire locale with format like
	 *	"full language ([full region, ]full country)". The string uses the langauge
	 * If the default locale was not installed for DTL, DTL always uses English as substitution.
	 */
	String getDisplayName (void) const;
	
	/**
	 * Returns a string of the entire locale with format like
	 *	"full language ([full region, ]full country)". The string uses the language
	 *	of the specified locale. If cannot find the translations of the specified locale,
	 *	uses the default locales of DTL (See getDisplayName ()). 
	 *
	 * @throw ArgumentException If the specified Locale object is null.
	 */
	String getDisplayName (const Locale* where) const;
	
	/**
	 * Tests the language this locale object represents whether is official langauge of this locale.
	 */
	bool isOfficialLanguage (void) const
	{
		return _isOfficialLang;
	}
	 
public:
	/**
	 * Gets current locale.
	 */ 
	static const Locale* getCurrentLocale (void);

	/**
	 * Returns US locale.
	 */
	static const Locale* getUSLocale (void)
	{
		return findLocale (UNITED_STATES);
	}
	
	/**
	 * Returns CHINA locale.
	 */
	static const Locale* getChinaLocale (void)
	{
		return findLocale (CHINA);
	}
	
	/**
	 * Sets current locale for DTL.
	 * @param locale 	The new locale.
	 */
	static void setCurrentLocale (const Locale* locale);		
	
	/**
	 * Finds the locale object with the locale code.
	 *
	 * @param code 	The locale code, it is the fourth parameter of 
	 *				Locale constructor.		 
	 *
	 * @throw ArgumentException If the specified code doesn't not implemented by DTL.
	 */
	static const Locale* findLocale (LocaleCode code);
	
	/**
	 * Changes the system default locale and the current locale for DTL.
	 *
	 * @param locale 	The new locale.
	 */
	static void setSystemDefaultLocale (const Locale* locale);
	
	/**
	 * Returns all locales that DTL supports.
	 */
	static void getAllLocales (vector<const Locale*>& locales);
	
	/**
	 *
	 */
	//static void clearCachedLocales (void);
	
private:
	static const Locale* _curLocale;		
	
protected:
	String _lang;
	String _country;
	String _region;
	LocaleCode _code : 24;
	bool _isOfficialLang;
}; // End class Locale

#endif // __DTL_SYS_LOCALE_H__
