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
      if (mounth <= Employee<D>::relativeStart()) {
        return 0;
      }
      return Employee<D>::basicSalary()
             + ((totalRecurcive(Employee<D>::subs(), mounth) * 3) / 100);
    }

   private:
    static std::uint64_t totalRecurcive(const std::set<Employee<D> *> &subs,
                                        int mounth) {
      std::uint64_t total{0};
      for (auto *s : subs) {
        total += s->totalSalary(mounth) + totalRecurcive(s->subs(), mounth);
      }
      return total;
    }

    friend class FactoryAccounting<D>;
  };
}  // namespace facc

#endif  // FACC_MANAGER_HPP_INCLUDED
