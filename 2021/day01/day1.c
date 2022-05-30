#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void solve(char* fname);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "USAGEUSAGE: day11 <input file>\n");
        exit(-1);
    }

    solve(argv[1]);
}

void solve(char* fname) {
    FILE *f;
    int A = 0;
    int B = 0;
    int num = 0;
    char buf[90];
    int a_prev = 0;
    int b_prev[3] = {0, 0, 0};

    f = fopen(fname, "r");
    if (f) {
        while (!feof(f)) {
            fscanf(f, "%s", &buf);
            num = strtol(buf, NULL, 10);
            if (num > a_prev) {
                A++;
            }
            a_prev = num;
        }

        fclose(f);
    } else {
        fprintf(stderr, "File %s could not be opened!", fname);
    }
}
