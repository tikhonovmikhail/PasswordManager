/*
 * TestRecords.cpp
 *
 *  Created on: Jun 11, 2016
 *      Author: misha123
 */

#include <string>
#include <memory>
#include <Record/Records.h>
#include <UnitTest.h>

using std::string;
using std::list;

#ifdef RUN_UNIT_TESTS

DECLARE(Records)
string title1;
string title2;
string title3;
Record* record1;
Record* record2;
Record* record3;
list<const Record*> expectedRecordsList;
END_DECLARE

SETUP(Records)
{
	title1 = "my title 1";
	title2 = "my title 2";
	title3 = "my title 3";
	record1 = new Record(title1, Record::SITE);
	record2 = new Record(title2, Record::SITE);
	record3 = new Record(title3, Record::SITE);
	expectedRecordsList.push_back(record1);
	expectedRecordsList.push_back(record2);
	expectedRecordsList.sort([](const Record* r1, const Record* r2)
			{
				return r1->getTitle() > r2->getTitle();
			});
}

TEARDOWN(Records)
{
	delete record1;
	delete record2;
	delete record3;
}

TESTF(Records, ShouldAddRecordIfTitleIsUnique)
{
	// Add some records
	Records records;
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
	Records records;
	ASSERT_TRUE(!records.add(NULL));
	ASSERT_EQUALS(list<const Record*>(), records.getAll());
}

TESTF(Records, ShouldReturnRecordIfWasFoundByTitle)
{
	Records records;
	records.add(record1);
	records.add(record2);

	ASSERT_EQUALS(record1, records.find(title1));
	ASSERT_EQUALS(record2, records.find(title2));
}

TESTF(Records, ShouldReturnNullIfRecordWasNotFoundByTitle)
{
	Records records;
	records.add(record1);
	records.add(record2);

	ASSERT_EQUALS(nullptr, records.find(title3));
}

TESTF(Records, ShouldRemoveRecordIfWasFoundByTitle)
{
	// Add some records
	Records records;
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
	// Add some records
	Records records;
	records.add(record1);
	records.add(record2);

	// Try remove unexisting record
	ASSERT_TRUE( !records.remove(title3) );

	// Check nothing changed
	ASSERT_EQUALS(expectedRecordsList, records.getAll());
}

TESTF(Records, ShouldNotReplaceUnexistingRecord)
{
	// Add some records
	Records records;
	records.add(record1);
	records.add(record2);

	// Try to replace record by unexisting title
	ASSERT_TRUE( !records.replace(title3, record3) );

	// Check nothing changed
	ASSERT_EQUALS(expectedRecordsList, records.getAll());
}

TESTF(Records, ShouldNotReplaceWithNullRecord)
{
	// Add some records
	Records records;
	records.add(record1);
	records.add(record2);

	// Try to replace record by unexisting title
	ASSERT_TRUE( !records.replace(title1, nullptr) );

	// Check nothing changed
	ASSERT_EQUALS(expectedRecordsList, records.getAll());
}

TESTF(Records, ShouldNotReplaceWithRecordWithDuplicateTitle)
{
	// Add some records
	Records records;
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
	// Add some records
	Records records;
	records.add(record1);
	records.add(record2);

	// Try to replace with unchanged title
	std::unique_ptr<Record> r (new Record(title1, Record::SITE));
	ASSERT_TRUE( records.replace(title1, r.get()) );

	//Check that record1 was replaced with r
	list<const Record*> expected;
	expected.push_back(record2);
	expected.push_back(r.get());

	ASSERT_EQUALS(expected, records.getAll());
}

TESTF(Records, ShouldReplaceWithRecordWithNewTitle)
{
	// Add some records
	Records records;
	records.add(record1);
	records.add(record2);

	// Try to replace with new title
	std::unique_ptr<Record> r (new Record(title3, Record::SITE));
	ASSERT_TRUE( records.replace(title1, r.get()) );

	//Check that record1 was replaced with r
	list<const Record*> expected;
	expected.push_back(record2);
	expected.push_back(r.get());
	expected.sort([](const Record* r1, const Record* r2)
			{
				return r1->getTitle() > r2->getTitle();
			});

	ASSERT_EQUALS(expected, records.getAll());
}

TESTF(Records, ShouldGetAllRecordsByType)
{
	// Add some records of the same type
	Records records;
	records.add(record1);
	records.add(record2);

	// Add record of another type
	Record r(title3, Record::BANKCARD);
	records.add(&r);

	// Check if returned only records of given type
	ASSERT_EQUALS(expectedRecordsList, records.getByType(Record::SITE));
}

TESTF(Records, ShouldSortRecords)
{
	// Add some records of the same type
	Records records;
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
