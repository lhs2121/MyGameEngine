#pragma once
#ifdef BaseLib
#define BaseAPI __declspec(dllexport)
#else 
#define BaseAPI __declspec(dllimport)
#endif

#ifdef D3D11Lib
#define D3D11API __declspec(dllexport)
#else 
#define D3D11API __declspec(dllimport)
#endif

#ifdef MediaLib
#define MediaAPI __declspec(dllexport)
#else 
#define MediaAPI __declspec(dllimport)
#endif

#ifdef CoreLib
#define CoreAPI __declspec(dllexport)
#else 
#define CoreAPI __declspec(dllimport)
#endif

#ifdef GameLib
#define GameAPI __declspec(dllexport)
#else 
#define GameAPI __declspec(dllimport)
#endif