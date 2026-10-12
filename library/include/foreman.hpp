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
      if (mounth <= Employee<D>::relativeStart()) {
        return 0;
      }
      const auto years{(mounth - Employee<D>::relativeStart()) / 12};
      auto salary{Employee<D>::basicSalary()
                  + ((years > 8)
                         ? (Employee<D>::basicSalary() * 4 / 10)
                         : ((Employee<D>::basicSalary() * years) / 20))};

      std::uint64_t subsTotal{0};
      for (auto *s : Employee<D>::subs()) {
        subsTotal += s->totalSalary(mounth);
      }
      return salary + (subsTotal * 7) / 100;
    }

    friend class FactoryAccounting<D>;
  };
}  // namespace facc
#endif  // FACC_FOREMAN_HPP_INCLUDED
