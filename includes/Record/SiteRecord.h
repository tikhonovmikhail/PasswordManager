/*
 * SiteRecord.h
 *
 *  Created on: May 24, 2016
 *      Author: mt
 */

#ifndef INCLUDES_SITERECORD_H_
#define INCLUDES_SITERECORD_H_

#include <string>
#include <Record/Record.h>

class SiteRecord: public Record {
public:
	static const std::string link;
	static const std::string login;
	static const std::string password;
	static const std::string comment;
	SiteRecord(const std::string& title);
	~SiteRecord();
	bool isValidFieldValue(const std::string& name, const std::string& value);
};

#endif /* INCLUDES_SITERECORD_H_ */
