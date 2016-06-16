/*
 * Record.cpp
 *
 *  Created on: May 23, 2016
 *      Author: mt
 */

#include <vector>
#include <typeinfo>
#include <algorithm>
#include <Core/Record.h>

using std::string;
using std::vector;
using std::set;
using std::invalid_argument;

const string Record::emptyFieldValue = "";

const string Record::site_link = "link";
const string Record::site_login = "login";
const string Record::site_password = "password";
const string Record::site_comment = "comment";

const string Record::bankcard_number = "number";
const string Record::bankcard_cardholder = "cardholder";
const string Record::bankcard_validThruMonth = "valid thru month";
const string Record::bankcard_validThruYear = "valid thru year";
const string Record::bankcard_cvv2cvc2 = "cvv2/cvc2";
const string Record::bankcard_comment = "comment";

const string Record::application_login = "login";
const string Record::application_password = "password";
const string Record::application_comment = "comment";

Record::Record(const string& title, const Type type) throw(invalid_argument)
{
	if (!isValidTitle(title))
	{
		throw invalid_argument(typeid(*this).name() + string(": construct with invalid title = '" + title + "'"));
	}

	if (!isValidType(type))
	{
		throw invalid_argument(typeid(*this).name() + string(": construct with invalid type = '" + std::to_string(type) + "'"));
	}

	setTitle(title);
	setType(type);

	vector<string> fields;
	if (type == SITE)
	{
		fields = {site_link, site_login, site_password, site_comment};
	}
	else if (type == BANKCARD)
	{
		fields = {bankcard_number, bankcard_cardholder,
				bankcard_validThruMonth, bankcard_validThruYear, bankcard_cvv2cvc2,
				bankcard_comment};
	}
	else if (type == APPLICATION)
	{
		fields = {application_login, application_password, application_comment};
	}
	else
	{
		// Impossible, type is validated above
	}
	initFields(fields);
}

bool Record::setTitle(const string& title)
{
	auto isValid = isValidTitle(title);
	if (isValid)
	{
		this->title = title;
	}
	return isValid;
}

bool Record::setType(const Type type)
{
	auto isValid = isValidType(type);
	if (isValid)
	{
		this->type = type;
	}
	return isValid;
}

Record::Type Record::getType() const
{
	return type;
}

string Record::getTitle() const
{
	return title;
}

bool Record::isValidTitle(const string& title) const
{
	return !title.empty();
}

bool Record::isValidType(const Type type) const
{
	return type < Type::END;
}

void Record::initFields(const vector<string>& names)
{
	std::for_each(names.begin(), names.end(), [this](const string& name)
			{
				fields.insert( std::make_pair(name, emptyFieldValue) );
			});
}

bool Record::isValidFieldName(const string& name) const
{
	fields.find(name) != fields.end();
}

bool Record::setFieldValue(const string& name, const string& value)
{
	if ( !isValidFieldName(name) )
	{
		return false;
	}

	fields[name] = value;
	return true;
}

bool Record::getFieldValue(const string& name, string& value) const
{
	if ( !isValidFieldName(name) )
	{
		return false;
	}

	value = fields.find(name)->second;
	return true;
}

set<string> Record::getFieldNames() const
{
	set<string> names;
	std::for_each(fields.begin(), fields.end(), [&names](const std::pair<string,string>& field)
			{
				names.insert(field.first);
			});
	return names;
}

