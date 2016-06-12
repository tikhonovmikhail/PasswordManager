/*
 * TextEncrypterDecrypter.h
 *
 *  Created on: Jun 13, 2016
 *      Author: misha123
 */

#ifndef TEXTENCRYPTERDECRYPTER_H_
#define TEXTENCRYPTERDECRYPTER_H_

#include <stdexcept>
#include <string>

class TextEncrypterDecrypter {
public:
	TextEncrypterDecrypter(const std::string& key) throw(std::invalid_argument);
	bool setKey(const std::string& key);
	std::string encrypt(const std::string& text);
	std::string decrypt(const std::string& text);
private:
	std::string key;
	std::string xorOperation(const std::string& text, std::string key);
};

#endif /* TEXTENCRYPTERDECRYPTER_H_ */
