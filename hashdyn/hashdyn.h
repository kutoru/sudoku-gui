#pragma once

#ifdef HASHDYN_EXPORTS
#define HASHDYN_API __declspec(dllexport)
#else
#define HASHDYN_API __declspec(dllimport)
#endif

extern "C" HASHDYN_API char* get_sha256(const char* str, int strSize);
