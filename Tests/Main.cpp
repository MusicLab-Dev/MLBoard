/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Board tests entry
 */

#include <iostream>

#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    try {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    } catch (const std::exception &e) {
        std::cout << "An error occured while testing:\n\t" << e.what() << std::endl;
    }
}