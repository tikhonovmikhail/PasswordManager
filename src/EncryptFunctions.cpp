/*
 * EncryptFunctions.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: misha123
 */

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
