#ifndef TILDE_UI_LIBRARY_GLOBAL_H
#define TILDE_UI_LIBRARY_GLOBAL_H

#ifdef _WIN32
#define LIB_EXPORT extern __declspec(dllexport)
#define LIB_C_EXPORT extern "C" __declspec(dllexport)
#else
#define LIB_EXPORT extern
#define LIB_C_EXPORT extern "C"
#endif

#endif // TILDE_UI_LIBRARY_GLOBAL_H
