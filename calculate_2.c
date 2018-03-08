#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp = fopen("hash1.txt", "r");
    FILE *output = fopen("output.txt", "w");
    if (!fp) {
        printf("ERROR opening input file hash1.txt\n");
        exit(0);
    }
    int i = 0;
    char append[50], find[50];
    double hash1_sum_a = 0.0, hash1_sum_f = 0.0, hash1_a, hash1_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &hash1_a, &hash1_f);
        hash1_sum_a += hash1_a;
        hash1_sum_f += hash1_f;
    }
    fclose(fp);

    fp = fopen("hash2.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file hash2.txt\n");
            exit(0);
        }
    }
    double hash2_sum_a = 0.0, hash2_sum_f = 0.0, hash2_a, hash2_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &hash2_a, &hash2_f);
        hash2_sum_a += hash2_a;
        hash2_sum_f += hash2_f;
    }
    fp = fopen("hash3.txt", "r");
    if (!fp) {
        fp = fopen("orig.txt", "r");
        if (!fp) {
            printf("ERROR opening input file hash3.txt\n");
            exit(0);
        }
    }
    double hash3_sum_a = 0.0, hash3_sum_f = 0.0, hash3_a, hash3_f;
    for (i = 0; i < 100; i++) {
        if (feof(fp)) {
            printf("ERROR: You need 100 datum instead of %d\n", i);
            printf("run 'make run' longer to get enough information\n\n");
            exit(0);
        }
        fscanf(fp, "%s %s %lf %lf\n", append, find, &hash3_a, &hash3_f);
        hash3_sum_a += hash3_a;
        hash3_sum_f += hash3_f;
    }

    fprintf(output, "append() %lf %lf %lf\n",hash1_sum_a / 100.0, hash2_sum_a / 100.0, hash3_sum_a / 100.0);
    fprintf(output, "findName() %lf %lf %lf", hash1_sum_f / 100.0, hash2_sum_f / 100.0, hash3_sum_f / 100.0);
    fclose(output);
    fclose(fp);
    return 0;
}
