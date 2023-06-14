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

2. Describe the 4 stages of compilation for a C program?

3. When using printf(), describe the following format specifiers:
%+05i -> 
%2o ->
%04X ->
%9.3f ->
%-25s ->

4. What type does a call to fopen() return?

5. What is the difference between printf() and fprintf() functions?

6. Create a new variable called personal_account for the structure defined below?
```c
struct account_s {
    int account_number;
    char first_name[50];
    char last_name[50];
    float balance;
};

```

7. Create a variable that is a pointer for the structure above.

8. How would you access the balance data member from the above variable?

9. Describe the difference between scope and extent for a variable in C.

10. The C function strcmp() returns only True or False?

11. What is a C typedef and give an example?

12. What is the difference between the * and & operators in C?

13. True or False: All character data in C are strings?

14. Give 3 examples of C Processor directives.

15. Which should occur first in your C programs, system include files or local include files?

16. What is conditional compilation in C?

17. Write a C macro called MIN that takes 2 parameters and returns the minimum of 2 values.

18. What are the C functions used for exception handling?

19. When a Unix system call fails, it sets a global integer called ________________



