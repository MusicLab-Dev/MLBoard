/**
 * @ Author: Paul Creze
 * @ Description: Network module
 */

#pragma once

#include <cstdint>

#if INTPTR_MAX == INT32_MAX
    #define ENVIRONMENT_32BITS
#elif INTPTR_MAX == INT64_MAX
    #define ENVIRONMENT_64BITS
#else
    #error "Environment not 32 or 64-bit."
#endif

constexpr std::size_t CacheLineSize = sizeof(void*) * 8ul; 
