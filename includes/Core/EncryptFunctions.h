/*
 * EncryptFunctions.h
 *
 *  Created on: Jun 14, 2016
 *      Author: misha123
 */

#ifndef ENCRYPTFUNCTIONS_H_
#define ENCRYPTFUNCTIONS_H_

#include <string>

std::string encryptText(const std::string& text, const std::string& key);
std::string decryptText(const std::string& text, const std::string& key);
std::string generateKey(const int keyLengthBytes);
std::string getSubkey(const std::string& key, const int subkeyStartPos, const int subkeyLength);

#endif /* ENCRYPTFUNCTIONS_H_ */
