/*
 * TestTextEncrypterDecrypter.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: misha123
 */

#include "UnitTest.h"
#include "TextEncrypterDecrypter.h"

using std::string;
using std::invalid_argument;

#ifdef RUN_UNIT_TESTS

TEST(TextEncrypterDecrypter, ShouldCreateObjectWithValidKey)
{
	try
	{
		TextEncrypterDecrypter ted("a");
	}
	catch(invalid_argument&)
	{
		ASSERT_TRUE(false);
		return;
	}
	ASSERT_TRUE(true);
}

TEST(TextEncrypterDecrypter, ShouldNotCreateObjectWithInvalidKey)
{
	try
	{
		TextEncrypterDecrypter ted("");
	}
	catch(invalid_argument&)
	{
		ASSERT_TRUE(true);
		return;
	}
	ASSERT_TRUE(false);
}

TEST(TextEncrypterDecrypter, ShouldEncryptAndDecryptTextShorterThanKey)
{
	string text = "http://vk.com";
	string key =  "xnviheqndsbvjsdfiwefcbsdjvsofiuhaecfw[aeinvwvbvoibv";
	TextEncrypterDecrypter ted(key);

	string encrypted = ted.encrypt(text);
	string decrypted = ted.decrypt(encrypted);

	ASSERT_TRUE(encrypted != text);
	ASSERT_EQUALS(decrypted, text);
}

TEST(TextEncrypterDecrypter, ShouldEncryptAndDecryptTextLongerThanKey)
{
	string text = "http://vk.com";
	string key =  "xnvvv";
	TextEncrypterDecrypter ted(key);

	string encrypted = ted.encrypt(text);
	string decrypted = ted.decrypt(encrypted);
	ASSERT_TRUE(encrypted != text);
	ASSERT_EQUALS(decrypted, text);
}

TEST(TextEncrypterDecrypter, ShouldEncryptAndDecryptTextLengthEqualToKeyLength)
{
	string text = "http://vk.com";
	string key =  "xnviheqndsbvj";
	TextEncrypterDecrypter ted(key);

	string encrypted = ted.encrypt(text);
	string decrypted = ted.decrypt(encrypted);
	ASSERT_TRUE(encrypted != text);
	ASSERT_EQUALS(decrypted, text);
}

#endif // RUN_UNIT_TESTS



