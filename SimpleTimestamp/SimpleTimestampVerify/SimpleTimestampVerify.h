#pragma once

#include "resource.h"
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

HWND CreateIPAddressFld(HWND hwndParent, HMENU ID, int xcoord, int ycoord);