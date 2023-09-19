#include "s21_grep.h"

int main(int argc, char **argv) {
  s21_grep(argc, argv);
  return 0;
}

int s21_grep(int argc, char **argv) {
  int errorCode = 0;
  char pattern[4096] = "";
  grep_flags flags = initFlagsStruct();

  parseStringArray(&flags, argc, argv, pattern);

  if (!flags.errorOccured) {
    searchPattern(&flags, argc, argv, pattern);
  } else {
    errorCode = 1;
  }

  return errorCode;
}

void parseStringArray(grep_flags *flags, int argc, char **argv, char *pattern) {
  int fileCount = 0;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      parseNextString(flags, argv, pattern, &i);
      clearString(argv[i]);
    } else {
      fileCount++;
    }
  }
  if (!flags->patternOptFound) {
    int i;
    for (i = 1; i < argc; i++) {
      if (argv[i][0]) {
        break;
      }
    }

    addStringToPattern(argv[i], pattern);
    clearString(argv[i]);
    fileCount--;
  }
  flags->printFilenames = fileCount > 1 ? s21_true : s21_false;
#if defined(__APPLE__)
  if (flags->options[invert_pattern] && flags->options[only_matched_part]) {
    flags->options[only_matched_part] = s21_false;
  }
#endif
  closePattern(pattern);
}

void parseNextString(grep_flags *flags, char **argv, char *pattern, int *i) {
  char *ptr = argv[*i];
  ptr++;

  while (*ptr) {
    if (*ptr == 'e') {
      ptr++;
      if (*ptr) {
        addStringToPattern(ptr, pattern);
      } else {
        clearString(argv[*i]);
        (*i)++;
        addStringToPattern(argv[*i], pattern);
      }
      flags->patternOptFound = s21_true;
      break;
    } else if (*ptr == 'i') {
      flags->options[ignore_case] = s21_true;
    } else if (*ptr == 'v') {
      flags->options[invert_pattern] = s21_true;
    } else if (*ptr == 'c') {
      flags->options[only_number_of_lines] = s21_true;
    } else if (*ptr == 'l') {
      flags->options[only_filenames] = s21_true;
    } else if (*ptr == 'n') {
      flags->options[numerate_lines] = s21_true;
    } else if (*ptr == 'h') {
      flags->options[hide_filenames] = s21_true;
    } else if (*ptr == 's') {
      flags->options[supress_file_error] = s21_true;
    } else if (*ptr == 'f') {
      ptr++;
      if (*ptr) {
        flags->errorOccured = addFileToPattern(ptr, pattern);
      } else {
        clearString(argv[*i]);
        (*i)++;
        flags->errorOccured = addFileToPattern(argv[*i], pattern);
      }
      flags->patternOptFound = s21_true;
      break;
    } else if (*ptr == 'o') {
      flags->options[only_matched_part] = s21_true;
    }
    ptr++;
  }
}

void closePattern(char *pattern) {
  char *ptr = pattern;

  while (*ptr) {
    ptr++;
  }
  *ptr = ')';
  *(++ptr) = '\0';
}

void addStringToPattern(char *source, char *dest) {
  if (*dest) {
    snprintf(dest, strlen(source) + 2, "%s|", source);
  } else {
    snprintf(dest, strlen(source) + 2, "(%s", source);
  }
}

s21_bool addFileToPattern(char *source, char *dest) {
  s21_bool isFileNotExists = s21_true;
  FILE *file;
  file = fopen(source, "r");

  if (file != NULL) {
    isFileNotExists = s21_false;
    char *ptr = dest;
    if (*dest) {
      while (*ptr) {
        ptr++;
      }
      *(ptr++) = '|';
      copyFileToString(ptr, file);
    } else {
      *(ptr++) = '(';
      copyFileToString(ptr, file);
    }
    fclose(file);
  } else {
    printf("grep: %s: No such file or directory\n", source);
  }
  return isFileNotExists;
}

void copyFileToString(char *dest, FILE *file) {
  char *line = NULL;

  for (line = my_getline(file); line != NULL;) {
    snprintf(dest, strlen(line) + 1, "%s", line);
    dest += strlen(line);
    free(line);
    line = my_getline(file);
    line ? *(dest++) = '|' : 0;
  }
  free(line);
}

void searchPattern(grep_flags *flags, int argc, char **argv, char *pattern) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0]) {
      FILE *file;
      file = fopen(argv[i], "r");
      if (file != NULL) {
        printMatchesFromFile(flags, pattern, file, argv[i]);
        fclose(file);
      } else {
        printf("grep: %s: No such file or directory\n", argv[i]);
      }
    }
  }
}

void printMatchesFromFile(grep_flags *flags, char *pattern, FILE *file,
                          char *filename) {
  int lineCount = 1;
  int linesMatched = 0;
  regmatch_t match[2];
  regex_t reg;
  flags->options[ignore_case] ? regcomp(&reg, pattern, REG_EXTENDED | REG_ICASE)
                              : regcomp(&reg, pattern, REG_EXTENDED);
  s21_bool isFilenameNeeded = checkPrintFilenameConditions(*flags);
  char *line = my_getline(file);
  for (; line != NULL; lineCount++) {
    int isNotMatched = regexec(&reg, line, 2, match, 0);

    if ((isNotMatched != REG_NOMATCH && !flags->options[invert_pattern]) ||
        (isNotMatched == REG_NOMATCH && flags->options[invert_pattern])) {
      linesMatched++;
    }

    if (!flags->options[only_number_of_lines] &&
        !flags->options[only_filenames]) {
      if ((!isNotMatched && !flags->options[invert_pattern] &&
           !flags->options[only_matched_part]) ||
          (isNotMatched == REG_NOMATCH && flags->options[invert_pattern] &&
           !flags->options[only_matched_part])) {
        printFilename(isFilenameNeeded, filename);
        printLineNumber(*flags, lineCount);
        printf("%s\n", line);

      } else if (!isNotMatched && !flags->options[invert_pattern] &&
                 flags->options[only_matched_part]) {
#if defined(__APPLE__)
        printFilename(isFilenameNeeded, filename);
        printLineNumber(*flags, lineCount);
#endif
        char *ptr = line;
        while (!isNotMatched) {
#if defined(__linux__)
          printFilename(isFilenameNeeded, filename);
          printLineNumber(*flags, lineCount);
#endif
          printf("%.*s\n", (int)(match[0].rm_eo - match[0].rm_so),
                 ptr + match[0].rm_so);
          ptr += match->rm_eo;
          isNotMatched = regexec(&reg, ptr, 2, match, 0);
        }
      }
    }
    free(line);
    line = my_getline(file);
  }
#if defined(__APPLE__)
  if (flags->options[only_number_of_lines]) {
    printFilename(isFilenameNeeded, filename);
    flags->options[only_filenames] ? printf("1\n")
                                   : printf("%d\n", linesMatched);
  }
#endif
#if defined(__linux__)
  if (flags->options[only_number_of_lines] && !flags->options[only_filenames]) {
    printFilename(isFilenameNeeded, filename);
    printf("%d\n", linesMatched);
  }
#endif
  if (flags->options[only_filenames] && linesMatched > 0) {
    printf("%s\n", filename);
  }
  free(line);
  regfree(&reg);
}

void printLineNumber(grep_flags flags, int lineCount) {
  flags.options[numerate_lines] ? printf("%d:", lineCount) : 0;
}

void printFilename(s21_bool isFilenameNeeded, char *filename) {
  isFilenameNeeded ? printf("%s:", filename) : 0;
}

s21_bool checkPrintFilenameConditions(grep_flags flags) {
  return flags.printFilenames && !flags.options[hide_filenames] &&
         (!flags.options[only_filenames] ||
          (flags.options[only_number_of_lines] &&
           flags.options[only_filenames]));
}

char *my_getline(FILE *file) {
  char *ptr = (char *)malloc(sizeof(char));
  if (ptr != NULL) {
    char c = getc(file);
    int charCount = 1;
    int i;
    for (i = 0; c != '\n' && c != -1; i++, charCount++) {
      ptr[i] = c;
      char *tmp_ptr = realloc(ptr, i + 2);
      if (tmp_ptr == NULL) {
        free(ptr);
        ptr = NULL;
        break;
      } else {
        c = getc(file);
        ptr = tmp_ptr;
      }
    }
    if (ptr) {
      ptr[i] = 0;
    }
    if (c == -1 && charCount == 1) {
      free(ptr);
      ptr = NULL;
    }
  }
  return ptr;
}

void clearString(char *str) { str[0] = '\0'; }

grep_flags initFlagsStruct(void) {
  grep_flags flags = {{s21_false, s21_false, s21_false, s21_false, s21_false,
                       s21_false, s21_false, s21_false},
                      s21_false,
                      s21_false,
                      s21_false};
  return flags;
}
