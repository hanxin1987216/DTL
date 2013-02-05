/*************************************************************************************************
time.h
	Public Header
	Copyright (c) Datatom Software, Inc.(2004 - 2008), All rights reserved

Purpose:
      headfile of DTL Timer

Author:
	fan.fei@datatom.com

Created:
	2012-3-1
***************************************************************************************************/

#ifndef __DTL_TIMER_H__
#define __DTL_TIMER_H__


#if PRAGMA_ONCE
#   pragma once
#endif

#ifndef __WINDOWS__ //linux
    #include <unistd.h>
#else
    #include <windows.h>
#endif

#include "../sys/date.h"
#include "../lang/string.h"

class DTimer;
/**
 * interface of task
 * one should implement run() and cancel()
 * for each task commit to timer
 */
class DTL_DLLEXPORT ITimerTask
{
    friend class DTimer;
public:
	ITimerTask (void) {}
	virtual ~ITimerTask (void) {}

	/**
     * get the status of ITimerTask
     * @return	 return true if this task is shelduling by a DTimer instance
     *          return false if it SHOULD not running 
     */
    inline bool isValid() const {return _valid;}


public:
    virtual void run() = 0;
    virtual void cancel() = 0;
    
private:
    /**
     * set the status
     * @param v the status value
     */
    inline void setValid(bool v) { _valid = v;}
    volatile bool _valid;
};



enum TimerStrategyMode
{
	EVERYDAY,
	WEEK,
	MONTH,
};



/**
 * 计时器策略类，提供策略输入方法和检查当前时间是否满足策略的方法
 *
 */
class DTL_DLLEXPORT DTimerStrategy
{
    friend class DTimer;
public:
    //默认的格式化时间字符串
    static const String DEFAULT_START_TIME;
    static const String INVALID_TIME;

    
	DTimerStrategy(void);
    /**
     * 构造函数
     * @param mode 策略模式，enum TimerStrategyMode中的一种
     * @param date 整数数组，模式为WEEK时代表周一～周日，模式为MONTH代表每月的几号
     *				模式为EVERYDAY时无效
     * @param startTime 起始时间
     * @param endTime 结束时间，等于INVALID_TIME时说明任务策略为单次运行
     * @param interval 仅在endTime有效时起作用，在startTime和endTime之间
     *            每隔[interval]秒运行一次任务
     */
	DTimerStrategy(TimerStrategyMode mode,
                    const std::vector<int> &date,
                    const String &startTime,
                    const String &endTime = INVALID_TIME,
                    unsigned int interval = 0);

	~DTimerStrategy(void) {}

	void setStrategy(TimerStrategyMode mode,
                    const std::vector<int> &date,
                    const String &startTime,
                    const String &endTime,
                    unsigned int interval);

    /**
     * 查看当前时间是否符合策略
     * @return: 符合返回true,否则返回false
     */
    bool shouldRun(void) const;

    /**
     * 查看指定时间是否符合策略
	 * 
	 * @param date: 与当前策略比较的时间
	 * @return: 符合返回true,否则返回false
     */
    bool shouldRun(const Date &date) const;


protected:
	TimerStrategyMode _mode;
	std::vector<int> _date;
	String _startTime;
	String _endTime;
	unsigned int _interval;

protected:
    /**
     * 检查Weekday和intday是否匹配
     *
     */
    static bool checkWeek(Weekday weekday, int intday);

    /**
     * 比较date表示的时刻和str表示的时刻先后
     *
     * @param date 日期类，这里只检查Date中的时刻信息
     *        忽略日期信息
     * @param timeStr 表示时刻信息的字符串,格式为"HH:MM"
     * @return: timeStr - date的时间(分钟)
     *         0 date == timeStr
     *         > 0 date在timeStr之前
     *         < 0 date在timeStr之后 
     *
     * 注意：仅支持格式为"HH:MM"的字符串
     */
    static int cmpDateWithTimeStr(const Date &date, 
                                 const String &timeStr);
};


class DTL_DLLEXPORT DTimer
{
public:
    DTimer (void);
    ~DTimer(void);
    /**
     * run the speciafied task begin at speciafied time
     * and then repeat every [interval] seconds
     *
     * @param task the task to run
     * @param firstTime the first time run task
     * @param interval the time BETWEEN previous task and next task,in second
     *          if interval == 0,the task will run only once
     */
    void shedule(const ITimerTask &task, 
                 const Date &firstTime, 
                 unsigned int interval=0);

    /**
     * run the speciafied task after speciafied delay
     * and then repeat every [interval] seconds
     *
     * @param task the task to run
     * @param delay delay time of the task after call shedule,in second
     * @param interval the time between previous task and next task,in second
     *          if interval == 0,the task will run only once
     */
    void shedule(const ITimerTask &task, 
                 unsigned int delay, 
                 unsigned int interval=0);

	/**
	 * sheduleAtFixedRate try to make the period between the begining time of tasks
	 * are exactly [interval] seconds
	 * for example,if a task start at 9:00:00,and [interval] is 60 seconds
	 * we assume task.run() will cost 30 seconds
	 *
	 *  if call shedule(), the next time call task.run() will be 9:01:30,
	 *  that means 30s runtime + 60s interval
	 *
	 *  if call sheduleAtFixRate(), the next time call task.run() will be 9:01:00,
	 *  the cost of task.run() is omitted
	 *  but if task.run() cost 90 seconds,the next time call task.run() will delayed to 9:01:30
	 *
	 */
    void sheduleAtFixedRate(const ITimerTask &task, 
                            const Date &firstTime, 
                            unsigned int interval);


    void sheduleAtFixedRate(const ITimerTask &task, 
                            unsigned int delay, 
                            unsigned int interval);


    void shedule(const ITimerTask &task,
                const DTimerStrategy &strate);

    /**
     * Terminate this timer,and try to cancel it's running task
     * @return: return point of current task
     */
    ITimerTask * cancel(void);

private:

private:
    /**
     * when canceled,we should have a handle of the task
     */
    ITimerTask			*_task;
    
    /**
     * use _canceled as a guard to avoid invalid _task point in destructor
     */
    volatile bool		_canceled;
};

#endif

