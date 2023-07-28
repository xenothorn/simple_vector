#include "simple_vector.h"
#include <iostream>
// Tests
#include "tests.h"

int main() {
 //   Test1();

    SimpleVector v{1,2,3,4,5,6};
    SimpleVector s{"hell", "bell", "tell"};

    for (int i = 0; i < 3; i++)
    {
        std::cout << s[i] << ' ';
    }std::cout << std::endl;

    for (int i = 0; i < 3; i++)
    {
        std::cout << s.At(i) << ' ';
    }std::cout << std::endl;

    for (auto it = s.begin(); it != s.end(); it++)
    {
        std::cout << *it << ' ';
    }std::cout << std::endl;

    s.Resize(10);
    
    for (auto it = s.begin(); it != s.end(); it++)
    {
        std::cout << *it << ' ';
    }std::cout << std::endl;    


    std::cout << " -- OK --- " << std::endl;



    return 0;
}