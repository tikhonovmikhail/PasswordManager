/*
 * TextEncrypterDecrypter.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: misha123
 */

#include <typeinfo>
#include "TextEncrypterDecrypter.h"

using std::string;
using std::invalid_argument;

TextEncrypterDecrypter::TextEncrypterDecrypter(const string& key) throw(invalid_argument)
{
	if ( !setKey(key) )
	{
		throw invalid_argument(typeid(*this).name() + string(": construct with invalid key = '" + key + "'"));
	}
}

bool TextEncrypterDecrypter::setKey(const string& key)
{
	if (key.empty())
	{
		return false;
	}
	else
	{
		this->key = key;
		return true;
	}
}

string TextEncrypterDecrypter::encrypt(const string& text)
{
	return xorOperation(text, key);
}

string TextEncrypterDecrypter::decrypt(const string& text)
{
	return xorOperation(text, key);
}

string TextEncrypterDecrypter::xorOperation(const string& text, string key)
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
