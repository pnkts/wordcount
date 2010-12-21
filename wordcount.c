#include <stdio.h>
#include <string.h>
#define MAXC 32
#ifndef Boolean
#define Boolean int
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

Boolean bCharDecision (char c) {
  int i;
  Boolean flg = FALSE;
  char *expct = " \n\r\t\v,.:;?!";
  for (i = 0; expct[i] != '\0'; i++) {
    if (c == expct[i]) flg = TRUE;
  }
  return flg;
}

int main (void) {
  int wc = 0, rc = 0;
  Boolean flg;
  FILE *fp;
  char filename[MAXC], c;

  printf("input file name > ");
  fgets(filename, MAXC, stdin);
  if (filename[strlen(filename)-1] == '\n')
    filename[strlen(filename)-1] = '\0';

  if((fp = fopen(filename, "r")) == NULL) {
    fprintf(stderr, "Can't open: %s\n", filename);
    return 1;
  }

  while ((c = getc(fp)) != EOF) {
    if (c >= 0x41 && c <= 0x5A ||
        c >= 0x61 && c <= 0x7A)
      flg = TRUE;
    if (bCharDecision(c)) {
      if (flg == TRUE) wc++;
      flg = FALSE;
    }
    if (c == '\n' || c == '\v') rc++;
  }

  fclose(fp);

  printf("%d rows.\n", rc);
  printf("%d words.\n", wc);

  return 0;
}
