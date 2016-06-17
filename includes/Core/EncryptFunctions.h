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

#endif /* ENCRYPTFUNCTIONS_H_ */
