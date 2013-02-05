/***************************************************************************************************
timer.cpp:	
	C++ Foundation Library header files
	Copyright (c) Datatom Software, Inc.(2011)

Purpose:
    Impl of DTL Timer

Author:
    fan.fei@datatom.com

Creating Time:
	2012-3-1
***************************************************************************************************/

#include "../prec.h"

#include "../lang/string.h"
#include "../lang/int.h"
#include "../sys/exception.h"
#include "../sys/date.h"

#include <assert.h>

#include "timer.h"

#define TIME_SCALE Date::ticksPerSecond

#ifndef __WINDOWS__
#define wait(waittime) \
    do { \
        unsigned int t = waittime; \
        for (;t>0 && tsafe->isValid();t--) { \
            sleep(1); \
        } \
    }while(0)
#else
#define wait(waittime) \
    do { \
        unsigned int t = waittime; \
        for (;t>0 && tsafe->isValid();t--) { \
            sleep(1000); \
        } \
    }while(0)
#endif


bool 
DTimerStrategy::checkWeek(Weekday weekday, int intday) {
    switch (weekday) {
        case SUNDAY:
            return intday == 7;
        case MONDAY:
            return intday == 1;
        case TUESDAY:
            return intday == 2;
        case WEDNESDAY:
            return intday == 3;
        case THURSDAY:
            return intday == 4;
        case FRIDAY:
            return intday == 5;
        case SATURDAY:
            return intday == 6;
        default:
            assert(false);
    }
    return false;
}

const String
DTimerStrategy::DEFAULT_START_TIME = String("00:00");

const String
DTimerStrategy::INVALID_TIME = String("99:99");

DTimerStrategy::DTimerStrategy() 
	: _mode(EVERYDAY)
	, _date(std::vector<int>())
	, _startTime(DEFAULT_START_TIME)
	, _endTime(INVALID_TIME)
	, _interval(0) {}

DTimerStrategy::DTimerStrategy(TimerStrategyMode mode,
                            const std::vector<int> &date,
                            const String &startTime,
                            const String &endTime,
                            unsigned int interval) {
    setStrategy(mode, date, startTime, endTime, interval);
}



void 
DTimerStrategy::setStrategy(TimerStrategyMode mode,
                    const std::vector<int> &date,
                    const String &startTime,
                    const String &endTime,
                    unsigned int interval) {
    _mode = mode;
    _date = date;
    _startTime = startTime;
    _endTime = endTime;
    _interval = interval;
}

bool
DTimerStrategy::shouldRun() const {
    //比较当前日期
    Date curDate;
    //std::cout<<"shouldrun:"<<std::boolalpha<< shouldRun(curDate)<< std::endl;
    return shouldRun( curDate);
}

bool
DTimerStrategy::shouldRun(const Date &date) const {
    bool rightDay = false;
    switch (_mode) {
        case EVERYDAY: {
            rightDay = true;
            break;
        }
        case WEEK: {
            for(std::vector<int>::const_iterator it = _date.begin()
                ;it != _date.end()
                ;++it) {
                if (checkWeek(date.getDayOfWeek(), *it)) {
                    rightDay = true;
                    break; //break for(..)
                }
            }
            break;
        }
        case MONTH: {
            for(std::vector<int>::const_iterator it = _date.begin()
                ;it != _date.end()
                ;++it) {
                if (static_cast<int>(date.getDay()) == *it) {
                    rightDay = true;
                    break; //break for(..)
                }
            }
            break;
        }
        default: {
            assert(false);
        }
    }
    //比较当前时间
    if (!rightDay) {
        return false;
    } else if (cmpDateWithTimeStr(date, _startTime) <= 0
             && cmpDateWithTimeStr(date, _endTime) > 0) {
        return true;
    }
    return false;
}

int
DTimerStrategy::cmpDateWithTimeStr(const Date &date,
                                 const String &timeStr) {
    //无效时间相当于正无穷
    if (timeStr == INVALID_TIME) {
        return Int::MAX_VALUE;
    }
    size_t sPos = timeStr.find(':');
    int tsHours = Int::getValue(timeStr.subString(0, sPos));
    int tsMin = Int::getValue(timeStr.subString(sPos+1));

    String dStr = date.toTimeString(TP_SHORT);
    sPos = dStr.find(':');
    int dHours = Int::getValue(dStr.subString(0, sPos));
    int dMin = Int::getValue(dStr.subString(sPos+1));
    
    if (tsHours < 0 || 24 < tsHours) {
        THROW("TIMER_INVALID_HOURS_VALUE_OUT_OF_RANGE");
    }
    if (tsMin < 0 || 60 < tsMin) {
        THROW("TIMER_INVALID_MINUTE_VALUE_OUT_OF_RANGE");
    }
    return (tsHours - dHours)*60 + (tsMin - dMin);
}

DTimer::DTimer()
	: _task(NULL)
	, _canceled(true)
{
}

DTimer::~DTimer() {
    //_canceled = true;
    if (!_canceled) {
        _task->setValid(false);
        if (_task != NULL) {
            _task->cancel();
        }
    }
    _task = NULL;
}

void 
DTimer::shedule(const ITimerTask &task, 
                    const Date &firstTime, 
                    unsigned int interval) {
    int64 iCurTime = Date::getCurrentTime();
    int64 delay = firstTime.time() - iCurTime;

    if  (delay < 0) {
        THROW("TIMER_INVALID_START_TIME");
    }

    //delay is milliseconds
    shedule(task, (unsigned int)delay/TIME_SCALE, interval);
}

void 
DTimer::shedule(const ITimerTask &task, 
                    unsigned int delay, 
                    unsigned int interval) {
    if (_task != NULL) {
        //THROW("shedule already run");
        return;
    }
    _task = const_cast<ITimerTask*>(&task);
    _canceled = false;
    _task->setValid(true);
    ITimerTask *tsafe = _task;//use this poiter for thread safty

    wait(delay);
    if (interval == 0) {
        tsafe->run();
    } else {
        //while (!_canceled ) {
        while (tsafe->isValid()) {
            tsafe->run();
            wait(interval);
        }
    }
}

void 
DTimer::sheduleAtFixedRate(const ITimerTask &task, 
                                const Date &firstTime, 
                                unsigned int interval) {
    Date curTime;
    int64 iCurTime = curTime.time();
    int64 delay = firstTime.time() - iCurTime;

    if (delay < 0) {
        THROW("TIMER_INVALID_START_TIME");
    }
    //delay is milliseconds
    sheduleAtFixedRate(task, (unsigned int)delay/TIME_SCALE, interval);
}


void 
DTimer::sheduleAtFixedRate(const ITimerTask &task, 
                                unsigned int delay, 
                                unsigned int interval) {

    if (interval == 0) {
        //no need to adept period when interval == 0
        shedule(task, delay, interval);
    } else {
        if (_task != NULL) {
            //THROWN("shedule already run");
            return;
        }
        _task = const_cast<ITimerTask*>(&task);
        //_canceled = false;
        _task->setValid(true);
        ITimerTask *tsafe = _task;//use this poiter for thread safty

        wait(delay);

        //while (!_canceled) {
        while (tsafe->isValid()) {
            int64 stime = Date::getCurrentTime();
            tsafe->run();
            int64 timeCost = (Date::getCurrentTime() - stime)/TIME_SCALE;
            int64 fixedDelay = timeCost > interval ? 0 : interval - timeCost;
            wait(fixedDelay);
        }
    }
}


void 
DTimer::shedule(const ITimerTask &task,
                const DTimerStrategy &strate) {
    if (_task != NULL) {
        return;
    }
    _task = const_cast<ITimerTask*>(&task);
    _canceled = false;
    _task->setValid(true);
    ITimerTask *tsafe = _task;//use this poiter for thread safty
    //DTimerStrategy *tstrate = const_cast<DTimerStrategy*>(&strate);

    /**
     * strate.shouldRun()判断的是当前时刻是否满足
     * DTimerStrategy中的日期(_mode,_date)和起止时间(_startTime,_endTime)
     * runable判断的是在满足strate.shouldRun()的条件后task时task是否可以运行
     * 解决一次性任务和循环执行任务的问题
     */
    bool runable = true;
    //while (!_canceled) {
    while (tsafe->isValid()) {
        wait(1);
        if (strate.shouldRun()) {
            if (runable) {
                if (strate._endTime == DTimerStrategy::INVALID_TIME) {
                    //_endTime无效，task只运行一次
run_once:
                    tsafe->run();
                    runable = false;
                } else {
                    //周期为0时task只运行一次
                    if (strate._interval == 0) {
                        goto run_once;
                    }
                    //每隔interval秒运行一次task
                    //while (!_canceled && strate.shouldRun()) {
                    while (tsafe->isValid() && strate.shouldRun()) {
                        tsafe->run();
                        wait(strate._interval);
                    }
                }
            } //if (runable)
        } else {
            runable = true;
        }
    }
}


ITimerTask*
DTimer::cancel() {
    assert(_task != NULL);
    _canceled = true;
    _task->setValid(false);
    _task->cancel();
    ITimerTask * ret = _task;
    _task = NULL;
    return ret;
}
