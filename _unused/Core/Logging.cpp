#include "Precompiled.h"

#define LOGURU_USE_FMTLIB      0
#define LOGURU_WITH_FILEABS    0
#define LOGURU_REDEFINE_ASSERT 1
#define LOGURU_IMPLEMENTATION  1
#include "loguru/loguru.hpp"
#include "Logging.h"

namespace edn
{
    namespace Logging
    {
        void init(int argc, char** argv)
        {
            loguru::init(argc, argv);
        }
    }
}
