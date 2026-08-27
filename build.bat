@echo off
cls
echo ==================================================
echo [AstraOS Compiler] Starting automatic build...
echo ==================================================

echo [1/3] Compiling main.c with Clang...
clang -target x86_64-pc-win32-coff -ffreestanding -fshort-wchar -mno-red-zone -Wno-microsoft-cast -c main.c -o boot.o
if %errorlevel% neq 0 (
    echo [ERROR] Clang compilation failed!
    pause
    exit /b
)

echo [2/3] Linking boot.o with lld-link...
lld-link -subsystem:efi_application -nodefaultlib -dll -entry:efi_main boot.o -out:bootx64.efi
if %errorlevel% neq 0 (
    echo [ERROR] Lld-link failed!
    pause
    exit /b
)

echo [3/3] Copying bootx64.efi to virtual disk...
copy bootx64.efi disk\EFI\BOOT\bootx64.efi
if %errorlevel% neq 0 (
    echo [ERROR] Copying failed! Make sure 'disk\EFI\BOOT' folder exists.
    pause
    exit /b
)

echo ==================================================
echo [SUCCESS] AstraOS successfully compiled!
echo [RUN] Launching QEMU Emulator with sound...
echo ==================================================

qemu-system-x86_64 -bios OVMF.fd -drive format=raw,file=fat:rw:disk -audiodev dsound,id=snd0 -machine pcspk-audiodev=snd0

exit
