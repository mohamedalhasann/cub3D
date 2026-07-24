# get_next_line

this project is a small C implementation of `get_next_line`, reads one line at a time from a file descriptor

## Build

Compile :

```sh
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```

## What i learned

working on this project taught me the basics of memory management in C:

every `malloc` needs a matching `free`, the importance to handle allocation failures before using a pointer
reusing a static buffer can help keep state between calls, but it must be cleaned up carefully.


