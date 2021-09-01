/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
 * THIS FILE IS PART OF HANVBASE64
 * HanvBase64.h - The header file of HanvBase64, includes function declarations
 * 
 * License to copy and use this software is granted provided that it is identified 
 * as the "Cosmo. Wang" or "HANV" in all material mentioning or referencing this
 * software or this function.
 *
 * Copyright (C) 2020, Cosmo. Wang (ciherenzai@hotmail.com). All rights reserved.
 * Version: 1.0.0.0
-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <string.h>

namespace hanv
{
	// functions for encryption
	/*	pOutBuf: buffer for output
	 *	u32OutBufSize: Before encryption, it's the bytes of buffer pointed by pOutBuf. After
	 *		encryption, its value will be the output bytes actually. if failed, its value is invalid.
	 *		You can use this code to get the output bytes actually:
	 *			uint32_t u32OutBufSize = 0;
	 *			uint32_t bytes = Base64Encrypt(pData, u32DataSize, nullptr, u32OutBufSize);
	 *	return value: the length of base64 string, if failed, it will be 0.
	 */
	extern uint32_t Base64Encrypt(const uint8_t *pData, uint32_t u32DataSize, uint8_t * const pOutBuf, uint32_t &u32OutBufSize);
	/*
	 * return value: the base64 string
	 */
	extern std::string Base64Encrypt(const uint8_t *pData, uint32_t u32DataSize);
	extern std::string Base64Encrypt(const char *pData, uint32_t u32DataSize);
	extern std::string Base64Encrypt(const std::string &data);
	extern std::string Base64Encrypt(const std::vector<uint8_t> &data);

	// functions for decryption
	/*	pOutBuf: buffer for output
	 *	u32OutBufSize: Before decryption, it's the bytes of buffer pointed by pOutBuf. After
	 *		decryption, its value will be the output bytes actually. if failed, its value is invalid.
	 *		You can use this code to get the output bytes actually:
	 *			uint32_t u32OutBufSize = 0;
	 *			uint32_t bytes = Base64Decrypt(pData, u32DataSize, nullptr, u32OutBufSize);
	 *	return value: the length of base64 string, if failed, it will be 0.
	 */
	extern uint32_t Base64Decrypt(const char *pData, uint32_t u32DataSize, uint8_t * const pOutBuf, uint32_t &u32OutBufSize);
	extern std::vector<uint8_t> Base64Decrypt(const char *pData, uint32_t u32DataSize);
	extern std::string Base64Decrypt2String(const char *pData, uint32_t u32DataSize);
}

#ifdef HANV_TEST_BASE64
inline void TestBase64()
{
	using namespace hanv;

	const char *ptr[] = { "Hello World!", "Hello World!!", "Hello World!!!" };

	for (size_t i = 0; i < sizeof(ptr) / sizeof(ptr[0]); i++)
	{
		size_t len = strlen(ptr[i]);

		printf("*****************************************************\n");
		printf("* original string: %s\n", ptr[i]);

		std::string base64 = Base64Encrypt((const uint8_t *)ptr[i], len);
		printf("* encrypted by Base64Encrypt(const uint8_t *, uint32_t): %s\n", base64.c_str());
		auto test = [&]() {
			std::string str = Base64Decrypt2String(base64.c_str(), base64.length());
			if (str != ptr[i]) printf("* Base64Decrypt2String failed!\n");
			else printf("* decrypted by Base64Decrypt2String: %s\n", str.c_str());
			std::vector<uint8_t> vec = Base64Decrypt(base64.c_str(), base64.length());
			if (memcmp(vec.data(), ptr[i], len)) printf("* Base64Decrypt failed!\n*\n");
			else
			{
				vec.push_back('\0');
				printf("* decrypted by Base64Decrypt: %s\n*\n", vec.data());
			}
		};
		test();

		base64 = Base64Encrypt((const char *)ptr[i], len);
		printf("* encrypted by Base64Encrypt(const char *, uint32_t): %s\n", base64.c_str());
		test();

		base64 = Base64Encrypt(std::string(ptr[i]));
		printf("* encrypted by Base64Encrypt(const std::string &): %s\n", base64.c_str());
		test();

		std::vector<uint8_t> data;
		data.resize(len);
		memcpy(data.data(), ptr[i], len);
		base64 = Base64Encrypt(data);
		printf("* encrypted by Base64Encrypt(const std::vector<uint8_t> &): %s\n", base64.c_str());
		test();

		uint32_t u32OutBufSize = 0;
		uint32_t bytes = Base64Encrypt((const uint8_t *)ptr[i], len, nullptr, u32OutBufSize);
		printf("* encryption need %u bytes for output\n", bytes);
		data.resize(bytes + 1);
		data[bytes] = 0;
		uint32_t outbytes = bytes;
		bytes = Base64Encrypt((const uint8_t *)ptr[i], len, data.data(), outbytes);
		printf("* encrypted by Base64Encrypt(const uint8_t *, uint32_t, const uint8_t *, uint32_t &);: %s\n", data.data());
		base64 = (const char *)data.data();
		outbytes = 0;
		bytes = Base64Decrypt((const char *)data.data(), data.size() - 1, nullptr, outbytes);
		printf("* decryption need %u bytes for output\n", bytes);
		std::vector<uint8_t> outbuf;
		outbuf.resize(bytes + 1, 0);
		outbytes = bytes;
		bytes = Base64Decrypt((const char *)data.data(), data.size() - 1, outbuf.data(), outbytes);
		if (memcmp(outbuf.data(), ptr[i], bytes) || (bytes != outbytes)) printf("* Base64Decrypt failed!\n");
		else printf("* decrypted by Base64Decrypt: %s\n", outbuf.data());
		test();
	}

	printf("*****************************************************\n");
}

#endif
