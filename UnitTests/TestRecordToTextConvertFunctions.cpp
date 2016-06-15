/*
 * TestRecordToTextConvertFunctions.cpp
 *
 *  Created on: Jun 15, 2016
 *      Author: mt
 */

#include <memory>
#include "UnitTest.h"
#include "RecordToTextConvertFunctions.h"

using std::string;

#ifdef RUN_UNIT_TESTS

DECLARE(RecordToTextConvertFunctions)
string title;
Record::Type type;
string link;
string login;
string password;
string comment;
string validText;
END_DECLARE

SETUP(RecordToTextConvertFunctions)
{
	title = "my title";
	type = Record::SITE;
	link = "http://vk.com";
	login = "misha";
	password = "12345678";
	comment = "";
	validText = title + "\n" +
		   std::to_string(type) + "\n" +
		   // in sorted order
		   comment + "\n" +
		   link + "\n" +
		   login + "\n" +
		   password + "\n";
}

TEARDOWN(RecordToTextConvertFunctions) {}

TESTF(RecordToTextConvertFunctions, ShouldConvertValidRecordToText)
{
	std::unique_ptr<Record> record(new Record(title, type));
	record.get()->setFieldValue(Record::site_link, link);
	record.get()->setFieldValue(Record::site_login, login);
	record.get()->setFieldValue(Record::site_password, password);
	record.get()->setFieldValue(Record::site_comment, comment);

	ASSERT_EQUALS(validText, recordToText(record.get()));
}

TESTF(RecordToTextConvertFunctions, ShouldReturnEmptyStringIfRecordIsNull)
{
	ASSERT_EQUALS("", recordToText(nullptr));
}

TESTF(RecordToTextConvertFunctions, ShouldConvertValidTextToRecord)
{
	std::unique_ptr<Record> record( textToRecord(validText) );
	string value;

	ASSERT_EQUALS(title, record->getTitle());
	ASSERT_EQUALS(type, record->getType());

	value.clear();
	record->getFieldValue(Record::site_link, value);
	ASSERT_EQUALS(link, value);

	value.clear();
	record->getFieldValue(Record::site_login, value);
	ASSERT_EQUALS(login, value);

	value.clear();
	record->getFieldValue(Record::site_password, value);
	ASSERT_EQUALS(password, value);

	value.clear();
	record->getFieldValue(Record::site_comment, value);
	ASSERT_EQUALS(comment, value);
}

TESTF(RecordToTextConvertFunctions, ShouldReturnNullIfEmptyTitle)
{
	string textWithoutTitle = "\n" +
			   std::to_string(type) + "\n" +
			   // in sorted order
			   comment + "\n" +
			   link + "\n" +
			   login + "\n" +
			   password + "\n";
	ASSERT_EQUALS(nullptr, textToRecord(textWithoutTitle));
}

TESTF(RecordToTextConvertFunctions, ShouldReturnNullIfEmptyType)
{
	string textWithEmptyType = title + "\n" +
				"" + "\n" +
				// in sorted order
				comment + "\n" +
				link + "\n" +
				login + "\n" +
				password + "\n";
	ASSERT_EQUALS(nullptr, textToRecord(textWithEmptyType));
}

TESTF(RecordToTextConvertFunctions, ShouldReturnNullIfBadType)
{
	string textWithBadType = title + "\n" +
			    std::to_string(Record::Type::END) + "\n" +
				// in sorted order
				comment + "\n" +
				link + "\n" +
				login + "\n" +
				password + "\n";
	ASSERT_EQUALS(nullptr, textToRecord(textWithBadType));
}

TESTF(RecordToTextConvertFunctions, ShouldReturnNullIfTypeHasBadFormat)
{
	string textWithBadTypeFormat = title + "\n" +
			    "1foo" + "\n" +
				// in sorted order
				comment + "\n" +
				link + "\n" +
				login + "\n" +
				password + "\n";
	ASSERT_EQUALS(nullptr, textToRecord(textWithBadTypeFormat));
}

TESTF(RecordToTextConvertFunctions, ShouldReturnNullIfBadFields)
{
	string textWithOneFieldLost = title + "\n" +
			   std::to_string(type) + "\n" +
			   // in sorted order
			   comment + "\n" +
			   link + "\n" +
			   password + "\n";
	ASSERT_EQUALS(nullptr, textToRecord(textWithOneFieldLost));
}

TESTF(RecordToTextConvertFunctions, ShouldWorkInBothDirections)
{
	std::unique_ptr<Record> record (textToRecord(validText));
	ASSERT_EQUALS(validText, recordToText(record.get()));
}

#endif // RUN_UNIT_TESTS
