
#include "pch.h"
#include "main.h"

//Convert an int to a LPCWSTR

std::wstring ws(std::to_wstring(32));
LPCWSTR lps = (LPCWSTR)(ws.c_str());