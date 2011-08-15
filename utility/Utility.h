
#ifndef UTILITY_H
#define UTILITY_H

#include "Structures.h"
#include "NoCopyable.h"
#include "Cloneable.h"
#include "Associateable.h"

#ifdef _DEBUG

#ifdef _DLL // /MDd
#pragma comment(lib, "utility_MDd")

#else // /MD
#pragma comment(lib, "utility_MD")
#endif // _DLL

#else

#ifdef _DLL // /MTd
#pragma comment(lib, "utility_MTd")

#else // /MT
#pragma comment(lib, "utility_MT")
#endif // _DLL

#endif // _DEBUG

#endif // UTILITY_H