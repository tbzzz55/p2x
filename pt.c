#include "pt.h"

void *dec1(unsigned char *buff, unsigned int len) {
	if (!buff || len < 1) {
		return NULL;
	}
	
	unsigned char *ret = malloc(len);
	
	if (!ret) {
		return NULL;
	}
	
	for (int i = 0; i < len; i++) {
		ret[i] = (char)((unsigned char)((signed char)(1 - (char)i) * (signed char)len) ^ (unsigned char)buff[len - i - 1]);
	}
	
	return ret;
}

void *dec2(unsigned char *buff, unsigned int len) {
	if (!buff || len < 1) {
		return NULL;
	}
	
	unsigned char *ret = malloc(len);
	
	if (!ret) {
		return NULL;
	}
	
	for (int i = 0; i < len; i++) {
		ret[i] = (unsigned char)((len - i) ^ (unsigned int)buff[i]);
	}
	
	return ret;
}

void *enc1(unsigned char *buff, unsigned int len) {
	if (!buff || len < 1) {
		return NULL;
	}
	
	unsigned char *ret = malloc(len);
	
	if (!ret) {
		return NULL;
	}
	
	for (int i = 0; i < len; i++) {
		ret[i] = (unsigned char)((len - i) ^ (unsigned int)buff[i]);
	}
	
	return ret;
}

void *enc2(unsigned char *buff, unsigned int len) {
	if (!buff || len < 1) {
		return NULL;
	}
	
	unsigned char *ret = malloc(len);
	
	if (!ret) {
		return NULL;
	}
	
	for (int i = 0; i < len; i++) {
		ret[len - i - 1] = buff[i] ^ (len - (i * len));
	}
	
	return ret;
}

void *z_com(unsigned char *data, unsigned int len, unsigned int *size) {
	if (!data || len < 1 || !size) {
		return NULL;
	}
	
	unsigned char *buf = malloc((*size = len + len / 100 + 13));
	
	if (!buf) {
		return NULL;
	}
	
	if (compress(buf, (uLongf*)size, data, len) != Z_OK) {
		free(buf);
		return NULL;
	}
	
	*size += 4;
	
	if (!(buf = realloc(buf, *size))) {
		return NULL;
	}
	
	memmove(buf + 4, buf, *size - 4);
	*((unsigned int*)(buf)) = (unsigned int)__builtin_bswap32(len);
	
	return buf;
}

void *z_dec(unsigned char *data, unsigned int len, unsigned int *size) {
	if (!data || len < 1 || !size) {
		return NULL;
	}
	
	uLongf destLen = __builtin_bswap32(*(unsigned int*)(data));
	unsigned char *buf = malloc(destLen);

	if (!buf) {
		return NULL;
	}
	
	if (uncompress(buf, &destLen, (const Bytef*)(data + 4), len - 4) != Z_OK) {
		free(buf);
		return NULL;
	}
	
	*size = destLen;
	
	return buf;
}

void *twofish_eax_dec(unsigned char *data, unsigned int len, unsigned int *size, char *key, char *iv) {
	if (!data || len < 1 || !size || !key || !iv) {
		return NULL;
	}

	if (register_cipher(&twofish_desc) != CRYPT_OK) {
		return NULL;
	}
	
	int twofish = find_cipher("twofish");
	
	unsigned char *dec = malloc((*size = len - 16));
	int res = 0;
	
	if (!dec) {
		return NULL;
	}
	
	if (eax_decrypt_verify_memory(twofish, key, 16, iv, 16, NULL, 0, data, *size, dec, data + len - 16, 16, &res) != CRYPT_OK || res != 1) {
		free(dec);
		return NULL;
	} 
	
	if (unregister_cipher(&twofish_desc) != CRYPT_OK) {
		return NULL;
	}
	
	return dec;
}

void *twofish_eax_enc(unsigned char *data, unsigned int len, unsigned int *size, char *key, char *iv) {
	if (!data || len < 1 || !size || !key || !iv) {
		return NULL;
	}
	
	if (register_cipher(&twofish_desc) != CRYPT_OK) {
		return NULL;
	}
	
	int twofish = find_cipher("twofish");
	
	unsigned char *enc = malloc((*size = len + 16));
	
	if (!enc) {
		return NULL;
	}
	
	unsigned long taglen = 16;
	
	if (eax_encrypt_authenticate_memory(twofish, key, 16, iv, 16, NULL, 0, data, len, enc, enc + len, &taglen) != CRYPT_OK) {
		free(enc);
		return NULL;
	}
	
	if (unregister_cipher(&twofish_desc) != CRYPT_OK) {
		return NULL;
	}
	
	return enc;
}