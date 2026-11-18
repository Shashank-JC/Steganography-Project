/*Name = SHASHANK J C
  Date = 12/11/2026
  Batch id = 26018f
  Steganography
  Steganography is a technique of hiding secret information inside an image
 * using the Least Significant Bit (LSB) method without visibly altering the image.
 * This project supports encoding and decoding secret files within BMP images.
 */
#include <stdio.h>
#include "encode.h"
#include "decode.h"
#include "types.h"
#include<string.h>
#include "common.h"
OperationType check_operation_type(char *);

int main(int argc, char *argv[]) // .aout -e <source_file> <secret_data_file> <optional>
{
   if(argc<2)
   {
    fprintf(stderr,RED "error: No argument is found\n" RESET);
    printf("please provide arguments like\n./a.out -e/-d <source_file> <secret_data_file> <optional>\n ");
    return e_failure;
   }                                        
   if(check_operation_type(argv[1])==e_encode)     
   {                       
   EncodeInfo encInfo;     
   if(argc>5)
   {
   fprintf(stderr,RED "error: TOO many arguments\n" RESET);
    return e_failure;
   }
   else if(argc<4)
   {
     fprintf(stderr,RED "error: required argument is not there\n" RESET);
    return e_failure;
   }
   char* extn=strrchr(argv[3],'.');
   strcpy(encInfo.extn_secret_file,extn);
   if(read_and_validate_encode_args(argv, &encInfo)==e_success)
   {
     printf("Succefully read and validated encode arguments\n");
   }
   else
   {
     fprintf(stderr,RED "error: failure to read and validate encode arguments\n" RESET);
     return e_failure;
   }
   if(do_encoding(&encInfo)==e_success)
   {
    printf("Successfully encoded\n");
    return 0;
   }
   else
   {
     fprintf(stderr,RED "error: failure to encode data\n" RESET);
     return e_failure;
   }
   }
   else if(check_operation_type(argv[1])==e_decode)
   {
    DecodeInfo decInfo;
    if(argc>4)
   {
    fprintf(stderr,RED "error: TOO many arguments\033[0m\n" RESET);
    return e_failure;
   }
   else if(argc<3)
   {
     fprintf(stderr,RED "error: required argument is not there\n" RESET);
    return e_failure;
   }
   if(read_and_validate_decode_args(argv, &decInfo)==e_success)
   {
     printf("Succefully read and validated decode arguments\n");
   }
   else
   {
     fprintf(stderr,RED "error: failure to read and validate decode arguments\n" RESET);
     return e_failure;
   }
   if(do_decoding(&decInfo)==e_success)
   {
    printf("Successfully decoded\n");
    return 0;
   }
   else
   {
     fprintf(stderr,RED "error: failure to decode data\n" RESET);
     return e_failure;
   }

   }
   else if(check_operation_type(argv[1])==e_unsupported)
   {
     fprintf(stderr,RED "error: command is unsupported\n" RESET);
     return e_failure;
   }
                                                                                                 
    //step 1 -> check check_operation_type(argv[1]) is returning e_encode or not
        // yes -> EncodeInfo encInfo; 
            // check read_and_validate_encode_args(argv, &encInfo) is returning e_success or e_failure
                // failure -> print error msg and stop
                // success -> print success msg 
                            // check do_encoding(&encInfo) is returning e_success or e_failure
                                    // failure -> print error msg and stop
                                    // success -> print success msg and stop
}

OperationType check_operation_type(char *symbol)
{
    if(strcmp(symbol,"-e")==0)
    {
        return e_encode;
    }
    else if(strcmp(symbol,"-d")==0)
    {
        return e_decode;
    }
    else
    {
       return e_unsupported; 
    }
    //step 1 -> check symbol is -e or not
        // yes -> return e_encode
    
    // step 2 -> check symbol is -d or not
        // yes -> return e_decode

    // return e_unsupported

}
