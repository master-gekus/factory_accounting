#ifndef FACC_MANAGER_HPP_INCLUDED
#define FACC_MANAGER_HPP_INCLUDED

#include "employee.hpp"

namespace facc {
  template <class D>
  class Manager final : public Employee<D> {
   public:
    using Type = typename Employee<D>::Type;

   private:
    template <typename... Args>
    Manager(Args &&...args) : Employee<D>{std::forward<Args>(args)...} {}

   public:
    virtual Type type() const noexcept {
      return Employee<D>::Type::Manager;
    }

    friend class FactoryAccounting<D>;
  };
}  // namespace facc

#endif  // FACC_MANAGER_HPP_INCLUDED
