#ifndef FACC_WORKER_HPP_INCLUDED
#define FACC_WORKER_HPP_INCLUDED

#include "employee.hpp"

namespace facc {
  template <class D>
  class Worker final : public Employee<D> {
   public:
    using Type = typename Employee<D>::Type;

   private:
    template <typename... Args>
    Worker(Args &&...args) : Employee<D>{std::forward<Args>(args)...} {}

   public:
    virtual Type type() const noexcept {
      return Employee<D>::Type::Worker;
    }

    friend class FactoryAccounting<D>;
  };
}  // namespace facc

#endif  // FACC_WORKER_HPP_INCLUDED
