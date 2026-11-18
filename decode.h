#ifndef DECODE_H
#define DECODE_H
#include <stdio.h>

#include "types.h"
typedef struct _DecodeInfo  
{
    char *stego_image_fname;
    char *output_fname;

    FILE *fptr_stego_image;
    FILE *fptr_output;

    char extn_secret_file[10];
    char* output_name;
    long size_secret_file;

} DecodeInfo;
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);  // read and validating command line arguments
Status do_decoding(DecodeInfo *decInfo);    // decoding function
Status decode_secret_file_data(long file_size, DecodeInfo *decInfo);   // decoding secret file data function
Status decode_secret_file_size(long *file_size, DecodeInfo *decInfo);  // decoding secret file size function
Status decode_secret_file_extn(int size, DecodeInfo *decInfo);         // decoding secret file extension function
Status decode_secret_file_extn_size(int *size, DecodeInfo *decInfo);   // decoding secret file extension size function
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo);   // decoding magic string function
Status decode_size_from_lsb(char *imageBuffer, int *size);  // decoding size form lsb
Status decode_byte_from_lsb(char *image_buffer, char *data);   // decoding bytes from lsb
Status open_dfiles(DecodeInfo *decInfo);   //file opening function

#endif