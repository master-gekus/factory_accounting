#ifndef FACC_FACTORY_ACCOUNTING_HPP_INCLUDED
#define FACC_FACTORY_ACCOUNTING_HPP_INCLUDED

#include <list>
#include "employee.hpp"
#include "worker.hpp"

namespace facc {
  template <class D>
  class FactoryAccounting final {
   public:
    using Type = typename facc::Employee<D>::Type;
    using Employee = typename facc::Employee<D>;
    using Worker = typename facc::Worker<D>;

   public:
    ~FactoryAccounting() {
      for (auto *e : employees_) {
        delete e;
      }
    }

   public:
    const auto &employees() const noexcept {
      return employees_;
    }

   public:
    template <typename... Args>
    const Employee *addWorker(Args &&...args) {
      auto *worker = new Worker{std::forward<Args>(args)...};
      employees_.push_back(worker);
      return worker;
    }

   private:
    std::list<Employee *> employees_;
  };
}  // namespace facc

#endif  // FACC_FACTORY_ACCOUNTING_HPP_INCLUDED
