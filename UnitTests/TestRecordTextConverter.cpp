/*
 * TestRecordTextConverter.cpp
 *
 *  Created on: Jun 12, 2016
 *      Author: misha123
 */

#include <memory>
#include "UnitTest.h"
#include "RecordTextConverter.h"

using std::string;

#ifdef RUN_UNIT_TESTS

DECLARE(RecordTextConverter)
string title;
Record::rtype type;
string link;
string login;
string password;
string comment;
string validText;
END_DECLARE

SETUP(RecordTextConverter)
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

TEARDOWN(RecordTextConverter) {}

TESTF(RecordTextConverter, ShouldConvertValidRecordToText)
{
	std::unique_ptr<Record> record(new Record(title, type));
	record.get()->setFieldValue(Record::site_link, link);
	record.get()->setFieldValue(Record::site_login, login);
	record.get()->setFieldValue(Record::site_password, password);
	record.get()->setFieldValue(Record::site_comment, comment);

	ASSERT_EQUALS(validText, RecordTextConverter::recordToText(record.get()));
}

TESTF(RecordTextConverter, ShouldReturnEmptyStringIfRecordIsNull)
{
	ASSERT_EQUALS("", RecordTextConverter::recordToText(nullptr));
}

TESTF(RecordTextConverter, ShouldConvertValidTextToRecord)
{
	auto record = RecordTextConverter::textToRecord(validText);
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

	delete record;
}

TESTF(RecordTextConverter, ShouldReturnNullIfEmptyTitle)
{
	string textWithoutTitle = "\n" +
			   std::to_string(type) + "\n" +
			   // in sorted order
			   comment + "\n" +
			   link + "\n" +
			   login + "\n" +
			   password + "\n";
	ASSERT_EQUALS(nullptr, RecordTextConverter::textToRecord(textWithoutTitle));
}

TESTF(RecordTextConverter, ShouldReturnNullIfEmptyType)
{
	string textWithEmptyType = title + "\n" +
				"" + "\n" +
				// in sorted order
				comment + "\n" +
				link + "\n" +
				login + "\n" +
				password + "\n";
	ASSERT_EQUALS(nullptr, RecordTextConverter::textToRecord(textWithEmptyType));
}

TESTF(RecordTextConverter, ShouldReturnNullIfBadType)
{
	string textWithBadType = title + "\n" +
			    std::to_string(Record::rtype::END) + "\n" +
				// in sorted order
				comment + "\n" +
				link + "\n" +
				login + "\n" +
				password + "\n";
	ASSERT_EQUALS(nullptr, RecordTextConverter::textToRecord(textWithBadType));
}

TESTF(RecordTextConverter, ShouldReturnNullIfTypeHasBadFormat)
{
	string textWithBadTypeFormat = title + "\n" +
			    "1foo" + "\n" +
				// in sorted order
				comment + "\n" +
				link + "\n" +
				login + "\n" +
				password + "\n";
	ASSERT_EQUALS(nullptr, RecordTextConverter::textToRecord(textWithBadTypeFormat));
}

TESTF(RecordTextConverter, ShouldReturnNullIfBadFields)
{
	string textWithOneFieldLost = title + "\n" +
			   std::to_string(type) + "\n" +
			   // in sorted order
			   comment + "\n" +
			   link + "\n" +
			   password + "\n";
	ASSERT_EQUALS(nullptr, RecordTextConverter::textToRecord(textWithOneFieldLost));
}

TESTF(RecordTextConverter, ShouldWorkInBothDirections)
{
	std::unique_ptr<Record> record (RecordTextConverter::textToRecord(validText));
	ASSERT_EQUALS(validText, RecordTextConverter::recordToText(record.get()));
}

#endif // RUN_UNIT_TESTS


