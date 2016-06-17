/*
 * Api.cpp
 *
 *  Created on: Jun 14, 2016
 *      Author: misha123
 */

#include <stdexcept>
#include <functional>
#include <algorithm>
#include <fstream>
#include <streambuf>

#include <Core/Record.h>
#include <Core/Records.h>
#include <Core/EncryptFunctions.h>
#include <Core/RecordToTextConvertFunctions.h>
#include <Core/RecordsApi.h>

using std::string;
using std::list;
using std::invalid_argument;
using std::ifstream;
using std::ofstream;

namespace LibPm {

Records records;

Record* createSiteRecord(const string& title,
		const string& link,
		const string& login,
		const string& password,
		const string& comment)
{
	Record* record = nullptr;
	try
	{
		record = new Record(title, Record::Type::SITE);
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
		record = new Record(title, Record::Type::BANKCARD);
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
		record = new Record(title, Record::Type::APPLICATION);
	}
	catch(invalid_argument&)
	{
		return nullptr;
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
	auto record = createSiteRecord(title, link, login, password, comment);
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
	auto record = createBankcardRecord(title, number, cardholder,
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
	auto record = createApplicationRecord(title, login, password, comment);
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
	auto record = createSiteRecord(title, link, login, password, comment);
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
	auto record = createBankcardRecord(title, number, cardholder,
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
	auto record = records.find(title);
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
	auto record = records.find(title);
	if (!record)
	{
		return false;
	}

	return  record->getFieldValue(Record::application_login, login) &&
			record->getFieldValue(Record::application_password, password) &&
			record->getFieldValue(Record::application_comment, comment);
}

bool getRecordType(const string& title, Recordtype& type)
{
	auto record = records.find(title);
	if (!record)
	{
		return false;
	}

	type = Recordtype(record->getType());
	return true;
}

void getRecordsTitles(list<string>& titles, const Recordtype type)
{
	list<const Record*> rlist;
	if (type == Recordtype::UNKNOWN)
	{
		rlist = records.getAll();
	}
	else
	{
		rlist = records.getByType( Record::Type(type) );
	}

	std::for_each(rlist.begin(), rlist.end(), [&titles](const Record* r)
					{
						titles.push_front(r->getTitle());
					});
}

bool importRecord(const string& text, string& title)
{
	auto record = textToRecord( unwrapTextFromFieldNames(text) );
	if (record)
	{
		records.add(record);
		title = record->getTitle();
	}

	return record != nullptr;
}

bool exportRecord(const string& title, string& text)
{
	auto record = records.find(title);
	if (record)
	{
		text = wrapTextWithFieldNames( recordToText(record), record->getType());
	}

	return !text.empty();
}

bool importRecords(const list<string>& texts)
{
	std::for_each(texts.begin(), texts.end(), [](const string& text)
			{
				string title;
				if ( !importRecord(text, title) )
				{
					return false;
				}
			});
	return true;
}

bool exportRecords(list<string>& texts)
{
	list<string> titles;
	getRecordsTitles(titles, Recordtype::UNKNOWN);

	std::for_each(titles.begin(), titles.end(), [&texts](const string& title)
			{
				string text;
				if ( exportRecord(title, text) )
				{
					texts.push_front(text);
				}
				else
				{
					return false;
				}
			});
	return true;
}

list<string> xcryptRecords(const list<string>& texts, const string& key,
		const std::function<string(const string&, const string&)>& xcryptFunc)
{
	list<string> result;
	std::for_each(texts.begin(), texts.end(), [&key, &xcryptFunc, &result](const string& text)
			{
				result.push_front( xcryptFunc(text, key) );
			});
	return result;
}

list<string> encryptRecords(const list<string>& texts, const string& key)
{
	return xcryptRecords(texts, key, encryptText);
}

list<string> decryptRecords(const list<string>& texts, const string& key)
{
	return xcryptRecords(texts, key, decryptText);
}


bool readRecords(const string& dir, const string& key)
{
	list<string> texts;
	for (auto index = 0; ; ++index)
	{
		ifstream ifs(dir + std::to_string(index));
		if ( !ifs.is_open() )
		{
			break;
		}

		string text((std::istreambuf_iterator<char>(ifs)),
				     std::istreambuf_iterator<char>());
		texts.push_back(text);
		ifs.close();
	}

	texts = decryptRecords(texts, key);
	return importRecords(texts);
}

bool writeRecords(const string& dir, const string& key)
{
	list<string> texts;
	if ( !exportRecords(texts) )
	{
		return false;
	}

	texts = encryptRecords(texts, key);

	int index = 0;
	std::for_each(texts.begin(), texts.end(), [dir, &index](const string& text)
			{
				ofstream ofs(dir + std::to_string(index));
				if (!ofs.is_open())
				{
					return false;
				}
				ofs << text << std::endl;
				ofs.close();
				++index;
			});
	return true;
}
}
