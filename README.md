*This project has been created as part of the 42 curriculum by bda-luz-*

# get_next_line 42

## Description
The goal of this project is to read and return one line at a time from a file descriptor while preserving the reading position between function calls. It focuses on understanding static variables, state persistence across function calls, safe memory management, buffer handling, and support for multiple file descriptors.

Returns the next line read from the file descriptor, including the trailing newline (`\n`) when present. Returns `NULL` when the end of the file is reached or an error occurs.

- Prototype:
```c
char *get_next_line(int fd);
```

## Instructions

### Compilation & Usage

### Prerequisites
Before compiling, ensure you have a C compiler (`cc` or `gcc`) installed and configured on your system.

### Compilation
This project is intended to be compiled using `cc` with the strict flags `-Wall -Wextra -Werror`.
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -o ProgramName
```
`BUFFER_SIZE` determines how many bytes are read from the file descriptor at each `read()` call.
Different values should produce the same behavior while potentially affecting performance.

### Bonus

Supports reading from multiple file descriptors simultaneously by maintaining independent state for each descriptor.
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c -o ProgramName
```


### Using
To use `get_next_line` in your own C project you can use this example:
```c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}
```

## Resources / References

- https://man7.org/linux/man-pages/man2/open.2.html
- https://man7.org/linux/man-pages/man2/read.2.html
- https://medium.com/@beatrizbazaglia/get-next-line-3872eb3189e6


### AI Usage

AI tools were used for:

- Clarifying function specifications and expected behavior.
- Assisting with the creation of this readme.

## Algorithm Explanation & Justification

This project utilizes a **Linked List architecture integrated with a Tail Pointer** to manage memory and buffer reads dynamically.

**The Problem (Why not string concatenation?):**
The most common approach to solving the *Get Next Line* problem is to read chunks of a file and continuously concatenate them using a function like `strjoin` (you can check the "old-main" branch with this version). However, this introduces a severe performance bottleneck. With small buffer sizes (e.g., `BUFFER_SIZE=1`), appending to a string requires allocating a new, larger block of memory and copying the entire history of previously read characters over and over. This results in an inefficient time complexity of $O(N^2)$. 

**The Solution:**
To bypass this limitation, this algorithm entirely avoids intermediate concatenations. Instead, every time a new buffer is read, it is simply stored inside a new node of a linked list. The characters are only consolidated into a single, contiguous string at the very end, exactly once, when a newline (`\n`) or EOF is encountered. 

**The Tail Pointer Optimization:**
While a standard linked list prevents continuous memory copying, appending a new node normally requires traversing the entire list to find the end, which would still create an $O(N)$ bottleneck per read operation. To solve this, a **tail pointer** is maintained to track the last node. This allows the algorithm to append new buffer nodes instantly, achieving an $O(1)$ insertion time regardless of the list's size.

**Conclusion:**
By combining a linked list with a tail pointer, the algorithm executes lightning-fast reads with a final time complexity of $O(N)$. It drastically reduces system calls (`malloc`) and memory copies, proving exceptionally resilient and fast even when processing massive files byte-by-byte.