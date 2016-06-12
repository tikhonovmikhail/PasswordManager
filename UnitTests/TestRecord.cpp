#include <iostream>
#include "UnitTest.h"
#include "Record.h"

using std::string;
using std::set;
using std::vector;
using std::invalid_argument;

#ifdef RUN_UNIT_TESTS

DECLARE(Record)
string goodTitle;
string goodTitle2;
vector<string> badTitles;
Record::rtype goodType;
Record::rtype goodType2;
Record::rtype badType;
string validFieldValue;
string validFieldValue2;
string validFieldName;
string invalidFieldName;
END_DECLARE

SETUP(Record)
{
	goodTitle = "my title";
	goodTitle2 = "foo";
	badTitles = {""}; // Add examples of bad names here
	goodType = Record::rtype::SITE;
	goodType2 = Record::rtype::BANKCARD;
	badType = Record::rtype(146);
	validFieldValue = "v";
	validFieldValue2 = "v2";
	validFieldName = Record::site_login;
	invalidFieldName = "foo";
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

TESTF(Record, ShouldSetValueOfValidField)
{
	Record r(goodTitle, goodType);
	ASSERT_TRUE(r.setFieldValue(validFieldName, validFieldValue));

	string actualValue = "";
	ASSERT_TRUE(r.getFieldValue(validFieldName, actualValue));
	ASSERT_EQUALS(validFieldValue, actualValue);
}

TESTF(Record, ShouldNotSetValueOfInvalidField)
{
	Record r(goodTitle, goodType);
	ASSERT_TRUE( !r.setFieldValue(invalidFieldName, validFieldValue) );
}

TESTF(Record, ShouldContainValidSetOfFields)
{
	Record rsite(goodTitle, Record::SITE);
	Record rbankcard(goodTitle, Record::BANKCARD);
	Record rapplication(goodTitle, Record::APPLICATION);

	auto actualSite  = rsite.getFieldNames();
	auto actualBankcard = rbankcard.getFieldNames();
	auto actualApplication = rapplication.getFieldNames();

	set<string> expectedSite {Record::site_link, Record::site_login,
		Record::site_password, Record::site_comment};
	set<string> expectedBankcard {Record::bankcard_number,
		Record::bankcard_cardholder, Record::bankcard_validThruMonth,
		Record::bankcard_validThruYear, Record::bankcard_cvv2cvc2,
		Record::bankcard_comment};
	set<string> expectedApplication {Record::application_login, Record::application_password,
		Record::application_comment};

	ASSERT_EQUALS(expectedSite, actualSite);
	ASSERT_EQUALS(expectedBankcard, actualBankcard);
	ASSERT_EQUALS(expectedApplication, actualApplication);
}

#endif // RUN_UNIT_TESTS
