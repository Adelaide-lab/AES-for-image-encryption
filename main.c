#include <stdio.h>
#include "file_encrp.h"



int main() { 

	FILE *fpin,*fpout;

	fpin=fopen("D:\\dachuang\\AES_picture\\c1.bmp","rb");
	fpout=fopen("D:\\dachuang\\AES_picture\\c2.bmp","wb+");

	encrypt_to_bmp(fpin,fpout);
	
	fclose(fpin);
	fclose(fpout);
	
	fpin=fopen("D:\\dachuang\\AES_picture\\c2.bmp","rb");
	fpout=fopen("D:\\dachuang\\AES_picture\\c3.bmp","wb+");
	
	deencrpt_to_bmp(fpout,fpin);

	fclose(fpin);
	fclose(fpout);

	return 0;
}
