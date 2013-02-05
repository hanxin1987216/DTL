#
# Makefile file for DTL
# Author: hanxin
#

# Defines the basic path for current directory

TARGET_TYPE = so
MODULE_NAME = libdtl

#
# 依赖
NEED_TCMALLOC = 1
NEED_ZLIB = 1
NEED_POCO = 1
NEED_LIBMAGIC = 1
NEED_LEVELDB = 1


#
# 头文件目录
#
CUSTOM_CXXFLAGS = -I$(DTDEPS)/mysql/include  -D__MAKE_DTL_DLL__ 

CUSTOM_LIB_FLAGS = -lpthread -lglib-2.0 -ldl -luuid

#  
# 源代码路径, 必须使用 : 隔开, 不能有空格...
#
VPATH = ./:./mono_base


#
# 资源文件
#
DO_RES_FILES = dtl.res


#
# 配置文件
#
CONFIG_FILES = conf/dtl.config	\
				conf/filetool.rule	\
				conf/magic
				
#
# 自定义 ALL 参数
#
CUSTOM_COPY_FILES = copy_deps_files


# All C files of (from mono)

ALL_C_FILES = \
	./mono_base/atomic.c \
	./mono_base/collection.c \
	./mono_base/critical-sections.c \
	./mono_base/sys-error.c \
	./mono_base/events.c \
	./mono_base/handles.c \
	./mono_base/io.c \
	./mono_base/misc.c \
	./mono_base/mutexes.c \
	./mono_base/mono-mutex.c \
	./mono_base/processes.c \
	./mono_base/shared.c \
	./mono_base/threads.c \
	./mono_base/timefuncs.c \
	./mono_base/wait.c \
	./mono_base/strenc.c \
	./util/linenoise.c
	


	
ALL_CPP_FILES =	./lang/string.cpp	\
				./lang/int64.cpp	\
				./lang/int.cpp	\
				./lang/uint.cpp	\
				./lang/char.cpp	\
					\
					\
				./sys/exception.cpp	\
				./sys/errorprovider.cpp	\
				./sys/lockfile.cpp	\
				./sys/lock.cpp	\
				./sys/timer.cpp	\
				./sys/date.cpp	\
				./sys/process.cpp	\
				./sys/locale.cpp	\
				./sys/timezone.cpp	\
				./sys/dateformat.cpp	\
				./sys/timediff.cpp	\
				./sys/thread.cpp	\
				./sys/library.cpp	\
				./sys/daemon.cpp	\
				./sys/slog.cpp		\
				./sys/env.cpp		\
				./sys/runtime.cpp	\
				./sys/signal_handler.cpp	\
					\
					\
				./io/comdef.cpp		\
				./io/basefile.cpp	\
				./io/path.cpp		\
				./io/basefile.cpp		\
				./io/file.cpp		\
				./io/directory.cpp	\
				./io/streamwriter.cpp	\
				./io/streamreader.cpp	\
				./io/filestream.cpp	\
				./io/fileinputstream.cpp \
				./io/fileoutputstream.cpp \
				./io/volume.cpp	\
				./io/filetool.cpp	\
					\
					\
				./net/httpsocket.cpp	\
				./net/json.cpp	\
				./net/jsontextwriter.cpp	\
				./net/bson.cpp	\
				./net/bcon.cpp	\
				./net/encoding.cpp	\
				./net/cgi.cpp	\
				./net/cgiexcept.cpp	\
				./net/cgiutil.cpp	\
				./net/smtp.cpp	\
					\
					\
				./util/util.cpp	\
				./util/resreader.cpp	\
				./util/guid.cpp	\
				./util/gzcompress.cpp	\
				./util/compress.cpp	\
				./util/random.cpp	\
				./util/hash.cpp	\
				./util/performance.cpp	\
				./util/devicemgm.cpp	\
					\
					\
				./log/log.cpp	\
					\
					\
				./security/rijndael.cpp	\
				./security/md5.cpp	\
				./security/encrypt.cpp	\
				./security/base16.cpp	\
				./security/base64.cpp	\
				./security/rc4.cpp		\
				./security/sha1.cpp		\
					\
					\
				./config/tinyxml/tinystr.cpp	\
				./config/tinyxml/tinyxml.cpp	\
				./config/tinyxml/tinyxmlerror.cpp	\
				./config/tinyxml/tinyxmlparser.cpp	\
				./config/configfile.cpp	\
					\
					\
				./mono_base/localemap.cpp	\
					\
					\
				./rude/rudesession/AbstractData.cpp	\
				./rude/rudesession/AbstractPersistance.cpp	\
				./rude/rudesession/Base64Encoder.cpp	\
				./rude/rudesession/ConfigFilePersistance.cpp	\
				./rude/rudesession/Configuration.cpp	\
				./rude/rudesession/Converter.cpp	\
				./rude/rudesession/Cookie.cpp	\
				./rude/rudesession/CookieParser.cpp	\
				./rude/rudesession/CookieReader.cpp	\
				./rude/rudesession/DatabasePersistance.cpp	\
				./rude/rudesession/DataStore.cpp	\
				./rude/rudesession/IDGenerator.cpp	\
				./rude/rudesession/Implementation.cpp	\
				./rude/rudesession/IPValidator.cpp	\
				./rude/rudesession/MetaData.cpp	\
				./rude/rudesession/Session.cpp	\
					\
					\
				./rude/rudedatabase/database.cpp	\
				./rude/rudedatabase/implementation.cpp	\
				./rude/rudedatabase/mysqlloaddll.cpp	\
					\
					\
				./rude/rudeconfig/AbstractData.cpp	\
				./rude/rudeconfig/AbstractOrganiser.cpp	\
				./rude/rudeconfig/AbstractParser.cpp	\
				./rude/rudeconfig/AbstractWriter.cpp	\
				./rude/rudeconfig/Base64Encoder.cpp	\
				./rude/rudeconfig/Comment.cpp	\
				./rude/rudeconfig/config.cpp	\
				./rude/rudeconfig/ConfigImpl.cpp	\
				./rude/rudeconfig/DataLine.cpp	\
				./rude/rudeconfig/File.cpp	\
				./rude/rudeconfig/KeyValue.cpp	\
				./rude/rudeconfig/ParserJuly2004.cpp	\
				./rude/rudeconfig/RealOrganiser.cpp	\
				./rude/rudeconfig/Section.cpp	\
				./rude/rudeconfig/WhiteSpace.cpp	\
				./rude/rudeconfig/Writer.cpp	\
					\
					\
				./dtl.cpp
				
include $(DTSRC)/config.gcc


#
# 编译dtl顺便将依赖的so 文件拷贝到 test_env 目录下
#
copy_deps_files:
	@echo ------------------------------------
	@echo ---copy deps so file ---
	@echo ------------------------------------
	
	cp $(DTDEPS)/zlib/lib/$(CPU)/*  $(TEST_ENV) -rf
	cp $(DTDEPS)/poco/lib/$(CPU)/*  $(TEST_ENV) -rf
	cp $(DTDEPS)/magic/lib/$(CPU)/* $(TEST_ENV) -rf
	cp $(DTDEPS)/leveldb/lib/$(CPU)/* $(TEST_ENV) -rf
	cp $(DTDEPS)/snappy/lib/$(CPU)/* $(TEST_ENV) -rf
	cp $(DTDEPS)/tcmalloc/lib/$(CPU)/* $(TEST_ENV) -rf