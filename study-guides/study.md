# Study Guide
- Tyler Taormina

## Linux Commands
- man = The man utility finds and displays online manual documentation pages
- ls = For each operand that names a file of a type other than directory, ls displays
       its name as well as any requested, associated information
- mkdir = creates a directory 
- rmdir = removes directory provided it''s empty
- chmod = changes file modes or access control lists
- pwd = return working directory name 
- cp = copy files
- mv = move files
- ln = the ln utility creates a new directory entry (linked file) for the file name specified by target_file.  The target_file will be created with the same file modes as the source_file
- less = file perusal filter similar to more but with more features
- find = search for files in a directory hierarchy
- grep = searches for pattern specified in files

## Bash 

-  Write the command that will set the mode on a file such that everyone can  
   execute the file, the owner can read and write the file, and everyone else
   can read the file. Use symbolic representation (not numeric) to represent the
   given mode.

    chmod 755

- How would you assign the value “hello world” to a variable called STR in a bash shell script?

    STR="hello world"

- How would you print to the terminal the bash script variable STR?
    echo $STR

- Describe the difference between single quotes and double quotes in bash shell scripting.
    single quotes = variables will not be expanded
    double quotes = variables will be expanded

- Describe the difference between single quotes and back-quotes in bash shell scripting.
    back quotes = takes whatever is in the quotes, runs it, and stores in variable

example ------------------------------------------------------
    STR1 = `date`
    echo $STR1 --> Wed 14 Jun 2023 03:50:41 PM PDT 

- What does the $? Variable represent in a bash script?
    $? expands to the exit status of the most recently executed foreground process

- What bash shell script commands would you use to create a variable COUNT and
  then add 1 to it?

    COUNT=1
    COUNT=$ ((COUNT + 1))

- Describe the –z operator when used within a bash if statement.

    the length of the string is 0

-  Describe the = operator when used within a bash if statement.
    
    string1 = string2 --> are they equivalent?

- Describe the –eq operator when used within a bash if statement.

    numerically equal
    int1 -eq int2

- Describe the –d operator when used within a bash if statement.

    file exists and is a directory

- Describe the –s operator when used within a bash if statement.

    file exists and its size is greater than 0 (its not empty)

- When using the bash built-in getopts, what would the string "hvm:M:" represent?

    options for the process. a colon means the option expects arguments passed
    ./process -h -v -m100 -Mfile.exe

- How would you run the who command and redirect it output into a file called file.txt?
    who > file.txt

- How would you run the wc command and redirect your Makefile as stdin?
    cat Makefile | wc -l -w -c

- What will be printed from the following bash statements?

```c

VALUE="A" case $VALUE in
"a" | "A" )
echo "A vowel was seen" ;;
"b" | "B" )
echo "A consonant was seen" ;;
*)
echo "A strange value $VALUE" ;;
esac

```
output --> A vowel was seen

## argc/argv/env/getopt
1. Describe the argc and argv parameters that are passed to main().
    argc - count of command line arguments given
    argv - array of pointers, each a null terminated character array
    
2. When using getopt(), when a character in the optstring is followed by a 
   single colon, it means _____

    It accepts arguments 

3. What does argv[0] represent?
    
    name of the program

4. True or False: The argv variable can be called a NULL terminated ragged array.
    
    yes

5. When writing C programs, what is the best function to use to parse the command line?

    getopt()

6. What is the optarg variable?

    contains argument passed for optstring characters that are follwed by a colon,
    otherwise it contains 0

    
7. What is the optind varialble?

    index of the next element being processed in argv. initialized to 1

8. What function do you use to find the value of an environment variable?
    
    getenv()

9. What function do to use to create a new environment variable?
    
    putenv()

## C programming
1. What is the difference between an array of char and a string in C?
    
    a string is null terminated where as an array of characters might not be

2. Describe the 4 stages of compilation for a C program?

    preprocessor, compiler, assembler, linker
    p -> expansion of header files, substitute macros and inline functions, 
         comments are removed
    
    c -> generate assembly language, verification of function usage and prototypes

    a -> generates machine code instructions, generates relocatable object file

    l -> binds necessary libraries, generates executable

3. When using printf(), describe the following format specifiers:
%+05i -> 
%2o ->
%04X ->
%9.3f ->
%-25s ->

4. What type does a call to fopen() return?

    returns a FILE pointer

5. What is the difference between printf() and fprintf() functions?

    printf writes output to stdout where as fprintf() can specify where output
    is written to. 

6. Create a new variable called personal_account for the structure defined below?
```c
struct account_s {
    int account_number;
    char first_name[50];
    char last_name[50];
    float balance;
};

struct account_s personal_account;
```

7. Create a variable that is a pointer for the structure above.

```c
struct account_s *acct_pointer = &personal_account;
```

8. How would you access the balance data member from the above variable?

```c
    acct_pointer->balance;
```

9. Describe the difference between scope and extent for a variable in C.

    - scope refers to the visibility of a variable or function
    - extent refers to the lifetime of the variable

10. The C function strcmp() returns only True or False?

    returns an int. 0 if the strings match.

11. What is a C typedef and give an example?

    Allows declaration of a custome type. See above question for an example.

12. What is the difference between the * and & operators in C?

    /* is a pointer operator or multiplication depending on context
    /& is the address operator or a 'and' depending on context

13. True or False: All character data in C are strings?

    False

14. Give 3 examples of C Processor directives.

```c
#define 
#ifndef
#include
#endif

```

15. Which should occur first in your C programs, system include files or local
    include files?

    system include files first, local second

16. What is conditional compilation in C?

    managing sections of code using preprocessor directive such as #ifdef,
    #ifndef, #else, #elif, and #endif

17. Write a C macro called MIN that takes 2 parameters and returns the minimum
    of 2 values.

```c
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
```
    

18. What are the C functions used for exception handling?

    None, use if statements and set perror.

19. When a Unix system call fails, it sets a global integer called ________________

    errno


## Malloc and Friends
1. What is returned when a call of malloc() fails?

    NULL

2. With what value is the memory returned from a call to malloc() initialized?

    memory from malloc is uninitialized

3. Describe the differences between malloc() and calloc().

    calloc initializes all memory to 0's

4. Describe the realloc() call.

    reallocates memory to an existing pointer. Copies the old block into the new
    block

5. Instead of obtaining memory from the heap, _____________ obtains memory from the
   stack.

   alloca()

6. If the stack overflows as a consequence of calling alloca(), then_____________________

    Program errors with a stack overflow or inexplicably crashses

7. Identify 2 advantages of using alloca() over malloc().

    - memory is on the stack versus heap so you don't risk double free errors
    - memroy is automatically free like any other stack variable

8. As your program calls functions and returns, the _______ segment grows and shrinks.

    - stack 

9. As your program allocates dynamic memory, the ______ segment grows.
    
    - heap

10. The sizeof() operator returns the ___________ required for the type or structure.

    bytes

11. True or False: The sum of the sizes of the members of a structure will 
    always be the same as the size of the structure as returned by sizeof().
    
    False

12. The memory allocated by a call to malloc() is always initialized to all zeroes.

    - false, it is uninitialized

13. The memory allocated by a call to malloc() is taken from the ______ segment.

    heap

14. List 3 common mistakes related to the use of free().

    - double free
    - free static or stack memory
    - attempting to free only part of a block

15. Describe the strdup() function.
    
    - returns a pointer to a new string that is a duplicate of the arg

16. Describe the 4 segments of a Unix program.

    stack, heap, data, text

17. Describe the memset() function.
    
    - fills memory with a constant byte

## Makefile
1. For a Makefile, when file A depends on file B, what does that mean?

    that file A rely's on code written in file B

2. True or False: make is definitely whey more cool than sliced bread.

    True

3. What is the default target in a Makefile?

    first target, typically called 'all'

4. True or False: In a Makefile, $(VAR) and ${VAR} are the same thing.
    
    true 

## TLPI Chapter 1
1. What was the operating system is considered the progenitor of UNIX?
    
    multics

2. POSIX stands for __________________

    Portable operating system interface

3. The UNIX operating system was initially developed at what institution(s)?
    
    AT&T Bell Labs


## TLPI Chapter 2
1. Describe the meaning of kernel for this class.

    - central software that managers and allocates computer resources

2. Identify 4 tasks performed by the UNIX kernel.

    - creation termination of processes
    - process scheduling
    - memory management
    - provide a file system
    - device access
    - network functions
    - System API

3. Describe the difference between user-mode and kernel-mode.
    - user = applications and libraries
    - kernel = process, memory, and device management

4. Describe what the shell is for UNIX.
    - command interpreter
    - reads input from users and executes programs in response

5. A “software interrupt” is another name for:
    - a signal

6. Match the file descriptors with their common name:
0 stdin
1 stdout
2 stderr

7. Like Microsoft Windows, each UNIX disk device has its own directory hierarchy.
    - 
8. For the purpose of accessing a file, the UNIX file system divides users into three categories.
     - user, group, and other

9. That the same system calls (open(), read(), write(), close(), and so on) are used to perform
   I/O on all types of files, including devices, is called _____________
    - universality of I/O

10. A process is ___________
    - instance of a running program

11. On UNIX, the “parent of all processes” is called.
    - init process (daemon)
12. What is conspicuously missing from the inode for a file on Unix?
    - name of the file

13. Identify 4 different file types on a Unix file system.
    - directory, symlink, named pipe, socket, device special, regular file

14. What is a UNIX dӕmon?
    - special process with no controlling terminal, managed by the system

15. What is interesting about the errors returned from the getpid() function call?
    - getpid() is alwasy successful

## TLPI Chapter 4
1. What does “Universality of I/O” mean for Unix?
     - the same system calls (open(), read(), write(), close(), and so on) are
        used to perform I/O on all types of files, including devices.

2. A successful call of the open() system call returns
    - the file descriptor (int)

3. For each open file, the kernel records a "file offset", which is the location 
   in the file at which the next read() or write() will commence.

4. What does the read() function return, when successful?
     - number of bytes read

5. What does the write() function return, when successful?
    - number of bytes written

6. When using the lseek() system call, a value of SEEK_CUR for the whence parameter will
adjust the file offset ________
    - offset is set to current location plus offset bytes

7. When using the open() system function, if the given file does not exist, the open() call will
always fail.
    - not if the O_CREAT flag is specified

8. What does the read() call return upon failure?
- (-1) is returned and errno is set

9. When the read() call returns a zero (0), it indicates that you are __________________
- at the end of a file

10. If you want to open a file for writing and create it if it does not exist and truncate it if it does
exist, what are the flags you should use for the flags in the open() call?
- O_CREATE, O_TRUNC, O_WRONLY

11. Explain the O_TRUNC flag used in the open() call.
- If the file already exists and is a regular file and the access mode allows
   writing (i.e., is  O_RDWR or  O_WRONLY)  it  will be truncated to length 0. 

12. A call to read() may return fewer bytes than specified in the call.
- True

13. A call to write() may return fewer bytes than specified in the call.
- True

14. Valid values for the whence parameter on the lseek() call are:
- SEEK_SET
- SEEK_CUR
- SEEK_END

15. Describe what the O_EXCL flag means in a call to open() on Unix.
- ensures that the call of open() creates the file, fails if it already 
  exists

16. Describe how the following flags to open() would behave when or-ed together.
O_CREAT | O_WRONLY | O_TRUNC
- 

17. The Unix filesystem divides the file permission bits into 3 groups. What are those groups?
- Owner, Group, Public


## TLPI Chapter 5
1. The concept that the kernel guarantees that all of the steps in a system call are completed
as a single operation, without being interrupted by another process or thread is called
_____
2. To ensure that a process is the creator of a file, combine the ______ flag with the O_CREAT
flag when calling open().
3. Appending data to the end of a file is always guaranteed to be atomic.
4. Describe what a race condition is for our class.
5. A call to the system commands truncate() or ftruncate() always result in a zero length file.
6. Describe the dup2() function.
7. Describe the difference between parallelism and concurrency (for our class).

## TLPI Chapter 8
1. Every user has a unique _________________ and an associated _____________________.
2. Is it possible for the /etc/passwd file to have duplicate UID entries?
3. The primary purpose of user IDs and group IDs is to determine ______________ of various
system resources.
4. Identify the colon separated fields within a line from the /etc/passwd file.
rchaney:*:2021:2000:Jesse Chaney:/u/rchaney:/bin/bash

## TLPI Chapter 9
1. A ______________ program allows a process to gain privileges it would not normally have.
2. Describe what the s means in the mode bits of the following directory listing.
-rwsr-xr-x 1 root root 32072 Nov 20 04:37 su*
---s--x--x 1 root root 130720 Nov 20 12:16 sudo*

## TLPI Chapter 10
1. On Unix system, the Epoch began on _______
2. Time zone information is compiled into the Unix kernel?
3. In this class, the term “locale” refers to:
4. The software clock on a Unix system measures time in ______
5. Match the 2 kinds of time in UNIX to the correct definition
• Real time
• Process time _____________
_____________
6. Regardless of geographic location, UNIX systems represent time internally as a measure of
seconds since the Epoch.
7. In UNIX, the 2038 Problem refers to ________
8. The time() system call returns ___________
9. Conversion of the time_t value from a call to time() into a more detailed structure
representing seconds, minutes, hours, days, .. is called
10. The %D format for strftime() function says _____
11. The function that converts from printable form to broken-down time is _____
12. The size of a jiffy is defined by ______
13. User CPU time is the amount of time spent executing in user mode.

## TLPI Chapter 12
1. Why is the /proc filesystem called a pseudo-filesystem?
2. Describe the kcore file in /proc.
3. Describe the loadavg file in /proc.
4. Describe the self symbolic link in /proc.
5. What are all the numbered directories in the /proc directory?

## TLPI Chapter 19
1. The file event monitoring interface for Linux is called _____________
2. The Linux inotify interface works across NFS mounts.
3. Give 3 examples of file events that can be monitored with the inotify interface.
4. Directories added in an inotify monitored directory are automatically added to the event
notification, recursively.
5. The inotify interface works across all POSIX compliant operating systems.


## TLPI Chapter 20
1. True or False: Delivery of a signal is blocked during the execution of its handler.
2. True or False: A signal is a synchronous notification sent to a process.
3. If you want to reset the disposition of a signal to its default, there is a constant that can be
used in place of a handler function. What is it?
4. On Linux, the standard signals are numbered ____ to ____ .
5. True or False: All signals can be caught or blocked.
6. Signals are sometimes described as _____________
7. With signals, it is generally pretty easy to determine when they will arrive.
8. True or False: Processes can send signals to other processes, but not itself.
9. What types of events can cause signals to be sent to a process?
10. The SIGPIPE signal means what?
11. The SIGSEGV signal represents ________
12. The second argument to the signal() function is
13. The value to use to instruct your process to ignore a signal is ________
14. The common system C function to send a signal to another process is ____
15. An easy way for a process to send a signal to itself is to call ___
16. A signal mask for a process represents a set of signals whose delivery to the process is
_____
17. If a process receives a signal that it is currently blocked, that signal is added to the process’
set of pending signals. When (and if) the signal is later unblocked, it is then delivered to the
process.
18. True or False: The normal set of signals are queued.
19. Receipt of signals can be reliably counted.
20. Write some C code that will count all the SIGUSR1 signals received by a process.
21. The system function that will suspend a process until a signal is received is _______
22. What UNIX command do you use to send a signal to a process?

## TLPI Chapter 21
1. A function the can safely be simultaneously executed by multiple threads of execution in
the same process, is called _______
2. A function where the implementation guarantees to be safe when called from a signal
handler is called ______
3. The value of errno will not change within a signal handler.
4. True or False: It is possible for signals to be lost for a process.
5. All system and library functions can be safely called from within a signal handler.
6. A function that employs only local variables is guaranteed to be reentrant.
7. When you use the SA_RESTART flag on a signal, all system calls will be automatically
restarted if interrupted by a signal.

## TLPI Chapter 24
1. After creating a child process using fork(), which runs first, the parent process or the child
process?
2. When successful, for the parent, fork() returns the _____ of the newly created child
process.
3. It is possible to call the fork() function and not exec a new program over the child.
4. The fork() system call _____ (describe it)
5. When successful, the returned pid value for fork() in the child process is _____
6. For a child process to find the value of its parent's PID, it should call ______.
7. When fork() fails, it returns the value ______
8. After a call to fork(), the child has a copy of the parent’s file descriptors.
9. A call to the vfork() command is just like a call to fork(), except faster.
10. Applications that implicitly or explicitly rely on a particular sequence of execution in order
to achieve correct results are open to failure due to race conditions.
11. A parent process may have at any one time only a single child process.
12. What are “related” processes?

## TLPI Chapter 25
1. By convention, a termination status of _____ indicates that a process completed
successfully.
2. Before a call to _exit() completes, calls are made to exit handlers (atexit() and onexit()) and
stdio buffers are flushed.
3. Exit handlers are way for a process to perform cleanup before a normal _______
4. Registered exit handlers are always called before a process terminates.
5. Exit handlers are not called if a program calls _exit() directly or if the process is terminated
abnormally by a signal.
6. Registering a signal handler for SIGKILL guarantees that an exit handler will be called for
that signal.
7. It is not possible to register multiple exit handlers when using atexit().
8. When a process invokes exit(), the exit handler functions are called in order of registration.
9. If an exit handler fails to return, either because it called _exit() or because the process was
terminated by a signal, then the remaining exit handlers are not called.
10. If an exit handler calls exit(), it may cause all of the exit handlers to be invoked again, which
can result in an infinite recursion.
11. A child process created via fork() does not inherit a copy of its parent’s exit handler
registrations.
12. When a process performs an exec(), all exit handler registrations are retained in the new
process.
13. A (nonstandard) alternative to atexit(), provided by glibc is ______
14. A general principle: in an application that creates child processes, typically only one of the
processes (most often the parent) should terminate via exit(), while the other processes
should terminate via _exit().
15. Typically only one process of a family of processes should terminate with a call to ________,
other processes should terminate with a call to _______.
16. Describe the nice() system call.
17. What is the return value from a call to exit()?

## TLPI Chapter 26
1. On a successful call to wait(), if no (previously unwaited-for) child of the calling process has
yet terminated, the call _______ until one of the children terminates.
2. What signal is used to terminate a zombie process?
3. Child processes are reaped using what system call?
4. Like the wait() call, the waitpid() call always blocks.
5. A common way of reaping dead child processes is to establish a handler for the _______
signal.
6. A child process that has terminated, but not yet had it parent process call wait() on it is
called a _______
7. In order to kill a zombie process you must ________
8. On success, a call to wait() returns _____
9. On failure, a call to wait() returns _____
10. What does the status parameter represent in a call to wait()?
11. What process becomes the parent of an orphaned child process?
12. What happens to a child process that terminates before its parent has had a chance to
perform a wait()?
13. If your program needs to wait for a specific child process to terminate, you should call
_________.
14. If a large number of such zombie children are created, they will eventually fill the kernel
process table, eventually _____
15. Describe the difference between a zombie process and an orphan process.

## TLPI Chapter 27
1. A successful call to one of the exec() functions returns what value?
2. When a call to a exec() does fail, a value in errno of EACCES means:
3. When a call to a exec() does fail, a value in errno of E2BIG means.
4. The exec()set of commands cannot be used to execute shell scripts (interpreter scripts).
5. The execve() system call loads a new program into a process’ memory.
6. During the execve() call, list what will happen with the process 4 segments:
7. When using the execve() call, the argv parameter does not need to set argv[0] to be the
command name.
8. After an execve(), the process ID of the new process is changed.
9. Which of the various exec() functions will search the PATH environment variable when
called?
10. By default, all file descriptors opened by a program that calls exec() remain open across the
exec() and are available for use by the new process.
11. The new image created by a call to one of the exec() functions inherits the old process’
signal handlers.
12. What are some of the advantages of using the system() call, when possible? (list 2)

## Pthreads tutorial
1. When compared to the cost of creating and managing a process, a thread can be created
with much less operating system overhead.
2. By having main() explicitly call pthread_exit() as the last thing it does, main() will block and
be kept alive to support the threads it created until they are done.

## TLPI Chapter 29
1. Threads allow a single process to perform multiple tasks concurrently?
2. Like processes, threads are an independent stream of execution.
3. Threads in a process do not share global memory?
4. When using PThreads, each thread has its own errno variable?
5. When a program makes a call to pthread_create(), the creating thread will always run first.
6. In a multithreaded application, a bug in one thread can damage all of the threads in the
process, since they share the same address space and other attributes?
7. In PThreads, the thread-id is guaranteed to be unique across all processes.
8. The pthread_join() function waits for the thread identified by thread to ______.
9. When we don’t care about a thread’s return status; we simply want the system to
automatically clean up and remove the thread when it terminates, we say the thread is
__________
10. Some of the attributes that threads within a process share are (list 5):
11. Some of the attributes that threads within a process DONOT share are (list 3):
12. In a multi-threaded process, if one thread is blocked on I/O, all threads are blocked.
13. List 2 advantages that a multi-threaded application has over a multi-process
implementation.
14. All Pthreads functions return 0 on success or a positive value on failure (unlike the return
value for system function).
15. The 3 ways a thread may terminate are:
16. When a thread calls exit(), only that thread actually terminates.
17. A thread can obtain its own ID using _________ call.
18. Calling pthread_join() for a thread ID that has been previously joined
can lead to __________.
19. If we neglect fail to call pthread_join() on a non-detached thread,
then, when the thread terminates, it produces the thread equivalent
of a ________
20. Unlike processes, threads are peers, any thread in a process can use pthread_join() to join
with any other thread in the process.
21. What is the PThreads call to “join with any thread” (as the wait() call does with processes)?
22. Once a thread has been detached, it is still possible to obtain its return status with
pthread_join().
23. What is the compiler flag you need to use to have your PThreaded code compile?
24. Any thread calling pthread_exit() will immediately exit. If no, explain.

## TLPI Chapter 30
1. In TLIP Chapter 30, the term critical section is used to refer to a section of code that
accesses a shared resource and whose execution should be ____
2. Before a statically allocated mutex can be used, it must be initialized.
3. On Linux, if a thread tries to lock a mutex for which it already has a lock, the default
behavior is to __
4. The term mutex stands for ____
5. A mutex has two states (identify them)
6. Correctly order the steps in the typical protocol when using a mutex to control access to a
shared resource.
7. To lock and unlock a mutex, we use the ______ and ______ calls.
8. The pthread_mutex_trylock() function is the same as pthread_mutex_lock(), except that if
the mutex is currently locked, pthread_mutex_trylock() call will ___
9. What kind of condition can occur when more than one thread is locking the same set of
mutexes?
10. A thread may not unlock a mutex that it did not lock.
11. The alternate terms ____ and ____ are sometimes used for mutex lock and unlock.
12. A thread may not unlock a mutex that is not currently locked.
13. Describe deadlock (as it relates to our class).
14. Use of a mutex will automatically detect and prevent deadlock.
15. PThread barrier locks allow all threads to reach a specific point in the program before
continuing.
16. Describe a barrier lock.
17. Describe how readers-writers locks work.
18. A function is said to be thread-safe if it can _________________________

## TLPI Chapter 31
1. A function is said to be thread-safe if it can _______
2. Identify 4 POSIX functions which are not thread-safe.
3. Is the following code fragment thread-safe? Why or why not?
```c
static int glob = 0;
static void incr(int loops)
{
    int loc, j;
    for (j = 0; j < loops; j++)
    {
        loc = glob;
        loc++;
        glob = loc;
    }
}
```

## TLPI Chapter 32
1. What is the PThreads call to request a thread to terminate?
2. The pthread_cancel() call will wait for the canceled thread to terminate before returning.

## TLPI Chapter 44
1. The oldest method of IPC on Unix is _________________
2. When TLPI refers to a pipe as a byte stream, it means __________
3. Data in a pipe can be randomly accessed using lseek()?
4. Attempts to read() from an empty (but open) pipe will, ___________
5. If the write end of a pipe is closed, then a process reading from the pipe will ____________
6. If multiple processes are writing to a single pipe, then it is guaranteed that their data won’t
be intermingled if they write no more than PIPE_BUF bytes at a time.
7. When writing to a pipe, the call to write() will block if ____
8. Describe what “unnamed pipes can be used between related processes” means.
9. When a pipe is created, the file descriptors used for the two ends of the pipe are the next
lowest-numbered descriptors available.
10. The popen() command can be used to write to and read from an executed command?
11. Another name for FIFO pipes is _______________
12. A FIFO shows up as an entry in the file system.
13. An unnamed pipe has ________________ persistence.
14. A FIFO has __________________ persistence
15. Once a FIFO has been created, it can be only be opened by a “related” process (subject to
file permission checks).
16. A (successful) call to the pipe() system call creates how many open file descriptors?
17. Pipes have unlimited capacity.
18. Pipes are a natural way to connect filters (programs that read from stdin and write to
stdout).
19. When all descriptors referring to a pipe or FIFO have been closed, any outstanding data are
_______
20. When a process opens one end of a FIFO, it blocks if the other end of the FIFO has not yet
been opened.

## TLPI Chapter 52
1. Describe how a POSIX message queue differs from a FIFO.
2. POSIX message queues are priority driven.
3. Like named pipes, message queues are byte streams.
4. Partial messages can be read from a POSIX message queue.

## TLPI Chapter 53
1. Semaphores were invented by whom?
2. A POSIX semaphore is an integer whose value is not permitted __________________
3. When initializing an unnamed POSIX semaphore using sem_init(), a value of 0 for the
pshared argument indicates, the semaphore is not to be shared between the threads of the
calling process.
5. The sem_destroy(sem) call is the preferred method to remove both named and unnamed
semaphores from the system.
6. A POSIX unnamed semaphore can be embedded inside a data structure object.
7. If a process attempts to decrease the value of a POSIX semaphore below 0, then, depending
on the function used, the call _______
8. The sem_post(sem) function (describe what it does):
9. If a blocked sem_wait() call is interrupted by a signal handler, then it
10. POSIX specifies two types of semaphores (list both):

## TLPI Chapter 54
1. POSIX shared memory allows to us to share a mapped memory region between unrelated
processes without needing to create a corresponding mapped file.
2. On a Linux system, the POSIX shared memory objects will persist even after no processes
has them open.
3. On a Linux system (kernel 2.4 and higher), the POSIX shared memory is stored mounted as
file system under _______
4. The POSIX call shm_open(), when successful, returns a __________________
5. When a shared memory object space is extended, the newly added bytes are automatically
initialized to -1.
6. When a new POSIX shared memory object is created, it initially has ____ length.
7. When opening a POSIX shared memory object, specifying O_EXCL in conjunction with
O_CREAT is a request to ensure that the caller is the creator of the object.
8. Removing a shared memory object doesn’t affect existing mappings of the object, but
prevents further shm_open() calls from opening the object.
9. Once the shared memory region has been mapped into the process’s virtual address space,
it looks just like any other part of the process’s memory space.
10. What form of synchronization does shared memory provide?

## TLPI Chapter 56
1. A POSIX datagram socket doesn’t need to be connected to another socket in order to be
used.
2. A socket that has been marked to allow incoming connection by calling listen() is called
____ (active or passive).
3. A stream socket is similar to using a pair of pipes to allow bidirectional communication
between two applications.
4. A successful call to socket() returns a _______ (don’t just say “a socket”).
5. By default, a socket that has been created using socket() is _______ (active/passive).
6. If an application attempts to write to a POSIX stream socket which the peer application has
closed, it will __________
7. If there are no pending connections when accept() is called, the call _______ until a
connection request arrives.
8. In most applications that employ stream sockets, a server application performs the _______
open, and the client performs the ________ open.
9. Just to make things easier, data type sizes between all systems are always the same (a C
long data type is always 32 bits).
10. Modern Unix/Linux operating systems support at least 3 socket communication domains.
What are those 3?
11. Since the underlying networking protocols may sometimes retransmit a data packet, the
same POSIX datagram socket messages could arrive more than once.
12. Socket I/O can be performed using the conventional read() and write() system calls.
13. Sockets are a method of IPC that allow data to be exchanged between applications on
different hosts connected by a network.
14. Complete the following table.
Property
Socket Type
Stream
Datagram
Reliable Delivery
Message boundaries preserved
Connection Oriented
15. With a stream socket, message boundaries are not preserved.
16. Transmission Control Protocol (TCP) is an example of datagram sockets.
17. When a peer application reads from a socket which has been closed, it will receive ____
18. When accept() returns, it creates a new socket that is connected to the peer socket that
performed a connect().
19. When using datagram sockets, messages may arrive out of order, be duplicated, or not
arrive at all.
20. With POSIX datagram sockets, message boundaries are preserved, but data transmission is
not reliable.

## TLPI Chapter 57
1. UNIX domain sockets only allow communication between processes on the same host
system.
2. The address family for UNIX Domain sockets is ____
3. When used to bind a UNIX domain socket, bind() creates
4. When listed with ls –F, a UNIX domain socket appends an ______ to the socket pathname.
5. A UNIX Domain socket may be bound to multiple pathnames.
6. Because UNIX Domain Sockets are pathnames, we can use the open() call to open one.
7. When a UNIX Domain socket is no longer required, its pathname entry should be removed
using unlink()
8. When creating a UNIX Domain socket, we can bind a socket to an existing pathname.
9. For UNIX domain sockets, datagram transmission is carried out within the kernel, and is
reliable.
10. To connect to a UNIX domain stream socket, only read permission is required on the socket
file.
11. With UNIX Domain sockets, a socket pair (created with the socketpair() call) is used in a
similar fashion to a pipe.
12. How do you create a UNIX Domain socket in the abstract namespace?
13. With UNIX Domain sockets (Linux specific), the abstract namespace are sockets that do not
exist in the file system.
14. UNIX Domain sockets in the abstract namespace still need to be unlinked from the file
system.
15. Which is likely to provide better performance, TCP sockets or UNIX sockets?

## TLPI Chapter 59
1. A system that is called big endian is one where the most significant byte is stored first (MSB,
leftmost).
2. One difference between IPv4 addresses and IPv6 address is that an IPv6 address is 64 bits,
not 32 bits like IPv4.
3. The inet_pton() and inet_ntop() functions are like inet_aton() and
inet_ntoa(), but differ in that they also handle ____
4. The result of a successful call to getaddrinfo() is _______
5. The standard network byte ordering used is called ______
6. The terms big endian and little endian derive from ______
7. With UDP sockets, if the incoming datagram would overflow the receiver’s queue, then the
datagram is __________
8. Two notable examples of little-endian architectures are: ________
9. The byte ordering used on a particular machine is called the _______
10. With the networking function htonl(), what does htonl actually stand for?
11. The process of putting data into a standard format for transmission across a network is
referred to as ____
12. If IPv4 and IPv6 coexist on a host, they can share the same port-number space.
13. An IPv6 address is composed of __________ bits.
14. On success, the inet_pton() function returns ____
15. In the inet_pton() and inet_ntop() functions, the p stands for _____ and the n
stands for ____
16. The getaddrinfo() function converts host and service names to _______
17. Given a host name and a service name, getaddrinfo() returns _______
