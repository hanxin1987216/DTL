/***************************************************************************************************
directorytc.cpp:	
	C++ Foundation Library TestCase cpp files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
	Directory 测试

Author:
	fan.fei@datatom.com

Creating Time:
	2012-3-19
***************************************************************************************************/
#include <dtprec.h>
#include <cppunit/tester.h>
#include <dtl/dtl.h>

#include "directorytc.h"

CPPUNIT_TEST_SUITE_REGISTRATION( DirectoryTestCase );

void
DirectoryTestCase::setUp(void) {
}

void 
DirectoryTestCase::tearDown(void) {
}

void
DirectoryTestCase::testExists(void) {
    Directory dr = Directory(".");
    //this dir must be exists
    CPPUNIT_ASSERT(dr.exists() == true);
    dr = Directory("ithinkthisdirisnotexistsinnonecomputeronearthormars");
    CPPUNIT_ASSERT(dr.exists() == false);
#ifdef __WINDOWS__       
#else
    dr = Directory("/usr/include");
    CPPUNIT_ASSERT(dr.exists() == true);
#endif
}

void
DirectoryTestCase::testGetName(void) {
    Directory dr = Directory(".");
    //printf("\n%s\n",dr.getName().getCStr());
    CPPUNIT_ASSERT(dr.getName() == String(_T(".")));
#ifdef __WINDOWS__       
    dr = Directory("C:\\windows\\system32");
    CPPUNIT_ASSERT(dr.getName() == String(_T("C:\\windows\\system32")));
#else
    Directory dr1 = Directory("/usr/include");
    //printf("\n%s\n",dr1.getName().getCStr());
    CPPUNIT_ASSERT(dr1.getName() == String(_T("include")));

    Directory dr2 = Directory("//usr//include/");
    CPPUNIT_ASSERT(dr2.getName() == String::EMPTY);
#endif
}

void
DirectoryTestCase::testCreate(void) {
    Directory dr = Directory("./testdirectory");
    CPPUNIT_ASSERT_NO_THROW(dr.removeTree());
    CPPUNIT_ASSERT(dr.exists() == false);
    CPPUNIT_ASSERT_NO_THROW(dr.create());
    CPPUNIT_ASSERT(dr.exists() == true);
    CPPUNIT_ASSERT_NO_THROW(dr.create());
    CPPUNIT_ASSERT_NO_THROW(dr.removeTree());

    dr = Directory("");
    CPPUNIT_ASSERT_THROW(dr.create(), Exception);
    dr = Directory(" ");
    CPPUNIT_ASSERT_THROW(dr.create(), Exception);
}

void
DirectoryTestCase::testCreateSubDirectory(void) {
    Directory dr = Directory("./testdirectory");
    if (!dr.exists()) { 
        dr.create(); 
    }
#ifdef __WINDOWS__
#else
    String subdr = "test\\sub";
    Directory dsub = dr.createSubDirectory(subdr);
    CPPUNIT_ASSERT(dsub.getName() == String(_T("test\\sub")));
    CPPUNIT_ASSERT(dsub.exists());
#endif
}

/**
 * create sub dir {sub1,sub2,sub3} and files {f1,f2,f3}
 * in currentdir/testDirectory
 *
 */
static void createTestDir(void) {
    Directory dr = Directory("./testdirectory");
    if (dr.exists()) { 
        dr.removeTree();
        dr.create(); 
    }
    dr.createSubDirectory(String(_T("sub1")));
    dr.createSubDirectory(String(_T("sub2")));
    dr.createSubDirectory(String(_T("sub3")));

    String fname = "./testdirectory/f";
    //String text = "test file";
    char text[] = "test file";
    for (int i=1; i<4 ; i++) {
        fname << i;
        FileOutputStream fo(fname, CREATE_MODE);
        //fo.write(text.getCStr(), text.getLength());
        fo.write((const unsigned char *)text, strlen(text));
        fo.close();
    }
}


#define INFILES(s,prefix) \
    (s == prefix"f1" || s == prefix"f12" || s == prefix"f123")

#define INDIRS(s,prefix) \
    (s == prefix"sub1" || s == prefix"sub2" || s == prefix"sub3")

void
DirectoryTestCase::testList(void) {
    createTestDir();
    vector<String> strlist;
    vector<Directory> dirlist;
    Directory dr = Directory("./testdirectory");


    //String tmp = "./testdirectory/f1";

    //CPPUNIT_ASSERT(INFILES(tmp,"./testdirectory/") || INDIRS(tmp,"./testdirectory"));

    CPPUNIT_ASSERT(dr.exists() == true);
    dr.list(strlist);
    dr.list(dirlist);
    for (vector<String>::iterator it = strlist.begin();
            it != strlist.end(); ++it) {
        //cout<< it->getCStr()<< " ";
        CPPUNIT_ASSERT(INFILES(*it, "./testdirectory/") || INDIRS(*it, "./testdirectory/"));
    }



    for (vector<Directory>::iterator it = dirlist.begin();
            it != dirlist.end(); ++it) {
        //cout<< it->getName().getCStr()<< " ";
        CPPUNIT_ASSERT(INFILES(it->getName(),"") || INDIRS(it->getName(),""));
    }
}

void
DirectoryTestCase::testListDirs(void) {
    createTestDir();
    vector<String> strlist;
    vector<Directory> dirlist;
    Directory dr = Directory("./testdirectory");
    CPPUNIT_ASSERT(dr.exists() == true);

    dr.listDirs(strlist);
    dr.listDirs(dirlist);
    for (vector<String>::iterator it = strlist.begin();
            it != strlist.end(); ++it) {
        //cout<< it->getCStr()<< " ";
        CPPUNIT_ASSERT(INDIRS(*it, "./testdirectory/"));
    }



    for (vector<Directory>::iterator it = dirlist.begin();
            it != dirlist.end(); ++it) {
        //cout<< it->getName().getCStr()<< " ";
        CPPUNIT_ASSERT(INDIRS(it->getName(),""));
    }
}

void
DirectoryTestCase::testListFiles(void) {
    createTestDir();
    vector<String> strlist;
    vector<File> filelist;
    Directory dr = Directory("./testdirectory");
    CPPUNIT_ASSERT(dr.exists() == true);

    dr.listFiles(strlist);
    dr.listFiles(filelist);
    for (vector<String>::iterator it = strlist.begin();
            it != strlist.end(); ++it) {
        //cout<< it->getCStr()<< " ";
        CPPUNIT_ASSERT(INFILES(*it, "./testdirectory/"));
    }



    for (vector<File>::iterator it = filelist.begin();
            it != filelist.end(); ++it) {
        //cout<< it->getName().getCStr()<< " ";
        CPPUNIT_ASSERT(INFILES(it->getName(),""));
    }

}


void
DirectoryTestCase::testGetParent(void) {
    createTestDir();
    Directory dr = Directory("./testdirectory");
    String curdir = Path::getCurrentPath();
    //printf("\n%s\n",curdir.getCStr()),
    //printf("\n%s\n",Path::makeFullPath(dr.getParent().getName()).getCStr());
    CPPUNIT_ASSERT(
            Path::equal(dr.getParent().getName()
                        + Path::separator, 
            curdir) == true);
}

void
DirectoryTestCase::testIsRoot(void) {
    Directory dr = Directory(".");
    CPPUNIT_ASSERT(dr.isRoot() == false);

    Directory dr2 = Directory("/");
    CPPUNIT_ASSERT(dr2.isRoot() == true);
}


void
DirectoryTestCase::testRemove(void) {
    createTestDir();
    Directory dr = Directory("./testdirectory");
    CPPUNIT_ASSERT_THROW(dr.remove(), Exception);
    dr.removeTree();
    CPPUNIT_ASSERT(dr.exists() == false);
}
