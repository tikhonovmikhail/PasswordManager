/*
 * TestRecords.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: misha123
 */

#include <string>
#include <memory>
#include <algorithm>
#include <UnitTest.h>
#include <Core/Records.h>

using std::string;
using std::list;

#ifdef RUN_UNIT_TESTS

bool recordsSortCondition(const Record* r1, const Record* r2)
{
	return r1->getTitle() > r2->getTitle();
}

DECLARE(Records)
#define CREATE_RECORDS \
	Records records; \
	\
	auto title1 = "my title 1"; \
	auto title2 = "my title 2"; \
	auto title3 = "my title 3"; \
	\
	auto record1 = new Record(title1, Record::SITE); \
	auto record2 = new Record(title2, Record::SITE); \
	auto record3 = new Record(title3, Record::SITE); \
	list<const Record*> expectedRecordsList; \
    expectedRecordsList.push_back(record1); \
	expectedRecordsList.push_back(record2); \
	expectedRecordsList.sort(recordsSortCondition);

/* Yes, I understand memory leak of record1, record2, record3.
 * The problem is that ~Records() deletes some of them,
 * and for each test I have to trace which of records will be
 * deleted in ~Records(), and which of records I must delete manually.
 * Its too exhausting. Its just a unit test code!
*/
END_DECLARE

SETUP(Records) { }

TEARDOWN(Records) {}

TESTF(Records, ShouldAddRecordIfTitleIsUnique)
{
	CREATE_RECORDS
	// Add some records
	ASSERT_TRUE(records.add(record1));
	ASSERT_TRUE(records.add(record2));

	// Check they were added
	ASSERT_EQUALS(expectedRecordsList, records.getAll());

	// Try to add duplicate record
	std::unique_ptr<Record> duplicate (new Record(title1, Record::SITE));
	ASSERT_TRUE(!records.add(duplicate.get()));
	// and check duplicate record was not added
	ASSERT_EQUALS(expectedRecordsList, records.getAll());
}

TESTF(Records, ShouldNotAddNullRecord)
{
	CREATE_RECORDS
	ASSERT_TRUE(!records.add(NULL));
	ASSERT_EQUALS(list<const Record*>(), records.getAll());
}

TESTF(Records, ShouldReturnRecordIfWasFoundByTitle)
{
	CREATE_RECORDS
	records.add(record1);
	records.add(record2);

	ASSERT_EQUALS(record1, records.find(title1));
	ASSERT_EQUALS(record2, records.find(title2));
}

TESTF(Records, ShouldReturnNullIfRecordWasNotFoundByTitle)
{
	CREATE_RECORDS
	records.add(record1);
	records.add(record2);

	ASSERT_EQUALS(nullptr, records.find(title3));
}

TESTF(Records, ShouldRemoveRecordIfWasFoundByTitle)
{
	CREATE_RECORDS
	// Add some records
	records.add(record1);
	records.add(record2);
	records.add(record3);

	// Remove one record
	ASSERT_TRUE(records.remove(title3));

	// Check it was removed
	ASSERT_EQUALS(expectedRecordsList, records.getAll());
}

TESTF(Records, ShouldNotRemoveRecordIfWasNotFoundByTitle)
{
	CREATE_RECORDS
	// Add some records
	records.add(record1);
	records.add(record2);

	// Try remove unexisting record
	ASSERT_TRUE( !records.remove(title3) );

	// Check nothing changed
	ASSERT_EQUALS(expectedRecordsList, records.getAll());
}

TESTF(Records, ShouldNotReplaceUnexistingRecord)
{
	CREATE_RECORDS
	// Add some records
	records.add(record1);
	records.add(record2);

	// Try to replace record by unexisting title
	ASSERT_TRUE( !records.replace(title3, record3) );

	// Check nothing changed
	ASSERT_EQUALS(expectedRecordsList, records.getAll());
}

TESTF(Records, ShouldNotReplaceWithNullRecord)
{
	CREATE_RECORDS
	// Add some records
	records.add(record1);
	records.add(record2);

	// Try to replace record by unexisting title
	ASSERT_TRUE( !records.replace(title1, nullptr) );

	// Check nothing changed
	ASSERT_EQUALS(expectedRecordsList, records.getAll());
}

TESTF(Records, ShouldNotReplaceWithRecordWithDuplicateTitle)
{
	CREATE_RECORDS
	// Add some records
	records.add(record1);
	records.add(record2);

	// Try to replace with duplicate title
	std::unique_ptr<Record> duplicate (new Record(title2, Record::SITE));
	ASSERT_TRUE( !records.replace(title1, duplicate.get()) );

	// Check nothing changed
	ASSERT_EQUALS(expectedRecordsList, records.getAll());
}

TESTF(Records, ShouldReplaceWithRecordWithUnchangedTitle)
{
	CREATE_RECORDS
	// Add some records
	records.add(record1);
	records.add(record2);

	// Try to replace with unchanged title
	auto unchanged = new Record(title1, Record::SITE);
	ASSERT_TRUE( records.replace(title1, unchanged) );

	//Check that record1 was replaced with r
	list<const Record*> expected;
	expected.push_back(record2);
	expected.push_back(unchanged);
	expected.sort(recordsSortCondition);

	ASSERT_EQUALS(expected, records.getAll());
}

TESTF(Records, ShouldReplaceWithRecordWithNewTitle)
{
	CREATE_RECORDS
	// Add some records
	records.add(record1);
	records.add(record2);

	// Try to replace with new title
	auto newtitled = new Record(title3, Record::SITE);
	ASSERT_TRUE( records.replace(title1, newtitled) );

	//Check that record1 was replaced with r
	list<const Record*> expected;
	expected.push_back(record2);
	expected.push_back(newtitled);
	expected.sort(recordsSortCondition);

	ASSERT_EQUALS(expected, records.getAll());
}

TESTF(Records, ShouldGetAllRecordsByType)
{
	CREATE_RECORDS
	// Add some records of the same type
	records.add(record1);
	records.add(record2);

	// Add record of another type
	auto r = new Record(title3, Record::BANKCARD);
	records.add(r);

	// Check if returned only records of given type
	ASSERT_EQUALS(expectedRecordsList, records.getByType(Record::SITE));
}

TESTF(Records, ShouldSortRecords)
{
	CREATE_RECORDS
	// Add some records of the same type
	records.add(record1);
	records.add(record3);
	records.add(record2);

	// Put records in right order
	list<const Record*> expected;
	expected.push_back(record3);
	expected.push_back(record2);
	expected.push_back(record1);

	// Check are sorted
	ASSERT_EQUALS(expected, records.getAll());
}

#endif // RUN_UNIT_TESTS
