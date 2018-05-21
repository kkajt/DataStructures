# DataStructures
Program made for "Algorithms and data structures" course.

Enables to test different data structures on given data. Possible data structures are: red-black tree, binary search tree and
hash table. Hash table firstly contains data in lists, but after breaking breakpoint certain lists switch into red-black trees.

# Input

Program as input parameter may accept data structure type: 
- "--type rbt"
- "--type bst"
- "--type hmap"

Input should consist of n+1 lines, where first line tells the n number which is number of operations to execute. Next lines
should contain operations commands. Available commands: 
- insert s - inserts string s to datastructure
- delete s - deletes string s from data structure if such exists
- find s - prints 0 if such string doesn't exist, 1 otherwise
- min - prints minimum value from data structure
- max - prints maximum value from data structure
- successor k - finds successor of string k
- inorder - prints out inorder walk on structure
- load f - loads every word from given file path f that is separate with whitespace

Given commands work only on data structures that enables certain operations (for example inorder is impossible on hash table).
If operation is not possible, the program prints empty line.
