#ifndef FACC_EMPLOYEE_HPP_INCLUDED
#define FACC_EMPLOYEE_HPP_INCLUDED

#include <set>
#include <utility>

namespace facc {
  template <class D>
  class FactoryAccounting;


  template <class D>
  class Employee {
   public:
    enum Type {
      Unknown,
      Worker,
      Foreman,
      Manager,
    };

   protected:
    template <typename... Args>
    Employee(Args &&...args) : d_{std::forward<Args>(args)...} {}

   private:
    virtual ~Employee() = default;

   private:
    Employee() = default;
    Employee(const Employee &) = delete;
    Employee(Employee &&) = delete;
    Employee &operator=(const Employee &) = delete;
    Employee &operator=(Employee &&) = delete;

   public:
    const D &data() const noexcept {
      return d_;
    }

    D &data() noexcept {
      return d_;
    }

    const auto &subs() const noexcept {
      return subs_;
    }

    const auto boss() const noexcept {
      return boss_;
    }

   public:
    virtual Type type() const noexcept = 0;

   private:
    D d_;
    Employee *boss_;
    std::set<Employee *> subs_;

    friend class FactoryAccounting<D>;
  };
}  // namespace facc

#endif  // FACC_EMPLOYEE_HPP_INCLUDED
