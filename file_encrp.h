#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#ifndef _FILE_ENCRYP_H_
#define _FILE_ENCRYP_H_

void *encrypt_to_bmp(FILE *fpin,FILE *fpout);

void *deencrpt_to_bmp(FILE *fpout,FILE *fpin);

#endif
