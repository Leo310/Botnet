#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <assert.h>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <WS2tcpip.h>

#ifdef BM_PLATFORM_WINDOWS
	#include <Windows.h>
#endif