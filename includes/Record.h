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
	Record(const std::string& title) throw(std::invalid_argument);
	virtual ~Record();
	bool setTitle(const std::string& title);
	std::string getTitle() const;
	bool setFieldValue(const std::string& name, const std::string& value);
protected:
	void initFields(const std::vector<std::string>& names);
#ifdef RUN_UNIT_TESTS
	virtual bool isValidFieldValue(const std::string& name, const std::string& value) {};
#else
	virtual bool isValidFieldValue(const std::string& name, const std::string& value) = 0;
#endif
private:
	static const std::string defaultFieldValue;
	std::string title;
	std::map<std::string,std::string> fields;
	bool isValidTitle(const std::string& title) const;
	bool isValidFieldName(const std::string& name) const;
};

#endif /* INCLUDES_RECORD_H_ */
