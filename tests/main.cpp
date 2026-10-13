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
    auto *w1{factory.hire<Factory::Worker>(100u, 0, "Worker 1")};
    EXPECT_EQ(factory.employees().size(), 1);
    auto *w2{factory.hire<Factory::Worker>(200u, 2, "Worker 2")};
    EXPECT_EQ(factory.employees().size(), 2);
    EXPECT_EQ(w1->data(), "Worker 1");
    EXPECT_EQ(w2->data(), "Worker 2");
    EXPECT_EQ(w1->subs().size(), 0);
    EXPECT_EQ(w2->subs().size(), 0);
    EXPECT_EQ(w1->boss(), nullptr);
    EXPECT_EQ(w2->boss(), nullptr);
    EXPECT_NE(dynamic_cast<Factory::Worker *>(w1), nullptr);
    EXPECT_NE(dynamic_cast<Factory::Worker *>(w2), nullptr);
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
    EXPECT_NE(dynamic_cast<Factory::Worker *>(w1), nullptr);
    EXPECT_NE(dynamic_cast<Factory::Worker *>(w2), nullptr);
    EXPECT_EQ(w1->basicSalary(), 100u);
    EXPECT_EQ(w2->basicSalary(), 200u);
    EXPECT_EQ(w1->relativeStart(), 0);
    EXPECT_EQ(w2->relativeStart(), 2);
  }
}

TEST(FactoryAccounting, HireForeman) {
  using Factory = facc::FactoryAccounting<std::string>;
  Factory factory;
  auto *f{factory.hire<Factory::Foreman>(100u, 0, "Foreman 1")};
  EXPECT_EQ(factory.employees().size(), 1);
  EXPECT_EQ(f->data(), "Foreman 1");
  EXPECT_EQ(f->subs().size(), 0);
  EXPECT_EQ(f->boss(), nullptr);
  EXPECT_NE(dynamic_cast<Factory::Foreman *>(f), nullptr);
  EXPECT_EQ(f->basicSalary(), 100u);
  EXPECT_EQ(f->relativeStart(), 0);
}

TEST(FactoryAccounting, HireManager) {
  using Factory = facc::FactoryAccounting<std::string>;
  Factory factory;
  auto *m{factory.hire<Factory::Manager>(100u, 0, "Manager 1")};
  EXPECT_EQ(factory.employees().size(), 1);
  EXPECT_EQ(m->data(), "Manager 1");
  EXPECT_EQ(m->subs().size(), 0);
  EXPECT_EQ(m->boss(), nullptr);
  EXPECT_NE(dynamic_cast<Factory::Manager *>(m), nullptr);
  EXPECT_EQ(m->basicSalary(), 100u);
  EXPECT_EQ(m->relativeStart(), 0);
}

TEST(FactoryAccounting, SimpleHireAndFire) {
  using Factory = facc::FactoryAccounting<std::string>;
  Factory factory;
  auto *w{factory.hire<Factory::Worker>(100u, 0, "Worker")};
  auto *f{factory.hire<Factory::Worker>(100u, 0, "Foreman")};
  auto *m{factory.hire<Factory::Worker>(100u, 0, "Manager")};
  EXPECT_EQ(factory.employees().size(), 3);
  factory.fire(w);
  EXPECT_EQ(factory.employees().size(), 2);
  factory.fire(w);
  EXPECT_EQ(factory.employees().size(), 2);
  factory.fire(m);
  EXPECT_EQ(factory.employees().size(), 1);
  factory.fire(m);
  EXPECT_EQ(factory.employees().size(), 1);
  factory.fire(f);
  EXPECT_EQ(factory.employees().size(), 0);
  factory.fire(f);
  EXPECT_EQ(factory.employees().size(), 0);
}

TEST(FactoryAccounting, SimpleSubordination) {
  using Factory = facc::FactoryAccounting<std::string>;
  Factory factory;
  auto *w{factory.hire<Factory::Worker>(100u, 0, "Worker")};
  auto *f{factory.hire<Factory::Foreman>(100u, 0, "Foreman")};
  auto *m{factory.hire<Factory::Manager>(100u, 0, "Manager")};
  EXPECT_FALSE(factory.createSubordination(w, f));
  EXPECT_FALSE(factory.createSubordination(w, m));
  EXPECT_FALSE(factory.createSubordination(f, f));
  EXPECT_FALSE(factory.createSubordination(m, m));
  EXPECT_TRUE(factory.createSubordination(f, w));
  EXPECT_TRUE(factory.createSubordination(m, f));
  EXPECT_FALSE(factory.createSubordination(f, w));
  EXPECT_FALSE(factory.createSubordination(m, f));

  EXPECT_EQ(w->boss(), f);
  EXPECT_EQ(f->boss(), m);
  EXPECT_EQ(f->subs().size(), 1);
  EXPECT_TRUE(f->subs().contains(w));
  EXPECT_EQ(m->subs().size(), 1);
  EXPECT_TRUE(m->subs().contains(f));
}

TEST(FactoryAccounting, ChangeSubordination) {
  using Factory = facc::FactoryAccounting<std::string>;
  Factory factory;
  auto *w{factory.hire<Factory::Worker>(100u, 0, "Worker")};
  auto *f{factory.hire<Factory::Foreman>(100u, 0, "Foreman")};
  auto *m{factory.hire<Factory::Manager>(100u, 0, "Manager")};
  EXPECT_TRUE(factory.createSubordination(f, w));
  EXPECT_TRUE(factory.createSubordination(m, f));
  EXPECT_FALSE(factory.createSubordination(f, w));
  EXPECT_FALSE(factory.createSubordination(m, f));

  EXPECT_EQ(w->boss(), f);
  EXPECT_EQ(f->boss(), m);
  EXPECT_EQ(f->subs().size(), 1);
  EXPECT_TRUE(f->subs().contains(w));
  EXPECT_EQ(m->subs().size(), 1);
  EXPECT_TRUE(m->subs().contains(f));

  // Отдаём рабочего менеджеру. У бригадира никого не остаётся. У менеджера -
  // двое.
  EXPECT_TRUE(factory.createSubordination(m, w));
  EXPECT_EQ(f->subs().size(), 0);
  EXPECT_EQ(w->boss(), m);
  EXPECT_EQ(m->subs().size(), 2);
  EXPECT_TRUE(m->subs().contains(w));
  EXPECT_TRUE(m->subs().contains(f));
}

TEST(FactoryAccounting, ReleaseSubordination) {
  using Factory = facc::FactoryAccounting<std::string>;
  Factory factory;
  auto *w1{factory.hire<Factory::Worker>(100u, 0, "Worker 1")};
  auto *w2{factory.hire<Factory::Worker>(100u, 0, "Worker 2")};
  auto *f{factory.hire<Factory::Foreman>(100u, 0, "Foreman")};
  auto *m{factory.hire<Factory::Manager>(100u, 0, "Manager")};
  EXPECT_TRUE(factory.createSubordination(f, w1));
  EXPECT_TRUE(factory.createSubordination(f, w2));
  EXPECT_TRUE(factory.createSubordination(m, f));

  EXPECT_EQ(w1->boss(), f);
  EXPECT_EQ(w2->boss(), f);
  EXPECT_EQ(f->subs().size(), 2);
  EXPECT_TRUE(f->subs().contains(w1));
  EXPECT_TRUE(f->subs().contains(w2));

  EXPECT_EQ(f->boss(), m);
  EXPECT_EQ(m->subs().size(), 1);
  EXPECT_TRUE(m->subs().contains(f));

  EXPECT_FALSE(factory.releaseSubordination(m, w1));
  EXPECT_TRUE(factory.releaseSubordination(f, w1));
  EXPECT_FALSE(factory.releaseSubordination(f, w1));

  EXPECT_EQ(w1->boss(), nullptr);
  EXPECT_EQ(w2->boss(), f);
  EXPECT_EQ(f->subs().size(), 1);
  EXPECT_TRUE(f->subs().contains(w2));

  EXPECT_EQ(f->boss(), m);
  EXPECT_EQ(m->subs().size(), 1);
  EXPECT_TRUE(m->subs().contains(f));
}

TEST(FactoryAccounting, Salary) {
  using Factory = facc::FactoryAccounting<std::string>;
  Factory factory;
  auto *w1{factory.hire<Factory::Worker>(100u, 0)};
  auto *w2{factory.hire<Factory::Worker>(100u, 1)};
  auto *w3{factory.hire<Factory::Worker>(100u, 2)};
  auto *f1{factory.hire<Factory::Foreman>(200u, 0)};
  auto *f2{factory.hire<Factory::Foreman>(200u, 1)};
  auto *m{factory.hire<Factory::Manager>(300u, 0)};
  ASSERT_TRUE(factory.createSubordination(f1, w1));
  ASSERT_TRUE(factory.createSubordination(f2, w2));
  ASSERT_TRUE(factory.createSubordination(f2, w3));
  ASSERT_TRUE(factory.createSubordination(m, f1));
  ASSERT_TRUE(factory.createSubordination(m, f2));

  EXPECT_EQ(w1->totalSalary(1), 100u);
  EXPECT_EQ(w2->totalSalary(1), 0);
  EXPECT_EQ(w3->totalSalary(1), 0);
  EXPECT_EQ(f1->totalSalary(1), 207u);
  EXPECT_EQ(f2->totalSalary(1), 0);

  EXPECT_EQ(w1->totalSalary(2), 100u);
  EXPECT_EQ(w2->totalSalary(2), 100u);
  EXPECT_EQ(w3->totalSalary(2), 0u);
  EXPECT_EQ(f1->totalSalary(2), 207u);
  EXPECT_EQ(f2->totalSalary(2), 207u);

  EXPECT_EQ(w1->totalSalary(10), 100u);
  EXPECT_EQ(w2->totalSalary(10), 100u);
  EXPECT_EQ(w3->totalSalary(10), 100u);
  EXPECT_EQ(f1->totalSalary(10), 207u);
  EXPECT_EQ(f2->totalSalary(10), 214u);

  EXPECT_EQ(w1->totalSalary(12), 110u);
  EXPECT_EQ(w2->totalSalary(12), 100u);
  EXPECT_EQ(w3->totalSalary(12), 100u);
  EXPECT_EQ(f1->totalSalary(12), 217u);
  EXPECT_EQ(f2->totalSalary(12), 214u);

  EXPECT_EQ(w1->totalSalary(26), 120u);
  EXPECT_EQ(w2->totalSalary(26), 120u);
  EXPECT_EQ(w3->totalSalary(26), 120u);
  EXPECT_EQ(f1->totalSalary(26), 228u);
  EXPECT_EQ(f2->totalSalary(26), 236u);

  EXPECT_EQ(m->totalSalary(1), 309u);
  EXPECT_EQ(m->totalSalary(2), 318u);
  EXPECT_EQ(m->totalSalary(10), 321u);
  EXPECT_EQ(m->totalSalary(12), 322u);
  EXPECT_EQ(m->totalSalary(26), 324u);

  EXPECT_EQ(factory.totalSalary(1), 616u);
  EXPECT_EQ(factory.totalSalary(2), 932u);
  EXPECT_EQ(factory.totalSalary(10), 1042u);
  EXPECT_EQ(factory.totalSalary(12), 1063u);
  EXPECT_EQ(factory.totalSalary(26), 1148u);
}
