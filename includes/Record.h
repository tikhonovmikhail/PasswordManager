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
	Record(const std::string& title) throw(std::invalid_argument);
	virtual ~Record();
	bool setTitle(const std::string& title);
	std::string getTitle() const;
private:
	std::string title;
	bool isValidTitle(const std::string& title);
};

#endif /* INCLUDES_RECORD_H_ */
