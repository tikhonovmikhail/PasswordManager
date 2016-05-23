/*
 * FieldOfRecord.cpp
 *
 *  Created on: May 23, 2016
 *      Author: mt
 */

#include <typeinfo>
#include <vector>
#include "FieldOfRecord.h"
#include "UnitTest.h"

using std::string;
using std::vector;
using std::invalid_argument;

FieldOfRecord::FieldOfRecord(const std::string& name, const std::string& value) throw(invalid_argument)
{
	if (isValidName(name))
	{
		setName(name);
		setValue(value);
	}
	else
	{
		throw invalid_argument(typeid(*this).name() + string(": construct with invalid name = '" + name + "'"));
	}
}

string FieldOfRecord::getName() const
{
	return name;
}

string FieldOfRecord::getValue() const
{
	return value;
}

bool FieldOfRecord::setName(const std::string& name)
{
	bool isValid = isValidName(name);
	if (isValid)
	{
		this->name = name;
	}

	return isValid;
}

void FieldOfRecord::setValue(const std::string& value)
{
	this->value = value;
}

bool FieldOfRecord::isValidName(const string& name) const
{
	return !name.empty();
}

#ifdef RUN_UNIT_TESTS

DECLARE(FieldOfRecord)
string goodName;
string goodValue;
string goodName2;
string goodValue2;
vector<string> badNames;
END_DECLARE

SETUP(FieldOfRecord)
{
	goodName = "my name";
	goodValue = "my value";
	goodName2 = "foo";
	goodValue2 = "bar";
	badNames = {""}; // Add examples of bad names here
}

TEARDOWN(FieldOfRecord) {}

TESTF(FieldOfRecord, ShouldCreateObjectWithValidParams)
{
	try
	{
		FieldOfRecord(goodName, goodValue);
	}
	catch(invalid_argument& exc)
	{
		ASSERT_TRUE(false);
		return;
	}
	ASSERT_TRUE(true);
}

TESTF(FieldOfRecord, ShouldNotCreateObjectWithInvalidParams)
{
	for (const auto &badName: badNames)
	{
		try
		{
			FieldOfRecord(badName, goodValue);
		}
		catch(invalid_argument& exc)
		{
			ASSERT_TRUE(true);
			continue;
		}
		ASSERT_TRUE(false);
	}
}

TESTF(FieldOfRecord, ShouldSetValidName)
{
	FieldOfRecord f(goodName, goodValue);
	ASSERT_TRUE(f.setName(goodName2));
	ASSERT_EQUALS(goodName2, f.getName());
}

TESTF(FieldOfRecord, ShouldNotSetInvalidName)
{
	FieldOfRecord f(goodName, goodValue);
	ASSERT_TRUE( !f.setName(badNames.at(0)) );
	ASSERT_EQUALS(goodName, f.getName());
}

TESTF(FieldOfRecord, ShouldSetAndReturnContent)
{
	FieldOfRecord f(goodName, goodValue);
	ASSERT_EQUALS(goodName, f.getName());
	ASSERT_EQUALS(goodValue, f.getValue());
	f.setName(goodName2);
	f.setValue(goodValue2);
	ASSERT_EQUALS(goodName2, f.getName());
	ASSERT_EQUALS(goodValue2, f.getValue());
}

#endif // RUN_UNIT_TESTS
