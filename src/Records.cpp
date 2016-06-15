/*
 * Records.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: misha123
 */

#include <algorithm>
#include "Records.h"

using std::string;
using std::list;

bool Records::add(const Record* record)
{
	if (!record || find(record->getTitle()))
	{
		return false;
	}
	else
	{
		records.push_back(record);
		records.sort([](const Record* r1, const Record* r2)
				{
					return r1->getTitle() > r2->getTitle();
				});
		return true;
	}
}

const Record* Records::find(const string& title) const
{
	auto it = std::find_if(records.begin(), records.end(),
			[title](const Record* r)
			{
				return r->getTitle() == title;
			});

	if (it == records.end())
	{
		return nullptr;
	}
	else
	{
		return *it;
	}
}


bool Records::remove(const string& title)
{
	auto r = find(title);
	if (r)
	{
		records.remove(r);
		return true;
	}
	else
	{
		return false;
	}
}

bool Records::replace(const string& title, const Record* record)
{
	if ( !find(title) || !record )
	{
		return false;
	}
	else
	{
		auto titleIsChanged = (title != record->getTitle());
		auto titleIsUnique = (find(record->getTitle()) == nullptr);
		if (!titleIsChanged || titleIsUnique)
		{
			this->remove(title);
			add(record);
			return true;
		}
		else
		{
			return false;
		}
	}
}

const list<const Record*>& Records::getAll() const
{
	return records;
}

list<const Record*> Records::getByType(const Record::Type type) const
{
	list<const Record*> recordsByType;

	std::for_each(records.begin(), records.end(), [type, &recordsByType](const Record* record)
			{
				if (record->getType() == type)
				{
					recordsByType.push_back(record);
				}
			});

	return recordsByType;
}
