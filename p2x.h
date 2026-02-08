#ifndef __P2X_H
#define __P2X_H

#include "pt.h"

struct pkt2xml {
	char *buffer;
	unsigned int size;
	
	unsigned char key[16];
	unsigned char iv[16];
};

void *p2x_open(char *filename);
void *p2x_buff(unsigned char *buff, unsigned int size);
void p2x_close(struct pkt2xml *ptr);

int p2x_pack(struct pkt2xml *p2x, unsigned char **pkt, unsigned int *pkt_size);
int p2x_unpack(struct pkt2xml *p2x, unsigned char **xml, unsigned int *xml_size);

#endif