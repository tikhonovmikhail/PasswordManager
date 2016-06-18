/*
 * TestRecordsApi.cpp
 *
 *  Created on: Jun 18, 2016
 *      Author: misha123
 */

#include <UnitTest.h>
#include <Api/RecordsApi.h>

using namespace LibPm;
using std::string;
using std::list;

#ifdef RUN_UNIT_TESTS

DECLARE(RecordsApi)
#define ON_TEST_END clearRecords();
string title1;
string title2;
string title3;

string actualLogin, actualPassword, actualComment,
		actualLink, actualNumber, actualCardholder,
		actualValidThruMonth, actualValidThruYear, actualCvv2cvc2;

string appTitle, bankTitle, siteTitle,
expectedAppLogin, expectedAppPass, expectedAppComment,
expectedBankNumber, expectedBankCardholder, expectedBankMonth, expectedBankYear,
expectedBankCode, expectedBankComment,
expectedSiteLink, expectedSiteLogin, expectedSitePassword, expectedSiteComment;
END_DECLARE

SETUP(RecordsApi)
{
	title1 = "title1";
	title2 = "title2";
	title3 = "title3";

	appTitle = "skype";
	bankTitle = "VTB";
	siteTitle = "Gmail";
	expectedAppLogin = "misha";
	expectedAppPass = "pass";
	expectedAppComment = "smth";
	expectedBankNumber = "28482748729";
	expectedBankCardholder = "Mister";
	expectedBankMonth = "03";
	expectedBankYear = "19";
	expectedBankCode = "123";
	expectedBankComment = "Salary";
	expectedSiteLink = "https://www.gmail.com";
	expectedSiteLogin = "mt";
	expectedSitePassword = "12345678";
	expectedSiteComment = "Work email";
}

TEARDOWN(RecordsApi) {}

TESTF(RecordsApi, ShouldAddRecord)
{
	addApplicationRecord(title1, "", "", "");
	addApplicationRecord(title2, "", "", "");

	list<string> titlesActual;
	getRecordsTitles(titlesActual, Recordtype::UNKNOWN);
	list<string> titlesExpected = {title1, title2};
	ASSERT_EQUALS(titlesExpected, titlesActual);

	ON_TEST_END
}

TESTF(RecordsApi, ShouldRemoveRecord)
{
	addSiteRecord(title1, "", "", "", "");
	addBankcardRecord(title2, "", "", "", "", "", "");
	removeRecord(title2);

	list<string> titlesActual;
	getRecordsTitles(titlesActual, Recordtype::UNKNOWN);
	list<string> titlesExpected = {title1};
	ASSERT_EQUALS(titlesExpected, titlesActual);

	ON_TEST_END
}

TESTF(RecordsApi, ShouldReplaceRecord)
{
	addSiteRecord(title1, "", "", "", "");
	replaceWithApplicationRecord(title1, title2, "", "", "");

	list<string> titlesActual;
	getRecordsTitles(titlesActual, Recordtype::UNKNOWN);
	list<string> titlesExpected = {title2};
	ASSERT_EQUALS(titlesExpected, titlesActual);

	Recordtype typeActual;
	getRecordType(title2, typeActual);
	ASSERT_EQUALS(Recordtype::APPLICATION, typeActual);

	ON_TEST_END
}

TESTF(RecordsApi, ShouldReturnRecordType)
{
	addBankcardRecord(title1, "", "", "", "", "", "");

	Recordtype typeActual;
	getRecordType(title1, typeActual);
	ASSERT_EQUALS(Recordtype::BANKCARD, typeActual);

	ON_TEST_END
}

TESTF(RecordsApi, ShouldReturnTitlesList)
{
	addSiteRecord(title1, "", "", "", "");
	addBankcardRecord(title2, "", "", "", "", "", "");
	addBankcardRecord(title3, "", "", "", "", "", "");

	// All
	list<string> titlesActual;
	getRecordsTitles(titlesActual, Recordtype::UNKNOWN);
	list<string> titlesExpected = {title1, title2, title3};
	ASSERT_EQUALS(titlesExpected, titlesActual);

	// By type
	titlesActual = {};
	getRecordsTitles(titlesActual, Recordtype::BANKCARD);
	titlesExpected = {title2, title3};
	ASSERT_EQUALS(titlesExpected, titlesActual);

	ON_TEST_END
}

TESTF(RecordsApi, ShouldClearRecords)
{
	addSiteRecord(title1, "", "", "", "");
	addApplicationRecord(title2, "", "", "");
	clearRecords();

	list<string> titles;
	getRecordsTitles(titles, Recordtype::UNKNOWN);
	ASSERT_EQUALS(0, titles.size());

	ON_TEST_END
}

TESTF(RecordsApi, ShouldReturnRecordWithAllFieldsByTitle)
{
	addApplicationRecord(appTitle,
			expectedAppLogin, expectedAppPass, expectedAppComment);
	addSiteRecord(siteTitle,
			expectedSiteLink, expectedSiteLogin,
			expectedSitePassword, expectedSiteComment);
	addBankcardRecord(bankTitle,
			expectedBankNumber, expectedBankCardholder,
			expectedBankMonth, expectedBankYear,
			expectedBankCode, expectedBankComment);

	getApplicationRecord(appTitle, actualLogin, actualPassword, actualComment);
	ASSERT_EQUALS(expectedAppLogin, actualLogin);
	ASSERT_EQUALS(expectedAppPass, actualPassword);
	ASSERT_EQUALS(expectedAppComment, actualComment);

	getSiteRecord(siteTitle, actualLink, actualLogin, actualPassword, actualComment);
	ASSERT_EQUALS(expectedSiteLink, actualLink);
	ASSERT_EQUALS(expectedSiteLogin, actualLogin);
	ASSERT_EQUALS(expectedSitePassword, actualPassword);
	ASSERT_EQUALS(expectedSiteComment, actualComment);

	getBankcardRecord(bankTitle, actualNumber, actualCardholder,
			actualValidThruMonth, actualValidThruYear,
			actualCvv2cvc2, actualComment);
	ASSERT_EQUALS(expectedBankNumber, actualNumber);
	ASSERT_EQUALS(expectedBankCardholder, actualCardholder);
	ASSERT_EQUALS(expectedBankMonth, actualValidThruMonth);
	ASSERT_EQUALS(expectedBankYear, actualValidThruYear);
	ASSERT_EQUALS(expectedBankCode, actualCvv2cvc2);
	ASSERT_EQUALS(expectedBankComment, actualComment);

	ASSERT_TRUE( !getApplicationRecord("foo",
			actualLogin, actualPassword, actualComment) );

	ON_TEST_END
}

#ifdef CAN_USE_REAL_ENVIRONMENT

TESTF(RecordsApi, ShouldWriteAndReadRecords)
{
	string dir = "./";
	string key = "secret";

	addApplicationRecord(appTitle,
			expectedAppLogin, expectedAppPass, expectedAppComment);
	addSiteRecord(siteTitle,
			expectedSiteLink, expectedSiteLogin, expectedSitePassword,
			expectedSiteComment);
	ASSERT_TRUE(writeRecords(dir, key));

	clearRecords();

	ASSERT_TRUE(readRecords(dir, key));
	list<string> titles;
	getRecordsTitles(titles, Recordtype::UNKNOWN);
	getApplicationRecord(appTitle, actualLogin, actualPassword, actualComment);
	ASSERT_EQUALS(expectedAppLogin, actualLogin);
	ASSERT_EQUALS(expectedAppPass, actualPassword);
	ASSERT_EQUALS(expectedAppComment, actualComment);
	getSiteRecord(siteTitle, actualLink, actualLogin, actualPassword, actualComment);
	ASSERT_EQUALS(expectedSiteLink, actualLink);
	ASSERT_EQUALS(expectedSiteLogin, actualLogin);
	ASSERT_EQUALS(expectedSitePassword, actualPassword);
	ASSERT_EQUALS(expectedSiteComment, actualComment);

	std::remove( string(dir + "0").c_str() );
	std::remove( string(dir + "1").c_str() );
	ON_TEST_END
}

TESTF(RecordsApi, ShouldNotWriteAndReadRecordsUsingBadDir)
{
	ASSERT_TRUE( !writeRecords("foo", "secret") );
	ASSERT_TRUE( !readRecords("foo", "secret") );

	ON_TEST_END
}

#endif // CAN_USE_REAL_ENVIRONMENT
#endif // RUN_UNIT_TESTS



