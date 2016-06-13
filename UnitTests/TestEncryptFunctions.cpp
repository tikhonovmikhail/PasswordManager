/*
 * TestEncryptFunctions.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: misha123
 */

#include "UnitTest.h"
#include "EncryptFunctions.h"

using std::string;

#ifdef RUN_UNIT_TESTS

static void encryptAndDecrypt(const string& text, const string& key,
		string& encrypted, string& decrypted)
{
	encrypted = encrypt(text, key);
	decrypted = decrypt(encrypted, key);
}

DECLARE(EncryptFunctions)
	string textToEncrypt;
	size_t textToEncryptLength;
	string keyToEncrypt;
END_DECLARE

SETUP(EncryptFunctions)
{
	textToEncrypt = "http://vk.com";
	keyToEncrypt = "xnviheqndsbvjsdfiwefcbsdjvsofiuhaecfw[aeinvwvbvoibv";
	textToEncryptLength = textToEncrypt.length();
}

TEARDOWN(EncryptFunctions) {}

TESTF(EncryptFunctions, ShouldEncryptAndDecryptTextShorterThanKey)
{
	string encrypted, decrypted;
	encryptAndDecrypt(textToEncrypt, keyToEncrypt.substr(0, textToEncryptLength + 1),
			encrypted, decrypted);

	ASSERT_TRUE(encrypted != textToEncrypt);
	ASSERT_EQUALS(decrypted, textToEncrypt);
}

TESTF(EncryptFunctions, ShouldEncryptAndDecryptTextLongerThanKey)
{
	string encrypted, decrypted;
	encryptAndDecrypt(textToEncrypt, keyToEncrypt.substr(0, textToEncryptLength - 1),
			encrypted, decrypted);

	ASSERT_TRUE(encrypted != textToEncrypt);
	ASSERT_EQUALS(decrypted, textToEncrypt);
}

TESTF(EncryptFunctions, ShouldEncryptAndDecryptTextLengthEqualToKeyLength)
{
	string encrypted, decrypted;
	encryptAndDecrypt(textToEncrypt, keyToEncrypt.substr(0, textToEncryptLength),
			encrypted, decrypted);

	ASSERT_TRUE(encrypted != textToEncrypt);
	ASSERT_EQUALS(decrypted, textToEncrypt);
}

#endif // RUN_UNIT_TESTS
