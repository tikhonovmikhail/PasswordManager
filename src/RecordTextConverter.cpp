/*
 * RecordTextConverter.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: misha123
 */

#include <set>
#include <vector>
#include <algorithm>
#include <sstream>

#include "RecordTextConverter.h"

using std::string;
using std::set;
using std::vector;
using std::stringstream;
using std::invalid_argument;
using std::out_of_range;

string RecordTextConverter::recordToText(const Record* record)
{
	string text;

	if (record)
	{
		text += record->getTitle() + "\n";
		text += std::to_string(record->getType()) + "\n";

		auto fields = record->getFieldNames();
		std::for_each(fields.begin(), fields.end(), [&text, record](string field)
				{
					string value;
					record->getFieldValue(field, value);
					text += value + "\n";

				});
	}

	return text;
}

Record* RecordTextConverter::textToRecord(const string& text)
{
	stringstream ss(text);

	// Read title and type
	string title;
	std::getline(ss, title);

	string typestr;
	std::getline(ss, typestr);
	int typeint;
	if ( !stringToInt(typestr, typeint) )
	{
		typeint = Record::rtype::END;
	}

	// Check if title and type are valid
	Record* record = nullptr;
	try
	{
		record = new Record(title, Record::rtype(typeint));
	}
	catch(invalid_argument& exc)
	{
		return nullptr;
	}

	// Read fields
	auto fieldNames = record->getFieldNames();
	size_t nFields = fieldNames.size();
	size_t nLinesRead = 0;
	for (const auto& name: fieldNames)
	{
		string value;
		if ( std::getline(ss, value) )
		{
			record->setFieldValue(name, value);
			++nLinesRead;
		}
		else
		{
			break;
		}
	}

	// Has enough fields?
	if (nLinesRead == nFields)
	{
		return record;
	}
	else
	{
		delete record;
		return nullptr;
	}
}

bool RecordTextConverter::stringToInt(const string& str, int& result)
{
    try
    {
        size_t lastChar;
        result = std::stoi(str, &lastChar, 10);
        return lastChar == str.size();
    }
    catch (invalid_argument&)
    {
        return false;
    }
    catch (out_of_range&)
    {
        return false;
    }
}
