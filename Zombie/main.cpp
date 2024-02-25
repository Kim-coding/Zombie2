#include "pch.h"

int main()
{
    FRAMEWORK.Init(1920, 
        80, "Timber");
    FRAMEWORK.Do();
    FRAMEWORK.Release();
    return 0;
}