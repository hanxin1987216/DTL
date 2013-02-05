/***************************************************************************************************
 
 C++ Network Library, Copyright (c) Datatom Software, Inc.(2012)

Author:
	韩欣 (han.xin@datatom.com)
Creating Time:
	2012-8-10
***************************************************************************************************/
#ifndef _DTL_NETWORK_RANDOM_H_
#define _DTL_NETWORK_RANDOM_H_


#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

// it's safe in mutil thread environment.
class DTL_DLLEXPORT Random
{
public:
	typedef unsigned long seed_type_t;

public:
    static const seed_type_t max_32_bit_long = 0xFFFFFFFFLU;
	static const seed_type_t random_max = max_32_bit_long;

	Random(const seed_type_t seed_ = 0)
	{
		reset(seed_);
	}

	// 种子处理
	void reset(const seed_type_t seed_ = 0)
	{
		m_seed[0] = (seed_ ^ 0xFEA09B9DLU) & 0xFFFFFFFELU;
		m_seed[0] ^= (((m_seed[0] << 7) & max_32_bit_long) ^ m_seed[0]) >> 31;

		m_seed[1] = (seed_ ^ 0x9C129511LU) & 0xFFFFFFF8LU;
		m_seed[1] ^= (((m_seed[1] << 2) & max_32_bit_long) ^ m_seed[1]) >> 29;

		m_seed[2] = (seed_ ^ 0x2512CFB8LU) & 0xFFFFFFF0LU;
		m_seed[2] ^= (((m_seed[2] << 9) & max_32_bit_long) ^ m_seed[2]) >> 28;

		rand_uint();
	}

	// 0~RandMax uint 随机数
	unsigned long rand_uint(void)
	{
		m_seed[0] = (((m_seed[0] & 0xFFFFFFFELU) << 24) & max_32_bit_long)
			^ ((m_seed[0] ^ ((m_seed[0] << 7) & max_32_bit_long)) >> 7);

		m_seed[1] = (((m_seed[1] & 0xFFFFFFF8LU) << 7) & max_32_bit_long)
			^ ((m_seed[1] ^ ((m_seed[1] << 2) & max_32_bit_long)) >> 22);

		m_seed[2] = (((m_seed[2] & 0xFFFFFFF0LU) << 11) & max_32_bit_long)
			^ ((m_seed[2] ^ ((m_seed[2] << 9) & max_32_bit_long)) >> 17);

		return (m_seed[0] ^ m_seed[1] ^ m_seed[2]);
	}

	// 返回[0.0, 1.0]之间的双精度浮点
	double rand_double(void)
	{
		return static_cast<double>(rand_uint())
			/ (static_cast<double>(random_max) );
	}

    // 随机范围 - [start_, end_)
	static uint32_t		get_rand(uint32_t start_, uint32_t end_);
    static int  rand_str(char * dest_, uint32_t len_);
    static int  rand_str(string& dest_, uint32_t len_);

    // 0 <= rate_ <= 100
    static bool calc_probability(int rate_);

private:
    seed_type_t m_seed[3];
};

static const char CCH[] = "_0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";

#endif // _DTL_NETWORK_RANDOM_H_
