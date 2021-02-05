#ifndef __CLEAR_CSQ__
#define __CLEAR_CSQ__

#include <stdlib.h>
#ifdef _WIN32
void clear() { system("cls"); }
#else
void clear() { system("clear"); }
#endif

#endif
