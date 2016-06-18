/*
 * EncryptFunctions.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: misha123
 */

#include <Core/EncryptFunctions.h>
#include <Core/md5.h>

using std::string;

string xorOperation(const string& text, string key);

string encryptText(const string& text, const string& key)
{
	return xorOperation(text, key);
}

string decryptText(const string& text, const string& key)
{
	return xorOperation(text, key);
}

string xorOperation(const string& text, string key)
{
	if (key.empty())
	{
		return text;
	}

	key = md5(key);

	auto textLength = text.length();
	string result(textLength, '\0'); // reserve size to prevent memory reallocations

	while (textLength > key.length())
	{
		key += key;
	}

	for (auto i = 0; i < textLength; ++i)
	{
		result.at(i) = text.at(i) ^ key.at(i);
	}

	return result;
}
