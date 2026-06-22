#include <Windows.h>

DWORD WINAPI func(void* me) {
    auto proc = GetCurrentProcess();
    auto base = reinterpret_cast<char*>(GetModuleHandle(NULL));
    using u8 = unsigned char;
    static const u8 patch[] = {0x3F, 0x00, 0x00, 0x00};
    WriteProcessMemory(proc, base + 0x20A677, patch, 4, NULL);

    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(me), 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE mod, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH)
        if (auto h = CreateThread(NULL, 0, &func, mod, 0, NULL))
            CloseHandle(h);
    return TRUE;
}
