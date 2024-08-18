#include <iostream>
#include <Platform/Defines.hpp>

int main(int argc, char const *argv[])
{
    #if GE_PLATFORM_LINUX

    std::cout << "Platform Linux" << std::endl;

    #endif

    return 0;
}
