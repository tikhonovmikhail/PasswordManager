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

const Record::type Record::site = 1;
const Record::type Record::bankCard = 2;

Record::Record(const string& title, const type rtype) throw(invalid_argument)
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

bool Record::setType(const type rtype)
{
	bool isValid = isValidType(rtype);
	if (isValid)
	{
		this->rtype = rtype;
	}
	return isValid;
}

Record::type Record::getType() const
{
	return rtype;
}

bool Record::isValidTitle(const string& title) const
{
	return !title.empty();
}

bool Record::isValidType(const type rtype) const
{
	return (rtype == site) || (rtype == bankCard);
}

#ifdef RUN_UNIT_TESTS

DECLARE(Record)
string goodTitle;
string goodTitle2;
vector<string> badTitles;
Record::type goodType;
Record::type goodType2;
Record::type badType;
END_DECLARE

SETUP(Record)
{
	goodTitle = "my title";
	goodTitle2 = "foo";
	badTitles = {""}; // Add examples of bad names here
	goodType = Record::site;
	goodType2 = Record::bankCard;
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
		Record r(goodTitle, badType);
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
