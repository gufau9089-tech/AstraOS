#pragma once
#include "inc/efi.h"

// Чистый код сравнения строк из официальной спецификации UEFI
int StrCmp(CHAR16 *str1, CHAR16 *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// Чистый код ввода строк с клавиатуры из официальной спецификации UEFI
void Input(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *buffer, UINTN max_size) {
    EFI_INPUT_KEY key;
    UINTN index = 0;
    
    while (index < max_size - 1) {
        // Ждем нажатия абсолютно любой клавиши
        while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) == EFI_NOT_READY) { }
        
        // Если нажали Enter — завершаем ввод слова
        if (key.UnicodeChar == L'\r') {
            break;
        }
        
        // Если нажали Backspace — стираем последний символ
        if (key.UnicodeChar == L'\b') {
            if (index > 0) {
                index--;
                SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\b \b");
            }
            continue;
        }
        
        // Если это любой обычный печатный символ — записываем и выводим на экран
        if (key.UnicodeChar >= 32) {
            buffer[index] = key.UnicodeChar;
            CHAR16 echo_str[] = { key.UnicodeChar, L'\0' };
            SystemTable->ConOut->OutputString(SystemTable->ConOut, echo_str);
            index++;
        }
    }
    buffer[index] = L'\0'; // Закрываем строку ноль-терминатором
}
// Полноценная функция для приема и мгновенного получения числа UINT32
UINT32 InputUint32(EFI_SYSTEM_TABLE* SystemTable) {
    EFI_INPUT_KEY key;
    UINT32 result = 0;
    UINTN digits_count = 0;

    while (1) {
        // 1. Ждем нажатия абсолютно любой клавиши
        while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) == EFI_NOT_READY) {}

        // 2. Если нажали Enter — завершаем ввод и возвращаем число
        if (key.UnicodeChar == L'\r' || key.UnicodeChar == L'\n') {
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
            break;
        }

        // 3. Если нажали Backspace — стираем последнюю цифру
        if (key.UnicodeChar == L'\b') {
            if (digits_count > 0) {
                digits_count--;
                result = result / 10; // Отбрасываем последний разряд числа
                SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\b \b"); // Стираем символ на экране
            }
            continue;
        }

        // 4. Если нажата цифра от '0' до '9' — собираем число
        if (key.UnicodeChar >= L'0' && key.UnicodeChar <= L'9') {
            // Ограничение: UINT32 вмещает до 10 знаков, защищаем от переполнения
            if (digits_count < 10) {
                UINT32 digit = key.UnicodeChar - L'0'; // Переводим символ в цифру
                result = (result * 10) + digit;       // Сдвигаем разряд и прибавляем
                digits_count++;

                // Выводим введенную цифру на экран
                CHAR16 echo_str[] = { key.UnicodeChar, L'\0' };
                SystemTable->ConOut->OutputString(SystemTable->ConOut, echo_str);
            }
        }
    }

    return result; // Возвращаем чистое 32-битное число
}

