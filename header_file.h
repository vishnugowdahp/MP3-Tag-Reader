/*
 * Header file for MP3 Tag Reader and Editor project.
 * Contains structure definitions and function declarations.
 */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>

/* 
 * Structure to hold MP3 tag info (ID3 v2.3)
 */
struct Song
{
    char tag[5];      // Tag name (ex : TIT2, TALB, TPE1, TYER)
    int size;         // Frame size
    char flag[3];     // Frame flags
    char data[600];   // Frame data (title, artist, etc.)
};

/* Utility */
void convert_size(int *size);

/* Read operations */
void get_tag(struct Song *info, FILE *fptr);
void get_size(struct Song *info, FILE *fptr);
void get_data(struct Song *info, FILE *fptr);
void show_mp3_info(char *file, struct Song *info);

/* Write operations */
void modify_mp3_info(char *file, char *option, char *new1, struct Song *info);

/* Help menu */
void show_help();

/* Validation */
int valid_view(int argc, char *argv);
int valid_edit(int argc, char *argv);
int valid_help(int argc, char *argv);

#endif
