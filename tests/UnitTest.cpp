
#ifndef CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_RUNNER
#endif

#include "Core/Platform.h"

#if defined(EDN_WINDOWS)
#define CATCH_CONFIG_COLOUR_WINDOWS
#endif

#include "UnitTest.h"

int main(int argc, char* const argv[])
{
	int result = Catch::Session().run(argc, argv);

#if defined(EDN_WINDOWS)
	system("pause");
#endif
	return result;
}
