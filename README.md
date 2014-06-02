Compression
===========

Basic text compression for /r/dailyprogrammer. Challenge can be found [here](http://www.reddit.com/r/dailyprogrammer/comments/25o2bd/5162014_challenge_162_hard_novel_compression_pt_3/)  
Usage: compression [option] [input file] [outputfile]  
Options: -c for compressing and -d for decompressing.

Formatting and Rules of Compression
==========================
- List of words used will be added to a dictionary, the position in the dictionary will be used to represent the word. (0 indexed)
- If the word starts with a capital letter the number will be followed by "^".
- If the word is in all caps the number will be followed by "!".

An error will occur if:
- A word is capitalised in any other different way than above.
- A word is not alphabetical (eg. has numbers in it)
- A symbol not in . , ? ! ; : - is encountered
- Two or more symbols are next to each other like ??1)

Example:  
> HELLO MY NAME IS STAN!  
My name is Stan

Will output:  
> 5  
hello  
my  
name  
is  
stan  
0! 1! 2! 3! 4! ! R 1^ 2 3 4^ . E


Formatting for Decompression
============================
- [number of words in the dictionary]
- [list of words in the dictionary seperated by a newline]
- [compressed text]

Example:
> 11  
the  
quick  
brown  
fox  
jumps  
over  
lazy  
dog  
or  
did  
it  
0^ 1 2 3 4 5 0 6 7 . R 8^ , 9 10 ? E  

This will output:  
> The quick brown fox jumps over the lazy dog.  
Or, did it?
