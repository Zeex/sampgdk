Don't use callbacks, they are still buggy and won't work if you run 
multiple GDK-based plugins. I doubt it's possible to fix them, sorry.

Natives should work though. See branch `no-callbacks`.

