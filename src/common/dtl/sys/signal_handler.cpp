/***************************************************************************************************
 
 C++ Network Library, Copyright (c) Datatom Software, Inc.(2012)

Author:
	韩欣 (han.xin@datatom.com)
Creating Time:
	2012-8-10
***************************************************************************************************/
#include <dtprec.h>
#include "../prec.h"
#include "signal_handler.h"


SignalHandler::SignalHandler()
{
    // 清空信号掩码
    sigemptyset(&m_wait_mask);
}

SignalHandler::~SignalHandler()
{
}

// 阻塞当前线程对所有信号的接受
//! 注; 这里是阻塞而不是忽略, 发生在内核态 
int SignalHandler::block_all_signal()
{
    sigset_t all_mask;
    sigfillset(&all_mask);
    return pthread_sigmask(SIG_BLOCK, &all_mask, NULL);
}

int SignalHandler::register_quit_signal(unsigned int signal_num_)
{
    sigaddset(&m_wait_mask, signal_num_);
    if (m_signal_func_map.end() != m_signal_func_map.find(signal_num_))
    {
        return -1;
    }

    m_signal_func_map[signal_num_] = signal_callback_func_t();
    return 0;
}

int SignalHandler::register_signal(unsigned int signal_num_, signal_callback_func_t signal_callback_func_)
{
    sigaddset(&m_wait_mask, signal_num_);
    if (m_signal_func_map.end() != m_signal_func_map.find(signal_num_))
    {
        return -1;
    }

    m_signal_func_map[signal_num_] = signal_callback_func_;
    return 0;
}

int SignalHandler::event_loop()
{
    pthread_sigmask(SIG_BLOCK, &m_wait_mask, 0);

    int sig_num = 0;
    while (!sigwait(&m_wait_mask, &sig_num))
    {
        m_signal_func_map_t::iterator it = m_signal_func_map.find(sig_num);
        if (m_signal_func_map.end() != it)
        {
            if (it->second)
            {
                // 调用signal callback进行处理
                (it->second)();
            }
            else
            {
                // 收到退出信号, 退出循环
                return 0;
            }
        }
        else
        {
            return -1;
        }
    }

    return 0;
}
