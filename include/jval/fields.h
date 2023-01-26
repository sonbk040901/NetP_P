#ifndef _FIELDS_
#define _FIELDS_

/** The fields library -- making input processing easier */

#include <stdio.h>
#define MAXLEN 1001
#define MAXFIELDS 1000

typedef struct inputstruct {
  char *name;               /**< File name */
  FILE *f;                  /**< File descriptor */
  int line;                 /**< Line number */
  char text1[MAXLEN];       /**< The line */
  char text2[MAXLEN];       /**< Working -- contains fields */
  int NF;                   /**< Number of fields */
  char *fields[MAXFIELDS];  /**< Pointers to fields */
  int file;                 /**< 1 for file, 0 for popen */
} *IS;

/** Builds the input struct. Use NULL for stdin. */
extern IS new_inputstruct(char *filename);
extern IS pipe_inputstruct(char *command);

/** Returns NF or -1 on EOF. Does not close the file. */
extern int get_line(IS is);

/** free(3) the IS and fclose(3) the file. */
extern void jettison_inputstruct(IS is);
#endif
