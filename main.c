#include "p2x.h"

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

enum optlist {
    OP_PACK = 1,
    OP_UNPACK
};

void usage(char *s) {
    printf("Usage: %s -i <input> -o <output> [-p|-u]\n\nOptions:\n  -i  input file\n  -o  output file\n  -p  pack\n  -u  unpack\n  -h  help\n\n", s);
    printf("Example:\n  %s -i example.pkt -o example.xml -u\n  %s -i example.xml -o example.pkt -p\n", s, s);
}

int main(int argc, char **argv) {
	printf("+-----------------------------------------------+\n");
	printf("|P2X - A Tool for Unpacking Packet Tracer Files |\n");
	printf("+-----------------------------------------------+\n");
	printf("|Github: https://github.com/tbzzz55             |\n");
	printf("|More: https://guns.lol/fangyuan000             |\n");
	printf("+-----------------------------------------------+\n\n");
	
    int opt = -1, op = 0;
    char *in = NULL, *out = NULL;

    while ((opt = getopt(argc, argv, "i:o:puh")) != -1) {
        switch (opt) {
            case 'i':
                in = optarg;
                break;

            case 'o':
                out = optarg;
                break;

            case 'p':
                op = OP_PACK;
                break;

            case 'u':
                op = OP_UNPACK;
                break;

            case 'h':
                usage(argv[0]);
                return 0;

            default:
                usage(argv[0]);
                return 1;
        }
    }

    if (!in || !out || !op) {
        usage(argv[0]);
        return 1;
    }

    struct pkt2xml *p2x = p2x_open(in);

    if (!p2x) {
        puts("p2x init failed!");
        return 1;
    }

    unsigned char *buf = NULL;
    unsigned int buf_size = 0;

    FILE *fp = NULL;

    switch (op) {
        case OP_PACK:
            printf("packing %s...\n", in);

            if (!p2x_pack(p2x, &buf, &buf_size)) {
                puts("p2x pack failed!");
                goto _ERR;
            }

            break;

        case OP_UNPACK:
            printf("unpacking %s...\n", in);

            if (!p2x_unpack(p2x, &buf, &buf_size)) {
                puts("p2x unpack failed!");
                goto _ERR;
            }

            break;

        default:
            goto _ERR;
    }

    p2x_close(p2x);
    p2x = NULL;

    if (!(fp = fopen(out, "wb"))) {
        printf("open %s failed!\n", out);
        goto _ERR;
    }

    if (fwrite(buf, 1, buf_size, fp) != buf_size) {
        printf("write %s failed!\n", out);
        goto _ERR;
    }

    fclose(fp);
    free(buf);

    printf("saved to %s\n", out);
    return 0;

    _ERR:
    if (buf) {
        free(buf);
    }

    if (p2x) {
        p2x_close(p2x);
    }

    if (fp) {
        fclose(fp);  
    }

    return 1;
}