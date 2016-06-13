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

TESTF(EncryptFunctions, ShouldGenerateKeyOfGivenLength)
{
	int keyLength = 1000;
	string key = generateKey(keyLength);
	ASSERT_EQUALS(keyLength, key.length());
}

TESTF(EncryptFunctions, ShouldExtractSubkeyFromKeyWhenValidSubkeyLength)
{
	int subkeyStartPos = 1;
	int subkeyLength = keyToEncryptLength - subkeyStartPos - 1;

	string subkey = getSubkey(keyToEncrypt, subkeyStartPos, subkeyLength);
	ASSERT_EQUALS("nviheqndsbvjsdfiwefcbsdjvsofiuhaecfw[aeinvwvbvoib", subkey);
}

TESTF(EncryptFunctions, ShouldExtractSubkeyFromKeyWhenTooLongSubkeyLength)
{
	int subkeyStartPos = 1;
	int subkeyLength = keyToEncryptLength + 100;

	string subkey = getSubkey(keyToEncrypt, subkeyStartPos, subkeyLength);
	ASSERT_EQUALS("nviheqndsbvjsdfiwefcbsdjvsofiuhaecfw[aeinvwvbvoibv", subkey);
}

#endif // RUN_UNIT_TESTS
