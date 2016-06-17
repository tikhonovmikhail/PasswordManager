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
	static const std::string filename;

	Config();
	bool importFromText(const std::string& text);
	std::string exportToText() const;
	bool setAppDataDir(const std::string& path);
	std::string getAppDataDir() const;
	const std::unordered_set<std::string>& getFavouriteTitles() const;
	bool addFavouriteTitle(const std::string& title);
	bool removeFavouriteTitle(const std::string& title);
private:
	std::string appDataDir;
	std::unordered_set<std::string> favouriteTitles;
};

#endif /* CONFIG_H_ */
