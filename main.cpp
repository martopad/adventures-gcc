#include <iostream>
#include <string>

//conan
#include <fmt/format.h>
#include <boost/regex.hpp>

//#include <boost/safe_numerics/safe_integer.hpp> // need to update gcc

int main()
{
    std::string s = fmt::format("{}", 42);
    std::cout << "Hello World: " << s <<'\n';
    static const boost::regex e("<(From )?([A-Za-z0-9_]+)>(.*?)");

    return 0;
}