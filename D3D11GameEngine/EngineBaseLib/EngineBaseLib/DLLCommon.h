#pragma once

#ifdef EngineDLLExport
#define EngineAPI __declspec(dllexport)
#else 
#define EngineAPI __declspec(dllimport)
#endif