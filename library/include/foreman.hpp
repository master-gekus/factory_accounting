#ifndef FACC_FOREMAN_HPP_INCLUDED
#define FACC_FOREMAN_HPP_INCLUDED

#include "employee.hpp"

namespace facc {
  template <class D>
  class Foreman final : public Employee<D> {
   public:
    using Type = typename Employee<D>::Type;

   private:
    template <typename... Args>
    Foreman(Args &&...args) : Employee<D>{std::forward<Args>(args)...} {}

   public:
    virtual Type type() const noexcept {
      return Employee<D>::Type::Foreman;
    }

    friend class FactoryAccounting<D>;
  };
}  // namespace facc
#endif  // FACC_FOREMAN_HPP_INCLUDED
