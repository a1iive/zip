#include <stdio.h>
#include <stdlib.h>

#include "zip.h"

int main() {
    void *buf = NULL;
    size_t bufsize;

    // struct zip_t *zip = zip_stream_open(NULL, 0, ZIP_DEFAULT_COMPRESSION_LEVEL, 'w');
    struct zip_t *zip = zip_open("test.zip", 0, 'r');
    {
        zip_entry_open(zip, "foo-1.txt");
        {
            zip_entry_read(zip, &buf, &bufsize);
        }
        zip_entry_close(zip);
    }
    zip_close(zip);

    FILE *fp = fopen("foo-1.txt", "w+");
    fwrite(buf, bufsize, 1, fp);
    
    free(buf);
}