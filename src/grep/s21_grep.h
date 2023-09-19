#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  ignore_case,
  invert_pattern,
  only_number_of_lines,
  only_filenames,
  numerate_lines,
  hide_filenames,
  supress_file_error,
  only_matched_part
};
typedef enum { s21_false, s21_true } s21_bool;

typedef struct s21_grep {
  s21_bool options[8];
  s21_bool patternOptFound;
  s21_bool printFilenames;
  s21_bool errorOccured;
} grep_flags;

int s21_grep(int argc, char **argv);
void searchPattern(grep_flags *flags, int argc, char **argv, char *pattern);
void printMatchesFromFile(grep_flags *flags, char *pattern, FILE *file,
                          char *filename);
void parseStringArray(grep_flags *flags, int argc, char **argv, char *pattern);
void parseNextString(grep_flags *flags, char **argv, char *pattern, int *i);
void closePattern(char *pattern);
void addStringToPattern(char *source, char *dest);
s21_bool addFileToPattern(char *source, char *dest);
void copyFileToString(char *dest, FILE *file);
void clearString(char *str);
grep_flags initFlagsStruct(void);
s21_bool checkPrintFilenameConditions(grep_flags flags);
void printLineNumber(grep_flags flags, int lineCount);
void printFilename(s21_bool isFilenameNeeded, char *filename);
char *my_getline(FILE *file);

#endif  // SRC_GREP_S21_GREP_H_
