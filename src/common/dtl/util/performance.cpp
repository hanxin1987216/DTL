/***************************************************************************************************
performance.h:
	Copyright (c) Datatom Software, Inc.(2011 - ~), All rights reserved
	
Purpose:
	
	性能剖析

Author:
	han.xin@datatom.com
	
Creating Time:
	2008-08-11
***************************************************************************************************/

#include <dtprec.h>
#include "../prec.h"
#include "../lang/string.h"
#include "../sys/exception.h"
#include "../mono_base/uglify.h"
#include "../io/comdef.h"
#include "../io/path.h"
#include "../io/file.h"
#include "../io/directory.h"
#include "../io/streamwriter.h"

#include "../sys/lock.h"


#include "performance.h"

String
makeKey (const String& file, const String& function, int line, const String& remark)
{
	String temp;
	temp += file;
	temp += String (_T(":"));
	temp += String::toString ((int) line);
	temp += String (_T(" ["));
	temp += function;
	temp += String (_T(" ()"));

	if (remark.isEmpty () == false) {
		temp += String (_T(" - "));
		temp += remark;
	}

	temp += String (_T("]"));
	return temp;
}

//
// 将花费时间转换为字符串
//
String
timeToString (double seconds)
{
	String time, tmp;

	if ((int) seconds <= 0) {
		tmp.format (_T("%f s"), seconds);
		time += tmp;
	}
	else {
		if ((int) (seconds) / 3600 > 0) {
			tmp.format (_T("%d h "), (int) (seconds) / 3600);
			time += tmp;
		}

		if ((int) (seconds) / 60 > 0) {
			tmp.format (_T("%d m "), (int) (seconds) / 60);
			time += tmp;
		}

		if ((int) (seconds) % 60) {
			int number = (int) (seconds) % 60;
			tmp.format (_T("%d.%d s"), number, (int) ((seconds - number) * 1000000));
			time += tmp;
		}
	}
	return time;
}

//
// 保存结果操作
//
class ncSaveOperator
{
public:
	void save (const tchar_t* fmt, ...) const
	{
		String tmp;

		va_list ap;
		va_start (ap, fmt);

		tmp.formatv (fmt, ap);

		va_end (ap);

		write (tmp);
	}

	virtual void write (const String& str) const = 0;
};

//
// 打印结果
//
class ncPrintSaveOperator : public ncSaveOperator
{
public:
	virtual void write (const String& str) const
	{
		cout << str.getCStr () << endl;
	}
};

//
// 保存结果到文件
//
class ncFileSaveOperator : public ncSaveOperator
{
public:
	ncFileSaveOperator (const String& file)
		: _writer (0)
	{
		Directory dir (Path::getDirectoryName (file));
		if (dir.exists () == false)
			dir.create ();
		
		_writer = new StreamWriter (file, true);
	}

	~ncFileSaveOperator (void)
	{
		delete _writer;
		_writer = 0;
	}

	virtual void write (const String& str) const
	{
		_writer->writeLine (str);
	}

private:
	StreamWriter* _writer;
};

//
// 排序
//
struct ncTempNode
{
	String				pos;
	ProfilerObject	object;
};

bool ncCountSort (const ncTempNode& left, const ncTempNode& right)
{
	return left.object.count < right.object.count;
}

bool ncTimeSort (const ncTempNode& left, const ncTempNode& right)
{
	return left.object.useTime < right.object.useTime;
}

void ncSaveResult (double useTime, const ProfilerMap& map, const ncSaveOperator* opt)
{
	if (opt == 0)
		return;

	vector <ncTempNode> nodes;
	nodes.reserve (map.size ());

	opt->save (_T("\r\n\r\n\r\n\r\n-----------------------------------------------------------------------------------------------------\r\n"));

	{
		opt->save (_T("\r\n\r\nSorting by function:\r\n"));

		int index = 0;
		ProfilerMap::const_iterator it, itend = map.end ();
		for (it = map.begin (); it != itend; ++it) {
			ncTempNode node;
			node.pos = it->first;
			node.object = it->second;
			nodes.push_back (node);

			opt->save (_T("\tNo%d. %s\r\n\t\tCalls:\t%d\r\n\t\tTime:\t%s\r\n"), ++index, it->first.getCStr (), it->second.count, ::timeToString (it->second.useTime).getCStr ());
		}
	}

	{
		opt->save (_T("\r\n\r\nSorting by calls:\r\n"));
		sort (nodes.begin (), nodes.end (), ncCountSort);
		for (size_t i = 0; i < nodes.size (); ++i)
			opt->save (_T("\tNo%d. %s\r\n\t\tCalls:\t%d\r\n\t\tTime:\t%s\r\n"), i + 1, nodes[i].pos.getCStr (), nodes[i].object.count, ::timeToString (nodes[i].object.useTime).getCStr ());
			//opt->save (_T("\t%d. Calls: %d, Time: %s, %s"), i + 1, nodes[i].object.count, ::timeToString (nodes[i].object.useTime).getCStr (), nodes[i].pos.getCStr ());
	}
	
	{
		opt->save (_T("\r\n\r\nSorting by time:\r\n"));
		sort (nodes.begin (), nodes.end (), ncTimeSort);
		for (size_t i = 0; i < nodes.size (); ++i)
			opt->save (_T("\tNo%d. %s\r\n\t\tCalls:\t%d\r\n\t\tTime:\t%s\r\n"), i + 1, nodes[i].pos.getCStr (), nodes[i].object.count, ::timeToString (nodes[i].object.useTime).getCStr ());
			//opt->save (_T("\t%d. Time: %s, Calls: %d, %s"), i + 1, ::timeToString (nodes[i].object.useTime).getCStr (), nodes[i].object.count, nodes[i].pos.getCStr ());
	}

	opt->save (_T("\r\n\t-----[Total Time: %s]-----"), ::timeToString (useTime).getCStr ());

	opt->save (_T("\r\n-----------------------------------------------------------------------------------------------------\r\n\r\n\r\n\r\n"));
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 结构体
//

//
// 记录单个分析节点的时间花费对象
//
ProfilerNode::ProfilerNode (char* fileName, char* func, int lineNum, const String& remarkStr)
	: start (0)
	, file (fileName)
	, function (func)
	, line (lineNum)
	, remark (remarkStr)
{
	start = ::GetTickCount ();
}

ProfilerNode::~ProfilerNode (void)
{
	//
	// 记录性能分析内容
	//
	PerformanceProfiler::getInstance ()->add (::makeKey (file, function, line, remark), start, ::GetTickCount ());
}

//
// 用于分析性能的目标
//
ProfilerObject::ProfilerObject (void)
	: count (0)
	, useTime (0)
{
}

void
ProfilerObject::use (double time)
{
	useTime += time;
	++count;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// PerformanceProfiler
//

PerformanceProfiler* PerformanceProfiler::_inst = 0;

// public
PerformanceProfiler*
PerformanceProfiler::getInstance (void)
{
	if (_inst == 0)
		_inst = new PerformanceProfiler ();
	return _inst;
}

// public
void
PerformanceProfiler::delInstance (void)
{
	if (_inst != 0)
		delete _inst;
	_inst = 0;
}

// public
void
PerformanceProfiler::add (const String& codePos, double start, double end)
{
	AutoLock<ThreadMutexLock> locker (&_lock);
	
	if (_map.empty () == true)
		_start = start;

	ProfilerMap::iterator it = _map.find (codePos);
	if (it == _map.end ()) {
		ProfilerObject object;
		_map[codePos] = object;
		it = _map.find (codePos);
	}

#ifdef __WINDOWS__
	double useTime = (double) (end - start) / (double) CLOCKS_PER_SEC;
#else
	double useTime = (double) (end - start) / (double) 1000;
#endif
	it->second.use (useTime);
}

// public
void
PerformanceProfiler::print (void)
{
	AutoLock<ThreadMutexLock> locker (&_lock);

	ncPrintSaveOperator opt;
	::ncSaveResult (getUseTime (), _map, &opt);
}

// public
void
PerformanceProfiler::save (const String& file)
{
	AutoLock<ThreadMutexLock> locker (&_lock);

	ncFileSaveOperator opt (file);
	::ncSaveResult (getUseTime (), _map, &opt);
}

// public
void
PerformanceProfiler::clear (void)
{
	AutoLock<ThreadMutexLock> locker (&_lock);
	_map.clear ();
	_start = 0;
}

// protected
PerformanceProfiler::PerformanceProfiler (void)
	: _start (0)
	, _lock ()
	, _map ()
{
}

// protected
PerformanceProfiler::~PerformanceProfiler (void)
{
}

// protected
double
PerformanceProfiler::getUseTime (void)
{
	double end = ::GetTickCount ();

#ifdef __WINDOWS__
	double useTime = (double) (end - _start) / (double) CLOCKS_PER_SEC;
#else
	double useTime = (double) (end - _start) / (double) 1000;
#endif

	return useTime;
}
