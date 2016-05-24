/*
 * SiteRecord.cpp
 *
 *  Created on: May 24, 2016
 *      Author: mt
 */

#include <vector>
#include <Record/SiteRecord.h>

using std::string;
using std::vector;

const string SiteRecord::link = "link";
const string SiteRecord::login = "login";
const string SiteRecord::password = "password";
const string SiteRecord::comment = "comment";

SiteRecord::SiteRecord(const string& title) : Record(title)
{
	initFields( vector<string>{link,login,password,comment} );
}

SiteRecord::~SiteRecord()
{

}

bool SiteRecord::isValidFieldValue(const string& name, const string& value)
{
	return true;
}

