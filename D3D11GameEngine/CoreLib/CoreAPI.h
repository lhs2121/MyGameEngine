#pragma once

#ifdef CoreLib
#define CoreAPI __declspec(dllexport)
#else 
#define CoreAPI __declspec(dllimport)
#endif