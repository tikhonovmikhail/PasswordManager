/*
 * Api.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: misha123
 */

#include <stdexcept>
#include <Api.h>
#include "Records.h"
#include "Record.h"
#include "RecordTextConverter.h"
#include "EncryptFunctions.h"

using std::string;
using std::list;
using std::invalid_argument;

namespace RecordsApi {

static Records records;

static int getSubkeyLength()
{
	return 1763;
}

Record* createSiteRecord(const string& title,
		const string& link,
		const string& login,
		const string& password,
		const string& comment)
{
	Record* record = nullptr;
	try
	{
		record = new Record(title, Record::rtype::SITE);
	}
	catch(invalid_argument&)
	{
		return nullptr;
	}

	record->setFieldValue(Record::site_link, link);
	record->setFieldValue(Record::site_login, login);
	record->setFieldValue(Record::site_password, password);
	record->setFieldValue(Record::site_comment, comment);

	return record;
}

Record* createBankcardRecord(const string& title,
		const string& number,
		const string& cardholder,
		const string& validThruMonth,
		const string& validThruYear,
		const string& cvv2cvc2,
		const string& comment)
{
	Record* record = nullptr;
	try
	{
		record = new Record(title, Record::rtype::BANKCARD);
	}
	catch(invalid_argument&)
	{
		return nullptr;
	}

	record->setFieldValue(Record::bankcard_number, number);
	record->setFieldValue(Record::bankcard_cardholder, cardholder);
	record->setFieldValue(Record::bankcard_validThruMonth, validThruMonth);
	record->setFieldValue(Record::bankcard_validThruYear, validThruYear);
	record->setFieldValue(Record::bankcard_cvv2cvc2, cvv2cvc2);
	record->setFieldValue(Record::bankcard_comment, comment);

	return record;
}

Record* createApplicationRecord(const string& title,
		const string& login,
		const string& password,
		const string& comment)
{
	Record* record = nullptr;
	try
	{
		record = new Record(title, Record::rtype::APPLICATION);
	}
	catch(invalid_argument&)
	{
		return false;
	}

	record->setFieldValue(Record::application_login, login);
	record->setFieldValue(Record::application_password, password);
	record->setFieldValue(Record::application_comment, comment);

	return record;
}

bool addSiteRecord(const string& title,
		const string& link,
		const string& login,
		const string& password,
		const string& comment)
{
	Record* record = createSiteRecord(title, link, login, password, comment);
	if (record)
	{
		records.add(record);
	}

	return record != nullptr;
}

bool addBankcardRecord(const string& title,
		const string& number,
		const string& cardholder,
		const string& validThruMonth,
		const string& validThruYear,
		const string& cvv2cvc2,
		const string& comment)
{
	Record* record = createBankcardRecord(title, number, cardholder,
			validThruMonth, validThruYear, cvv2cvc2, comment);
	if (record)
	{
		records.add(record);
	}

	return record != nullptr;
}

bool addApplicationRecord(const string& title,
		const string& login,
		const string& password,
		const string& comment)
{
	Record* record = createApplicationRecord(title, login, password, comment);
	if (record)
	{
		records.add(record);
	}

	return record != nullptr;
}

bool removeRecord(const string& title)
{
	return records.remove(title);
}

bool replaceWithSiteRecord(const string& oldTitle,
		const string& title,
		const string& link,
		const string& login,
		const string& password,
		const string& comment)
{
	Record* record = createSiteRecord(title, link, login, password, comment);
	if ( records.replace(oldTitle, record) )
	{
		return true;
	}
	else
	{
		delete record;
		return false;
	}
}

bool replaceWithBankcardRecord(const string& oldTitle,
		const string& title,
		const string& number,
		const string& cardholder,
		const string& validThruMonth,
		const string& validThruYear,
		const string& cvv2cvc2,
		const string& comment)
{
	Record* record = createBankcardRecord(title, number, cardholder,
			validThruMonth, validThruYear, cvv2cvc2, comment);
	if ( records.replace(oldTitle, record) )
	{
		return true;
	}
	else
	{
		delete record;
		return false;
	}
}

bool replaceWithApplicationRecord(const string& oldTitle,
		const string& title,
		const string& login,
		const string& password,
		const string& comment)
{
	Record* record = createApplicationRecord(title, login, password, comment);
	if ( records.replace(oldTitle, record) )
	{
		return true;
	}
	else
	{
		delete record;
		return false;
	}
}

bool getSiteRecord(const string& title,
		string& link,
		string& login,
		string& password,
		string& comment)
{
	const Record* record = records.find(title);
	if (!record)
	{
		return false;
	}

	return  record->getFieldValue(Record::site_link, link) &&
			record->getFieldValue(Record::site_login, login) &&
			record->getFieldValue(Record::site_password, password) &&
			record->getFieldValue(Record::site_comment, comment);
}

bool getBankcardRecord(const string& title,
		string& number,
		string& cardholder,
		string& validThruMonth,
		string& validThruYear,
		string& cvv2cvc2,
		string& comment)
{
	const Record* record = records.find(title);
	if (!record)
	{
		return false;
	}

	return  record->getFieldValue(Record::bankcard_number, number) &&
			record->getFieldValue(Record::bankcard_cardholder, cardholder) &&
			record->getFieldValue(Record::bankcard_validThruMonth, validThruMonth) &&
			record->getFieldValue(Record::bankcard_validThruYear, validThruYear) &&
			record->getFieldValue(Record::bankcard_cvv2cvc2, cvv2cvc2) &&
			record->getFieldValue(Record::bankcard_comment, comment);
}

bool getApplicationRecord(const string& title,
		string& login,
		string& password,
		string& comment)
{
	const Record* record = records.find(title);
	if (!record)
	{
		return false;
	}

	return  record->getFieldValue(Record::application_login, login) &&
			record->getFieldValue(Record::application_password, password) &&
			record->getFieldValue(Record::application_comment, comment);
}

bool getRecordType(const string& title, recordtype& type)
{
	const Record* record = records.find(title);
	if (!record)
	{
		return false;
	}

	type = recordtype(record->getType());
	return true;
}

void getRecordsTitles(list<string>& titles, const recordtype type)
{
	if (type == UNKNOWN)
	{
		auto rlist = records.getAll();
		for (const auto& r: rlist)
		{
			titles.push_front(r->getTitle());
		}
	}
	else
	{
		auto rlist = records.getByType( Record::rtype(type) );
		for (const auto& r: rlist)
		{
			titles.push_front(r->getTitle());
		}
	}
}

bool importRecord(const string& text, string& title)
{
	Record* record = RecordTextConverter::textToRecord(text);
	if (record)
	{
		records.add(record);
		title = record->getTitle();
	}

	return record != nullptr;
}

bool exportRecord(const string& title, string& text)
{
	const Record* record = records.find(title);
	if (record)
	{
		text = RecordTextConverter::recordToText(record);
	}

	return !text.empty();
}

string encryptRecord(const string& text, const string& key)
{
	return encrypt(text, key);
}

string decryptRecord(const string& text, const string& key)
{
	return decrypt(text, key);
}

string generateKeyBase()
{
	return generateKey(10000000 + getSubkeyLength());
}

string getKeyFromBase(const string& baseKey, const int startPos)
{
	return getSubkey(baseKey, startPos, getSubkeyLength());
}

}
