#include <windows.h>
#include <string>
#include <iostream>


std::string getProcArchitecture(SYSTEM_INFO& si)
{
    std::string procArc = "";

    switch (si.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_AMD64:
        procArc = "x64";
        break;
    case PROCESSOR_ARCHITECTURE_ARM:
        procArc = "ARM";
        break;
    case PROCESSOR_ARCHITECTURE_ARM64:
        procArc = "ARM64";
        break;
    case PROCESSOR_ARCHITECTURE_IA64:
        procArc = "Intel Itanium-based";
        break;
    case PROCESSOR_ARCHITECTURE_INTEL:
        procArc = "x86";
        break;
    default:
        procArc = "Unknown architecture";
    }

    return procArc;
}


std::string getSysInfo(SYSTEM_INFO& si) 
{
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    GetVersionEx((LPOSVERSIONINFO)&osvi);

    std::string winvi = "";
    if      (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0 && osvi.wProductType == VER_NT_WORKSTATION)    winvi = "Windows 10";
    else if (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0 && osvi.wProductType != VER_NT_WORKSTATION)    winvi = "Windows Server 2016";
    else if (osvi.dwMajorVersion == 6  && osvi.dwMinorVersion == 3 && osvi.wProductType == VER_NT_WORKSTATION)    winvi = "Windows 8.1";
    else if (osvi.dwMajorVersion == 6  && osvi.dwMinorVersion == 3 && osvi.wProductType != VER_NT_WORKSTATION)    winvi = "Windows Server 2012 R2";
    else if (osvi.dwMajorVersion == 6  && osvi.dwMinorVersion == 2 && osvi.wProductType == VER_NT_WORKSTATION)    winvi = "Windows 8";
    else if (osvi.dwMajorVersion == 6  && osvi.dwMinorVersion == 2 && osvi.wProductType != VER_NT_WORKSTATION)    winvi = "Windows Server 2012";
    else if (osvi.dwMajorVersion == 6  && osvi.dwMinorVersion == 1 && osvi.wProductType == VER_NT_WORKSTATION)    winvi = "Windows 7";
    else if (osvi.dwMajorVersion == 6  && osvi.dwMinorVersion == 1 && osvi.wProductType != VER_NT_WORKSTATION)    winvi = "Windows Server 2008 R2";
    else if (osvi.dwMajorVersion == 6  && osvi.dwMinorVersion == 0 && osvi.wProductType != VER_NT_WORKSTATION)    winvi = "Windows Server 2008";
    else if (osvi.dwMajorVersion == 6  && osvi.dwMinorVersion == 0 && osvi.wProductType == VER_NT_WORKSTATION)    winvi = "Windows Vista";
    else if (osvi.dwMajorVersion == 5  && osvi.dwMinorVersion == 2 && GetSystemMetrics(SM_SERVERR2) != 0)         winvi = "Windows Server 2003 R2";
    else if (osvi.dwMajorVersion == 5  && osvi.dwMinorVersion == 2 && osvi.wSuiteMask & VER_SUITE_WH_SERVER)      winvi = "Windows Home Server";
    else if (osvi.dwMajorVersion == 5  && osvi.dwMinorVersion == 2 && GetSystemMetrics(SM_SERVERR2) == 0)         winvi = "Windows Server 2003";
    else if (osvi.dwMajorVersion == 5  && osvi.dwMinorVersion == 2 && 
        (osvi.wProductType == VER_NT_WORKSTATION) && (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)) winvi = "Windows XP Professional x64 Edition";
    else if (osvi.dwMajorVersion == 5  && osvi.dwMinorVersion == 1)                                               winvi = "Windows XP";
    else if (osvi.dwMajorVersion == 5  && osvi.dwMinorVersion == 0)                                               winvi = "Windows 2000";

    std::string spvi = "";
    if (osvi.wServicePackMajor != 0) spvi = " Service Pack #" + std::to_string(osvi.wServicePackMajor) + "." + std::to_string(osvi.wServicePackMinor);

    std::string buildInfo = std::to_string(osvi.dwBuildNumber);

    std::string sysInfo = winvi + spvi + " (Build " + buildInfo + ")";
    return sysInfo;
}


int main()
{
    SYSTEM_INFO si;
    GetSystemInfo(&si);

    std::string procArc = getProcArchitecture(si);
    std::string sysInfo = getSysInfo(si);

    std::cout << "Operating system: " << sysInfo << " " << procArc << std::endl;

    system("pause");
    return 0;
}