#include "s21_cat.h"

int main(int argc, char **argv) {
  s21_cat(argc, argv);
  return 0;
}

int s21_cat(int argc, char **argv) {
  int errorCode = 0;

  cat_flags flags = initFlagsStruct();
  parseStringArray(&flags, argc, argv);

  if (!flags.errorOccured) {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0]) {
        printFile(&flags, argv[i]);
      }
    }
  } else {
    errorCode = 1;
  }

  return errorCode;
}

void parseStringArray(cat_flags *flags, int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      parseNextString(flags, &argv[i][1]);
      clearString(&argv[i][0]);
    }

    if (flags->errorOccured) {
      printOptionNotFoundError(argv[i][1]);
      break;
    }
    neutralizeConflictingOptions(flags);
  }
}

void parseNextString(cat_flags *flags, char *string) {
  char *ptr = string;

  if (*ptr == '-') {
    parceLongFlag(flags, ptr + 1);
  } else {
    while (*ptr) {
      parceShortFlags(flags, *ptr);
      ptr++;
    }
  }
}

void parceShortFlags(cat_flags *flags, char c) {
  if (c == 'b') {
    flags->options[number_nonBlank] = s21_true;

  } else if (c == 'e') {
    flags->options[dollar] = s21_true;
    flags->options[nonPrintable] = s21_true;

  } else if (c == 'n') {
    flags->options[number] = s21_true;

  } else if (c == 's') {
    flags->options[squeeze] = s21_true;

  } else if (c == 't') {
    flags->options[tabs] = s21_true;
    flags->options[nonPrintable] = s21_true;

  } else if (c == 'E') {
    flags->options[dollar] = s21_true;

  } else if (c == 'T') {
    flags->options[tabs] = s21_true;

  } else if (c == 'v') {
    flags->options[nonPrintable] = s21_true;

  } else {
    flags->errorOccured = s21_true;
  }
}

void parceLongFlag(cat_flags *flags, char *string) {
  if (!strcmp(string, "number-nonblank")) {
    flags->options[number_nonBlank] = s21_true;

  } else if (!strcmp(string, "number")) {
    flags->options[number] = s21_true;

  } else if (!strcmp(string, "squeeze-blank")) {
    flags->options[squeeze] = s21_true;

  } else {
    flags->errorOccured = s21_true;
  }
}

void printFile(cat_flags *flags, char *string) {
  FILE *file;
  file = fopen(string, "r");

  if (file == NULL) {
    printf("s21_cat: %s: No such file or directory", string);
  } else {
    s21_bool isTab;
    s21_bool isNonprintable;
    s21_bool isNewLine = s21_true;
#if defined(__linux__)
    static int lineNumber = 1;
#elif defined(__APPLE__)
    int lineNumber = 1;
#endif
    char nextChar;
    char currentChar = fgetc(file);
    for (char prevChar = 0; currentChar != -1;
         prevChar = currentChar, currentChar = nextChar) {
      nextChar = fgetc(file);
      squeezeBlankLines(flags, file, &nextChar, &currentChar, &prevChar);
      if (isNewLine) {
        printLineNumber(flags, currentChar, &lineNumber);
        isNewLine = s21_false;
      }
      printDollar(flags, currentChar);

      isTab = printTab(flags, currentChar);
      isNonprintable = printNonPrintable(flags, currentChar);
      if (!isTab && !isNonprintable) {
        putc(currentChar, stdout);
      }
      if (currentChar == '\n') {
        isNewLine = s21_true;
      }
    }
    fclose(file);
  }
}

void printDollar(cat_flags *flags, char currentChar) {
  if (flags->options[dollar] && currentChar == '\n') {
    putc('$', stdout);
  }
}

void squeezeBlankLines(cat_flags *flags, FILE *file, char *nextChar,
                       char *currentChar, const char *prevChar) {
  if (flags->options[squeeze]) {
    if (*currentChar == '\n' && *nextChar == '\n' && *prevChar == '\n') {
      while (*nextChar == '\n') {
        *currentChar = *nextChar;
        *nextChar = fgetc(file);
      }
    }
  }
}

s21_bool printTab(cat_flags *flags, char currentChar) {
  s21_bool found = s21_false;

  if (flags->options[tabs] && currentChar == '\t') {
    printf("^I");
    found = s21_true;
  }
  return found;
}

s21_bool printNonPrintable(cat_flags *flags, char currentChar) {
  s21_bool found = s21_false;

  if (flags->options[nonPrintable]) {
    if (currentChar >= 0 && currentChar <= 31 && currentChar != '\t' &&
        currentChar != '\n') {
      currentChar += 64;
      printf("%c%c", '^', currentChar);
      found = s21_true;
    }
  }
  return found;
}

void printLineNumber(cat_flags *flags, char currentChar, int *lineNumber) {
  if (flags->options[number]) {
    printf("%6d\t", *lineNumber);
    (*lineNumber)++;

  } else if (flags->options[number_nonBlank] && currentChar != '\n') {
    printf("%6d\t", *lineNumber);
    (*lineNumber)++;
  }
}

cat_flags initFlagsStruct(void) {
  cat_flags flags = {
      {s21_false, s21_false, s21_false, s21_false, s21_false, s21_false},
      s21_false};
  return flags;
}

void clearString(char *str) { str[0] = '\0'; }

void printOptionNotFoundError(char errorOption) {
  printf("cat: illegal option: %c\nusage: cat [-benstv] [file ...]",
         errorOption);
}

void neutralizeConflictingOptions(cat_flags *flags) {
  s21_bool isNeutralizationNeeded =
      flags->options[number] && flags->options[number_nonBlank];

  if (isNeutralizationNeeded) {
    flags->options[number] = s21_false;
  }
}
