/*
 * Record.cpp
 *
 *  Created on: May 23, 2016
 *      Author: mt
 */

#include <vector>
#include <typeinfo>
#include "Record.h"
#include "UnitTest.h"

using std::string;
using std::vector;
using std::invalid_argument;

Record::Record(const string& title, const types rtype) throw(invalid_argument)
{
	if (!isValidTitle(title))
		throw invalid_argument(typeid(*this).name() + string(": construct with invalid title = '" + title + "'"));

	if (!isValidType(rtype))
		throw invalid_argument(typeid(*this).name() + string(": construct with invalid type = '" + std::to_string(rtype) + "'"));

	setTitle(title);
	setType(rtype);
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

bool Record::setType(const types rtype)
{
	bool isValid = isValidType(rtype);
	if (isValid)
	{
		this->rtype = rtype;
	}
	return isValid;
}

Record::types Record::getType() const
{
	return rtype;
}

bool Record::isValidTitle(const string& title) const
{
	return !title.empty();
}

bool Record::isValidType(const types rtype) const
{
	return rtype < types::nTypes;
}

#ifdef RUN_UNIT_TESTS

DECLARE(Record)
string goodTitle;
string goodTitle2;
vector<string> badTitles;
Record::types goodType;
Record::types goodType2;
int badType;
END_DECLARE

SETUP(Record)
{
	goodTitle = "my title";
	goodTitle2 = "foo";
	badTitles = {""}; // Add examples of bad names here
	goodType = Record::types::site;
	goodType2 = Record::types::bankCard;
	badType = 146;
}

TEARDOWN(Record) {}

TESTF(Record, ShouldCreateObjectWithValidParams)
{
	try
	{
		Record r(goodTitle, goodType);
	}
	catch(invalid_argument& exc)
	{
		ASSERT_TRUE(false);
		return;
	}
	ASSERT_TRUE(true);
}

TESTF(Record, ShouldNotCreateObjectWithInvalidTitle)
{
	for (const auto &badTitle: badTitles)
	{
		try
		{
			Record r(badTitle, goodType);
		}
		catch(invalid_argument& exc)
		{
			ASSERT_TRUE(true);
			continue;
		}
		ASSERT_TRUE(false);
	}
}

TESTF(Record, ShouldNotCreateObjectWithInvalidType)
{
	try
	{
		Record r(goodTitle, Record::types(badType));
	}
	catch (invalid_argument& exc)
	{
		ASSERT_TRUE(true);
		return;
	}
	ASSERT_TRUE(false);
}

TESTF(Record, ShouldSetValidTitle)
{
	Record r(goodTitle, goodType);
	ASSERT_TRUE(r.setTitle(goodTitle2));
	ASSERT_EQUALS(goodTitle2, r.getTitle());
}

TESTF(Record, ShouldNotSetInvalidTitle)
{
	Record r(goodTitle, goodType);
	ASSERT_TRUE( !r.setTitle(badTitles.at(0)) );
	ASSERT_EQUALS(goodTitle, r.getTitle());
}

#endif // RUN_UNIT_TESTS
