/**
 * @ Author: Matthieu Moinvaziri
 * @ Description: Unit tests of Board class
 */

#include <gtest/gtest.h>

#include <MLBoard/Scheduler.hpp>

TEST(Scheduler, InitDestroy)
{
    // No parameters
    Scheduler(std::vector<std::string> {});

    // Invalid parameters
    ASSERT_TRHOW(Scheduler(std::vector<std::string> { "dummy parameter" }));
}
