#ifndef LANG_H
#define LANG_H

#define MAX_LANG_CODE_LENGTH 6

#define MAX_TRANSLATIONS 1024

typedef struct {
    char langCode[MAX_LANG_CODE_LENGTH];
    char translation[100];
} Translation;

extern Translation translations[MAX_TRANSLATIONS];

void addTranslation(const char* langCode, const char* translation);

const char* getTranslation(const char* langCode);

int isLangCodeValid(const char* langCode);

int initializeLanguage();

#endif