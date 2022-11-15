
#include <iostream>
#include <gtest/gtest.h>
#include "trie.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        std::vector<int> a{1, 2, 3};

        std::cout << a.size() << std::endl;
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        std::cout << "All done" << std::endl;
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
        }
    return 0;
}