/*
 * BankCardRecord.cpp
 *
 *  Created on: May 24, 2016
 *      Author: mt
 */

#include <vector>
#include <BankCardRecord.h>

using std::string;
using std::vector;

const string BankCardRecord::number = "number";
const string BankCardRecord::cardholder = "cardholder";
const string BankCardRecord::validThruMonth = "valid thru month";
const string BankCardRecord::validThruYear = "valid thru year";
const string BankCardRecord::cvv2cvc2 = "cvv2/cvc2";
const string BankCardRecord::comment = "comment";

BankCardRecord::BankCardRecord(const string& title) : Record(title)
{
	/*fields.insert( std::make_pair(number, defaultFieldValue) );
	fields.insert( std::make_pair(cardholder, defaultFieldValue) );
	fields.insert( std::make_pair(validThruMonth, defaultFieldValue) );
	fields.insert( std::make_pair(validThruYear, defaultFieldValue) );
	fields.insert( std::make_pair(cvv2cvc2, defaultFieldValue) );
	fields.insert( std::make_pair(comment, defaultFieldValue) );*/

	initFields( vector<string>{number,cardholder,validThruMonth,validThruYear,cvv2cvc2,comment} );
}

BankCardRecord::~BankCardRecord()
{

}

