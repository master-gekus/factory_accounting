#include <gtest/gtest.h>
#include <string>

#include "factory_accounting.hpp"

TEST(FactoryAccounting, CreateEmpty) {
  facc::FactoryAccounting<std::string> factory;

  EXPECT_EQ(factory.employees().size(), 0);
}

TEST(FactoryAccounting, AddWorkers) {
  {
    using Factory = facc::FactoryAccounting<std::string>;
    Factory factory;
    const auto *w1{factory.addWorker(100u, 0, "Worker 1")};
    EXPECT_EQ(factory.employees().size(), 1);
    const auto *w2{factory.addWorker(200u, 2, "Worker 2")};
    EXPECT_EQ(factory.employees().size(), 2);
    EXPECT_EQ(w1->data(), "Worker 1");
    EXPECT_EQ(w2->data(), "Worker 2");
    EXPECT_EQ(w1->subs().size(), 0);
    EXPECT_EQ(w2->subs().size(), 0);
    EXPECT_EQ(w1->boss(), nullptr);
    EXPECT_EQ(w2->boss(), nullptr);
    EXPECT_TRUE((w1->type() == Factory::Type::Worker));
    EXPECT_TRUE((w2->type() == Factory::Type::Worker));
    EXPECT_EQ(w1->basicSalary(), 100u);
    EXPECT_EQ(w2->basicSalary(), 200u);
    EXPECT_EQ(w1->relativeStart(), 0);
    EXPECT_EQ(w2->relativeStart(), 2);
  }
  {
    struct name {
      std::string n1;
      std::string n2;
    };

    using Factory = facc::FactoryAccounting<name>;
    Factory factory;
    auto *w1{factory.addWorker(100u, 0, "Worker 1 n1", "Worker 1 n2")};
    EXPECT_EQ(factory.employees().size(), 1);
    auto *w2{factory.addWorker(200u, 2, "Worker 2 n1", "Worker 2 n2")};
    EXPECT_EQ(factory.employees().size(), 2);
    EXPECT_EQ(w1->data().n1, "Worker 1 n1");
    EXPECT_EQ(w1->data().n2, "Worker 1 n2");
    EXPECT_EQ(w2->data().n1, "Worker 2 n1");
    EXPECT_EQ(w2->data().n2, "Worker 2 n2");
    EXPECT_EQ(w1->subs().size(), 0);
    EXPECT_EQ(w2->subs().size(), 0);
    EXPECT_EQ(w1->boss(), nullptr);
    EXPECT_EQ(w2->boss(), nullptr);
    EXPECT_TRUE((w1->type() == Factory::Type::Worker));
    EXPECT_TRUE((w2->type() == Factory::Type::Worker));
    EXPECT_EQ(w1->basicSalary(), 100u);
    EXPECT_EQ(w2->basicSalary(), 200u);
    EXPECT_EQ(w1->relativeStart(), 0);
    EXPECT_EQ(w2->relativeStart(), 2);
  }
}
