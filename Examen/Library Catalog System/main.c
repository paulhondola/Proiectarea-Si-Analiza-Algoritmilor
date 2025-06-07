/*
A university library uses a computerized catalog system to organize millions of
books. You receive a dump of their index structure in the following format:

[m=5]
"Fiction"|["Adventure","Biography"]|["History","Mathematics","Physics"]|["Art","Chemistry"]|["Drama","Fantasy"]|["Geology","Medicine"]|["Poetry","Science","Technology","Zoology"]

The format represents book categories where m=5 indicates the maximum number of
categories per node, quoted strings are internal node categories, and bracketed
lists are leaf collections.

Your task is to:

Parse and validate this catalog structure
Implement a search function to find which section contains a given book category
Calculate the maximum number of comparisons needed to find any category
Determine if the structure is optimally balanced for search operations
*/
