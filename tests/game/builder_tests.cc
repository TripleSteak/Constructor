#include "gtest/gtest.h"
#include "../../src/game/builder.h"

TEST(Builder, GetBuilderNumber) {
    int builderNumber = 3;
    Builder builder = Builder(builderNumber, 'G');
    EXPECT_EQ(builder.getBuilderNumber(), builderNumber);
}

TEST(Builder, GetBuilderColour) {
    char builderColour = 'B';
    Builder builder = Builder(2, builderColour);
    EXPECT_EQ(builder.getBuilderColour(), builderColour);
}

TEST(Builder, GetBuildingPointsEmpty) {
    Builder builder = Builder(3, 'G');
    EXPECT_EQ(builder.getBuildingPoints(), 0);
}
