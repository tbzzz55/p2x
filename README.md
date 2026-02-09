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

## Features

- Unpack `.pkt` → `.xml`
- Modify XML data
- Pack `.xml` → `.pkt`

## Build

### Linux

```bash
chmod +x build-linux.sh
./build-linux.sh
```

### Windows (UCRT64)
```bash
chmod +x build-ucrt64.sh
./build-ucrt64.sh
```

## Usage
```bash
Usage: ./p2x -i <input> -o <output> [-p|-u]

Options:
  -i  input file
  -o  output file
  -p  pack
  -u  unpack
  -h  help
```

## Example
```bash
./p2x -u -i example.pkt -o example.xml
./p2x -p -i example.xml -o example.pkt
```
## Tested

- Cisco Packet Tracer 8.2.2 and 9.0.0

## Referrence

- Open Source Used In Cisco Packet Tracer 9.0: https://www.cisco.com/c/dam/en_us/about/doing_business/open_source/docs/CiscoPacketTracer-90-1758829197.pdf
- libTomCrypt manual: https://www.co.tt/files/libTomCryptDoc.pdf
- zlib manual: https://www.zlib.net/manual.html
