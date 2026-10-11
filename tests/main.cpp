#include <gtest/gtest.h>
#include <string>

#include "factory_accounting.hpp"

TEST(FactoryAccounting, CreateEmpty) {
  facc::FactoryAccounting<std::string> factory;

  EXPECT_EQ(factory.employees().size(), 0);
}
