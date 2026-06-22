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