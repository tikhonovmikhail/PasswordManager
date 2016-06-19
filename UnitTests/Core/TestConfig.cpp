/*
 * TestConfig.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: mt
 */

#include <UnitTest.h>

#ifdef RUN_UNIT_TESTS

#include <string>
#include <Core/Config.h>

using std::string;

DECLARE(Config)
string appDataDir;
string favouriteTitle1;
string favouriteTitle2;
string exportedText;
END_DECLARE

SETUP(Config)
{
	appDataDir = "mydir";
	favouriteTitle1 = "title1";
	favouriteTitle2 = "title2";
	exportedText =
			appDataDir + "\n" +
			favouriteTitle1 + "\n" +
			favouriteTitle2;
}

TEARDOWN(Config) {}

TESTF(Config, ShouldHaveDefaultAppDataDir)
{
	Config config;
	ASSERT_EQUALS(Config::defaultAppDataDir, config.getAppDataDir());
}

TESTF(Config, ShouldSetConfigAppDataDir)
{
	Config config;
	ASSERT_TRUE( config.setAppDataDir(appDataDir) );
	ASSERT_TRUE( !config.setAppDataDir("") );

	ASSERT_EQUALS(appDataDir, config.getAppDataDir());
}

TESTF(Config, ShouldAddUniqueFavouriteTitle)
{
	Config config;

	ASSERT_TRUE( config.addFavouriteTitle(favouriteTitle1) );
	ASSERT_TRUE( config.addFavouriteTitle(favouriteTitle2) );
	ASSERT_TRUE( !config.addFavouriteTitle(favouriteTitle1) );
}

TESTF(Config, ShouldNotAddInvalidFavouriteTitle)
{
	Config config;
	ASSERT_TRUE( !config.addFavouriteTitle("") );
	ASSERT_EQUALS(0, config.getFavouriteTitles().size());
}

TESTF(Config, ShouldRemoveExistingFavouriteTitle)
{
	Config config;
	config.addFavouriteTitle(favouriteTitle1);
	config.addFavouriteTitle(favouriteTitle2);
	ASSERT_TRUE( config.removeFavouriteTitle(favouriteTitle1) );

	ASSERT_EQUALS(1, config.getFavouriteTitles().size());
	ASSERT_EQUALS(favouriteTitle2, *(config.getFavouriteTitles().begin()));
}

TESTF(Config, ShouldNotRemoveUnexistingFavouriteTitle)
{
	Config config;
	config.addFavouriteTitle(favouriteTitle1);
	config.addFavouriteTitle(favouriteTitle2);
	ASSERT_TRUE( !config.removeFavouriteTitle("foo") );

	ASSERT_EQUALS(2, config.getFavouriteTitles().size());
}

TESTF(Config, ShouldExportToText)
{
	Config config;
	config.setAppDataDir(appDataDir);
	config.addFavouriteTitle(favouriteTitle2);
	config.addFavouriteTitle(favouriteTitle1);

	ASSERT_EQUALS(exportedText, config.exportToText());
}

TESTF(Config, ShouldImportFromValidText)
{
	Config config;
	ASSERT_TRUE( config.importFromText(exportedText) );
	ASSERT_EQUALS( appDataDir, config.getAppDataDir() );
	ASSERT_EQUALS(2, config.getFavouriteTitles().size() );
}

TESTF(Config, ShouldNotImportFromInvalidText)
{
	Config config;
	// Put good config
	config.importFromText(exportedText);
	// Put bad config
	ASSERT_TRUE( !config.importFromText("") );
	// Make sure config was not corrupted
	ASSERT_EQUALS(exportedText, config.exportToText() );
}

TESTF(Config, ShouldCleanFavouriteTitlesBeforeImport)
{
	Config config;
	config.addFavouriteTitle("foo"); // this must be erased when imports config
	config.importFromText(exportedText);
	ASSERT_EQUALS(2, config.getFavouriteTitles().size());
}

#endif //RUN_UNIT_TESTS

