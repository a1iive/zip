#include <stdio.h>
#include <stdlib.h>

#include "zip.h"

int main() {

    size_t header_size = 30;
    void *header = malloc(header_size * sizeof(char));

    struct zip_t *zip = zip_stream_open(NULL, 0, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    // struct zip_t *zip = zip_open("foo.zip", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    FILE *fp = fopen("test.zip", "w+");
    FILE *tfp = fopen("test.txt", "w+");
    {
        size_t outSize = 30+strlen("foo-1.txt");
        void *outBuf = malloc(outSize * sizeof(char));
        // 从中获取file header+file name
        zip_entry_open_out(zip, "foo-1.txt", outBuf, &outSize);
        if (fp) {
            fwrite(outBuf, outSize, 1, fp);
        }
        // zip_entry_open(zip, "foo-1.txt");
        {
            char *inbuf1 = (char*)malloc(4096 * sizeof(char));
            memset(inbuf1, 'a', 4096);
            size_t outbufsize1 = strlen(inbuf1);
            void *outbuf1 = malloc(outbufsize1 * sizeof(char));
            // zip_entry_write(zip, inbuf1, strlen(inbuf1));
            zip_entry_write_out(zip, inbuf1, 4096, outbuf1, &outbufsize1);
            if (fp) {
                printf("before compress: %d, after compress: %d\n", strlen(inbuf1), outbufsize1);
                fwrite(outbuf1, outbufsize1, 1, fp);
            }
            // size_t debuf_size = 0;
            // void *debuf = zip_decompress(outbuf1, outbufsize1, &debuf_size, 4);
            // if (tfp) {
            //     printf("debuf_size = %d\n", debuf_size);
            //     fwrite(debuf, debuf_size, 1, fp);
            // }

            const char *inbuf2 = "Append some data here 2...\0";
            size_t outbufsize2 = strlen(inbuf2);
            void *outbuf2 = malloc(outbufsize2 * sizeof(char));
            // zip_entry_write(zip, inbuf2, strlen(inbuf2));
            zip_entry_write_out(zip, inbuf2, strlen(inbuf2), outbuf2, &outbufsize2);
            if (fp) {
                fwrite(outbuf2, outbufsize2, 1, fp);
            }
            
        }
        size_t outSize0 = 2;
        void *outBuf0 = malloc(outSize0 * sizeof(char));
        zip_entry_close_before(zip, outBuf0, &outSize0);
        if (fp) {
            fwrite(outBuf0, outSize0, 1, fp);
        }
        zip_entry_close_out(zip, header, &header_size);
        // zip_entry_close(zip);
    }

    size_t outbufsize = 100;
    void *outbuf = malloc(outbufsize * sizeof(char));
    // zip_close_out(zip, outbuf, &outbufsize);
    zip_stream_close_out(zip, outbuf, &outbufsize);

    if (fp) {
        fwrite(outbuf, outbufsize, 1, fp);
        fseek(fp, 0, SEEK_SET);
        fwrite(header, header_size, 1, fp);
    }
    

    /////////////////////////////////////////////////////////
    

    // // struct zip_t *zip = zip_open("foo.zip", ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    // struct zip_t *zip = zip_stream_open(NULL, 0, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    // {
    //     zip_entry_open(zip, "foo---1.txt");
    //     {
    //         const char *buf1 = "Some data here 1...\0";
    //         zip_entry_write(zip, buf1, strlen(buf1));
    //         const char *buf2 = "Some data here 2...\0";
    //         zip_entry_write(zip, buf2, strlen(buf2));
    //     }
    //     zip_entry_close(zip);
        
    // }
    // // zip_close(zip);
    // zip_stream_close(zip);
}