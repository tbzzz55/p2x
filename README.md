## Features

- Unpack `.pkt` → `.xml`
- Modify XML data
- Pack `.xml` → `.pkt`

## Build

### Linux

```bash
chmod +x linux_build.sh
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
p2x -u -i example.pkt -o example.xml
p2x -p -i example.xml -o example.pkt
```
