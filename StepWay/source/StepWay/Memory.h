#pragma once
#include "Core.h"
#include "Types.h"
#include <crtdbg.h>

//Rewrite later
#if defined(SW_DEBUG)
	#define swNew		new ( _CLIENT_BLOCK , __FILE__ , __LINE__ )
	#define swDelete	delete
#else
	#define swNew		new
	#define swDelete	delete
#endif

