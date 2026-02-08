#include "p2x.h"

void p2x_close(struct pkt2xml *ptr) {
	if (!ptr) {
		return;
	}
	
	if (ptr->buffer) {
		free(ptr->buffer);
	}
	
	free(ptr);
}

void *p2x_buff(unsigned char *buff, unsigned int size) {
	if (!buff || size < 1) {
		return NULL;
	}
	
	struct pkt2xml *p2x = calloc(1, sizeof(struct pkt2xml));
	
	if (!p2x) {
		return NULL;
	}
	
	if (!(p2x->buffer = malloc((p2x->size = size)))) {
		p2x_close(p2x);
		return NULL;
	}
	
	memcpy(p2x->buffer, buff, size);
	
	memset(p2x->key, 0x89, 16);
	memset(p2x->iv, 0x10, 16);
	
	return p2x;
}

void *p2x_open(char *filename) {
	if (!filename) {
		return NULL;
	}
	
	FILE *fp = fopen(filename, "rb");
	
	if (!fp) {
		return NULL;
	}
	
	struct pkt2xml *p2x = calloc(1, sizeof(struct pkt2xml));
	
	if (!p2x) {
		goto _ERR;
	}
	
	fseek(fp, 0, SEEK_END);
	p2x->size = ftell(fp);
	rewind(fp);
	
	if (!(p2x->buffer = malloc(p2x->size))) {
		p2x_close(p2x);
		goto _ERR;
	}
	
	if (fread(p2x->buffer, 1, p2x->size, fp) != p2x->size) {
		p2x_close(p2x);
		goto _ERR;
	}
	
	fclose(fp);
	
	memset(p2x->key, 0x89, 16);
	memset(p2x->iv, 0x10, 16);

	return p2x;
	
	_ERR:
	fclose(fp);
	return NULL;
}

int p2x_unpack(struct pkt2xml *p2x, unsigned char **xml, unsigned int *xml_size) {
	if (!p2x || !xml || !xml_size || !p2x->buffer || p2x->size < 1) {
		return 0;
	}
	
	unsigned char *dec1buf = dec1(p2x->buffer, p2x->size);
	
	if (!dec1buf) {
		return 0;
	}
	
	unsigned int fishlen = 0;
	unsigned char *fishdec = twofish_eax_dec(dec1buf, p2x->size, &fishlen, p2x->key, p2x->iv);
	
	if (!fishdec) {
		free(dec1buf);
		return 0;
	}
	
	free(dec1buf);
	
	unsigned char *dec2buf = dec2(fishdec, fishlen);
	
	if (!dec2buf) {
		free(fishdec);
		return 0;
	}
	
	free(fishdec);
	
	*xml_size = 0;
	if (!(*xml = z_dec(dec2buf, fishlen, xml_size))) {
		free(dec2buf);
		return 0;
	}
	
	free(dec2buf);
	return 1;
}

int p2x_pack(struct pkt2xml *p2x, unsigned char **pkt, unsigned int *pkt_size) {
	if (!p2x || !pkt || !pkt_size || !p2x->buffer || p2x->size < 1) {
		return 0;
	}
	
	unsigned int comsz = 0;
	unsigned char *comp = z_com(p2x->buffer, p2x->size, &comsz);
	
	if (!comp) {
		return 0;
	}
	
	unsigned char *enc1buf = enc1(comp, comsz);
	
	if (!enc1buf) {
		free(comp);
		return 0;
	}
	
	free(comp);
	
	unsigned int fishencsz = 0;
	unsigned char *fishenc = twofish_eax_enc(enc1buf, comsz, &fishencsz, p2x->key, p2x->iv);
	
	if (!fishenc) {
		free(enc1buf);
		return 0;
	}
	
	free(enc1buf);
	
	*pkt_size = fishencsz;
	if (!(*pkt = enc2(fishenc, fishencsz))) {
		free(fishenc);
		return 0;
	}
	
	free(fishenc);
	return 1;
}