#pragma once

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <string>
#include <iostream>
#include <array>
#include "winerror.h"
#include <charconv>
#include <windows.h>
#include <uxtheme.h>
#include <unknwn.h>
#include <strsafe.h> // for StringCchXXX functions
#include <olectl.h> // for SELFREG_E_CLASS
#include <shlobj.h> // for IDeskband2, IObjectWithSite, IPesistStream, and IInputObject

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

#include <thread>
#include <chrono>
