/*
 * ApplicationRecord.cpp
 *
 *  Created on: May 26, 2016
 *      Author: mt
 */

#include <vector>
#include <Record/ApplicationRecord.h>

using std::string;
using std::vector;

const string ApplicationRecord::login = "login";
const string ApplicationRecord::password = "password";

ApplicationRecord::ApplicationRecord(const string& title) : Record(title)
{
	initFields( vector<string>{login,password} );
}

