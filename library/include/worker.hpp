#ifndef FACC_WORKER_HPP_INCLUDED
#define FACC_WORKER_HPP_INCLUDED

#include "employee.hpp"

namespace facc {
  template <class D>
  class Worker final : public Employee<D> {
   private:
    template <typename... Args>
    Worker(Args &&...args) : Employee<D>{std::forward<Args>(args)...} {}

   public:
    std::uint64_t totalSalary(int mounth) const override {
      return Employee<D>::basicSalary() * 10;
    }

    friend class FactoryAccounting<D>;
  };
}  // namespace facc

#endif  // FACC_WORKER_HPP_INCLUDED
