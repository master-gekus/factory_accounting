#ifndef FACC_FOREMAN_HPP_INCLUDED
#define FACC_FOREMAN_HPP_INCLUDED

#include "employee.hpp"

namespace facc {
  template <class D>
  class Foreman final : public Employee<D> {
   private:
    template <typename... Args>
    Foreman(Args &&...args) : Employee<D>{std::forward<Args>(args)...} {}

   public:
    std::uint64_t totalSalary(int mounth) const override {
      return Employee<D>::basicSalary() * 15;
    }

    friend class FactoryAccounting<D>;
  };
}  // namespace facc
#endif  // FACC_FOREMAN_HPP_INCLUDED
