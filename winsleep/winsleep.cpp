// winsleep.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>

int getNum(wchar_t c)
{
    if (!(L'0' <= c && c <= L'9'))
    {
        const char message[] = "Not a number\r\n";
        DWORD dwWritten;
        WriteFile(GetStdHandle(STD_ERROR_HANDLE),
            message,
            sizeof(message)-1,
            &dwWritten,
            nullptr);
        ExitProcess(1);
    }
    return c - L'0';
}

size_t getLen(LPWSTR p)
{
    size_t len = 0;
    for (; *p; ++p)
        ++len;
    return len;
}
unsigned long long power10(size_t nKeta)
{
    unsigned long long nRet = 1;
    for (size_t n = 0; n < nKeta; ++n)
        nRet *= 10;
    return nRet;
}
void entry()
{
    LPWSTR p = GetCommandLine();
    bool bDQed = *p == L'"';
    if (bDQed)
        ++p;
    for (; *p; ++p)
    {
        if (bDQed)
        {
            if (*p == L'"')
            {
                bDQed = false;
            }
        }
        else
        {
            if (*p == L' ')
                break;
        }
    }
    for (; *p; ++p)
    {
        if (*p != L' ')
            break;
    }
    int len = (int)getLen(p);

    unsigned long long nWait = 0;
    size_t nKeta = 1;

    size_t index = 0;
    for (int i = len - 1; i >= 0; --i,++index)
    {
        nWait += getNum(p[index]) * power10(i);
    }
    Sleep((DWORD)nWait);
}
