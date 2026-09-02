#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Error: Invalid number of arguments. Usage: ./RPN \"<expression>\"" << std::endl;
        return 1;
    }
    
    try
    {
        RPN rpn;
        rpn.executeExpression(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
