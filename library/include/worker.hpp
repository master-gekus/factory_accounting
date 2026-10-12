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
      if (mounth <= Employee<D>::relativeStart()) {
        return 0;
      }
      const auto years{(mounth - Employee<D>::relativeStart()) / 12};
      return Employee<D>::basicSalary()
             + ((years > 10) ? Employee<D>::basicSalary()
                             : ((Employee<D>::basicSalary() * years) / 10));
    }

    friend class FactoryAccounting<D>;
  };
}  // namespace facc

#endif  // FACC_WORKER_HPP_INCLUDED
