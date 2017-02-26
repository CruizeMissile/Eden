
#ifndef CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_RUNNER
#endif

#define CATCH_CONFIG_COLOUR_WINDOWS 

#include "UnitTest.h"

int main(int argc, char* const argv[])
{
	int result = Catch::Session().run(argc, argv);

	// global clean-up...
	//if (result != 0)
	system("pause");
	return result;
}