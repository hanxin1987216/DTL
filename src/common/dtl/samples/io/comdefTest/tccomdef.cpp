/***************************************************************************************************
tcdate.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2012)

Purpose:
test the date function

Author:
	”¶“µ√Ù

Creating Time:
	2012-2-8
***************************************************************************************************/
#include <dtprec.h>
#include <dtl.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

class TcComdef
{
public:
	void hxapi_time_t_to_filetime1 ( void );
	void daysInMonth ( void );
	void fileTimeToTime ( void );
	void timeToFileTime ( void );
	void FileTimeToSystemTime ( void );
	void hxwapi_stat_to_file_attributes ( void );
	void GetFileAttributes ( void );
	void loadFileAttributes ( void );
	void SetFileAttributes ( void );
	void GetFileAttributesEx ( void );
};

void
TcComdef::hxapi_time_t_to_filetime1 ( void )
{
	cout << "test the hxapi_time_t_to_filetime ():" << endl;

	time_t timeval;
	WapiFileTime filetime;
	timeval = time ((time_t *) 0 );

	cout << timeval << endl;
	hxapi_time_t_to_filetime ( timeval, &filetime );

	cout << ( int64 )filetime.dwLowDateTime << endl;
	cout << ( int64 )filetime.dwHighDateTime << endl;

	struct timeval tv;
	gettimeofday ( &tv, NULL );
	cout << tv.tv_sec << "  " << tv.tv_usec << endl;
	hxapi_timeval_to_filetime ( &tv, &filetime );

	cout << ( int64 )filetime.dwLowDateTime << endl;
	cout << ( int64 )filetime.dwHighDateTime << endl;
}

void
TcComdef::daysInMonth ( void )
{
	cout << "test the dayInMonth ():" << endl;

	cout << "the number of the days is:" 
		              << ::daysInMonth( 1905, 2 ) << endl;

	cout << "the number of the days is:" 
		              << ::daysInMonth( 1904, 2 ) << endl;

	cout << "the number of the days is:" 
		              << ::daysInMonth( 2011, 12 ) << endl;

	cout << "the number of the days is:" 
		              << ::daysInMonth( 2100, 2 ) << endl;

	cout << "the number of the days is:" 
		              << ::daysInMonth( 2100, 23 ) << endl;

	cout << "the number of the days is:" 
		              << ::daysInMonth( 1, 2 ) << endl;

	cout << "the number of the days is:" 
		              << ::daysInMonth( 21002400, 2 ) << endl;

	cout << "the number of the days is:" 
		              << ::daysInMonth( 0, 2 ) << endl;

	cout << "the number of the days is:" 
		              << ::daysInMonth( -2100, 2 ) << endl;///// ‰≥ˆ29

	/*cout << "the number of the days is:" 
		              << ::daysInMonth( 2100, -2 ) << endl;*/
}

void
TcComdef::fileTimeToTime ()
{
	cout << "test the fileTimeToTime ():" << endl;

	time_t timeval;
	WapiFileTime filetime;
	timeval = time ((time_t *) 0 );
	hxapi_time_t_to_filetime ( timeval, &filetime );
	cout << ( int64 )filetime.dwLowDateTime << endl;
	cout << ( int64 )filetime.dwHighDateTime << endl;

	int64 result;
	::fileTimeToTime ( &result, &filetime );
	cout << "the time is:" << result << endl;

	WapiFileTime filetime1;
	filetime1.dwLowDateTime = 325325696;
	filetime1.dwHighDateTime = 30203349;
	int64 result1;
	::fileTimeToTime ( &result1, &filetime1 );
	cout << "the time is:" << result1 << endl;
}

void
TcComdef::timeToFileTime ( void )
{
	cout << "test the timeToFileTime ():" << endl;

	int64 t = 1327654321000000;
	WapiFileTime pft;
	::timeToFileTime ( &pft, t );
	cout << "the filetime is:" << pft.dwLowDateTime 
		   << "   " << pft.dwHighDateTime << endl;

	t = 1234567891234569;
	::timeToFileTime ( &pft, t );
	cout << "the filetime is:" << pft.dwLowDateTime 
		   << "   " << pft.dwHighDateTime << endl;

	t = 123456789000;
	::timeToFileTime ( &pft, t );
	cout << "the filetime is:" << pft.dwLowDateTime 
		   << "   " << pft.dwHighDateTime << endl;
}

void
TcComdef::FileTimeToSystemTime ( void )
{
	cout << "test the FileTimeToSystemTime ():" << endl;

	WapiFileTime filetime;
	WapiSystemTime systemtime;
	time_t timeval;
	timeval = time ((time_t *) 0 );
	hxapi_time_t_to_filetime ( timeval, &filetime );
	::FileTimeToSystemTime ( &filetime, &systemtime );
	cout << "the systemtime is:" << systemtime.wYear << endl;
	cout << "the systemtime is:" << systemtime.wMonth << endl;
	cout << "the systemtime is:" << systemtime.wDay << endl;
	cout << "the systemtime is:" << systemtime.wHour << endl;
	cout << "the systemtime is:" << systemtime.wMinute << endl;
	cout << "the systemtime is:" << systemtime.wSecond << endl;
	cout << "the systemtime is:" << systemtime.wMilliseconds << endl;
	cout << "the systemtime is:" << systemtime.wDayOfWeek << endl;
}

void
TcComdef::hxwapi_stat_to_file_attributes ( void )
{
	cout << "test the hxwapi_stat_to_file_attributes ():" << endl;

	static char filename[]="t1.txt" ;
    int handle ;
	handle = creat( filename, 0755 ) ;

    if ( handle == -1 )
		cout << "create failure !" << filename << endl;
    else
        cout << "open success !" << filename << endl;

	struct stat buf;
	if ( stat ( filename, &buf ) < 0 )
		cout << "Mesg:" << strerror ( 1 );
	//cout << "Mesg:" << strerror ( 1 );
	cout << "attrs is:" << ::hxwapi_stat_to_file_attributes ( &buf ) << endl;

	chmod ( filename, S_ISGID );
	if ( stat ( filename, &buf ) < 0 )
		cout << "Mesg:" << strerror ( 1 );
	//cout << "Mesg:" << strerror ( 1 );
	cout << "attrs is:" << ::hxwapi_stat_to_file_attributes ( &buf ) << endl;

	mkdir ( "123456", S_IRUSR );
	if ( stat ( "123456", &buf ) < 0 )
		cout << "Mesg:" << strerror ( 1 );
	//cout << "Mesg:" << strerror ( 1 );
	cout << "attrs is:" << ::hxwapi_stat_to_file_attributes ( &buf ) << endl;
}

void
TcComdef::GetFileAttributes ( void )
{
	cout << "test the GetFileAttributes ():" << endl;

	creat( "1234", 0755 ) ;
	cout << "*****" << ::GetFileAttributes ( "1234" ) << endl;

	open ( "12345", O_CREAT, S_IWOTH );
	cout << "*****" << ::GetFileAttributes ( "12345" ) << endl;

	mkdir( "123456", S_IXUSR );
	cout << "*****" << ::GetFileAttributes ( "123456" ) << endl;

	mkdir( "1234567", S_IRUSR );
	cout << "*****" << ::GetFileAttributes ( "1234567" ) << endl;
}

void
TcComdef::loadFileAttributes ( void )
{
	cout << "test the loadFileAttributes ():" << endl;

	creat( "123", 0777 );
	cout << (UINT32)::loadFileAttributes ( "123" ) << endl;

	mkdir ( "1234", S_IRUSR );
	cout << (UINT32)::loadFileAttributes ( "1234" ) << endl;
}

void
TcComdef::SetFileAttributes ( void )
{
	cout << "test the SetFileAttributes ():" << endl;

	creat ( "123", 0145 );
	bool bl;
	struct stat buf;
	stat ( "123", &buf );
	cout << "*****" << buf.st_mode << endl;

	bl = ::SetFileAttributes ( "123", 2 );
	if (bl)
		cout << "success!" << endl;
	else
		cout << "failure!" << endl;

	struct stat buf1;
	stat ( "123", &buf1 );
	cout << "*****" << buf1.st_mode << endl;

	creat ( "1234", 0555 );
	bool bl1;
	struct stat buf2;
	stat ( "1234", &buf2 );
	cout << "*****" << buf2.st_mode << endl;

	bl1 = ::SetFileAttributes ( "1234", 456456 );
	if (bl1)
		cout << "success!" << endl;
	else
		cout << "failure!" << endl;

	struct stat buf3;
	stat ( "1234", &buf3 );
	cout << "*****" << buf3.st_mode << endl;
}

void
TcComdef::GetFileAttributesEx ( void )
{
	cout << "test the GetFileAttributesEx ():" << endl;

	tchar_t ptr[] = "abcdefg";
	size_t handle,i;
	FILE *in;
	fstream file;
	bool bl;

	handle = open ( "file.in", O_CREAT );
	file.open ( "file.in" );
	in =fopen( "file.in", "w" );

	for ( i = 0; i < strlen( ptr ) ; i++ )
		fputc( ptr[i], in );
	//close( handle );
	file.close();

	if ( file.is_open() )
		cout << "the file is open !" << endl;
	else
		cout << "the file is close !" << endl;

	fopen ( "file.in", "w" );

	struct stat buf;
	stat( "file.in", &buf );
	cout << "the mode is:" << buf.st_mode << endl;
	cout << "the st_mtime is:" << buf.st_mtime << endl;
	cout << "the st_ctime is:" << buf.st_ctime << endl;
	cout << "the st_atime is:" << buf.st_atime << endl;
	cout << "the st_size is:" << buf.st_size << endl;

	WapiGetFileExInfoLevels level = GetFileExInfoStandard;
	WapiFileAttributesData info;
	bl = ::GetFileAttributesEx ( "file.in", level, &info );

	if ( bl )
		cout << "success !" << endl;
	else
		cout << "failure !" << endl;

	cout << "the dwFileAttributes is:" << info.dwFileAttributes << endl;
	cout << "the ftCreationTime is:" << (info.ftCreationTime).dwHighDateTime << endl;
	cout << "the ftCreationTime is:" << (info.ftCreationTime).dwLowDateTime << endl;
	cout << "the ftLastAccessTime is:" << (info.ftLastAccessTime).dwHighDateTime << endl;
	cout << "the ftLastAccessTime is:" << (info.ftLastAccessTime).dwLowDateTime << endl;
	cout << "the ftLastWriteTime is:" << (info.ftLastWriteTime).dwHighDateTime << endl;
	cout << "the ftLastWriteTime is:" << (info.ftLastWriteTime).dwLowDateTime << endl;
	cout << "the nFileSizeHigh is:" << info.nFileSizeHigh << endl;
	cout << "the nFileSizeLow is:" << info.nFileSizeLow << endl;

	WapiSystemTime st;
	::FileTimeToSystemTime ( &( info.ftCreationTime ), &st );
	cout << "*****" << st.wYear << endl;
	cout << "*****" << st.wMonth << endl;
	cout << "*****" << st.wDay << endl;
	cout << "*****" << st.wHour << endl;
	cout << "*****" << st.wMinute << endl;
	cout << "*****" << st.wSecond << endl;
	cout << "*****" << st.wDayOfWeek << endl;
}



int main ()
{
	TcComdef tcc;
	tcc.hxapi_time_t_to_filetime1 ();
	tcc.daysInMonth ();
	tcc.fileTimeToTime ();
	tcc.timeToFileTime ();
	tcc.FileTimeToSystemTime ();
	tcc.hxwapi_stat_to_file_attributes ();
	tcc.GetFileAttributes ();
	tcc.loadFileAttributes ();
	tcc.SetFileAttributes ();
	tcc.GetFileAttributesEx ();
}




