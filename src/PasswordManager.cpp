#include "easyunit/testharness.h"
#include "UnitTestProperties.h"

int main()
{
#ifdef RUN_TESTS
	TestRegistry::runAndPrint();
	return 0;
#else
	return 0;
#endif // RUN_TESTS
}
