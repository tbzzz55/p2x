#ifndef __PT_H
#define __PT_H

#include <stdlib.h>
#include <string.h>

#include <zlib.h>
#include <tomcrypt.h>

void *dec1(unsigned char *buff, unsigned int len);
void *dec2(unsigned char *buff, unsigned int len);

void *enc1(unsigned char *buff, unsigned int len);
void *enc2(unsigned char *buff, unsigned int len);

void *z_com(unsigned char *data, unsigned int len, unsigned int *size);
void *z_dec(unsigned char *data, unsigned int len, unsigned int *size);

void *twofish_eax_dec(unsigned char *data, unsigned int len, unsigned int *size, char *key, char *iv);
void *twofish_eax_enc(unsigned char *data, unsigned int len, unsigned int *size, char *key, char *iv);

#endif