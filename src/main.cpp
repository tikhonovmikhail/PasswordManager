#include "UnitTest.h"

#ifdef RUN_UNIT_TESTS

#include "easyunit/testharness.h"
int main(void)
{
	TestRegistry::runAndPrint();
	return 0;
}
#endif
