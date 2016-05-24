/*
 * Record.cpp
 *
 *  Created on: May 23, 2016
 *      Author: mt
 */

#include <vector>
#include <typeinfo>
#include <Record/Record.h>
#include "UnitTest.h"

using std::string;
using std::vector;
using std::invalid_argument;

const string Record::defaultFieldValue = "";

Record::Record(const string& title) throw(invalid_argument)
{
	if (!isValidTitle(title))
		throw invalid_argument(typeid(*this).name() + string(": construct with invalid title = '" + title + "'"));

	setTitle(title);
}

Record::~Record()
{

}

bool Record::setTitle(const string& title)
{
	bool isValid = isValidTitle(title);
	if (isValid)
	{
		this->title = title;
	}
	return isValid;
}

string Record::getTitle() const
{
	return title;
}

bool Record::isValidTitle(const string& title) const
{
	return !title.empty();
}

void Record::initFields(const vector<string>& names)
{
	for (const auto& name: names)
	{
		fields.insert( std::make_pair(name,defaultFieldValue) );
	}
}

bool Record::isValidFieldName(const string& name) const
{
	fields.find(name) != fields.end();
}

bool Record::setFieldValue(const string& name, const string& value)
{
	if ( !isValidFieldName(name) )
		return false;

	return isValidFieldValue(name, value);
}


