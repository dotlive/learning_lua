#include "test/test_case.h"

int main(int argc, char* argv[])
{
    std::cout << "test_luastack---------------------------------------" << std::endl;
    test_luastack();
    std::cout << "test_cppcalllua-------------------------------------" << std::endl;
    test_cppcalllua();
    std::cout << "test_luacallcpp-------------------------------------" << std::endl;
    test_luacallcpp();
    std::cout << "test_customsearcher---------------------------------" << std::endl;
    test_customsearcher();

    system("pause");
    return 0;
}
