/*
 * Config.h
 *
 *  Created on: Jun 17, 2016
 *      Author: mt
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>
#include <unordered_set>

class Config {
public:
	static const std::string defaultAppDataDir;
	static const std::string defaultConfFilename;

	Config();
	bool importFromText(const std::string& text);
	std::string exportToText();
	bool setConfFilename(const std::string& filename);
	std::string getConfFilename();
	bool setAppDataDir(const std::string& path);
	std::string getAppDataDir();
	const std::unordered_set<std::string>& getFavouriteTitles();
	bool addFavouriteTitle(const std::string& title);
	bool removeFavouriteTitle(const std::string& title);
private:
	std::string appDataDir;
	std::string confFilename;
	std::unordered_set<std::string> favouriteTitles;
};

#endif /* CONFIG_H_ */
