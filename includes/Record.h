/*
 * Record.h
 *
 *  Created on: May 23, 2016
 *      Author: mt
 */

#ifndef INCLUDES_RECORD_H_
#define INCLUDES_RECORD_H_

#include <string>
#include <stdexcept>

class Record {
public:
	enum types {site, bankCard, nTypes};
	Record(const std::string& title, const types rtype) throw(std::invalid_argument);
	virtual ~Record();
	bool setTitle(const std::string& title);
	std::string getTitle() const;
	types getType() const;
private:
	std::string title;
	types rtype;
	bool setType(const types rtype);
	bool isValidTitle(const std::string& title) const;
	bool isValidType(const types rtype) const;
};

#endif /* INCLUDES_RECORD_H_ */
