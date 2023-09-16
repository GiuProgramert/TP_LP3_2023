#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

char *read_from_file(const char *filename, size_t length)
{
    char *buffer;
    int fd;
    ssize_t bytes_read;
    /* Allocate the buffer. */
    buffer = (char *)malloc(length);
    if (buffer == NULL)
        return NULL;
    /* Open the file. */
    fd = open(filename, O_RDONLY);
  
    if (fd == -1)
    {
        /* open failed. Deallocate buffer before returning. */
        free(buffer);
        return NULL;
    }
    /* Read the data. */
    bytes_read = read(fd, buffer, length);
  
    /* Everything's fine. Close the file and return the buffer. */
    close(fd);
    return buffer;
}

int main()
{
    const char *filename = "archivo.txt"; // archivo, se modifica
    size_t length = 100;                  // bits a leer

    char *data = read_from_file(filename, length);
  
    if (data != NULL)
    {
        
        printf("Data read from file: %s\n", data);

        // liberar la memoria
        free(data);
    }
    else
    {
        printf("Error reading from file.\n");
    }

    return 0;
}