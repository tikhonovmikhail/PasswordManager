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
	typedef int type;
	static const type site;
	static const type bankCard;

	Record(const std::string& title, const type rtype) throw(std::invalid_argument);
	virtual ~Record();
	bool setTitle(const std::string& title);
	std::string getTitle() const;
	type getType() const;
private:
	std::string title;
	type rtype;
	bool setType(const type rtype);
	bool isValidTitle(const std::string& title) const;
	bool isValidType(const type rtype) const;
};

#endif /* INCLUDES_RECORD_H_ */
