/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
 * THIS FILE IS PART OF HANVBASE64
 * HanvBase64.cpp - The implementation of functions
 *
 * License to copy and use this software is granted provided that it is identified
 * as the "Cosmo. Wang" or "HANV" in all material mentioning or referencing this
 * software or this function.
 *
 * Copyright (C) 2020, Cosmo. Wang (ciherenzai@hotmail.com). All rights reserved.
 * Version: 1.0.0.0
-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <memory.h>

using namespace std;

static const uint8_t s_u8Base64[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

//static uint8_t s_u8InvBase642[256];

static const uint8_t s_u8InvBase64[] =
{
	128, //0
	128, //1
	128, //2
	128, //3
	128, //4
	128, //5
	128, //6
	128, //7
	128, //8
	128, //9
	128, //10
	128, //11
	128, //12
	128, //13
	128, //14
	128, //15
	128, //16
	128, //17
	128, //18
	128, //19
	128, //20
	128, //21
	128, //22
	128, //23
	128, //24
	128, //25
	128, //26
	128, //27
	128, //28
	128, //29

	128, //30
	128, //31
	128, //32
	128, //33
	128, //34
	128, //35
	128, //36
	128, //37
	128, //38
	128, //39
	128, //40
	128, //41
	128, //42

	62, //'+' 43

	128, //44
	128, //45
	128, //46

	63, //'/' 47

	52, //'0' 48
	53, //'1' 49
	54, //'2' 50
	55, //'3' 51
	56, //'4' 52
	57, //'5' 53
	58, //'6' 54
	59, //'7' 55
	60, //'8' 56
	61, //'9' 57
	128, //58
	128, //59
	128, //60
	129, //'=' 61
	128, //62
	128, //63
	128, //64

	0, //'A' 65
	1, //'B' 66
	2, //'C' 67
	3, //'D' 68
	4, //'E' 69
	5, //'F' 70
	6, //'G' 71
	7, //'H' 72
	8, //'I' 73
	9, //'J' 74
	10, //'K' 75
	11, //'L' 76
	12, //'M' 77
	13, //'N' 78
	14, //'O' 79
	15, //'P' 80
	16, //'Q' 81
	17, //'R' 82
	18, //'S' 83
	19, //'T' 84
	20, //'U' 85
	21, //'V' 86
	22, //'W' 87
	23, //'X' 88
	24, //'Y' 89
	25, //'Z' 90

	128, //91
	128, //92
	128, //93
	128, //94
	128, //95
	128, //96

	26, //'a' 97
	27, //'b' 98
	28, //'c' 99
	29, //'d' 100
	30, //'e' 101
	31, //'f' 102
	32, //'g' 103
	33, //'h' 104
	34, //'i' 105
	35, //'j' 106
	36, //'k' 107
	37, //'l' 108
	38, //'m' 109
	39, //'n' 110
	40, //'o' 111
	41, //'p' 112
	42, //'q' 113
	43, //'r' 114
	44, //'s' 115
	45, //'t' 116
	46, //'u' 117
	47, //'v' 118
	48, //'w' 119
	49, //'x' 120
	50, //'y' 121
	51, //'z' 122

	128, //123
	128, //124
	128, //125
	128, //126
	128, //127

	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, //128-143
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, //144-159
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, //160-175
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, //176-191
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, //192-207
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, //208-223
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, //224-239
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, //240-255
};

namespace hanv
{
	static void Base64Encrypt(const uint8_t in0, const uint8_t in1, const uint8_t in2, uint8_t u8Out[4])
	{
		uint32_t temp = (in0 << 16) | (in1 << 8) | (in2 << 0);
		for (uint32_t i = 0; i < 4; i++)
		{
			uint32_t index = (temp >> (18 - i * 6)) & 0x3F;
			u8Out[i] = s_u8Base64[index];
		}
	}

	static void Base64Encrypt(const uint8_t in0, const uint8_t in1, const uint8_t in2, string &out)
	{
		uint32_t temp = (in0 << 16) | (in1 << 8) | (in2 << 0);
		for (uint32_t i = 0; i < 4; i++)
		{
			uint32_t index = (temp >> (18 - i * 6)) & 0x3F;
			out += (const char)s_u8Base64[index];
		}
	}

	uint32_t Base64Encrypt(const uint8_t *pData, uint32_t u32DataSize, uint8_t * const pOutBuf, uint32_t &u32OutBufSize)
	{
		uint32_t ret = ((u32DataSize + 2) / 3) * 4;
		//Check output buffer size
		if(!pOutBuf || u32OutBufSize < ret) return ret;

		uint8_t temp[4];

		uint32_t offset = 0;
		for (uint32_t i = 3; i <= u32DataSize; i += 3, offset += 4)
		{
			Base64Encrypt(pData[i - 3], pData[i - 2], pData[i - 1], temp);
			memcpy(pOutBuf + offset, temp, 4);
		}

		uint32_t tail = u32DataSize % 3;
		if (tail == 1)	//补两个字节
		{
			Base64Encrypt(pData[u32DataSize - 1], 0, 0, temp);
			temp[2] = '=';
			temp[3] = '=';
			memcpy(pOutBuf + offset, temp, 4);
#ifdef _DEBUG
			offset += 4;
#endif
		}
		else if (tail == 2)	//补一个字节
		{
			Base64Encrypt(pData[u32DataSize - 2], pData[u32DataSize - 1], 0, temp);
			temp[3] = '=';
			memcpy(pOutBuf + offset, temp, 4);
#ifdef _DEBUG
			offset += 4;
#endif
		}
#ifdef _DEBUG
		if(offset != ret) printf("Maybe something was wrong...");
#endif
		return u32OutBufSize = ret;
	}

	string Base64Encrypt(const uint8_t *pData, uint32_t u32DataSize)
	{
		string out = "";

		if (!pData || !u32DataSize)
		{
			return out;
		}

		for (uint32_t i = 3; i <= u32DataSize; i += 3)
		{
			Base64Encrypt(pData[i - 3], pData[i - 2], pData[i - 1], out);
		}

		uint32_t tail = u32DataSize % 3;
		if (tail == 1)	//补两个字节
		{
			Base64Encrypt(pData[u32DataSize - 1], 0, 0, out);
			size_t n = out.size();
			out.replace(n - 2, 2, 2, '=');
		}
		else if (tail == 2)	//补一个字节
		{
			Base64Encrypt(pData[u32DataSize - 2], pData[u32DataSize - 1], 0, out);
			size_t n = out.size();
			out.replace(n - 1, 1, 1, '=');
		}

		return out;
	}

	string Base64Encrypt(const char *pData, uint32_t u32DataSize)
	{
		return Base64Encrypt((uint8_t *)pData, u32DataSize);
	}

	string Base64Encrypt(const string &data)
	{
		return Base64Encrypt(data.c_str(), data.length());
	}

	string Base64Encrypt(const vector<uint8_t> &data)
	{
		return Base64Encrypt(data.data(), data.size());
	}

	template<class T> bool Base64Decrypt(uint8_t in0, uint8_t in1, uint8_t in2, uint8_t in3, T &out)
	{
		//	memset(s_u8InvBase642, 0x80, sizeof(s_u8InvBase642));
		//	for(int i = 0 ;i <64; i ++)
		//	{
		//		s_u8InvBase642[s_u8Base64[i]] = i;
		//	}
		//	s_u8InvBase642[(int)'='] = 0;
		//	for(int i = 0; i < 256; i ++)
		//	{
		//		if(s_u8InvBase64[i] != s_u8InvBase642[i]) printf("wrong: %d %d %d", i, s_u8InvBase64[i], s_u8InvBase642[i]);
		//	}

		//printf("--- %d --- %d=>%d %d=>%d %d=>%d %d=>%d\n", sizeof(s_u8InvBase64), in0, s_u8InvBase64[in0], in1, s_u8InvBase64[in1], in2, s_u8InvBase64[in2], in3, s_u8InvBase64[in3]);
		in0 = s_u8InvBase64[in0]; if (in0 == 0x80) return false;
		in1 = s_u8InvBase64[in1]; if (in1 == 0x80) return false;
		in2 = s_u8InvBase64[in2]; if (in2 == 0x80) return false;
		in3 = s_u8InvBase64[in3]; if (in3 == 0x80) return false;

		uint32_t n = ((in0 == 0x81) ? 1 : 0) + ((in1 == 0x81) ? 1 : 0) + ((in2 == 0x81) ? 1 : 0) + ((in3 == 0x81) ? 1 : 0);

		uint32_t temp = ((uint32_t)in0 << 18) | ((uint32_t)in1 << 12) | ((uint32_t)in2 << 6) | in3;
		in0 = temp >> 16;
		in1 = temp >> 8;
		in2 = temp;

		if (n > 2) return false;
		else
		{
			if (n < 3) out.push_back(in0);
			if (n < 2) out.push_back(in1);
			if (n < 1) out.push_back(in2);
		}
		return true;
	}

	bool Base64Decrypt(uint8_t in0, uint8_t in1, uint8_t in2, uint8_t in3, uint8_t out[3], uint32_t &outbytes)
	{
		in0 = s_u8InvBase64[in0]; if (in0 == 0x80) return false;
		in1 = s_u8InvBase64[in1]; if (in1 == 0x80) return false;
		in2 = s_u8InvBase64[in2]; if (in2 == 0x80) return false;
		in3 = s_u8InvBase64[in3]; if (in3 == 0x80) return false;

		uint32_t n = ((in0 == 0x81) ? 1 : 0) + ((in1 == 0x81) ? 1 : 0) + ((in2 == 0x81) ? 1 : 0) + ((in3 == 0x81) ? 1 : 0);

		uint32_t temp = ((uint32_t)in0 << 18) | ((uint32_t)in1 << 12) | ((uint32_t)in2 << 6) | in3;
		in0 = temp >> 16;
		in1 = temp >> 8;
		in2 = temp;

		if (n > 2) return false;
		else
		{
			outbytes = 3 - n;
			out[0] = in0;
			out[1] = in1;
			out[2] = in2;
		}

		return true;
	}

	uint32_t Base64Decrypt(const char *pData, uint32_t u32DataSize, uint8_t * const pOutBuf, uint32_t &u32OutBufSize)
	{
		if (u32DataSize < 4)
		{
#ifdef _DEBUG
			printf("Base64 u32DataSize=%u is wrong!\n", u32DataSize);
#endif
			return 0;
		}

		uint32_t ret = (u32DataSize >> 2) * 3;
		uint32_t u32DataSize2 = u32DataSize - (u32DataSize & 3);
		if(pData[u32DataSize2 - 1] == '=') ret --;
		if(pData[u32DataSize2 - 2] == '=') ret --;
		if(!pData || u32OutBufSize < ret) return ret;

		uint32_t offset = 0;
		uint32_t bytes = 0;
		uint8_t temp[3];
		for (uint32_t i = 4; i <= u32DataSize; i += 4)
		{
			bool ret = Base64Decrypt(pData[i - 4], pData[i - 3], pData[i - 2], pData[i - 1], temp, bytes);
			if (!ret)
			{
#ifdef _DEBUG
				printf("Base64 decrypt failed!\n");
				printf("Base64: %s\n", pData);
#endif
				return 0;
			}

			if(bytes) memcpy(pOutBuf + offset, temp, bytes);
			offset += bytes;
		}
#if _DEBUG
		if(offset != ret) printf("Maybe something was wrong...\n");
#endif
		return u32OutBufSize = ret;
	}

	vector<uint8_t> Base64Decrypt(const char *pData, uint32_t u32DataSize)
	{
		vector<uint8_t> out;

		if (!pData || !u32DataSize)
		{
#ifdef _DEBUG
				printf("Base64 u32DataSize=%u is wrong!\n", u32DataSize);
#endif
			return out;
		}

		for (uint32_t i = 4; i <= u32DataSize; i += 4)
		{
			bool ret = Base64Decrypt(pData[i - 4], pData[i - 3], pData[i - 2], pData[i - 1], out);
			if (!ret)
			{
#ifdef _DEBUG
				printf("Base64 decrypt failed!\n");
				printf("Base64: %s\n", pData);
#endif
				out.clear();
				return out;
			}
		}

		return out;
	}

	string Base64Decrypt2String(const char *pData, uint32_t u32DataSize)
	{
		string out;

		if (!pData || !u32DataSize)
		{
#ifdef _DEBUG
				printf("Base64 u32DataSize=%u is wrong!\n", u32DataSize);
#endif
			return out;
		}

		for (uint32_t i = 4; i <= u32DataSize; i += 4)
		{
			bool ret = Base64Decrypt(pData[i - 4], pData[i - 3], pData[i - 2], pData[i - 1], out);
			if (!ret)
			{
#if _DEBUG
				printf("Base64 decrypt failed!\n");
				printf("Base64: %s\n", pData);
#endif
				out.clear();
				return out;
			}
		}

		return out;
	}
}

#ifdef HANV_TEST_BASE64
#include "HanvBase64.h"
using namespace hanv;
int main()
{
	TestBase64();

	getchar();
}
#endif
