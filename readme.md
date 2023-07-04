# Programming Assignment 5

 Due May 31 by 5pm Points 100

# Overview

 For this assignment you will write a server program that allows other programs to store and retrieve data.

 Your server program will act as a key-value store

 (https://en.wikipedia.org/wiki/Key%E 2 % 80 % 93 value_database) and will implement two types of requests:

 set and get. In addition, your program must maintain an index

 (https://en.wikipedia.org/wiki/Database_index) to allow efficient lookups by key for "get" requests.

# Setup

 Clone the repository.

 Accept the GitHub Classroom Assignment 5 invitation

 (https://classroom.github.com/a/ 41 RMp 6 q 8 ).

## Functional Overview

 Your program will maintain a database of key/value pairs. Keys will be strings up to 32 characters in

 length (following the rules of C variable names, ie: no spaces or special characters), values will be

 strings up to 1024 characters in length.

## Requirement 1

 Your primary server program should be named kvstore and must accept two command-line arguments,

 in this order:

 1. The name of the file (discussed below, in R4) containing the database records in plain text format.

 2. The file name of the FIFO / named pipe that will accept requests from other programs. Your program

 should create this FIFO file if it does not already exist.

 For example, your program should run as follows:

```
./kvstore test.db db_fifo
```

## Requirement 2

 Implement a separate client program to access your database. Your client should be minimal; it should

 be constructed to pass key/value strings to a running kvstore process via the named pipe provided as

 its first command line argument. This client program should be named kvclient, and should accept

 commands as follows:

```
./kvclient <named pipe> <get or set> <key> [<value>]
```
 For example, to store the string first in first out under key a (note the double quotes around the

 value to treat this as a single command line argument; the quotes should not be stored as part of the

 value):

```
$ ./kvclient db_fifo set a "first in first out"
```
 Example retrieval of the value for key a:

```
$ ./kvclient db_fifo get a
first in first out
```
 After issuing each get request, your client should read and print the value.

 Your kvclient program should terminate after handling a single set/get request, and it should print a

 notification message if an error occurs.

## Requirement 3

 Your kvstore program should be constructed to run continuously, accepting requests until it receives a

 SIGQUIT signal. While running, your program should accept request strings sent over the server's FIFO /

 named pipe. Commands will be structured as follows:

```
get <client process ID> <key>
```
 or

```
set <key> <value>
```
 Each request will be terminated with a newline character. Values will never contain commas.

 A set request for an existing key should overwrite the value for that key in your database file. Get

 requests must be handled by creating a separate client-specific named pipe, and writing the response

 this this separate pipe to be read by the client. It is up to you to design a strategy for internal handling of

 client-specific pipes.


## Requirement 4

 Your database file should be maintained in plan text form, with a comma-separated key/value pair stored

 on each line. For example, this sequence of commands:

```
set a value for a
set b b's value
set a new a value
set my_c another value
```
 Should yield a database file with this content:

```
b,b's value
a,new a value
my_c,another value
```
 Note that lines may be stored in any order, they do not need to be sorted by key.

## Requirement 5

 To support efficient lookups by key, your kvstore program must maintain an in-memory index

 (https://en.wikipedia.org/wiki/Database_index). It is up to you to define an indexing strategy; the

 fundamental requirement is that the indexing strategy you implement must support lookups that are more

 efficient than an O(n) "full scan." Possible approaches include the following data structures:

 Hash table (https://en.wikipedia.org/wiki/Hash_table)

 B-Tree (https://en.wikipedia.org/wiki/B-tree)

 Skip list (https://en.wikipedia.org/wiki/Skip_list)

## Requirement 6

 The data within your database must be stored on disk and must be available for use by subsequent

 executions of your kvstore program. For example, if a user stores values using keys a, b, and c and

 your kvstore program is then terminated and re-run at a later time, the user should be able to retrieve

 the values previously stored for keys a, b, and c. Your index should be maintained entirely in-

 memory by the kvstore program, and should be rebuilt (based on any existing entries) every time your

 kvstore program starts up.

## Requirement 7

 Your program must properly manage resources to avoid running out of processes/memory. Your program

 must pass a valgrind check with zero errors.


 Assignment Rubric (1)

## Forward-looking Note

 The next (and last) programming assignment will re-use this implementation as part of its functionality.

 Assignment 6 will involve the construction of a network server that handles HTTP requests, using your

 kvstore program for data storage.

## Deliverables

 Source Code (and Makefile) - Push all relevant source code and an appropriate Makefile to your

 repository.

 During testing, the autograder creates files/directories with the prefix: ag_ Please make sure your

 repository does not include files or directories named with this prefix with these names.

 Please do not commit compiled/executable files to git (ie. do not add: a.out, kvstore (the

 executable file, without an extension), main.o, etc.)

 For full credit, your git commit history must be sufficiently detailed to illustrate how you approached

 the assignment, addressed bugs, etc. Commit often, with descriptive commit labels. For example:

 "initial data structures and function prototypes", "implemented the -a switch to display hidden files",

 "solved resource leak in function xyz()" There is no fixed minimum number of commits. As one

 example guideline, you will not be eligible for full credit if your submitted git repository includes just 2-

 3 commits where large blocks of code are added in each commit.


 Total Points: 100

 Criteria Ratings Pts

 50 pts

 10 pts

 10 pts

 10 pts

 20 pts

Functionality **50 pts
Full Marks
0 pts
No Marks**
Code Review **10 pts
Full Marks
0 pts
No Marks**
Valgrind Check **10 pts
Full Marks
0 pts
No Marks**
Resource Management **10 pts
Full Marks
0 pts
No Marks**
Index Implementation **20 pts
Full Marks
0 pts
No Marks**


