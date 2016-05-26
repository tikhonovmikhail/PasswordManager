/*
 * ApplicationRecord.h
 *
 *  Created on: May 26, 2016
 *      Author: mt
 */

#ifndef INCLUDES_RECORD_APPLICATIONRECORD_H_
#define INCLUDES_RECORD_APPLICATIONRECORD_H_

#include <string>
#include <Record/Record.h>

class ApplicationRecord: public Record {
public:
public:
	static const std::string login;
	static const std::string password;
	ApplicationRecord(const std::string& title);
};

#endif /* INCLUDES_RECORD_APPLICATIONRECORD_H_ */
