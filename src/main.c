#pragma once
#include "inc/efi.h"
#include <stdint.h>
#include "headers/sound.h"
#include "headers/uefilib.h"
#include <stdbool.h>

// (c) 2026 Portal. All rights reserved.
// Daniel Shirvanyan developer

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    SystemTable->ConOut->EnableCursor(SystemTable->ConOut, 0);
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Choose option\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"1 Continue booting\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"2 Restart\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"3 Shutdown\r\n");
    
    EFI_INPUT_KEY key;
    while(SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &key) == EFI_NOT_READY) { }
    
    if(key.UnicodeChar == L'2') {
        SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
    if(key.UnicodeChar == L'3') {
        SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
    }
    
    bool shutdown = false;
    CHAR16 command[50]; 
    bool admin = false;
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 2);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"+-------------------------------------------------------------+\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"|                                                             |\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"|   XXXXX   XXXXXX  XXXXXXX  XXXXXX   XXXXX    XXXXXX   XXXXX |\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"|  XX   XX XX          XX    XX   XX XX   XX  XX    XX XX     |\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"|  XXXXXXX  XXXXX      XX    XXXXXX  XXXXXXX  XX    XX  XXXXX |\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"|  XX   XX      XX     XX    XX   XX XX   XX  XX    XX      XX|\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"|  XX   XX XXXXXX      XX    XX   XX XX   XX   XXXXXX  XXXXXX |\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"|                                                             |\r\n");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"+-------------------------------------------------------------+\r\n"); 
    beep_on(200);
    SystemTable->BootServices->Stall(1000000);
    beep_on(500);
    SystemTable->BootServices->Stall(1000000);
    beep_on(800);
    SystemTable->BootServices->Stall(2000000);
    beep_off();
   
    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, 0x07);
    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Welcome to AstraOS ver 0.2 type help for see commands.\r\n");
    // SystemTable->ConOut->OutputString(SystemTable->ConOut, L"You can see our site\r\n");
    SystemTable->ConOut->EnableCursor(SystemTable->ConOut, 1);
    
    while(shutdown == false) {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"AstraOS>");
        
        
        Input(SystemTable, command, 50);
        SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
        
        
        if(StrCmp(command, L"ver") == 0) {
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"AstraOS version 0.2\r\n");
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Terminal version 0.2\r\n");
        }
        else if(StrCmp(command, L"shutdown") == 0) {
            shutdown = true;
        }
        else if(StrCmp(command, L"restart") == 0) {
            SystemTable->RuntimeServices->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
        }
        else if(StrCmp(command, L"help") == 0){
            SystemTable->ConOut->OutputString(SystemTable->ConOut,L"Available commands: cls,help,ver,shutdown,restart,setting\r\n");
        }
        else if(StrCmp(command, L"") == 0){
        }
        else if(StrCmp(command, L"cls") == 0){
            SystemTable->ConOut->ClearScreen(SystemTable->ConOut);
        }
        else if (StrCmp(command, L"setting -u") == 0){
            admin = true;
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"You are Admin\r\n");
        }
        // help command -h argument
        else if( StrCmp(command, L"setting -h") == 0){
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"This is setting help\r\n");
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Available Arguments:\r\n");
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"-u - Admin set\r\n");
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"-h - help\r\n");

        }
        else if(StrCmp(command, L"setting") == 0){
            SystemTable->ConOut->OutputString(SystemTable->ConOut, L"For see setting command argument type setting -h\r\n");
        }
        


        else{
            SystemTable->ConOut->OutputString(SystemTable->ConOut,L"Invalid command\r\n");
        }
    }
    SystemTable->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_SUCCESS, 0, NULL);
    return EFI_SUCCESS;
}

