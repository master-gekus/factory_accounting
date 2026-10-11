#ifndef FACC_FACTORY_ACCOUNTING_HPP_INCLUDED
#define FACC_FACTORY_ACCOUNTING_HPP_INCLUDED

#include <list>
#include "employee.hpp"

namespace facc {
  template <class D>
  class FactoryAccounting final{
   public:
    using Employee = facc::Employee<D>;

   public:
    ~FactoryAccounting() {
      for(auto* e: employees_) {
        delete e;
      }
    }

   public:
    const auto &employees() const noexcept {
      return employees_;
    }

   private:
    std::list<Employee *> employees_;
  };
}  // namespace facc

#endif  // FACC_FACTORY_ACCOUNTING_HPP_INCLUDED
