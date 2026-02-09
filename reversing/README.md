## Decryption Flow (as analyzed)

The following steps describe the observed decryption pipeline derived from reverse analysis:

1. Initial decoding  
   `dec1(sample.pkt)`  
   → `dec1.bin`

2. Symmetric decryption (Twofish in EAX mode)  
   - Input : `dec1.bin`  
   - Key   : `0x89` repeated 16 bytes  
   - Nonce : `0x10` repeated 16 bytes  
   - Output: `2fish_eax.bin`

3. Secondary decoding  
   `dec2(2fish_eax.bin)`  
   → `dec2.bin`

4. Decompression (zlib)  
   - Input : `dec2.bin`  
   - Method: `Z_DEFAULT_COMPRESSION`  
   - Output: `decrypted.xml`
