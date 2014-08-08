GetQueueuSize has been deprecated,
RemoveAllRouteIDFromQueue no longer can remove specific route ID's from the queue, it clears the whole queue.
Calling 1000 times CalculatePath and then waiting till the callback is called with the last calculation takes 34 seconds which gives an average execution time of 34ms
You still need sampgdk installed on linux AND on windows.
The windows version uses the Microsoft Visual C++ 2012 x86 runtime library (C++11) from now on (not 2010 like in the previous versions)
The linux version uses Intel Thread Building Block for concurrence queueu.