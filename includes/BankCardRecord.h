/*
 * BankCardRecord.h
 *
 *  Created on: May 24, 2016
 *      Author: mt
 */

#ifndef INCLUDES_BANKCARDRECORD_H_
#define INCLUDES_BANKCARDRECORD_H_

#include <string>
#include <Record.h>

class BankCardRecord: public Record {
public:
	static const std::string number;
	static const std::string cardholder;
	static const std::string validThruMonth;
	static const std::string validThruYear;
	static const std::string cvv2cvc2;
	static const std::string comment;

	BankCardRecord(const std::string& title);
	~BankCardRecord();
};

#endif /* INCLUDES_BANKCARDRECORD_H_ */
