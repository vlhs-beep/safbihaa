/* dump.c:   Display a file's bytes in hex and ASCII */

#include <stdio.h>
#include <ctype.h>

/* Number of bytes per line */
#define NBYTES 16

void dump(FILE *, char *);

main(int argc, char *argv[])
{
    FILE *f;
    int i;

    /* Process files on command-line */
    for (i = 1; i < argc; ++i)
        if ((f = fopen(argv[i],"rb")) == NULL)
            fprintf(stderr,"Can't open %s\n");
        else
        {
            dump(f,argv[i]);
            fclose(f);
            putchar('\f');
        }

    return 0;
}

void dump(FILE *f, char *s)
{
    unsigned char buf[NBYTES];
    int count;
    long size = 0L;

    printf("Dump of %s:\n\n",s);
    while ((count = fread(buf,1,NBYTES,f)) > 0)
    {
        int i;

        /* Print byte counter */
        printf("  %06X ",size += count);

        /* Print Hex Bytes */
        for (i = 0; i < NBYTES; ++i)
        {
            /* Print gutter space between columns */
            if (i == NBYTES / 2)
                putchar(' ');

            /* Display hex byte */
            if (i < count)
            {
                printf(" %02X",buf[i]);
                if (!isprint(buf[i]))
                    buf[i] = '.';
            }
            else
            {
                /* Spacing for partial last line */
                fputs("   ",stdout);
                buf[i] = ' ';
            }
        }

        /* Print Text Bytes */
        printf(" |%16.16s|\n",buf);
    }
}

