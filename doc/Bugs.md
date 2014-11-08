Bugs
========

Note: I note here bugs that cannot be fixed immediately.
If you find something not working in the engine, maybe it's
a feature in development, or a TODO/FIXME item hasn't been done yet.

AngelScript
------------

- Array declarations ending with a ',' after the last element have the wrong size (+1).
int[] a = {0,1,2,3}; // a.length == 4
int[] b = {0,1,2,3,}; // a.length == 5, but should be 4
