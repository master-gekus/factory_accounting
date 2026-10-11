#ifndef FACC_FACTORY_ACCOUNTING_HPP_INCLUDED
#define FACC_FACTORY_ACCOUNTING_HPP_INCLUDED

#include <set>
#include <type_traits>

#include "employee.hpp"
#include "foreman.hpp"
#include "manager.hpp"
#include "worker.hpp"

namespace facc {
  template <class D>
  class FactoryAccounting final {
   public:
    using Type = typename facc::Employee<D>::Type;
    using Employee = typename facc::Employee<D>;
    using Worker = typename facc::Worker<D>;
    using Foreman = typename facc::Foreman<D>;
    using Manager = typename facc::Manager<D>;

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
    template <typename T, typename... Args>
    /// \todo Переделать на requires
    typename std::enable_if<std::is_same_v<T, Worker>
                                || std::is_same_v<T, Foreman>
                                || std::is_same_v<T, Manager>,
                            Employee *>::type hire(Args &&...args) {
      auto *employee = new T{std::forward<Args>(args)...};
      employees_.insert(employee);
      return employee;
    }

   private:
    std::set<Employee *> employees_;
  };
}  // namespace facc

#endif  // FACC_FACTORY_ACCOUNTING_HPP_INCLUDED
