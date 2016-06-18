/*
 * Api.h
 *
 *  Created on: Jun 14, 2016
 *      Author: misha123
 */

#ifndef RECORDSAPI_H_
#define RECORDSAPI_H_

#include <string>
#include <list>

namespace LibPm {

enum class Recordtype {SITE, BANKCARD, APPLICATION, UNKNOWN};

bool addSiteRecord(const std::string& title,
		const std::string& link,
		const std::string& login,
		const std::string& password,
		const std::string& comment);

bool addBankcardRecord(const std::string& title,
		const std::string& number,
		const std::string& cardholder,
		const std::string& validThruMonth,
		const std::string& validThruYear,
		const std::string& cvv2cvc2,
		const std::string& comment);

bool addApplicationRecord(const std::string& title,
		const std::string& login,
		const std::string& password,
		const std::string& comment);

bool removeRecord(const std::string& title);

bool replaceWithSiteRecord(const std::string& oldTitle,
		const std::string& title,
		const std::string& link,
		const std::string& login,
		const std::string& password,
		const std::string& comment);

bool replaceWithBankcardRecord(const std::string& oldTitle,
		const std::string& title,
		const std::string& number,
		const std::string& cardholder,
		const std::string& validThruMonth,
		const std::string& validThruYear,
		const std::string& cvv2cvc2,
		const std::string& comment);

bool replaceWithApplicationRecord(const std::string& oldTitle,
		const std::string& title,
		const std::string& login,
		const std::string& password,
		const std::string& comment);

bool getSiteRecord(const std::string& title,
		std::string& link,
		std::string& login,
		std::string& password,
		std::string& comment);

bool getBankcardRecord(const std::string& title,
		std::string& number,
		std::string& cardholder,
		std::string& validThruMonth,
		std::string& validThruYear,
		std::string& cvv2cvc2,
		std::string& comment);

bool getApplicationRecord(const std::string& title,
		std::string& login,
		std::string& password,
		std::string& comment);

bool getRecordType(const std::string& title, Recordtype& type);

void getRecordsTitles(std::list<std::string>& titles, const Recordtype type = Recordtype::UNKNOWN);

bool readRecords(const std::string& dir, const std::string& key = "");

bool writeRecords(const std::string& dir, const std::string& key = "");
}

#endif /* RECORDSAPI_H_ */
