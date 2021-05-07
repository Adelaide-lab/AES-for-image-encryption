#include <stdio.h>
#include "file_encrp.h"

int main() { 

	FILE *fpin,*fpout;

	fpin=fopen("D:\\c1.bmp","rb"); /*path to your original file*/
	fpout=fopen("D:\\c2.bmp","wb+");/*path to the file you create*/

	encrypt_to_bmp(fpin,fpout);
	
	fclose(fpin);
	fclose(fpout);
	
	fpin=fopen("D:\\c2.bmp","rb");
	fpout=fopen("D:\\c3.bmp","wb+");
	
	deencrpt_to_bmp(fpout,fpin);

	fclose(fpin);
	fclose(fpout);

	return 0;
}
