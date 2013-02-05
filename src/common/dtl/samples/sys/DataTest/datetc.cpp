/***************************************************************************************************
datetc.h:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Date， TimeZone, Locale等测试程序

Author:
	韩欣

Creating Time:
	2012-3-8
***************************************************************************************************/

#include <dtprec.h>
#include <dtl/dtl.h>

#include <iostream>


static void 

printCurrentLocaleInfo (void)

{
	cout << "------------------------------------printCurrentLocaleInfo (void) ------------------------------------" <<endl;

	const Locale* curLocale = Locale::getCurrentLocale ();	
	String msg;
	String region = curLocale->getRegion ();

	if (region.isEmpty ()) {
		msg.format (_T("Prints information about country '%s'."), curLocale->getCountry ().getCStr ());
	}

	else {
		msg.format (_T("Prints information about region '%s'."), region.getCStr ());
	}		

	cout << msg.getCStr () << endl;

	msg.format (_T(" - Locale code: %u."), curLocale->getLocaleCode ());
	cout << msg.getCStr () << endl;
			

	msg.format (_T(" - Locale string: %s."), curLocale->toString ().getCStr ());
	cout << msg.getCStr () << endl;

	msg.format (_T(" - Native name: %s."), curLocale->getNativeName ().getCStr ());
	cout << msg.getCStr () << endl;

		

	msg.format (_T(" - English name: %s."), curLocale->getEnglishName ().getCStr ());
	cout << msg.getCStr () << endl;

		

	msg.format (_T(" - Display name: %s."), curLocale->getDisplayName ().getCStr ());
	cout << msg.getCStr () << endl;
	

	cout<<endl;

}



static void

printCurrentTimeZoneInfo (void)

{
	cout << "------------------------------------printCurrentTimeZoneInfo (void) ------------------------------------" <<endl;
	const TimeZone* tz = TimeZone::getCurrentTimeZone ();

	String msg;
	msg.format (_T("Prints information about time zone '%s'."), tz->getDisplayName ().getCStr ());	

    cout << msg.getCStr() << endl;
	Date date;

	msg.format (_T(" - The UTC offset is %s."), String::toString (tz->getUTCOffset (&date)).getCStr ());
	cout << msg.getCStr () << endl;
	
	cout<<endl;

}



static void

printDate (const Date& date)

{

	cout << "------------------------------------printDate (void) ------------------------------------" <<endl;


	String msg;
	msg.format (_T("Full date & time: %s."), date.toString (FD_GENERAL_FULL).getCStr ());
	cout << msg.getCStr () <<endl;

	msg.format (_T("Long date & time: %s."), date.toString (FD_GENERAL_LONG).getCStr ());

	cout << msg.getCStr () << endl;

	

	msg.format (_T("Short date & time: %s."), date.toString (FD_GENERAL_SHORT).getCStr ());

	cout << msg.getCStr () << endl;

	

	msg.format (_T("Long date: %s."), date.toDateString (DP_LONG).getCStr ());

	cout << msg.getCStr () << endl;

	

	msg.format (_T("Short date: %s."), date.toDateString (DP_SHORT).getCStr ());

	cout << msg.getCStr () << endl;

	

	msg.format (_T("Month day: %s."), date.toDateString (DP_MONTH_DAY).getCStr ());

	cout << msg.getCStr () << endl;

	

	msg.format (_T("Year month: %s."), date.toDateString (DP_YEAR_MONTH).getCStr ());

	cout << msg.getCStr () << endl;


	msg.format (_T("Long time: %s."), date.toTimeString (TP_LONG).getCStr ());

	cout << msg.getCStr () << endl;

	

	msg.format (_T("Short time: %s."), date.toTimeString (TP_SHORT).getCStr ());

	cout << msg.getCStr () << endl;

	

	const DateFormat* localFormat = DateFormat::getLocalInstance ();

	

	msg.format (_T("e, d MMM yyyy HH:mm::ss O: %s."), 

					localFormat->format (&date, _T("e, d MMM yyyy HH:mm::ss O")).getCStr ());

	cout << msg.getCStr () << endl;

	

	LocaleDateFormat lf (Locale::getUSLocale ());

	msg.format (_T("US: e, d MMM yyyy HH:mm::ss O: %s."), 

					lf.format (&date, _T("e, d MMM yyyy HH:mm::ss O")).getCStr ());

	cout << msg.getCStr () << endl;

									

	msg.format (_T("Year %u, Month %u, Day %u, Day of week %u, Day of year %u, Hours %u, Minutes %u, Seconds %u"),

				date.getYear (), 

				date.getMonth (),

				date.getDay (),

				date.getDayOfWeek (),

				date.getDayOfYear (),

				date.getHours (),

				date.getMinutes (),

				date.getSeconds ());

	cout << msg.getCStr () << endl;

	

	msg.format (_T("Total days %u."), (size_t) date.timeOfDay ());			

	cout << msg.getCStr () << endl;

}



static void

printCurrentTime (void)

{

	cout << "------------------------------------printCurrentTime (void) ------------------------------------" <<endl;

	Date date;	


	cout<<"Information about the current time."<<endl;



	printDate (date);			

	cout<<endl;

}



static void

printFormatTime (void)

{

	cout << "------------------------------------printFormatTime (void) ------------------------------------" <<endl;

	const DateFormat* fmt = DateFormat::getLocalInstance ();
	const Locale* curLocale = Locale::getCurrentLocale ();	

	String dateStr;
	if (curLocale->toString () == _T("zh_CN"))
		dateStr = _T("2004-12-4");
	else
		dateStr = _T("12/04/2009");

	int64 ticks = fmt->parse (dateStr);
	printDate (Date(ticks));

	

	dateStr = _T("13:02");
	ticks = fmt->parse (dateStr);
	printDate (Date(ticks));


	dateStr = _T("13:02:54");
	ticks = fmt->parse (dateStr);
	printDate (Date(ticks));

	
	dateStr = _T("2004年12月4日");
	ticks = fmt->parse (dateStr);
	printDate (Date(ticks));

}



int main (int argc, char* argv[])

{

	printf ("Step1\n");		

	try {
			
		Locale locale (CHINA);
		Locale::setCurrentLocale (&locale);

		printf ("Step4\n");

		printCurrentLocaleInfo ();

		printCurrentTimeZoneInfo ();

		printCurrentTime ();

		printFormatTime ();

	}

	catch (Exception& e) {

		cout<<"Exception occurred: " << endl;

	}

	return 0;	 

}



