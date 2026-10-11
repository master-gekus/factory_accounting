#include <gtest/gtest.h>
#include <string>

#include "factory_accounting.hpp"

TEST(FactoryAccounting, CreateEmpty) {
  facc::FactoryAccounting<std::string> factory;

  EXPECT_EQ(factory.employees().size(), 0);
}

TEST(FactoryAccounting, HireWorkers) {
  {
    using Factory = facc::FactoryAccounting<std::string>;
    Factory factory;
    const auto *w1{factory.hire<Factory::Worker>(100u, 0, "Worker 1")};
    EXPECT_EQ(factory.employees().size(), 1);
    const auto *w2{factory.hire<Factory::Worker>(200u, 2, "Worker 2")};
    EXPECT_EQ(factory.employees().size(), 2);
    EXPECT_EQ(w1->data(), "Worker 1");
    EXPECT_EQ(w2->data(), "Worker 2");
    EXPECT_EQ(w1->subs().size(), 0);
    EXPECT_EQ(w2->subs().size(), 0);
    EXPECT_EQ(w1->boss(), nullptr);
    EXPECT_EQ(w2->boss(), nullptr);
    EXPECT_TRUE(w1->type() == Factory::Type::Worker);
    EXPECT_TRUE(w2->type() == Factory::Type::Worker);
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
    auto *w1{
        factory.hire<Factory::Worker>(100u, 0, "Worker 1 n1", "Worker 1 n2")};
    EXPECT_EQ(factory.employees().size(), 1);
    auto *w2{
        factory.hire<Factory::Worker>(200u, 2, "Worker 2 n1", "Worker 2 n2")};
    EXPECT_EQ(factory.employees().size(), 2);
    EXPECT_EQ(w1->data().n1, "Worker 1 n1");
    EXPECT_EQ(w1->data().n2, "Worker 1 n2");
    EXPECT_EQ(w2->data().n1, "Worker 2 n1");
    EXPECT_EQ(w2->data().n2, "Worker 2 n2");
    EXPECT_EQ(w1->subs().size(), 0);
    EXPECT_EQ(w2->subs().size(), 0);
    EXPECT_EQ(w1->boss(), nullptr);
    EXPECT_EQ(w2->boss(), nullptr);
    EXPECT_TRUE(w1->type() == Factory::Type::Worker);
    EXPECT_TRUE(w2->type() == Factory::Type::Worker);
    EXPECT_EQ(w1->basicSalary(), 100u);
    EXPECT_EQ(w2->basicSalary(), 200u);
    EXPECT_EQ(w1->relativeStart(), 0);
    EXPECT_EQ(w2->relativeStart(), 2);
  }
}

TEST(FactoryAccounting, HireForeman) {
  using Factory = facc::FactoryAccounting<std::string>;
  Factory factory;
  const auto *f{factory.hire<Factory::Foreman>(100u, 0, "Foreman 1")};
  EXPECT_EQ(factory.employees().size(), 1);
  EXPECT_EQ(f->data(), "Foreman 1");
  EXPECT_EQ(f->subs().size(), 0);
  EXPECT_EQ(f->boss(), nullptr);
  EXPECT_TRUE(f->type() == Factory::Type::Foreman);
  EXPECT_EQ(f->basicSalary(), 100u);
  EXPECT_EQ(f->relativeStart(), 0);
}

TEST(FactoryAccounting, HireManager) {
  using Factory = facc::FactoryAccounting<std::string>;
  Factory factory;
  const auto *m{factory.hire<Factory::Manager>(100u, 0, "Foreman 1")};
  EXPECT_EQ(factory.employees().size(), 1);
  EXPECT_EQ(m->data(), "Foreman 1");
  EXPECT_EQ(m->subs().size(), 0);
  EXPECT_EQ(m->boss(), nullptr);
  EXPECT_TRUE(m->type() == Factory::Type::Manager);
  EXPECT_EQ(m->basicSalary(), 100u);
  EXPECT_EQ(m->relativeStart(), 0);
}
