SA:MP Gamemode Development Kit for C++ 2.0
==========================================


Major differences from 1.x:
---------------------------

*    Callback system is fully rewritten

     Now you just export callbacks with PLUGIN_EXPORT as other plugin functions like Supports/Load/etc.
     This is somewhat similar to how you usually do it in Pawn.
     
     
*    Many compilers, one library 
    
     The dynamic library is (I believe) binary compatible across different compilers, e.g. there's no need for two 
     different .dll's for MinGW and VC++.  
                                   

SA-MP functions not included in GDK
-----------------------------------
*   `SetTimer`, `SetTimerEx` - use ProcessTick or a third-party timer library instead
*   `CallLocalFunction`, `CallRemoteFunction` - useless, you have function/method pointers in C++
*   `format` - just use the `sprintf` function form `<stdio.h>` 

Known issues
------------
*    Callbacks like 'OnPlayerCommandText`, `OnRconCommand`, etc with "non-standard" return values are treted in the same way
     as the rest, which means you should return 0 if you want to prevent them from being called in other GDK-enabled plugins, if any. 
     Furthermore, the returned 0 is passed directly to SA-MP server resulting in an `Server: Unknown Command`message though the command 
     has been found.  
