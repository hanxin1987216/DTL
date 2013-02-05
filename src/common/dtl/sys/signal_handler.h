/***************************************************************************************************
 
 C++ Network Library, Copyright (c) Datatom Software, Inc.(2012)

Author:
	韩欣 (han.xin@datatom.com)
Creating Time:
	2012-8-10
***************************************************************************************************/
#ifndef _DTL_SIGNAL_HANDLER_H_
#define _DTL_SIGNAL_HANDLER_H_


#include <signal.h>
#include <stddef.h>

#include <map>
using namespace std;

class DTL_DLLEXPORT SignalHandler
{
public:

    // 注册的信号callback函数
    typedef                                                 void (*signal_callback_func_t)();
    typedef map<unsigned int, signal_callback_func_t>       m_signal_func_map_t;

public:

    SignalHandler();

    ~SignalHandler();

    // 阻塞当前线程对所有信号的接受
    int block_all_signal();

    int register_quit_signal(unsigned int signal_num_);

    int register_signal(unsigned int signal_num_, signal_callback_func_t signal_callback_func_ = NULL);

    int event_loop();

private:

    sigset_t                        m_wait_mask;            // 信号掩码
    m_signal_func_map_t             m_signal_func_map;
};

#endif //! _DTL_SIGNAL_HANDLER_H_


