#include "file_encrp.h"
#include "aes.h"
#define SIZE 16

/* fixed code for the first 54 bytes data, these datas save the basic information for bmp file, which we don't need encrypt */
    uint8_t soi[54];
	
/* input plainmessage for 128 bits*/
    uint8_t in[SIZE];
    
/* output code after encryption*/		
	uint8_t out[SIZE]; 	
					
/* 128 bits key */
	uint8_t key[] = {
		0xa0, 0x88, 0x23, 0x2a, 
		0xfa, 0x54, 0xa3, 0x6c, 
		0xfe, 0x2c, 0x39, 0x76, 
		0x17, 0xb1, 0x39, 0x05}; 
		
/* 128 bits last byte code
	Note that if (size-54) can't be divided by 16
	we need extra proccess to deal with the last few bytes					
						*/
	uint8_t last[] = {
		0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00};
	
void *encrypt_to_bmp(FILE *fpin,FILE *fpout)
{
	/* expanded key for 128 bits*/
	uint8_t *w = aes_init(sizeof(key));
	aes_key_expansion(key, w);
	
	uint8_t i;
	
	long int j;			
	/*
	basic information for the file we want to encrypt
	we can gain the memory size of the file, it is vital in later processing procedure
	*/
	fseek(fpin, 0, SEEK_END);
    long int size = ftell(fpin);
    long int newsize = (size-54)/16;
    int mode = (size-54)%16;
    
    rewind(fpin);
    
    printf("get the size is: %ld\n", size);
    
    fread(soi,sizeof(unsigned char),54,fpin);
   	fwrite(soi,sizeof(unsigned char),54,fpout);
   

	for(j=0;j<newsize;j++)
	{
		fread(in,sizeof(unsigned char),SIZE,fpin);
		aes_cipher(in /* in */, out /* out */, w /* expanded key */);
		fwrite(out,sizeof(unsigned char),SIZE,fpout);
	}
	
	if(mode)
	{
		fread(last,sizeof(unsigned char),mode,fpin);
		aes_cipher(last /* in */, out /* out */, w /* expanded key */);
		fwrite(out,sizeof(unsigned char),mode,fpout);
	}
	free(w);
}

void *deencrpt_to_bmp(FILE *fpout,FILE *fpin)
{
	/* expanded key for 128 bits*/
	uint8_t *w = aes_init(sizeof(key));
	aes_key_expansion(key, w);
	
	uint8_t i;
	
	long int j;
	
	fseek(fpin, 0, SEEK_END);
    long int size = ftell(fpin);
    long int newsize = (size-54)/16;
    int mode = (size-54)%16;
    
    rewind(fpin);
    printf("get the size is: %ld\n", size);
    
	if(fpin==NULL)
	{
		printf("Open File Failing!");
		exit(0);	
				}
				
	fread(soi,sizeof(unsigned char),54,fpin);
   	fwrite(soi,sizeof(unsigned char),54,fpout);
	
	for(j=0;j<newsize;j++)
	{
		fread(out,sizeof(unsigned char),SIZE,fpin);
		aes_inv_cipher(out, in, w);
		fwrite(in,sizeof(unsigned char),SIZE,fpout);
	}
	
		if(mode)
	{
		fread(last,sizeof(unsigned char),mode,fpin);
		aes_inv_cipher(last, in, w);
		fwrite(in,sizeof(unsigned char),mode,fpout);
	}
	
	free(w);
}

	
