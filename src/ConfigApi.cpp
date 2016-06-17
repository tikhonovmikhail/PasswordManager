/*
 * ConfigApi.cpp
 *
 *  Created on: Jun 18, 2016
 *      Author: misha123
 */

#include <fstream>
#include <ConfigApi.h>
#include <Config.h>

using std::string;
using std::stringstream;
using std::unordered_set;
using std::ifstream;
using std::ofstream;

namespace LibPm {

Config config;

bool writeConfig()
{
	ofstream ofs(Config::filename);
	if (!ofs.is_open())
	{
		return false;
	}

	ofs << config.exportToText();
	ofs.close();
	return true;
}

bool readConfig()
{
	ifstream ifs(Config::filename);
	if ( !ifs.is_open() )
	{
		return false;
	}

	string content;
	ifs >> content;
	ifs.close();
	return config.importFromText(content);
}

bool setAppDataDir(const string& path)
{
	return config.setAppDataDir(path);
}

string getAppDataDir()
{
	return config.getAppDataDir();
}

const unordered_set<string>& getFavouriteTitles()
{
	return config.getFavouriteTitles();
}

bool addFavouriteTitle(const string& title)
{
	return config.addFavouriteTitle(title);
}

bool removeFavouriteTitle(const string& title)
{
	return config.removeFavouriteTitle(title);
}

}


