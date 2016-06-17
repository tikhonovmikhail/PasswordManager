/*
 * ConfigApi.h
 *
 *  Created on: Jun 18, 2016
 *      Author: misha123
 */

#ifndef CONFIGAPI_H_
#define CONFIGAPI_H_

#include <string>
#include <unordered_set>

namespace LibPm {

bool writeConfig();
bool readConfig();
bool setAppDataDir(const std::string& path);
const std::string& getAppDataDir();
const std::unordered_set<std::string>& getFavouriteTitles();
bool addFavouriteTitle(const std::string& title);
bool removeFavouriteTitle(const std::string& title);

}

#endif /* CONFIGAPI_H_ */
