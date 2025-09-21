# wordfishing
Search for a set of words in a char diagram.

## Compile
`g++ main.cpp InputFile.cpp wordfishing.cpp -o wordfishing -std=c++20 -pthread`

*C++20 to support `ends_with`*

## File format
```txt
int rows int columns
diagram[rows][columns].
words to find
```

## Algorithm
Uses 8 threads to search in all directions at the same time (N, S, W, E, NW, NE, SW, SE) and displays the result diagram with words remark in green, bold and up text; Found words summary with position and direction

