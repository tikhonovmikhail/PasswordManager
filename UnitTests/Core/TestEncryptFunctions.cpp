/*
 * TestEncryptFunctions.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: misha123
 */

#include <UnitTest.h>

#ifdef RUN_UNIT_TESTS

#include <string>
#include <Core/EncryptFunctions.h>

using std::string;

static void encryptAndDecrypt(const string& text, const string& key,
		string& encrypted, string& decrypted)
{
	encrypted = encryptText(text, key);
	decrypted = decryptText(encrypted, key);
}

DECLARE(EncryptFunctions)
	string textToEncrypt;
	size_t textToEncryptLength;
	string keyToEncrypt;
	size_t keyToEncryptLength;
END_DECLARE

SETUP(EncryptFunctions)
{
	textToEncrypt = "http://vk.com";
	keyToEncrypt = "xnviheqndsbvjsdfiwefcbsdjvsofiuhaecfw[aeinvwvbvoibv";
	textToEncryptLength = textToEncrypt.length();
	keyToEncryptLength = keyToEncrypt.length();
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

TESTF(EncryptFunctions, ShouldNotModifyTextIfKeyIsEmpty)
{
	string encrypted, decrypted;
	encryptAndDecrypt(textToEncrypt, "",
				encrypted, decrypted);

	ASSERT_EQUALS(textToEncrypt, encrypted);
	ASSERT_EQUALS(textToEncrypt, decrypted);
}

#endif // RUN_UNIT_TESTS
