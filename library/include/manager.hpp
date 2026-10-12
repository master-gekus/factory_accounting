#ifndef FACC_MANAGER_HPP_INCLUDED
#define FACC_MANAGER_HPP_INCLUDED

#include "employee.hpp"

namespace facc {
  template <class D>
  class Manager final : public Employee<D> {
   private:
    template <typename... Args>
    Manager(Args &&...args) : Employee<D>{std::forward<Args>(args)...} {}

   public:
    std::uint64_t totalSalary(int mounth) const override {
      return Employee<D>::basicSalary() * 12;
    }

    friend class FactoryAccounting<D>;
  };
}  // namespace facc

#endif  // FACC_MANAGER_HPP_INCLUDED
