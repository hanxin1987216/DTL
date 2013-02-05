/***************************************************************************************************
 
 C++ Network Library, Copyright (c) Datatom Software, Inc.(2012)

Author:
	韩欣 (han.xin@datatom.com)
Creating Time:
	2012-8-10
***************************************************************************************************/
#include <dtprec.h>
#include "../prec.h"
#include "random.h"

Random	g_rand_gen	= Random((unsigned)time(NULL));

// 随机范围 - [start_, end_)
uint32_t Random::get_rand(uint32_t start_, uint32_t end_)
{
	return (uint32_t)((end_ - start_) * g_rand_gen.rand_double()) + start_;
}

int 
Random::rand_str(char * dest_, uint32_t len_)
{
    for (uint32_t i = 0; i < len_; ++i)
    {
        int x = Random::get_rand(0, sizeof(CCH) - 1);
        dest_[i] = CCH[x];
    }

    return 0;
}

int  
Random::rand_str(string& dest_, uint32_t len_)
{
    dest_ = "";
    dest_.reserve(len_ + 1);
    for (uint32_t i = 0; i < len_; ++i)
    {
        int x = Random::get_rand(0, sizeof(CCH) - 1);
        dest_  += CCH[x];
    }

    return 0;
}

bool 
Random::calc_probability(int rate_)
{
    if (rate_ < 0 || rate_ > 100)
    {
        return false;
    }

    int val = Random::get_rand(0, 101);
    bool ret = val <= rate_ ? true : false ;

    return ret;
}

