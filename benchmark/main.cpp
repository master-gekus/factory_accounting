#include <chrono>
#include <iostream>
#include <string>

#include "factory_accounting.hpp"

using Factory = facc::FactoryAccounting<std::string>;
using Employee = Factory::Employee;
using Worker = Factory::Worker;
using Foreman = Factory::Foreman;
using Manager = Factory::Manager;

using namespace std::chrono;

void createTree(Factory &factory,
                unsigned managers,
                unsigned foremen_per_manager,
                unsigned workers_per_foreman) {
  {
    const auto start{steady_clock::now()};
    for (unsigned i = 0; i < managers; ++i) {
      auto *m = factory.hire<Manager>(100u, 0);
      for (unsigned j = 0; j < foremen_per_manager; ++j) {
        auto *f = factory.hire<Foreman>(100u, 0);
        factory.createSubordination(m, f);
        for (unsigned k = 0; k < workers_per_foreman; ++k) {
          factory.createSubordination(f, factory.hire<Worker>(100u, 0));
        }
      }
    }
    std::cout
        << "Creating (" << managers << ", " << foremen_per_manager << ", "
        << workers_per_foreman << "): "
        << duration_cast<milliseconds>(steady_clock::now() - start).count()
        << std::endl;
  }
  {
    const auto start{steady_clock::now()};
    factory.totalSalary(100);
    std::cout
        << "Calc for 100 months): "
        << duration_cast<milliseconds>(steady_clock::now() - start).count()
        << std::endl;
  }
}

int main(int, char **) {
  {
    Factory factory;
    createTree(factory, 1, 1000, 1000);
  }
  return 0;
}
