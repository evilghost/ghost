
#ifndef WIDGET_H
#define WIDGET_H

#include "WContainer.h"
#include "WView.h"

#ifdef _DEBUG

#ifdef _DLL // /MDd
#pragma comment(lib, "widget_MDd")

#else // /MD
#pragma comment(lib, "widget_MD")
#endif // _DLL

#else

#ifdef _DLL // /MTd
#pragma comment(lib, "widget_MTd")

#else // /MT
#pragma comment(lib, "widget_MT")
#endif // _DLL

#endif // _DEBUG

#endif // WIDGET_H