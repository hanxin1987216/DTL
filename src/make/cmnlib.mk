#
# Configuration file for common lib
# Author: han.xin@datatom.com
#

####################################################################################################
COMMON_LIB_PATH = $(BUILD_PATH)


#################################
# DTL
#
ifeq ("$(NEED_DTL)", "1")
DTL_LIB = -ldtl
DTL_INCLUDE = -DUSE_DTL_DLL -D__USING_DTL__ -I$(DTSRC)/common 

NEED_ZLIB = 1
NEED_TCMALLOC = 1
NEED_POCO = 1
NEED_LIBMAGIC = 1
NEED_LEVELDB = 1

endif

#################################
# need POCO
#
ifeq ("$(NEED_POCO)", "1")

ifeq ("$(BUILD)", "debug")
	LIB_POCO_LIB = -L$(DTDEPS)/poco/lib/$(CPU) -lPocoFoundationd -lPocoNetd -lPocoUtild -lPocoXMLd
	LIB_POCO_INCLUDE = -I$(DTDEPS)/poco/include
else
	LIB_POCO_LIB = -L$(DTDEPS)/poco/lib/$(CPU) -lPocoFoundation -lPocoNet -lPocoUtil -lPocoXML
	LIB_POCO_INCLUDE = -I$(DTDEPS)/poco/include
endif	
	
endif


#################################
# need log 
#
ifeq ("$(NEED_LOG)", "1")
LOG_LIB = -lpthread -llog
LOG_INCLUDE = -I$(DTSRC)/common/log 
endif

#################################
# tokyocabinet
#
ifeq ("$(NEED_TOKYOCABINET)", "1")
TOKYOCABINET_LIB = -L$(DTDEPS)/tokyocabinet/lib/$(CPU) -ltokyocabinet
TOKYOCABINET_INCLUDE = -I$(DTDEPS)/tokyocabinet/include/ 
endif

#################################
# leveldb
#
ifeq ("$(NEED_LEVELDB)", "1")
LEVELDB_LIB = -L$(DTDEPS)/leveldb/lib/$(CPU) -lleveldb -L$(DTDEPS)/snappy/lib/$(CPU) -lsnappy
LEVELDB_INCLUDE = -I$(DTDEPS)/leveldb/include/ -I$(DTDEPS)/snappy/include/ 
endif


#################################
# sqlite3
#
ifeq ("$(NEED_SQLITE3)", "1")
SQLITE3_LIB = -L$(DTDEPS)/sqlite3/lib/$(CPU) -lsqlite3
SQLITE3_INCLUDE = -I$(DTDEPS)/sqlite3/include
endif



#################################
# mysql
#
ifeq ("$(NEED_MYSQL)", "1")
MYSQL_LIB = -L$(DTDEPS)/mysql/lib/$(CPU) -lmysqlclient
MYSQL_INCLUDE = -I$(DTDEPS)/mysql/include
endif

#################################
# ADO
#
ifeq ("$(NEED_ADO)", "1")
ADO_LIB =  -L$(DTDEPS)/sqlite3/lib/$(CPU) -lsqlite3 \
			-L$(DTDEPS)/mysql/lib/$(CPU) -lmysqlclient \
			-L$(DTDEPS)/tokyocabinet/lib/$(CPU) -ltokyocabinet \
			-L$(DTDEPS)/leveldb/lib/$(CPU) -lleveldb	\
			-L$(DTDEPS)/snappy/lib/$(CPU) -lsnappy	\
			-L$(DTDEPS)/hiredis/lib/$(CPU) -lhiredis	\
			-lado
ADO_INCLUDE = -I$(DTSRC)/common -I$(DTDEPS)/sqlite3/include \
			-I$(DTDEPS)/mysql/include  	\
			-I$(DTDEPS)/tokyocabinet/include/ \
			-I$(DTDEPS)/leveldb/include/ 	\
			-I$(DTDEPS)/snappy/include/	\
			-I$(DTDEPS)/hiredis/include 
			
endif



#################################
# need netframework 
#
ifeq ("$(NEED_NETFRAME)", "1")
LIBNEED_NETFRAME_LIB = -lnetframework 
LIBNEED_NETFRAME_INCLUDE = -I$(DTSRC)/common  -D__USE_NETFRAME_DLL__
endif

#################################
# need tcmalloc 
#
ifeq ("$(NEED_TCMALLOC)", "1")
TCMALLOC_LIB = -L$(DTDEPS)/tcmalloc/lib/$(CPU) -ltcmalloc -lunwind
TCMALLOC_INCLUDE = -I$(DTDEPS)/tcmalloc/include
endif


#################################
# need IDML
#
ifeq ("$(NEED_IDML)", "1")
IDML_LIB = -lidmlprotocol -lidmlbll
IDML_INCLUDE = -I$(DTSRC)/dtcore/idml
endif


#################################
# need idml protocol 
#
ifeq ("$(NEED_IDMLPROTOCOL)", "1")
PROTOCOL_LIB = -lidmlprotocol
PROTOCOL_INCLUDE = -I$(DTSRC)/dtcore/idml
endif

#################################
# need idml archive 
#
ifeq ("$(NEED_IDMLARCHIVE)", "1")
ARCHIVE_LIB = -lidmlarchive
ARCHIVE_INCLUDE = -I$(DTSRC)/dtcore/idml/sdk
endif


####################
# Python
#
ifeq ("$(NEED_PYTHON)", "1")
PYTHON_LIB = -lpython
PYTHON_INCLUDE = -I$(DTDEPS)/python/include
endif



#################################
# libz
#
ifeq ("$(NEED_ZLIB)", "1")
ZLIB_LIB = -L$(DTDEPS)/zlib/lib/$(CPU) -lz
ZLIB_INCLUDE = -I$(DTDEPS)/zlib/include
endif



#################################
# CPPUNIT
#
ifeq ("$(NEED_CPPUNIT)", "1")
CPPUNIT_LIB = -lcppunit
CPPUNIT_INCLUDE = -I$(DTSRC)/common -I$(DTSRC)/common/cppunit
endif



####################
# Ffmpeg
#
ifeq ("$(NEED_MEDIA)", "1")
MEDIA_LIB = -lffmpegmgm -lmedia -lavformat -lavcodec -lswscale -lavutil -lpostproc -lavdevice -ljpeg
MEDIA_INCLUDE = -I$(DTDEPS)/ffmpeg/include
endif


####################
# OpenLdap
#
ifeq ("$(NEED_OPENLDAP)", "1")
OPENLDAP_LIB = -L$(DTDEPS)/openldap/lib/$(CPU) -lldap
OPENLDAP_INCLUDE = -I$(DTDEPS)/openldap/include
endif


#################################
# SYSTEM 
#
ifeq ("$(NEED_SYSTEM)", "1")
LIBSYSTEM_LIB = -lsystem 
LIBSYSTEM_INCLUDE = -I$(DTSRC)/dtcore/system/
endif

#################################
# IDML client sdk
#
ifeq ("$(NEED_IDMLCLIENT)", "1")
LIBIDMLCLIENT_LIB = -lidmltcp -lidmlhttp
LIBIDMLCLIENT_INCLUDE = -I$(DTSRC)/dtcore/idml/sdk
endif


#################################
# LIBCURL
#
ifeq ("$(NEED_CURL)", "1")
CURL_LIB = -L$(DTDEPS)/libcurl/lib/$(CPU) -lcurl
CURL_INCLUDE = -I$(DTDEPS)/libcurl/include/
endif

#################################
# LIBXAPIAN
#
ifeq ("$(NEED_XAPIAN)", "1")
XAPIAN_LIB = -L$(DTDEPS)/xapian/lib/x64 -lxapian
XAPIAN_INCLUDE = -I$(DTDEPS)/xapian/include
endif

#################################
# LIBMMSEG
#
ifeq ("$(NEED_MMSEG)", "1")
MMSEG_LIB = -L$(DTDEPS)/libmmseg/lib/$(CPU) -lmmseg -lmmsegmgm
MMSEG_INCLUDE = -I$(DTDEPS)/libmmseg/include
endif

#################################
# libmagic
#
ifeq ("$(NEED_LIBMAGIC)", "1")
LIBMAGIC_LIB = -L$(DTDEPS)/magic/lib/$(CPU) -lmagic
LIBMAGIC_INCLUDE = -I$(DTDEPS)/magic/include
endif


ifeq ("$(NEED_VERSION)", "1")
VERSION_LIB = -lversion
VERSION_INCLUDE =
endif

##################################
# lib catalogtemplate
#
ifeq ("$(NEED_CATALOGTEMPLATE)", "1")
CATALOGTEMPLATE_LIB = -lcatalogtemplate
CATALOGTEMPLATE_INCLUDE =
endif

#################################
# libimage
#
ifeq ("$(NEED_IMAGE)", "1")
IMAGE_LIB = -L$(DTDEPS)/image/lib/$(CPU) -lfreeimage -lgd -limage
IMAGE_INCLUDE = -I$(DTDEPS)/image/include
endif

##################################
# lib catatogtemplatemgm (it is not the same with catalogtemplate!)
#
ifeq ("$(NEED_CATALOGTEMPLATEMGM)", "1")
CATALOGTEMPLATEMGM_LIB = -lcatalogtemplatemgm
CATALOGTEMPLATEMGM_INCLUDE =
endif

ifeq ("$(NEED_CATALOGMGM)", "1")
CATALOGMGM_LIB = -lcatalogmgm
CATALOGMGM_INCLUDE = -DUSE_CATALOGMGM_DLL__ -D__USE_CATALOGMGM_DLL__
endif

ifeq ("$(NEED_MEDIASPACE)", "1")
MEDIASPACEMGM_LIB = -lmediaspace
MEDIASPACEMGM_INCLUDE =
endif

ifeq ("$(NEED_USERSHAREMGM)", "1")
USERSHAREMGM_LIB = -lusersharemgm
USERSHAREMGM_INCLUDE = -DUSE_USERSHAREMGM_DLL__ -D__USE_USERSHAREMGM_DLL__
endif

ifeq ("$(NEED_USERMGM)", "1")
DUSER_LIB = -lusermgm
DUSER_INCLUDE = -I$(DTSRC)/dtcore/user
endif

ifeq ("$(NEED_TASKMGM)", "1")
TASKMGM_LIB = -ltaskmgm
TASKMGM_INCLUDE = -I$(DTSRC)/dtcore
endif

ifeq ("$(NEED_SHAREMGM)", "1")
SHAREMGM_LIB = -lshare
SHAREMGM_INCLUDE =  -DUSE_CIFSMGM_DLL__ -D__USE_CIFSMGM_DLL__
endif

ifeq ("$(NEED_STORAGE)", "1")
STORAGEMGM_LIB = -lstorage
STORAGEMGM_INCLUDE = -DUSE_STORAGEMGM_DLL__ -D__STORAGEMGM_DLL__
endif


ifeq ("$(NEED_FULLTEXT)", "1")
FULLTEXT_LIB = -lfulltext
FULLTEXT_INCLUDE = -I$(DTSRC)/dtcore/fulltext
endif

ifeq ("$(NEED_WORKFLOW)", "1")
WORKFLOW_LIB = -lworkflowmgm
WORKFLOW_INCLUDE = -I$(DTSRC)/dtcore/workflow
endif

#################################
# LIBREDIS
#
ifeq ("$(NEED_REDIS)", "1")
REDIS_LIB = -L$(DTDEPS)/hiredis/lib/$(CPU)  -lhiredis
REDIS_INCLUDE = -I$(DTDEPS)/hiredis/include
endif



CMN_LIB = -L$(COMMON_LIB_PATH) $(DTL_LIB) $(LIBNEED_NETFRAME_LIB) $(LOG_LIB) \
			$(LIBIDMLCLIENT_LIB) $(TOKYOCABINET_LIB) \
			$(MYSQL_LIB) $(SQLITE3_LIB) $(ZLIB_LIB) $(CPPUNIT_LIB) $(ADO_LIB) $(CURL_LIB) \
			$(LIBMAGIC_LIB)	 $(CATALOGMGM_LIB) $(CATALOGTEMPLATE_LIB) $(CATALOGTEMPLATEMGM_LIB)   \
			$(MEDIASPACEMGM_LIB) $(LIB_POCO_LIB) $(XAPIAN_LIB) $(MMSEG_LIB)	\
			$(USERSHAREMGM_LIB) $(PYTHON_LIB) $(DUSER_LIB) \
			$(MEDIA_LIB) $(TASKMGM_LIB) $(PROTOCOL_LIB)	\
			$(TCMALLOC_LIB)	$(IDML_LIB) $(LIBSYSTEM_LIB) $(LEVELDB_LIB)  $(VERSION_LIB)	\
			$(SHAREMGM_LIB)	$(STORAGEMGM_LIB) $(FULLTEXT_LIB) $(WORKFLOW_LIB) $(ARCHIVE_LIB)	\
			$(CEPH_LIB) $(REDIS_LIB) $(IMAGE_LIB) $(OPENLDAP_LIB)
		
CMN_LIB_INCLUDE = $(DTL_INCLUDE) $(LIBNEED_NETFRAME_INCLUDE) \
					$(LIBIDMLCLIENT_INCLUDE)	\
					$(TOKYOCABINET_INCLUDE) $(MYSQL_INCLUDE) $(SQLITE3_INCLUDE) \
					$(ZLIB_INCLUDE) $(CPPUNIT_INCLUDE) $(ADO_INCLUDE) $(CURL_INCLUDE) 	\
					$(LIB_POCO_INCLUDE) $(XAPIAN_INCLUDE) $(MMSEG_INCLUDE)	$(MEDIA_INCLUDE) \
					$(LIBMAGIC_INCLUDE) $(PYTHON_INCLUDE) $(DUSER_INCLUDE)	\
					$(TASKMGM_INCLUDE) $(PROTOCOL_INCLUDE) $(LOG_INCLUDE) \
					$(TCMALLOC_INCLUDE) $(IDML_INCLUDE) $(LIBSYSTEM_INCLUDE) $(LEVELDB_INCLUDE) $(VERSION_INCLUDE)	\
					$(SHAREMGM_INCLUDE) $(MEDIASPACEMGM_INCLUDE) $(STORAGEMGM_INCLUDE)	\
					$(FULLTEXT_INCLUDE) $(CATALOGTEMPLATE_INCLUDE) $(CATALOGTEMPLATEMGM_INCLUDE) $(WORKFLOW_INCLUDE)	\
					$(ARCHIVE_INCLUDE) $(CEPH_INCLUDE) $(REDIS_INCLUDE) $(IMAGE_INCLUDE) $(OPENLDAP_INCLUDE)

				
				
