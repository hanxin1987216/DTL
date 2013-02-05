/***************************************************************************************************
pathtc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Path 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-15
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "pathtc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( PathTestCase );

void
PathTestCase::setUp(void) {
}

void 
PathTestCase::tearDown(void) {
}

void
PathTestCase::testConst(void) {
#ifdef __WINDOWS__       
    CPPUNIT_ASSERT(Path::separator == _T('\\'));
    CPPUNIT_ASSERT(Path::altSeparator == _T('/'));
    CPPUNIT_ASSERT(Path::volumeSeparator == _T(':'));
    CPPUNIT_ASSERT(Path::pathSeparator == _T(';'));
#else
    CPPUNIT_ASSERT(Path::separator == '/');
    CPPUNIT_ASSERT(Path::altSeparator == '/');
    CPPUNIT_ASSERT(Path::volumeSeparator == '/');
    CPPUNIT_ASSERT(Path::pathSeparator == ':');
#endif
}

void
PathTestCase::testCombine(void) 
{
    String p1,p2;
    //cout<<endl<< Path::getInvalidPathChars().getCStr()<<endl;
    //test empty path
    CPPUNIT_ASSERT_THROW(Path::combine(p1, p2), Exception);
    
    //test illegal chars
    String invalid = Path::getInvalidPathChars();
    p1 = "root";
    p2 = "home";
    for(size_t i=0; i<invalid.getLength(); i++) {
        CPPUNIT_ASSERT_THROW(Path::combine(p1+invalid[i], p2), Exception);
    }

    for(size_t i=0; i<invalid.getLength(); i++) {
        CPPUNIT_ASSERT_THROW(Path::combine(p1, p2+invalid[i]), Exception);
    }

    //test a empty combine one legal path
    CPPUNIT_ASSERT(Path::combine(String(), p1) == p1);
    CPPUNIT_ASSERT(Path::combine(p2,String()) == p2);

#ifdef __WINDOWS__
    p2 = _T("c:\\windows");
#else
    p2 = "/home";
#endif
    //test absolute path
    CPPUNIT_ASSERT(Path::combine(p1, p2) == p2);

    p1 = "root";
    p2 = "home";
    //test normal case
#ifdef __WINDOWS__
    CPPUNIT_ASSERT(Path::combine(p1, p2) == _T("root\\home"));
    CPPUNIT_ASSERT(Path::combine(p1+'\\', p2) == _T("root\\home"));
#else
    CPPUNIT_ASSERT(Path::combine(p1, p2) == "root/home");
    CPPUNIT_ASSERT(Path::combine(p1+'/', p2) == "root/home");
#endif
}

void
PathTestCase::testMakeFullPath(void) {
#ifdef __WINDOWS__
    String p = _T("c:\\windows\\system32");
#else
    String p = "/home/Datatom/fan";
#endif
    CPPUNIT_ASSERT(Path::makeFullPath(p) == p);

    p = "";
    String curpwd = Path::getCurrentPath();
    //cout<<endl<< Path::makeFullPath(p).getCStr()<<endl;
    //cout<<endl<< Path::getCurrentPath().getCStr()<<endl;
    CPPUNIT_ASSERT(Path::makeFullPath(p) == curpwd);

    //cout<<endl<<Path::makeFullPath(_T("Datatom\\fan")).getCStr()<<endl;
    CPPUNIT_ASSERT(Path::makeFullPath(_T("Datatom\\fan")) 
                    == Path::combine(curpwd , "Datatom\\fan"));

    CPPUNIT_ASSERT(Path::makeFullPath(_T("Datatom/fan")) 
                    == Path::combine(curpwd , "Datatom/fan"));

#ifdef __WINDOWS__
    CPPUNIT_ASSERT_THROW(Path::makeFullPath(_T("Datatom/?><fan")), Exception); 
#else
    CPPUNIT_ASSERT(Path::makeFullPath(_T("Datatom/?><fan")) 
                    == Path::combine(curpwd , "Datatom/?><fan"));
#endif
    //cout<<endl<< Path::makeFullPath(String("../asdsdf/../../a")).getCStr()<<endl;
    for(int i=0; i<500; ++i) { p += "a"; }
    CPPUNIT_ASSERT(Path::makeFullPath(p) == Path::combine(curpwd,p));

    String relpath = _T("dir1/../dir2/dir21/../dir22");
    String realpath = _T("dir2/dir22");
    CPPUNIT_ASSERT(Path::makeFullPath(relpath) == Path::combine(curpwd,realpath));
}

void
PathTestCase::testIsAbsolutePath(void) {
    String p = "\\\\192.168.0.1\\home\\mnt";
    CPPUNIT_ASSERT(Path::isAbsolutePath(p) == true);
#ifdef __WINDOWS__
    p = "z:\\avstars\\something";
    CPPUNIT_ASSERT(Path::isAbsolutePath(p) == true);

    p = "hello world";
    CPPUNIT_ASSERT(Path::isAbsolutePath(p) == false);

    p = "\\\\c:iasdf";
    CPPUNIT_ASSERT(Path::isAbsolutePath(p) == true);
#else
    p = "/mnt/games/MassEffect2";
    CPPUNIT_ASSERT(Path::isAbsolutePath(p) == true);

    p = "hello world";
    CPPUNIT_ASSERT(Path::isAbsolutePath(p) == false);

    p = "\\\\c:iasdf";
    CPPUNIT_ASSERT(Path::isAbsolutePath(p) == true);
#endif
}

void
PathTestCase::testGetCurrentPath(void) {
	
	// TODO

    ////String src = getenv("DTSRC");
    ////CPPUNIT_ASSERT(Path::getCurrentPath() 
    ////                == Path::combine(src,"test_env/debug/x64/"));
}

void
PathTestCase::testGetDirectoryName(void) {
#ifdef __WINDOWS__
    String p1 = _T("\\\\c\\something\\list");
    String p2 = _T("\\\\c\\something\\");

    CPPUNIT_ASSERT(Path::getDirectoryName(p1) == String(_T("\\\\c\\somthing")));
    CPPUNIT_ASSERT(Path::getDirectoryName(p2) == String(_T("\\\\c\\somthing")));
#else
    String p1 = _T("/root/list/mnt/help");
    String p2 = _T("/root/list/mnt/");
    CPPUNIT_ASSERT(Path::getDirectoryName(p1) == String(_T("/root/list/mnt")));
    CPPUNIT_ASSERT(Path::getDirectoryName(p2) == String(_T("/root/list/mnt")));
#endif
    //printf("\n%s\n",Path::getDirectoryName(p1).getCStr());
    //printf("\n%s\n",Path::getDirectoryName(p2).getCStr());
    //printf("\n%s\n",Path::getDirectoryName(p3).getCStr());
    //printf("\n%s\n",Path::getDirectoryName(p4).getCStr());
}

void
PathTestCase::testGetFileName(void) {
    String p1 = _T("/root/list/mnt/help");
    String p2 = _T("/root/list/mnt/");
    //printf("\n%s\n",Path::getFileName(p1).getCStr());
    //printf("\n%s\n",Path::getFileName(p2).getCStr());
    CPPUNIT_ASSERT(Path::getFileName(p1) == String(_T("help")));
    CPPUNIT_ASSERT(Path::getFileName(p2) == String::EMPTY);
}
void 
PathTestCase::testGetPathRoot(void) {
    CPPUNIT_ASSERT(Path::getPathRoot(String(_T("hello"))) == String::EMPTY);
#ifdef __WINDOWS__
    String p2 = _T("C:\\mnt\\test\\a");
    //printf("\n%s\n",Path::getPathRoot(p2).getCStr());
    CPPUNIT_ASSERT(Path::getPathRoot(p2) == String(_T("C:\\")));

    String p1 = _T("\\\\192.168.0.1\\mnt\\movie");
    //printf("\n%s\n",Path::getPathRoot(p1).getCStr());
    CPPUNIT_ASSERT(Path::getPathRoot(p1) == String(_T("\\\\192.168.0.1\\mnt")));

#else
    String p1 = _T("//192.168.0.1/mnt/movie");
    //printf("\n%s\n",Path::getPathRoot(p1).getCStr());

    String p2 = _T("/mnt/test/a");
    CPPUNIT_ASSERT(Path::getPathRoot(p2) == String(_T("/")));
    CPPUNIT_ASSERT(Path::getPathRoot(p1) == String(_T("//192.168.0.1/mnt")));
#endif
}

void
PathTestCase::testChangeExtension(void) {
    String p1 = _T("/root/help");
    Path::changeExtension(p1,String(_T("txt")));
    CPPUNIT_ASSERT(p1 == String(_T("/root/help.txt")));

    p1 = _T("/root/help");
    Path::changeExtension(p1,String(_T(".txt")));
    CPPUNIT_ASSERT(p1 == String(_T("/root/help.txt")));

    String p2 = _T("/root/help.txt");
    Path::changeExtension(p2,String::EMPTY);
    CPPUNIT_ASSERT(p2== String(_T("/root/help")));

    String p3 = _T("/root/help.");
    Path::changeExtension(p3,String(_T(".txt")));
    //printf("\n%s\n",p3.getCStr());
    CPPUNIT_ASSERT(p3 == String(_T("/root/help..txt")));

    String p4 = _T("/root/help.pkg.tool");
    Path::changeExtension(p4,String(_T(".txt")));
    //printf("\n%s\n",p4.getCStr());
    CPPUNIT_ASSERT(p4 == String(_T("/root/help.pkg.txt")));

    String p5 = _T("/root/help.pkg.\\tool");
    Path::changeExtension(p5,String(_T(".txt")));
    //printf("\n%s\n",p5.getCStr());
    CPPUNIT_ASSERT(p5 == String(_T("/root/help.pkg.txt")));
}

void
PathTestCase::testAddExtension(void) {
    String p1 = _T("/root/help");
    Path::addExtension(p1, ".txt");
    CPPUNIT_ASSERT(p1 == String(_T("/root/help.txt")));

    String p2 = _T("/root/help");
    Path::addExtension(p2, "txt");
    CPPUNIT_ASSERT(p2 == String(_T("/root/help.txt")));
}

void
PathTestCase::testGetExtensionName(void) {
    String p1 = _T("/root/help");
    CPPUNIT_ASSERT(Path::getExtensionName(p1) == String::EMPTY);

    String p2 = _T("/root/help.pkg.tool");
    CPPUNIT_ASSERT(Path::getExtensionName(p2) == String(_T(".tool")));
}

void
PathTestCase::testIsValidPath(void) {
#ifdef __WINDOWS__
    String invalid = Path::getInvalidPathChars();
    String p1 = _T("root");
    for(size_t i=0; i<invalid.getLength(); i++) {
        CPPUNIT_ASSERT(Path::isValidPath(p1+invalid[i]) == false);
    }
    CPPUNIT_ASSERT(Path::isValidPath(p1+":") == false);

    p1 = _T("v:\\somedir:\\b");
    CPPUNIT_ASSERT(Path::isValidPath(p1) == false);

    //there's a GUID windows path like \\?\Volume{aaxxx-xxcccc}\xxxxx
    p1 = _T("z:\\testc\\somedir\\a.some");
    CPPUNIT_ASSERT(Path::isValidPath(p1) == true);

    p1 = _T("z:\\testc\\somedir\\简体中文.some");
    CPPUNIT_ASSERT(Path::isValidPath(p1) == true);
#else
    String p1 = _T("/usr/lib/include");
    CPPUNIT_ASSERT(Path::isValidPath(p1) == true);

    p1 = _T("/home/fan/桌面");
    CPPUNIT_ASSERT(Path::isValidPath(p1) == true);
    
    p1 = _T("/home/fan/\\/\\/\\");
    CPPUNIT_ASSERT(Path::isValidPath(p1) == true);
#endif
}

void
PathTestCase::testGetCurrentModulePath(void) {

	// todo


    //String p = Path::getCurrentModulePath();
    //String src = getenv("DTSRC");
    ////printf("\n%s\n",p.getCStr());
    //CPPUNIT_ASSERT(p == Path::combine(src, String(_T("test_env/debug/x64/"))));
}

void
PathTestCase::testEqual(void) {
    String p1 = _T("/root/dor ");
    String p2 = _T("/root/dor/ ");
    CPPUNIT_ASSERT(Path::equal(p1,p2) == false);
    CPPUNIT_ASSERT(Path::equal(p2,p1) == false);

    p1 = _T("/root/dor");
    p2 = _T("/root/c/../dor");
    CPPUNIT_ASSERT(Path::equal(p1,p2) == true);
}

void
PathTestCase::testIsParentPath(void) {
    String p1 = _T("/root/father");
    String p2 = _T("/root/father/son");
    CPPUNIT_ASSERT(Path::isParentPath(p1, p2));

    p1 = _T("/root//father");
    p2 = _T("/root/father/son");
    CPPUNIT_ASSERT(Path::isParentPath(p1, p2));

    p1 = _T("/root/father");
    p2 = _T("/root//father/son");
    CPPUNIT_ASSERT(Path::isParentPath(p1, p2));

    p1 = _T("/root/father/");
    p2 = _T("/root//father/son");
    CPPUNIT_ASSERT(Path::isParentPath(p1, p2));

    p1 = _T("/root/father/");
    p2 = _T("/root//father/son/");
    CPPUNIT_ASSERT(Path::isParentPath(p1, p2));
}

void
PathTestCase::testGetInvalidPathChars(void) {
    String ipc = Path::getInvalidPathChars();
    
    const tchar_t invalidPathChars[] = {
#if defined(__WINDOWS__)
        '"',				/* double quote, which seems allowed in MS.NET but should be rejected */
        '<',				/* less than */
        '>',				/* greater than */
        //'/',
        //'\\',
        '|',				/* pipe */
        //'*',
        //'?',
        0x08,				/* backspace */
        0x10,				/* data link escape */
        0x11,				/* device control 1 */
        0x12,				/* device control 2 */
        0x13,				/* device control 3 */
        0x14,				/* device control 4 */
        0x15,				/* negative acknowledge */
        0x16,				/* synchronous idle */
        0x17,				/* end of trans, block */
        0x18,				/* cancel */
        0x19,				/* substitute */
#else
        //'/',              /* '/' in linux is root path.*/
#endif
        0x0000				/* null */
    };

    CPPUNIT_ASSERT(ipc == String(invalidPathChars));
}

void
PathTestCase::testGetSeparatorChars(void) {
    String sep = Path::getSeparatorChars();
#ifdef __WINDOWS__
    CPPUNIT_ASSERT(sep == String(_T("\\/")));
#else
    CPPUNIT_ASSERT(sep == String(_T("//")));
#endif
}

void
PathTestCase::testAdaptSep(void) {
#ifdef __WINDOWS__
    String p1 = _T("\\/cdefg\\\\../a");
    CPPUNIT_ASSERT(Path::adaptSep(p1) == String(_T("\\\\cdefg\\..\a")));

    String p2 = _T("///server/.//..?s/");
    CPPUNIT_ASSERT(Path::adaptSep(p2) 
                 == String(_T("\\\\\\server\\.\\..?s\\")));

#else
    String p1 = "\\//cdefg\\\\../a";
    CPPUNIT_ASSERT(Path::adaptSep(p1) == String(_T("\\/cdefg\\\\../a")));

    String p2 = "///server/.//..?s/";
    CPPUNIT_ASSERT(Path::adaptSep(p2) 
                 == String(_T("/server/./..?s/")));

    String p3 = "//server/.//..?s/";
    CPPUNIT_ASSERT(Path::adaptSep(p3) 
                 == String(_T("//server/./..?s/")));
#endif
}

void
PathTestCase::testSplit(void) {
    String dir,file;
#ifdef __WINDOWS__
    //TODO compelete windows testcase
    String p1 = "c:";
    String p2 = "\\\\?\\volume{longlong}\\somethin";
    String p3 = "\\\\.\\device\\mnt";
#else
    String p1 = "//";
    String p2 = "//c";
    String p3 = "//server/mnt/license";
    String p4 = "//server/mnt/license/";
    String p5 = "///server///mnt/license/";
    Path::split(p1, dir, file);
    CPPUNIT_ASSERT(dir == String(_T("//")));
    CPPUNIT_ASSERT(file == String::EMPTY);

    Path::split(p2, dir, file);
    CPPUNIT_ASSERT(dir == String("//"));
    CPPUNIT_ASSERT(file == String("c"));

    Path::split(p3, dir, file);
    CPPUNIT_ASSERT(dir == String("//server/mnt"));
    CPPUNIT_ASSERT(file == String("license"));

    Path::split(p4, dir, file);
    CPPUNIT_ASSERT(dir == String("//server/mnt/license"));
    CPPUNIT_ASSERT(file == String::EMPTY);

    Path::split(p5, dir, file);
    CPPUNIT_ASSERT(dir == String("/server/mnt/license"));
    CPPUNIT_ASSERT(file == String::EMPTY);
#endif
}
