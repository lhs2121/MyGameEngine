#pragma once
#ifdef EngineBaseLib
#define EngineBaseAPI __declspec(dllexport)
#else 
#define EngineBaseAPI __declspec(dllimport)
#endif