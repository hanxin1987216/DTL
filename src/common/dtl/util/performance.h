/***************************************************************************************************
performance.h:
	Copyright (c) Datatom Software, Inc.(2011 - ~), All rights reserved

Purpose:
	性能剖析
	
Author:
	han.xin@datatom.com
	
Creating Time:
	2012-08-11
***************************************************************************************************/

#ifndef __PERFORMANCE_PROFILER_H__
#define __PERFORMANCE_PROFILER_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 性能剖析宏
//
// 
//#define __USE_PERFORMANCE_PROFILER__				(1)

#ifdef __USE_PERFORMANCE_PROFILER__

	//
	// 使用性能分析
	//
	#define DTL_ADD_PROFILER_CODE()						\
		ProfilerNode __tmpProfilerNode__ ((char*) __FILE__, (char*) __FUNCTION__, __LINE__, String::EMPTY);

	#define DTL_ADD_PROFILER_CODE_EX(remark)						\
		ProfilerNode __tmpProfilerNode__ ((char*) __FILE__, (char*) __FUNCTION__, __LINE__, remark);
		
	#define DTL_PROFILER_PRINT()					\
		PerformanceProfiler::getInstance ()->print ();

#else

	//
	// 不使用性能分析
	//
	#define DTL_ADD_PROFILER_CODE()						do {;} while (false);
	#define DTL_ADD_PROFILER_CODE_EX(remark)			do {;} while (false);
	#define DTL_PROFILER_PRINT()						do {;} while (false);

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// 性能剖析器
//

//
// 记录单个分析节点的时间花费对象
//
struct DTL_DLLEXPORT ProfilerNode
{
public:
	ProfilerNode (char* fileName, char* func, int lineNum, const String& remarkStr);
	~ProfilerNode (void);

public:
	double	start;

	char*	file;
	char*	function;
	int		line;
	String	remark;
};

//
// 用于分析性能的目标
//
struct DTL_DLLEXPORT ProfilerObject
{
public:
	ProfilerObject (void);
	void use (double time);
	
public:
	unsigned int count;										// 记录被调用次数
	double		 useTime;									// 总花费时间
};

typedef map <String, ProfilerObject> ProfilerMap;

class DTL_DLLEXPORT PerformanceProfiler
{
public:
	static PerformanceProfiler* getInstance (void);
	static void delInstance (void);

public:
	/**
	 * 添加剖析记录
	 *
	 * @param codePos:		代码位置信息 = __FILE__:__LINE__ (__FUNCTION__)
	 * @param start:		开始时间
	 * @param end:			结束时间
	 */
	void add (const String& codePos, double start, double end);

	/**
	 * 将结果输出到终端
	 */
	void print (void);

	/**
	 * 将结果保存到文件
	 */
	void save (const String& file);

	/**
	 * 清除记录
	 */
	void clear (void);

protected:
	PerformanceProfiler (void);
	~PerformanceProfiler (void);

	/**
	 * 获取使用时间
	 */
	double getUseTime (void);

protected:
	double			_start;

	ThreadMutexLock _lock;
	ProfilerMap		_map;

	static PerformanceProfiler* _inst;
};

#endif //__PERFORMANCE_PROFILER_H__
