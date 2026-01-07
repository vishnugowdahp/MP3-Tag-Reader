/*
*   Functions to read and display MP3 tag information (ID3 v2.3).
*   Steps :
*     1. Open the audio file which is in mp3 format
*     2. Verify if it's in required format
*     3. Read the file by skipping the header
*     4. Then the file info is displayed
*     5. At last close the file
*/

#include "header_file.h"
/* 
 * Read the next tag (4 bytes)
*/

void get_tag(struct Song *info, FILE *fptr)
{
    fread(info->tag, 4, 1, fptr);
    info->tag[4] = '\0';   // Null-terminate
}

/* 
 * Read the size of the frame (4 bytes) and convert endianess
*/
void get_size(struct Song *info, FILE *fptr)
{
    fread(&info->size, 4, 1, fptr);
    convert_size(&(info->size));
}

/*
* Convert 4-byte integer between big-endian and little-endian
*/
void convert_size(int *size)
{
    char *b = (char*)size;
    for (int i = 0; i < 2; i++)
    {
        char temp = b[i];
        b[i] = b[3 - i];
        b[3 - i] = temp;
    }
}

/* 
 * Read frame data (text/info stored in tag)
 */
void get_data(struct Song *info, FILE *fptr)
{
    fread(info->data, info->size - 1, 1, fptr);
    info->data[info->size - 1] = '\0';
}

/* 
 * Display all MP3 tag information
*/
void show_mp3_info(char *file, struct Song *info)
{
    printf("\n====== MP3 Tag Reader and Editor =======\n");
    printf("------------- Version: 2.3 ---------------\n");

    FILE *fptr = fopen(file, "r");
    if (fptr == NULL)
    {
        printf("Error: File not found.\n");
        return;
    }

    // Skip 10-byte ID3 header
    fseek(fptr, 10, SEEK_SET);

    for (int i = 0; i < 6; i++)
    {
        get_tag(info, fptr);

        if (strcmp(info->tag, "TIT2") == 0)
            printf("\tTitle   -> ");
        else if (strcmp(info->tag, "TALB") == 0)
            printf("\tAlbum   -> ");
        else if (strcmp(info->tag, "TPE1") == 0)
            printf("\tArtist  -> ");
        else if (strcmp(info->tag, "TYER") == 0)
            printf("\tYear    -> ");
        else if (strcmp(info->tag, "COMM") == 0)
            printf("\tGenre   -> ");
        else if (strcmp(info->tag, "TCON") == 0)
            printf("\tContent -> ");

        // Read size, skip flags, then read data
        get_size(info, fptr);
        fseek(fptr, 3, SEEK_CUR);
        get_data(info, fptr);

        printf("%s\n", info->data);
    }
    fclose(fptr);
}