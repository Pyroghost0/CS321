#include <stdio.h>
#include <stdlib.h>
  
int main()
{
    FILE *f1, *f2;
    char filename[256], c;
  
    printf("What file do you want to copy?\n");
    scanf("%s", filename);
  
    f1 = fopen(filename, "r");
    if (f1 == NULL)
    {
        printf("%s does not exist... Exiting\n", filename);
        exit(0);
    }
  
    printf("What file do you want to paste into?\n");
    scanf("%s", filename);
  
    f2 = fopen(filename, "w");
    if (f2 == NULL)
    {
        printf("%s does not exist... Exiting\n", filename);
        exit(0);
    }
  
    c = fgetc(f1);
    while (c != EOF)
    {
        fputc(c, f2);
        c = fgetc(f1);
    }
  
    printf("\nCompeted...");
  
    fclose(f1);
    fclose(f2);
    return 0;
}
