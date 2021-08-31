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

namespace hanv
{
	// functions for encryption
	extern std::string Base64Encrypt(const uint8_t *pData, uint32_t u32DataSize);
	extern std::string Base64Encrypt(const char *pData, uint32_t u32DataSize);
	extern std::string Base64Encrypt(const std::string &data);
	extern std::string Base64Encrypt(const std::vector<uint8_t> &data);

	// functions for decryption
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
	}

	printf("*****************************************************\n");
}

#endif