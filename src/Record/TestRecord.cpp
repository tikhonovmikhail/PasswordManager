#include "UnitTest.h"
#include <Record/Record.h>
#include <Record/BankCardRecord.h>
#include <Record/SiteRecord.h>

using std::string;
using std::vector;
using std::invalid_argument;

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
