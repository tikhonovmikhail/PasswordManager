/*
 * RecordToTextConvertFunctions.cpp
 *
 *  Created on: Jun 15, 2016
 *      Author: mt
 */

#include <set>
#include <vector>
#include <algorithm>
#include <sstream>
#include <Core/RecordToTextConvertFunctions.h>

using std::string;
using std::set;
using std::vector;
using std::stringstream;
using std::invalid_argument;
using std::out_of_range;

static bool stringToInt(const string& str, int& result);
static void removeLastNewLineFromString(string& str);

string recordToText(const Record* record)
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
		removeLastNewLineFromString(text);
	}

	return text;
}

Record* textToRecord(const string& text)
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
		typeint = Record::Type::END;
	}

	// Check if title and type are valid
	Record* record = nullptr;
	try
	{
		record = new Record(title, Record::Type(typeint));
	}
	catch(invalid_argument& exc)
	{
		return nullptr;
	}

	// Read fields
	auto fieldNames = record->getFieldNames();
	auto nFields = fieldNames.size();
	auto nLinesRead = 0;

	std::for_each(fieldNames.begin(), fieldNames.end(), [&record, &nLinesRead, &ss](const string& name)
			{
				string value;
				if ( std::getline(ss, value) )
				{
					record->setFieldValue(name, value);
					++nLinesRead;
				}
			});

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

string wrapTextWithFieldNames(const string& text, const Record::Type recordType)
{
	string result;
	stringstream ss(text);

	string title;
	std::getline(ss, title);
	result += "title:" + title + "\n";
	string type;
	std::getline(ss, type);
	result += "type:" + type + "\n";

	set<string> fieldNames;
	try
	{
		fieldNames = Record("title", recordType).getFieldNames();
	}
	catch (invalid_argument&)
	{
		return "";
	}

	std::for_each(fieldNames.begin(), fieldNames.end(), [&result, &ss](const string& name)
			{
				string value;
				std::getline(ss, value);
				result += name + ":" + value + "\n";
			});

	removeLastNewLineFromString(result);
	return result;
}

string unwrapTextFromFieldNames(const string& text)
{
	string result;
	stringstream ss(text);

	string line;
	while (std::getline(ss, line))
	{
		auto fieldNameLastChar = line.find(':');
		if (fieldNameLastChar == string::npos)
		{
			return "";
		}
		else
		{
			result += line.substr(fieldNameLastChar + 1) + "\n";
		}
	}

	removeLastNewLineFromString(result);
	return result;
}

static bool stringToInt(const string& str, int& result)
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

void removeLastNewLineFromString(string& str)
{
	str.pop_back();
}




