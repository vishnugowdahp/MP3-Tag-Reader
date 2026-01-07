/*
 *  Functions to modify MP3 tag information (ID3 v2.3)
    Here we aren't editing the actual original mp3 file but copy it to new file in mp3 format
    This is done to avoid truncating original mp3 file if opened in write format
    Steps :
     1. Open two files one is original mp3 file and a temporary mp3 file(temp.mp3 in this case)
     2. Copy each and every info from original mp3 file to temp.mp3 
     3. In the same process user can edit the desired info by copying new values parallely
     4. Then the temporary file is displayed
     5. Temporary file is renamed with original file name
     6. At last close both the files
 */

#include "header_file.h"

/* 
 * Edit and update tag in MP3 file
 */
void modify_mp3_info(char *file, char *option, char *new1, struct Song *info)
{
    char tag[5];

    // Map user option to tag
    if (strcmp(option, "-t") == 0)
        strcpy(tag, "TIT2");
    else if (strcmp(option, "-A") == 0)
        strcpy(tag, "TALB");
    else if (strcmp(option, "-a") == 0)
        strcpy(tag, "TPE1");
    else if (strcmp(option, "-y") == 0)
        strcpy(tag, "TYER");
    else if (strcmp(option, "-C") == 0)
        strcpy(tag, "COMM");
    else if (strcmp(option, "-c") == 0)
        strcpy(tag, "TCON");
    else
    {
        printf("Invalid tag option.\n");
        printf("Valid tags: -t (title), -A (album), -a (artist), -y (year), -C (genre), -c (content)\n");
        return;
    }

    FILE *in = fopen(file, "r");
    if (in == NULL)
    {
        printf("Error: File not found.\n");
        return;
    }

    FILE *out = fopen("temp.mp3", "w");

    char buffer[10];
    fread(buffer, 10, 1, in);
    fwrite(buffer, 10, 1, out);

    for (int i = 0; i < 6; i++)
    {
        get_tag(info, in);
        get_size(info, in);
        fread(info->flag, 3, 1, in);
        get_data(info, in);

        if (strcmp(tag, info->tag) == 0)  // if tag matches then replace the values accordingly
        {
            fwrite(info->tag, 4, 1, out);

            int size = strlen(new1) + 1;
            int temp_size = size;
            convert_size(&size);

            fwrite(&size, 4, 1, out);
            fwrite(info->flag, 3, 1, out);
            fwrite(new1, temp_size - 1, 1, out);

            printf("Tag updated successfully!\n");
            break;
        }
        else
        {
            fwrite(info->tag, 4, 1, out);

            int temp_size = info->size;
            convert_size(&(info->size));

            fwrite(&info->size, 4, 1, out);
            fwrite(info->flag, 3, 1, out);
            fwrite(info->data, temp_size - 1, 1, out);
        }
    }

    // Copy rest of the info to the temp file
    char copy[1024];
    int rb;
    while ((rb = fread(copy, 1, sizeof(copy), in)) > 0)
    {
        fwrite(copy, 1, rb, out);
    }

    fclose(in);
    fclose(out);

    remove(file);
    rename("temp.mp3", file);
}
