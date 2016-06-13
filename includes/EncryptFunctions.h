/*
 * EncryptFunctions.h
 *
 *  Created on: Jun 14, 2016
 *      Author: misha123
 */

#ifndef ENCRYPTFUNCTIONS_H_
#define ENCRYPTFUNCTIONS_H_

#include <string>

std::string encrypt(const std::string& text, const std::string& key);
std::string decrypt(const std::string& text, const std::string& key);

#endif /* ENCRYPTFUNCTIONS_H_ */
