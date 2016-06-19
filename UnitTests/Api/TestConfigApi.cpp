/*
 * TestConfigApi.cpp
 *
 *  Created on: Jun 19, 2016
 *      Author: misha123
 */

#include <UnitTest.h>

#ifdef RUN_UNIT_TESTS

#include <string>
#include <unordered_set>
#include <Core/Config.h>
#include <Api/ConfigApi.h>

using std::string;
using std::unordered_set;
using namespace LibPm;

/*
 * Almost all API functions are just wrappers under Config functions
 * and they are already tested. So we need test only IO.
 */

#ifdef CAN_USE_REAL_ENVIRONMENT

TEST(ConfigApi, ShouldWriteAndReadConfig)
{
	string appDataDir = "/home/mt";
	string title1 = "title1";
	string title2 = "title2";
	unordered_set<string> expectedTitles = {title1, title2};

	setAppDataDir(appDataDir);
	addFavouriteTitle(title1);
	addFavouriteTitle(title2);

	writeConfig();
	clearConfig();
	readConfig();

	ASSERT_EQUALS(appDataDir, getAppDataDir());
	auto actualTitles = getFavouriteTitles();
	ASSERT_EQUALS(expectedTitles, actualTitles);

	std::remove(Config::filename.c_str());
}

#endif // CAN_USE_REAL_ENVIRONMENT

#endif // RUN_UNIT_TESTS


