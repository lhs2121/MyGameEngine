#pragma once

#ifdef EngineDLLProject
#define EngineAPI __declspec(dllexport)
#else 
#define EngineAPI __declspec(dllimport)
#endif