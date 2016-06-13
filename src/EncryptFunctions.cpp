/*
 * EncryptFunctions.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: misha123
 */

#include <cstdlib>
#include <ctime>
#include "EncryptFunctions.h"

using std::string;

string xorOperation(const string& text, string key);

string encrypt(const string& text, const string& key)
{
	return xorOperation(text, key);
}

string decrypt(const string& text, const string& key)
{
	return xorOperation(text, key);
}

string xorOperation(const string& text, string key)
{
	size_t textLength = text.length();
	string result(textLength, '\0'); // reserve size to prevent memory reallocations

	while (textLength > key.length())
	{
		key += key;
	}

	for (size_t i = 0; i < textLength; ++i)
	{
		result.at(i) = text.at(i) ^ key.at(i);
	}

	return result;
}

string generateKey(const int keyLengthBytes)
{
	string key(keyLengthBytes, '\0');

	srand(time(NULL));
	for (int i = 0; i < keyLengthBytes; ++i)
	{
		key[i] = rand() % 256;
	}

	return key;
}

string getSubkey(const string& key, const int subkeyStartPos, const int subkeyLength)
{
	return key.substr(subkeyStartPos, subkeyLength);
}
