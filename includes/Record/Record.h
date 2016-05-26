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
#include <set>
#include <vector>
#include <stdexcept>
#include <UnitTest.h>

class Record {
public:
	enum rtype {SITE, BANKCARD, APPLICATION, END};

	static const std::string site_link;
	static const std::string site_login;
	static const std::string site_password;
	static const std::string site_comment;
	static const std::string bankcard_number;
	static const std::string bankcard_cardholder;
	static const std::string bankcard_validThruMonth;
	static const std::string bankcard_validThruYear;
	static const std::string bankcard_cvv2cvc2;
	static const std::string bankcard_comment;
	static const std::string application_login;
	static const std::string application_password;
	static const std::string application_comment;

	static const std::string emptyFieldValue;
	Record(const std::string& title, const rtype type) throw(std::invalid_argument);
	bool setTitle(const std::string& title);
	std::string getTitle() const;
	rtype getType() const;
	bool setFieldValue(const std::string& name, const std::string& value);
	bool getFieldValue(const std::string& name, std::string& value) const;

#ifdef RUN_UNIT_TESTS
	std::set<std::string> getFieldNames();
#endif

protected:
	void initFields(const std::vector<std::string>& names);
private:
	std::string title;
	rtype type;
	std::map<std::string,std::string> fields;
	bool isValidTitle(const std::string& title) const;
	bool setType(const rtype type);
	bool isValidFieldName(const std::string& name) const;
	bool isValidType(const rtype type) const;
};

#endif /* INCLUDES_RECORD_H_ */
