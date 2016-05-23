/*
 * FieldOfRecord.h
 *
 *  Created on: May 23, 2016
 *      Author: mt
 */

#ifndef INCLUDES_FIELDOFRECORD_H_
#define INCLUDES_FIELDOFRECORD_H_

#include <string>
#include <stdexcept>

class FieldOfRecord {
public:
	FieldOfRecord(const std::string& name, const std::string& value) throw(std::invalid_argument);
	std::string getName() const;
	std::string getValue() const;
	bool setName(const std::string& name);
	void setValue(const std::string& value);
private:
	std::string name;
	std::string value;
	bool isValidName(const std::string& name) const;
};

#endif /* INCLUDES_FIELDOFRECORD_H_ */
