#include "../../src/common/resource.h"
#include "gtest/gtest.h"

TEST(Resource, InputOperatorForValidResources) {
    std::istringstream in("BRICK ENERGY GLASS HEAT WIFI");

    Resource res1, res2, res3, res4, res5;
    in >> res1 >> res2 >> res3 >> res4 >> res5;

    EXPECT_EQ(res1, BRICK);
    EXPECT_EQ(res2, ENERGY);
    EXPECT_EQ(res3, GLASS);
    EXPECT_EQ(res4, HEAT);
    EXPECT_EQ(res5, WIFI);
}

TEST(Resource, InputOperatorForPark) {
    std::istringstream in("PARK");
    Resource resource;
    EXPECT_ANY_THROW(in >> resource);
}

TEST(Resource, InputOperatorForInvalidResource) {
    std::istringstream in("STONE");
    Resource resource;
    EXPECT_ANY_THROW(in >> resource);
}

TEST(Resource, OutputOperatorForResources) {
    std::ostringstream out;
    out << BRICK << " " << ENERGY << " " << GLASS << " " << HEAT << " " << PARK << " " << WIFI;
    EXPECT_EQ(out.str(), "BRICK ENERGY GLASS HEAT PARK WIFI");
}
