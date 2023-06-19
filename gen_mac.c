#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE* f = fopen("mac.h", "w");
    if (f == NULL) {
        fprintf(stderr, "Error opening file!\n");
        exit(1);
    }

    char* buff = malloc(200);
    if (buff == NULL) {
        fprintf(stderr, "Error allocating memory!\n");
        exit(1);
    }

    for (size_t i = 0; i <= 10; ++i)
    {
        for (size_t j = 0; j <= 10; ++j)
        {
            memset(buff, 0, 200);
            sprintf(buff, "\n#if defined(UMAKE_EQ_%zu_%zu)\n\t#undef UMAKE_EQ_%zu_%zu\n#endif\n#define UMAKE_EQ_%zu_%zu %zu\n", i, j, i, j, i, j, i == j ? 1 : 0);
            fwrite(buff, 1, strlen(buff), f);
        }
    }

    fclose(f);
    free(buff);
    
    return 0;
}