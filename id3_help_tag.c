/*
 *  Displays usage instructions for MP3 Tag Reader and Editor
 */

#include "header_file.h"

void show_help()
{
    printf("\n============ MP3 Tag Reader and Editor ============\n");
    printf("Options:\n");
    printf("\t  -v <file.mp3>               View MP3 tags\n");
    printf("\t  -e <file.mp3> -tag <value>  Edit specific tag\n");
    printf("\t  -h                          Show help menu\n");

    printf("\n   Supported tags for editing:\n");
    printf("  -t : Title\n");
    printf("  -A : Album\n");
    printf("  -a : Artist\n");
    printf("  -y : Year\n");
    printf("  -C : Genre\n");
    printf("  -c : Content\n");
}
