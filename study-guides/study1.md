# Study Guide
- Tyler Taormina

## Wait
```
#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *status);
```
- Blocks execution of calling process until one of its child processes changes status (typically temrinate)
- if calling process has a child process, wait() will return child proc pid
- no child proc for parent proc, wait() immediately returns -1
-  

