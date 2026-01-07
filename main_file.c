/*
 *      Author : Vishnu Gowda H P
        Date : 05/01/26
        Description : The program that help user to view or edit the file tags in .mp3 files 
        Prerequisits : Arrays, Structures, Functions, Files concepts, mp3-tags and 2D array concepts
        Sample input : ./a.out -v
        Sample output : === MP3 Tag Reader and Editor ===
                        --- Version: 2.3 ---
                        Title   -> Pudhu_vellai_mazhai
                        Artist  -> AR_Rahaman
                        Album   -> Roja
                        Year    -> 1995
                        Content -> Chithra,Hariharan
                        Genre   -> Romantic
        Sample input : ./a.out
        Sample output : Error: Not enough arguments :(

                        ============ MP3 Tag Reader and Editor ============
                        Options:
                                  -v <file.mp3>               View MP3 tags
                                  -e <file.mp3> -tag <value>  Edit specific tag
                                  -h                          Show help menu

                            Supported tags for editing:
                            -t : Title
                            -A : Album
                            -a : Artist
                            -y : Year
                            -C : Genre
                            -c : Content
        Sample input : ./a.out -h
        Sample output : 
                        ============ MP3 Tag Reader and Editor ============
                        Options:
                                  -v <file.mp3>               View MP3 tags
                                  -e <file.mp3> -tag <value>  Edit specific tag
                                  -h                          Show help menu

                            Supported tags for editing:
                            -t : Title
                            -A : Album
                            -a : Artist
                            -y : Year
                            -C : Genre
                            -c : Content
        Sample input : ./a.out -v
        Sample output : Invalid argument!!!
                        Hints:  -v (view), -e (edit), -h (help)
        Sample input : ./a.out -v file.c
        Sample output : Error: Please provide a .mp3 file !!!
        Sample input : ./a.out -v file.c -e sample.mp3
        Sample output : Error: View requires exactly 3 arguments :(
 */

#include "header_file.h"

/* 
 * Validate arguments for view option 
 * Usage: ./a.out -v <file.mp3>
 */
int valid_view(int argc, char *argv)
{
    if (argc == 3)
    {
        if (strstr(argv, ".mp3"))
        {
            return 0;
        }
        else
        {
            printf("Error: Please provide a .mp3 file !!!\n");
            return 1;
        }
    }
    printf("Error: View requires exactly 3 arguments :(\n");
    return 1;
}

/* 
 * Validate arguments for edit option 
 * Usage: ./a.out -e <file.mp3> -tag new_value
 */
int valid_edit(int argc, char *argv)
{
    if (argc == 5)
    {
        if (strstr(argv, ".mp3"))
        {
            return 0;
        }
        else
        {
            printf("Error: Please provide a .mp3 file!!!\n");
            return 1;
        }
    }
    printf("Error: Edit requires exactly 5 arguments!!!\n");
    return 1;
}

/* 
 * Validate arguments for help option 
 * Usage: ./a.out -h
 */
int valid_help(int argc, char *argv)
{
    if (argc == 2)
    {
        return 0;
    }
    printf("Error: Help requires exactly 2 arguments!!!\n");
    return 1;
}

/* 
 * Main function
 */
int main(int argc, char *argv[])
{
    struct Song songInfo;

    if (argc >= 3)
    {
        if (strcmp(argv[1], "-v") == 0)     // View option
        {
            if (valid_view(argc, argv[2]) == 0)
            {
                printf("======== View Option Selected =========\n");
                show_mp3_info(argv[2], &songInfo);
            }
        }
        else if (strcmp(argv[1], "-e") == 0)   // Edit option
        {
            if (valid_edit(argc, argv[2]) == 0)
            {
                printf("=========Edit Option Selected ========\n");
                modify_mp3_info(argv[2], argv[3], argv[4], &songInfo);
                printf("===== After editing =====");
                show_mp3_info(argv[2], &songInfo);
            }
        }
        else
        {
            printf("Error: Unknown option!!!\n");
            show_help();
        }
    }
    else if (argc >= 2)
    {
        if (strcmp(argv[1], "-h") == 0)   //Help option
        {
            if (valid_help(argc, argv[1]) == 0)
            {
                show_help();
            }
        }
        else
        {
            printf("Invalid argument!!!\n");
            printf("Hints:  -v (view), -e (edit), -h (help)\n");
        }
    }
    else
    {
        printf("Error: Not enough arguments :(\n");
        show_help();
    }
    return 0;
}
