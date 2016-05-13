#ifndef H_CORE_DEBUG_H
#define H_CORE_DEBUG_H

#include "Platform.h"
#include "Utility.h"

#if defined(EDN_DEBUG)

// Output a note durring compilation. Can double click on NOTE to jump to in-file.
#define EDN_NOTE( MESSAGE ) \
	__pragma( message (__FILE__ "(" EDN_STRINGIZE(__LINE__) ") : NOTE [ " MESSAGE " ]") )

// Output a warning durring compilation. Can double click on WARN to jump to in-file.
#define EDN_WARN( MESSAGE ) \
	__pragma( message(__FILE__ "(" EDN_STRINGIZE(__LINE__) ") : WARNING [ " MESSAGE " ]" ))

// Output a todo durring compilation. Can double click on TODO to jump to in-file.
#define EDN_TODO( MESSAGE ) \
	__pragma( message(__FILE__ "(" EDN_STRINGIZE(__LINE__) ") : TODO [ " MESSAGE " ]" ))

#else

#define EDN_NOTE ( MESSAGE )
#define EDN_WARN ( MESSAGE )
#define EDN_TODO ( MESSAGE )

#endif

#endif