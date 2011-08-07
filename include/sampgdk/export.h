// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

#ifndef SAMPGDK_EXPORT_H
#define SAMPGDK_EXPORT_H

#if defined WIN32 || defined _WIN32
    #define SAMPGDK_EXPORT __declspec(dllexport)
    #define SAMPGDK_CALL   __stdcall
#else
    #define SAMPGDK_EXPORT 
    #define SAMPGDK_CALL
#endif 

#endif
