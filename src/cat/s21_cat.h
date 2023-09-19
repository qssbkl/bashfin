#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <string.h>

enum { number_nonBlank, dollar, number, squeeze, tabs, nonPrintable };
typedef enum { s21_false, s21_true } s21_bool;

typedef struct s21_cat {
  s21_bool options[6];
  s21_bool errorOccured;
} cat_flags;

int s21_cat(int argc, char **argv);
void parseStringArray(cat_flags *flags, int argc, char **argv);
void parseNextString(cat_flags *flags, char *string);
void parceShortFlags(cat_flags *flags, char c);
void parceLongFlag(cat_flags *flags, char *string);
void neutralizeConflictingOptions(cat_flags *flags);
void printFile(cat_flags *flags, char *string);
void printDollar(cat_flags *flags, char currentChar);
void squeezeBlankLines(cat_flags *flags, FILE *file, char *nextChar,
                       char *currentChar, const char *prevChar);
s21_bool printTab(cat_flags *flags, char currentChar);
s21_bool printNonPrintable(cat_flags *flags, char currentChar);
void printLineNumber(cat_flags *flags, char nextChar, int *lineNumber);
void clearString(char *str);
void printOptionNotFoundError(char errorOption);
cat_flags initFlagsStruct(void);

#endif  // SRC_CAT_S21_CAT_H_
