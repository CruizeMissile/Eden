#pragma once

#include "loguru/loguru.hpp"

// ------------------------------------------------------------------------------------------------
// Undefining loguru's macros

#undef LOG_F
#undef LOG_IF_F
#undef LOG_SCOPE_F
#undef RAW_LOG_F
#undef LOG_SCOPE_FUNCTION
#undef ABORT_F

#undef CHECK_F
#undef CHECK_NOTNULL_F
#undef CHECK_EQ_F
#undef CHECK_NE_F
#undef CHECK_LT_F
#undef CHECK_GT_F
#undef CHECK_LE_F
#undef CHECK_GE_F

#undef DLOG_F
#undef DVLOG_F
#undef DLOG_IF_F
#undef DVLOG_IF_F
#undef DRAW_LOG_F
#undef DRAW_VLOG_F
#undef DCHECK_F
#undef DCHECK_NOTNULL_F
#undef DCHECK_EQ_F
#undef DCHECK_NE_F
#undef DCHECK_LT_F
#undef DCHECK_LE_F
#undef DCHECK_GT_F
#undef DCHECK_GE_F

// ------------------------------------------------------------------------------------------------
// Log macro definitions

#define LOG(verbosity_name, ...) VLOG_F(loguru::Verbosity_ ## verbosity_name, __VA_ARGS__)
#define LOG_IF(verbosity_name, cond, ...) VLOG_IF_F(loguru::Verbosity_ ## verbosity_name, cond, __VA_ARGS__)
#define LOG_SCOPE(verbosity_name, ...) VLOG_SCOPE_F(loguru::Verbosity_ ## verbosity_name, __VA_ARGS__)
#define LOG_SCOPE_FUNCTION(verbosity_name) VLOG_SCOPE_F(verbosity_name, __PRETTY_FUNCTION__)

// Raw logging - no preamble, no indentation. Slightly faster than full logging.
#define RLOG(verbosity_name, ...) RAW_VLOG_F(loguru::Verbosity_ ## verbosity_name, __VA_ARGS__)

// Usage: ABORT("Caused by %s", error_str), Message is optional.
#define ABORT(...) loguru::log_and_abort(0, "ABORT: ", __FILE__, __LINE__, __VA_ARGS__)

// Checked at runtime too. Will print error, call the faital_handler(if any), then 'abort'
// Note that the test must be boolean.
// CHECK_F(ptr); will not compile, but CHECK_F(ptr != nullptr); will.
#define CHECK(test, ...) CHECK_WITH_INFO_F(test, #test, ##__VA_ARGS__)
#define CHECK_NOTNULL(x, ...) CHECK_WITH_INFO_F((x) != nullptr, #x " != nullptr", ##__VA_ARGS__)

#define CHECK_EQ(a, b, ...) CHECK_OP_F(a, b, ==, ##__VA_ARGS__)
#define CHECK_NE(a, b, ...) CHECK_OP_F(a, b, !=, ##__VA_ARGS__)
#define CHECK_LT(a, b, ...) CHECK_OP_F(a, b, < , ##__VA_ARGS__)
#define CHECK_GT(a, b, ...) CHECK_OP_F(a, b, > , ##__VA_ARGS__)
#define CHECK_LE(a, b, ...) CHECK_OP_F(a, b, <=, ##__VA_ARGS__)
#define CHECK_GE(a, b, ...) CHECK_OP_F(a, b, >=, ##__VA_ARGS__)

#if defined(EDN_DEBUG)
#define DLOG(verbosity_name, ...)     LOG(verbosity_name, __VA_ARGS__)
#define DLOG_IF(verbosity_name, ...)  LOG_IF(verbosity_name, __VA_ARGS__)
#define DRLOG(verbosity_name, ...)    RLOG(verbosity_name, __VA_ARGS__)
#define DCHECK(test, ...)             CHECK(test, ##__VA_ARGS__)
#define DCHECK_NOTNULL(x, ...)        CHECK_NOTNULL(x, ##__VA_ARGS__)
#define DCHECK_EQ(a, b, ...)          CHECK_EQ(a, b, ##__VA_ARGS__)
#define DCHECK_NE(a, b, ...)          CHECK_NE(a, b, ##__VA_ARGS__)
#define DCHECK_LT(a, b, ...)          CHECK_LT(a, b, ##__VA_ARGS__)
#define DCHECK_LE(a, b, ...)          CHECK_LE(a, b, ##__VA_ARGS__)
#define DCHECK_GT(a, b, ...)          CHECK_GT(a, b, ##__VA_ARGS__)
#define DCHECK_GE(a, b, ...)          CHECK_GE(a, b, ##__VA_ARGS__)
#else
#define DLOG(verbosity_name, ...)
#define DLOG_IF(verbosity_name, ...)
#define DRLOG(verbosity_name, ...)
#define DCHECK(test, ...)
#define DCHECK_NOTNULL(x, ...)
#define DCHECK_EQ(a, b, ...)
#define DCHECK_NE(a, b, ...)
#define DCHECK_LT(a, b, ...)
#define DCHECK_LE(a, b, ...)
#define DCHECK_GT(a, b, ...)
#define DCHECK_GE(a, b, ...)
#endif

namespace edn
{
	namespace Logging
	{
		void init(int argc, char** argv);
	}
}
