#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;

bool is_jpg_header(uint8_t buffer[]);
void close_file(FILE *current_file);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image \n");
        return 1;
    }

    //opens the file into a pointer variable file
    FILE *file = fopen(argv[1], "r");

    //error checks file
    if (file == NULL)
    {
        printf("Unable to open file: %s\n", argv[1]);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    size_t bytes_read;
    bool is_first_jpg = false;
    FILE *current_file;
    char filename[10]; // xxx.jpg\0 need 8 for null-terminating character
    int jpg_count = 0;
    bool jpg_found = false;

    while (true)
    {
        // due to FAT file system we can read 512 into buffer at one time
        bytes_read = fread(buffer, sizeof(BYTE), BLOCK_SIZE, file);
        if (bytes_read == 0)
        {
            //if 0 we are at the end of the file
            break;
        }

        if (is_jpg_header(buffer))
        {
            jpg_found = true;
            //if all true we have a jpg. start of file will always give picture type info
            if (!is_first_jpg)
            {
                //skips next block on first jpg being found
                is_first_jpg = true;
            }
            else
            {
                //close current file and open new file
                close_file(current_file);
            }
            //formats a string and sends it to a pointer
            sprintf(filename, "%03i.jpg", jpg_count);
            current_file = fopen(filename, "w");
            jpg_count++;
        }
        if (jpg_found)
        {
            fwrite(buffer, sizeof(BYTE), bytes_read, current_file);
        }
    }
    fclose(file);             //close raw file
    close_file(current_file); //close the last file opened
    return 0;
}

bool is_jpg_header(uint8_t buffer[])
{
    return buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;
}

void close_file(FILE *current_file)
{
    fclose(current_file);
}