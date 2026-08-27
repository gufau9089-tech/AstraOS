#pragma once
#include "inc/efi.h"


int StrCmp(CHAR16 *str1, CHAR16 *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

void Input(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *buffer, UINTN max_size) {
    EFI_INPUT_KEY key;
    UINTN index = 0;
    
    while (index < max_size - 1) {
  
        while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) == EFI_NOT_READY) { }
        
        if (key.UnicodeChar == L'\r') {
            break;
        }
        
        if (key.UnicodeChar == L'\b') {
            if (index > 0) {
                index--;
                SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\b \b");
            }
            continue;
        }
        
        if (key.UnicodeChar >= 32) {
            buffer[index] = key.UnicodeChar;
            CHAR16 echo_str[] = { key.UnicodeChar, L'\0' };
            SystemTable->ConOut->OutputString(SystemTable->ConOut, echo_str);
            index++;
        }
    }
    buffer[index] = L'\0';
}

UINT32 InputUint32(EFI_SYSTEM_TABLE* SystemTable) {
    EFI_INPUT_KEY key;
    UINT32 result = 0;
    UINTN digits_count = 0;

    while (1) {
       
        while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) == EFI_NOT_READY) {}

       
        if (key.UnicodeChar == L'\r' || key.UnicodeChar == L'\n') {
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
            break;
        }

     
        if (key.UnicodeChar == L'\b') {
            if (digits_count > 0) {
                digits_count--;
                result = result / 10;
                SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\b \b"); 
            }
            continue;
        }

      
        if (key.UnicodeChar >= L'0' && key.UnicodeChar <= L'9') {
           
            if (digits_count < 10) {
                UINT32 digit = key.UnicodeChar - L'0';
                result = (result * 10) + digit;      
                digits_count++;
                CHAR16 echo_str[] = { key.UnicodeChar, L'\0' };
                SystemTable->ConOut->OutputString(SystemTable->ConOut, echo_str);
            }
        }
    }

    return result;
}

