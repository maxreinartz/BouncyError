#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "lang.h"

Translation translations[MAX_TRANSLATIONS];
int currentSize = 0;

void addTranslation(const char *langCode, const char *translation)
{
    if (currentSize >= MAX_TRANSLATIONS)
    {
        printf("Translations array is full. Cannot add more translations.\n");
        return;
    }

    Translation newTranslation;

    strncpy(newTranslation.langCode, langCode, MAX_LANG_CODE_LENGTH - 1);
    newTranslation.langCode[MAX_LANG_CODE_LENGTH - 1] = '\0';
    strncpy(newTranslation.translation, translation, sizeof(newTranslation.translation) - 1);
    newTranslation.translation[sizeof(newTranslation.translation) - 1] = '\0';

    translations[currentSize] = newTranslation;
    currentSize++;
}

const char *getTranslation(const char *langCode)
{
    for (int i = 0; i < sizeof(translations) / sizeof(translations[0]); i++)
    {
        if (strcmp(translations[i].langCode, langCode) == 0)
        {
            return translations[i].translation;
        }
    }

    return NULL;
}

int isLangCodeValid(const char *langCode)
{
    char newLangCode[MAX_LANG_CODE_LENGTH] = {0};
    int j = 0;
    for (int i = 0; langCode[i] != '\0' && i < MAX_LANG_CODE_LENGTH - 1; i++)
    {
        if (isalpha(langCode[i]) || langCode[i] == '-')
        {
            newLangCode[j++] = tolower(langCode[i]);
        }
    }
    newLangCode[j] = '\0';

    for (int i = 0; i < currentSize; i++)
    {
        if (strcmp(translations[i].langCode, newLangCode) == 0)
        {
            return 0;
        }
    }

    return 2;
}

int initializeLanguage()
{
    addTranslation("en-us", "Task failed successfully.");                     // English (United States)
    addTranslation("en-uk", "Task failed successfully.");                     // English (United Kingdom)
    addTranslation("de-de", "Aufgabe erfolgreich fehlgeschlagen.");           // German (Germany)
    addTranslation("fr-fr", "La tâche a échoué avec succès.");                // French (France)
    addTranslation("es-es", "Tarea fallida con éxito.");                      // Spanish (Spain)
    addTranslation("ja-jp", "タスクが正常に失敗しました。");                  // Japanese (Japan)
    addTranslation("zh-cn", "任务成功失败。");                                // Chinese (China)
    addTranslation("ru-ru", "Задача успешно провалилась.");                   // Russian (Russia)
    addTranslation("pt-br", "Tarefa falhou com sucesso.");                    // Portuguese (Brazil)
    addTranslation("it-it", "Attività fallita con successo.");                // Italian (Italy)
    addTranslation("ko-kr", "작업이 성공적으로 실패했습니다.");               // Korean (South Korea)
    addTranslation("nl-nl", "Taak succesvol mislukt.");                       // Dutch (Netherlands)
    addTranslation("pl-pl", "Zadanie nie powiodło się pomyślnie.");           // Polish (Poland)
    addTranslation("sv-se", "Uppgiften misslyckades framgångsrikt.");         // Swedish (Sweden)
    addTranslation("tr-tr", "Görev başarılı bir şekilde başarısız oldu.");    // Turkish (Turkey)
    addTranslation("ar-sa", "فشلت المهمة بنجاح.");                            // Arabic (Saudi Arabia)
    addTranslation("hi-in", "कार्य सफलतापूर्वक विफल हो गया।");                   // Hindi (India)
    addTranslation("th-th", "งานล้มเหลวอย่างประสบความสำเร็จ.");                  // Thai (Thailand)
    addTranslation("vi-vn", "Nhiệm vụ thất bại thành công.");                 // Vietnamese (Vietnam)
    addTranslation("id-id", "Tugas gagal berhasil.");                         // Indonesian (Indonesia)
    addTranslation("ms-my", "Tugas gagal berjaya.");                          // Malay (Malaysia)
    addTranslation("tl-ph", "Nabigo ang gawain nang matagumpay.");            // Filipino (Philippines)
    addTranslation("cs-cz", "Úkol se úspěšně nezdařil.");                     // Czech (Czech Republic)
    addTranslation("hu-hu", "A feladat sikeresen meghiúsult.");               // Hungarian (Hungary)
    addTranslation("ro-ro", "Sarcina a eșuat cu succes.");                    // Romanian (Romania)
    addTranslation("sk-sk", "Úloha sa úspešne nepodarila.");                  // Slovak (Slovakia)
    addTranslation("uk-ua", "Завдання успішно не вдалося.");                  // Ukrainian (Ukraine)
    addTranslation("bg-bg", "Задачата неуспешно успя.");                      // Bulgarian (Bulgaria)
    addTranslation("hr-hr", "Zadatak je uspješno neuspješan.");               // Croatian (Croatia)
    addTranslation("el-gr", "Η εργασία απέτυχε με επιτυχία.");                // Greek (Greece)
    addTranslation("fi-fi", "Tehtävä epäonnistui onnistuneesti.");            // Finnish (Finland)
    addTranslation("no-no", "Oppgaven mislyktes vellykket.");                 // Norwegian (Norway)
    addTranslation("da-dk", "Opgaven mislykkedes succesfuldt.");              // Danish (Denmark)
    addTranslation("is-is", "Verkefni mistókst með árangri.");                // Icelandic (Iceland)
    addTranslation("et-ee", "Ülesanne ebaõnnestus edukalt.");                 // Estonian (Estonia)
    addTranslation("lv-lv", "Uzdevums veiksmīgi neizdevās.");                 // Latvian (Latvia)
    addTranslation("lt-lt", "Užduotis sėkmingai nepavyko.");                  // Lithuanian (Lithuania)
    addTranslation("sl-si", "Naloga je uspešno spodletela.");                 // Slovenian (Slovenia)
    addTranslation("mt-mt", "It-taħriġ rebaħ b'suċċess.");                    // Maltese (Malta)
    addTranslation("sq-al", "Detyra dështoi me sukses.");                     // Albanian (Albania)
    addTranslation("mk-mk", "Задачата неуспешно успеа.");                     // Macedonian (North Macedonia)
    addTranslation("be-by", "Задача паспяха неўдала.");                       // Belarusian (Belarus)
    addTranslation("hy-am", "Առաջարկը ձախողվեց հաջողությամբ։");               // Armenian (Armenia)
    addTranslation("ka-ge", "დავა წარმატებით ჩაიჭერა.");                      // Georgian (Georgia)
    addTranslation("az-az", "Tapşırıq uğurla baş tutmadı.");                  // Azerbaijani (Azerbaijan)
    addTranslation("kk-kz", "Тапсырыс сәтті сәтсіз болды.");                  // Kazakh (Kazakhstan)
    addTranslation("uz-uz", "Vazifa muvaffaqiyatli muvaffaqiyatsiz bo'ldi."); // Uzbek (Uzbekistan)
    addTranslation("tk-tm", "Ugruk işi üstünlikli ugruq olmady.");            // Turkmen (Turkmenistan)
    addTranslation("ky-kg", "Иш ийгиликтүү эмес ийгиликсиз болду.");          // Kyrgyz (Kyrgyzstan)
    addTranslation("tg-tj", "Вазифа бо муваффақият ба муваффақият нашуд.");   // Tajik (Tajikistan)
    addTranslation("mn-mn", "Ажлыг амжилтгүй амжилтгүй болгосон.");           // Mongolian (Mongolia)
    addTranslation("ps-af", "د کار په ناکامۍ سره کام کړل شوې.");              // Pashto (Afghanistan)
    addTranslation("ku-iq", "کار بە سەرکەوتویی شکست دا.");                    // Kurdish (Iraq)
    addTranslation("sd-pk", "ڪام موفقيت سان ناڪام ٿيو.");                     // Sindhi (Pakistan)
    addTranslation("ne-np", "काम सफलतापूर्वक असफल भयो।");                       // Nepali (Nepal)
    addTranslation("si-lk", "කාර්යය සාර්ථකව අසාර්ථක විය.");                       // Sinhala (Sri Lanka)
    addTranslation("my-mm", "လုပ်ကို အောင်မြင်စွာ မအောင်မြင်ခဲ့သည်။");                    // Burmese (Myanmar)
    addTranslation("ka-kg", "დავა წარმატებით ჩაიჭერა.");                      // Georgian (Kyrgyzstan)
    addTranslation("am-et", "ስለሆነ ስለሆነ የሚቀጥለው ስህተት አልተሳነውም።");                // Amharic (Ethiopia)
    addTranslation("ti-er", "ሓበሬታ ተሓትተን ኣለዎ።");                               // Tigrinya (Eritrea)
    addTranslation("so-so", "Dhawrka waa la guuleystay.");                    // Somali (Somalia)
    addTranslation("sw-ke", "Kazi ilishindwa kwa mafanikio.");                // Swahili (Kenya)
    addTranslation("rw-rw", "Umushinga wabaye neza.");                        // Kinyarwanda (Rwanda)
    addTranslation("mg-mg", "Tombontsoa tsara tamin'ny fahafahana.");         // Malagasy (Madagascar)
    addTranslation("uwu", "task f-faiwed s-successfuwwy.");                   // UwU~

    char allLangsStr[1024] = "";
    for (int
             i = 0;
         i < sizeof(translations) / sizeof(translations[0]); i++)
    {
        char langCode[MAX_LANG_CODE_LENGTH];
        strncpy(langCode, translations[i].langCode, MAX_LANG_CODE_LENGTH);
        if (i == sizeof(translations) / sizeof(translations[0]) - 1)
        {
            strcat(allLangsStr, langCode);
        }
        else
        {
            strcat(allLangsStr, langCode);
            strcat(allLangsStr, ", ");
        }
    }
    printf("Supported languages: %s\n", allLangsStr);
    // MessageBoxA(NULL, allLangsStr, "Supported languages", MB_OK | MB_ICONINFORMATION);

    return 0;
}
