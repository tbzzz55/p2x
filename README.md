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

- libTomCrypt manual: https://www.co.tt/files/libTomCryptDoc.pdf
- zlib manual: https://www.zlib.net/manual.html
- Open Source Used In Cisco Packet Tracer 9.0: https://www.cisco.com/c/dam/en_us/about/doing_business/open_source/docs/CiscoPacketTracer-90-1758829197.pdf
