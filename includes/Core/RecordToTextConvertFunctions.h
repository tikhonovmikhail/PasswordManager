/*
 * RecordToTextConvertFunctions.h
 *
 *  Created on: Jun 15, 2016
 *      Author: mt
 */

#ifndef RECORDTOTEXTCONVERTFUNCTIONS_H_
#define RECORDTOTEXTCONVERTFUNCTIONS_H_

#include <string>
#include "Record.h"

std::string recordToText(const Record* record);
Record* textToRecord(const std::string& text);
std::string wrapTextWithFieldNames(const std::string& text, const Record::Type recordType);
std::string unwrapTextFromFieldNames(const std::string& text);

#endif /* RECORDTOTEXTCONVERTFUNCTIONS_H_ */
