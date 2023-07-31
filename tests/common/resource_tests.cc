#include "../../src/common/resource.h"
#include "gtest/gtest.h"

TEST(Resource, InputOperatorForValidResources) {
    std::istringstream in("0 1 2 3 4 5");

    Resource res1, res2, res3, res4, res5, res6;
    in >> res1 >> res2 >> res3 >> res4 >> res5 >> res6;

    EXPECT_EQ(res1, BRICK);
    EXPECT_EQ(res2, ENERGY);
    EXPECT_EQ(res3, GLASS);
    EXPECT_EQ(res4, HEAT);
    EXPECT_EQ(res5, WIFI);
    EXPECT_EQ(res6, PARK);
}

TEST(Resource, InputOperatorForInvalidResource) {
    std::istringstream in("6");
    Resource resource;
    EXPECT_ANY_THROW(in >> resource);
}

TEST(Resource, OutputOperatorForResources) {
    std::ostringstream out;
    out << BRICK << " " << ENERGY << " " << GLASS << " " << HEAT << " " << PARK << " " << WIFI;
    EXPECT_EQ(out.str(), "BRICK ENERGY GLASS HEAT PARK WIFI");
}
