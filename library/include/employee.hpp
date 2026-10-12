#ifndef FACC_EMPLOYEE_HPP_INCLUDED
#define FACC_EMPLOYEE_HPP_INCLUDED

#include <cstdint>

#include <set>
#include <utility>

namespace facc {
  template <class D>
  class FactoryAccounting;

  template <class D>
  class Employee {
   protected:
    template <typename... Args>
    Employee(std::uint64_t basicSalary, int relativeStart, Args &&...args)
        : basicSalary_{basicSalary},
          relativeStart_{relativeStart},
          d_{std::forward<Args>(args)...},
          boss_{nullptr} {}
    virtual ~Employee() {
      for (auto *s : subs_) {
        s->removeBoss(this);
      }
      if (boss_) {
        boss_->removeSub(this);
      }
    };

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

    auto *boss() const noexcept {
      return boss_;
    }

    auto basicSalary() const noexcept {
      return basicSalary_;
    }

    auto relativeStart() const noexcept {
      return relativeStart_;
    }

   public:
    virtual std::uint64_t totalSalary(int mounth) const = 0;

   private:
    void removeBoss(Employee *boss) {
      if (boss_ == boss) {
        boss_ = nullptr;
      }
    }

    void removeSub(Employee *sub) {
      subs_.erase(sub);
    }

    bool hasSubRecurcive(Employee *sub) const {
      if ((this == sub) || subs_.contains(sub)) {
        return true;
      }

      for (auto *s : subs_) {
        if (subs_.contains(sub)) {
          return true;
        }
      }

      return false;
    }

   private:
    const std::uint64_t basicSalary_;
    const int relativeStart_;
    D d_;
    std::set<Employee *> subs_;
    Employee *boss_;

    friend class FactoryAccounting<D>;
  };
}  // namespace facc

#endif  // FACC_EMPLOYEE_HPP_INCLUDED
