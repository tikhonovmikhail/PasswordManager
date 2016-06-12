/*
 * Records.h
 *
 *  Created on: Jun 11, 2016
 *      Author: misha123
 */

#ifndef RECORDS_H_
#define RECORDS_H_

#include <list>
#include <string>
#include "Record.h"
#include "UnitTest.h"

class Records {
public:
	bool add(const Record* record);
	const Record* find(const std::string& title) const;
	bool remove(const std::string& title);
	bool replace(const std::string& title, const Record* record);
	const std::list<const Record*>& getAll() const;
	std::list<const Record*> getByType(const Record::rtype type) const;
private:
	std::list<const Record*> records;
};

#endif /* RECORDS_H_ */
