#pragma once
#ifdef BaseLib
#define BaseAPI __declspec(dllexport)
#else 
#define BaseAPI __declspec(dllimport)
#endif

#ifdef ResourceLib
#define ResourceAPI __declspec(dllexport)
#else 
#define ResourceAPI __declspec(dllimport)
#endif

#ifdef MediaLib
#define MediaAPI __declspec(dllexport)
#else 
#define MediaAPI __declspec(dllimport)
#endif

#ifdef EngineLib
#define EngineAPI __declspec(dllexport)
#else 
#define EngineAPI __declspec(dllimport)
#endif

#ifdef CollisionLib
#define CollisionAPI __declspec(dllexport)
#else 
#define CollisionAPI __declspec(dllimport)
#endif

#ifdef GameLib
#define GameAPI __declspec(dllexport)
#else 
#define GameAPI __declspec(dllimport)
#endif

