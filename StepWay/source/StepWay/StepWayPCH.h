#pragma once
//it's precompiled header
//#ifndef SW_BUILD_DLL
//#error precompiled header only for internal usage
//#endif


#include "Core.h"
#include "Log.h"
#include "Types.h"



//std containers
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <memory.h>

#include <functional>
#include <algorithm>

#include <locale>
#include <codecvt>


#ifdef SW_PLATFORM_WINDOWS
#include <Windows.h>
#include <Windowsx.h>
#endif // SW_PLATFORM_WINDOWS
