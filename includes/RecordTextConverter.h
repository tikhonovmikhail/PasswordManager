/*
 * RecordTextConverter.h
 *
 *  Created on: Jun 12, 2016
 *      Author: misha123
 */

#ifndef RECORDTEXTCONVERTER_H_
#define RECORDTEXTCONVERTER_H_

#include <string>
#include <Record/Record.h>

class RecordTextConverter {
public:
	static std::string recordToText(const Record* record);
	static Record* textToRecord(const std::string& text);
private:
	static bool stringToInt(const std::string& str, int& result);
};

#endif /* RECORDTEXTCONVERTER_H_ */
