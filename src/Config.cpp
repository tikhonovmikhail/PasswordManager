/*
 * Config.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: mt
 */

#include <algorithm>
#include <sstream>
#include <Config.h>

using std::string;
using std::stringstream;
using std::unordered_set;

const string Config::defaultConfFilename = "pmconf";
const string Config::defaultAppDataDir = "./";

Config::Config()
{
	confFilename = defaultConfFilename;
	appDataDir = defaultAppDataDir;
}

string Config::getConfFilename()
{
	return confFilename;
}

string Config::getAppDataDir()
{
	return appDataDir;
}

bool Config::setConfFilename(const string& filename)
{
	if ( !filename.empty() )
	{
		confFilename = filename;
	}
	return !filename.empty();
}

bool Config::setAppDataDir(const string& path)
{
	if ( !path.empty() )
	{
		appDataDir = path;
	}
	return !path.empty();
}

bool Config::addFavouriteTitle(const string& title)
{
	if ( title.empty() )
	{
		return false;
	}

	auto isAdded = favouriteTitles.insert(title).second;
	return isAdded;
}

bool Config::removeFavouriteTitle(const string& title)
{
	return favouriteTitles.erase(title) == 1;
}

const unordered_set<string>& Config::getFavouriteTitles()
{
	return favouriteTitles;
}

string Config::exportToText()
{
	string text;

	text += confFilename + "\n";
	text += appDataDir + "\n";
	std::for_each(favouriteTitles.begin(), favouriteTitles.end(),[&text](const string& title)
			{
				text += title + "\n";
			} );

	text.pop_back();
	return text;
}

bool Config::importFromText(const string& text)
{
	auto backup = exportToText();
	stringstream ss(text);

	string confFile;
	std::getline(ss, confFile);
	string dataDir;
	std::getline(ss, dataDir);
	if ( !setConfFilename(confFile) || !setAppDataDir(dataDir) )
	{
		importFromText(backup);
		return false;
	}

	favouriteTitles.clear();
	string title;
	while (std::getline(ss, title) && addFavouriteTitle(title));
	return true;
}


