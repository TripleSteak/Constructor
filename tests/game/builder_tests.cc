#include "gtest/gtest.h"

TEST(SampleTest, TestingTestPass) {
    EXPECT_EQ(0, 0);
}

TEST(SampleTest, TestingTestFail) {
    EXPECT_EQ(0, 1);
}