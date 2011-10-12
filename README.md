SA:MP Gamemode Development Kit for C++ 2.0
==========================================

Major differences from 1.x:

*    Callback system is fully rewritten 
     Now you just export needed callbacks as other plugin functions like Supports or Load.
*    Many compilers, one library 
     The dynamic library can be binary compatible across different compilers, e.g. there's no need for two 
     different .dll's for MinGW and VC++ as before.  
*    Single header for all stuff 
     Just #include <sampgdk.h> and you're done.
