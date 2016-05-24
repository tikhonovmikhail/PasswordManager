/*
 * Record.h
 *
 *  Created on: May 23, 2016
 *      Author: mt
 */

#ifndef INCLUDES_RECORD_H_
#define INCLUDES_RECORD_H_

#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <UnitTest.h>

class Record {
public:
#ifndef RUN_UNIT_TESTS
	// This class is asbtract, but unit tests need to instantiate it
	virtual void abstractClass() = 0;
#endif
	Record(const std::string& title) throw(std::invalid_argument);
	virtual ~Record();
	bool setTitle(const std::string& title);
	std::string getTitle() const;
protected:
	void initFields(const std::vector<std::string>& names);
private:
	static const std::string defaultFieldValue;
	std::string title;
	std::map<std::string,std::string> fields;
	bool isValidTitle(const std::string& title) const;
};

#endif /* INCLUDES_RECORD_H_ */
