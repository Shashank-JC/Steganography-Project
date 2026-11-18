#include<stdio.h>
#include "decode.h"
#include "types.h"
#include "common.h"
#include<string.h>

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    if(strstr(argv[2], ".bmp") != NULL)     // Read and validating input commands 
    {                                       //source file having bmp extension or not 
        decInfo->stego_image_fname = argv[2];
    }
    else
    {
        return e_failure;
    }

    if(argv[3] != NULL)                // checking user given output file not if not create new decoded file or create user given name file
    {
        decInfo->output_name = argv[3];
    }
    else
    {
        decInfo->output_name = "decoded";
    }

    return e_success;
}
Status do_decoding(DecodeInfo *decInfo)
{
    if(open_dfiles(decInfo) != e_success)
    {                                                           // opening the source file
        fprintf(stderr,RED"Unable to open files\n"RESET);
        return e_failure;
    }

    if(decode_magic_string(MAGIC_STRING, decInfo) != e_success)
    {
        fprintf(stderr,RED"Magic string doesn't match\n"RESET);   // checking magic string is matched or not
        return e_failure;
    }

    int extn_size;

    decode_secret_file_extn_size(&extn_size, decInfo);   

    decode_secret_file_extn(extn_size, decInfo);

    long file_size;

    decode_secret_file_size(&file_size, decInfo);

    if(decode_secret_file_data(file_size, decInfo) != e_success)
    {
        return e_failure;                           
    }

    printf("Successfully decoded the data\n");

    return e_success;
}
Status decode_secret_file_data(long file_size, DecodeInfo *decInfo)
{
    char buffer[8];
    char data;                               // decoding the file data

    for(long i = 0; i < file_size; i++)
    {
        fread(buffer, sizeof(char), 8, decInfo->fptr_stego_image);   // reading 8 byte from sourcefile and storing in buffer array

        decode_byte_from_lsb(buffer, &data);   // passing to decode byte from lsb function 

        fwrite(&data, sizeof(char), 1, decInfo->fptr_output);  //writing the decoded data in output file
    } 

    return e_success;
}
Status decode_secret_file_size(long *file_size, DecodeInfo *decInfo)
{
    char buffer[32];                               // decoding secret file size

    fread(buffer, sizeof(char), 32, decInfo->fptr_stego_image);  //reading 32byte from source file and storing in buffer array

    int size;
    decode_size_from_lsb(buffer, &size);   // passing buffer array to function to decode the size

    *file_size = size;   // storing the size in file size

    return e_success;
}
Status decode_secret_file_extn(int size, DecodeInfo *decInfo)
{
    char buffer[8];
    char data;              // decoding secret file extension 

    for(int i = 0; i < size; i++)
    {
        fread(buffer, sizeof(char), 8, decInfo->fptr_stego_image);  

        decode_byte_from_lsb(buffer, &data);

        decInfo->extn_secret_file[i] = data;
    }

    decInfo->extn_secret_file[size] = '\0';
   
     char file[100];
     strcpy(file,decInfo->output_name);
     decInfo->output_fname = strcat(file,decInfo->extn_secret_file);   // concatenating file name and file extension
    decInfo->fptr_output = fopen(decInfo->output_fname, "w");   // opening the output file
    return e_success;
}

Status decode_secret_file_extn_size(int *size, DecodeInfo *decInfo)
{                                 
    char buffer[32];                        // decoding secret file extension size

    fread(buffer, sizeof(char), 32, decInfo->fptr_stego_image);

    decode_size_from_lsb(buffer, size);

    return e_success;
}
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo)
{
    char buffer[8];
    char data;
    fseek(decInfo->fptr_stego_image,54,SEEK_SET);     // decoding magic string 
    for(int i = 0; i < strlen(magic_string); i++)
    {
        fread(buffer, sizeof(char), 8, decInfo->fptr_stego_image);
        decode_byte_from_lsb(buffer, &data);

        if(data != magic_string[i])
        {
            return e_failure;
        }
    }

    return e_success;
}
Status decode_size_from_lsb(char *imageBuffer, int *size)
{
    *size = 0;
                                          // decoding 32 bytes from lsb
    for(int i = 0; i < 32; i++)
    {
        int bit = imageBuffer[i] & 1;
        *size = *size | (bit << i);
    }

    return e_success;
}
Status decode_byte_from_lsb(char *image_buffer, char *data)
{
    *data = 0;
                               // decoding 8 bytes from lsb
    for(int i = 0; i < 8; i++)
    {                                       
        char bit = image_buffer[i] & 1;
        *data = *data | (bit << i);
    }

    return e_success;
}
Status open_dfiles(DecodeInfo *decInfo)
{
    decInfo->fptr_stego_image =
        fopen(decInfo->stego_image_fname, "r");    

    if(decInfo->fptr_stego_image == NULL)
    {
        return e_failure;
    }

    // decInfo->fptr_output =
    //     fopen(decInfo->output_fname, "w");

    // if(decInfo->fptr_output == NULL)
    // {
    //     fclose(decInfo->fptr_stego_image);
    //     return e_failure;
    // }

    return e_success;
}