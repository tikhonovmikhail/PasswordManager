#include "UnitTest.h"
#include "easyunit/testharness.h"

int main(void)
{
#ifdef RUN_UNIT_TESTS
	TestRegistry::runAndPrint();
#else

#endif
	return 0;
}
