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

#ifdef RUN_UNIT_TESTS

DECLARE(Record)
string goodTitle;
string goodTitle2;
vector<string> badTitles;
END_DECLARE

SETUP(Record)
{
	goodTitle = "my title";
	goodTitle2 = "foo";
	badTitles = {""}; // Add examples of bad names here
}

TEARDOWN(Record) {}

TESTF(Record, ShouldCreateObjectWithValidParams)
{
	try
	{
		Record r(goodTitle);
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
			Record r(badTitle);
		}
		catch(invalid_argument& exc)
		{
			ASSERT_TRUE(true);
			continue;
		}
		ASSERT_TRUE(false);
	}
}

TESTF(Record, ShouldSetValidTitle)
{
	Record r(goodTitle);
	ASSERT_TRUE(r.setTitle(goodTitle2));
	ASSERT_EQUALS(goodTitle2, r.getTitle());
}

TESTF(Record, ShouldNotSetInvalidTitle)
{
	Record r(goodTitle);
	ASSERT_TRUE( !r.setTitle(badTitles.at(0)) );
	ASSERT_EQUALS(goodTitle, r.getTitle());
}

#endif // RUN_UNIT_TESTS
