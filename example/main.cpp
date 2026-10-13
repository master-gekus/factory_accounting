#include <algorithm>
#include <format>
#include <iostream>
#include <string>
#include <vector>

#include <cstdint>

#include "factory_accounting.hpp"

using Factory = facc::FactoryAccounting<std::string>;
using Employee = Factory::Employee;
using Worker = Factory::Worker;
using Foreman = Factory::Foreman;
using Manager = Factory::Manager;

void sortList(std::vector<Employee *> &employees) {
  std::sort(
      employees.begin(), employees.end(), [](Employee *a, Employee *b) -> bool {
        return a->data() < b->data();
      });
}

std::string salary_to_string_formatted(std::uint64_t value) {
  if (value > 999'999'99) {
    return std::format("{},{:03},{:03}.{:02}",
                       value / 1'000'000'00,
                       (value / 1'000'00) % 1000,
                       (value / 100) % 1000,
                       value % 100);
  } else if (value > 999'99) {
    return std::format("  {:3},{:03}.{:02}",
                       (value / 1'000'00) % 1000,
                       (value / 100) % 1000,
                       value % 100);
  } else {
    return std::format("      {:3}.{:02}", value / 100, value % 100);
  }
}

std::string work_duration_to_string_formatted(unsigned value) {
  return std::format(" {:2}л.{:2}м. ", value / 12, value % 12);
}

size_t utf8Len(const std::string &s) {
  return std::count_if(s.begin(), s.end(), [](char c) {
    return (static_cast<unsigned char>(c) & 0xC0) != 0x80;
  });
}

std::uint64_t printRecursive(const std::vector<Employee *> &employees,
                             int mounth,
                             int level = 0) {
  std::uint64_t total{0};
  for (auto *e : employees) {
    auto padding{76 - utf8Len(e->data()) - level * 2};
    if (padding < 0) {
      padding = 0;
    }

    std::cout << "| " << std::string(level * 2, ' ') << e->data()
              << std::string(padding, ' ') << "|";
    if (e->relativeStart() >= mounth) {
      std::cout << "   ----   |    ---     |    ---     |";
    } else {
      const auto totalSalary{e->totalSalary(mounth)};
      std::cout << work_duration_to_string_formatted(mounth
                                                     - e->relativeStart())
                << "|" << salary_to_string_formatted(e->basicSalary()) << "|"
                << salary_to_string_formatted(totalSalary) << "|";
      total += totalSalary;
    }
    std::cout << std::endl;
    std::vector<Employee *> subs;
    for (auto *s : e->subs()) {
      subs.push_back(s);
    }
    sortList(subs);
    total += printRecursive(subs, mounth, level + 1);
  }
  return total;
}

void printTopLevel(std::vector<Employee *> &employees, int mounth) {
  std::cout << "По состоянию на начало месяца " << mounth << std::endl;
  std::cout << "+=============================================================="
               "===============+===========+============+============+"
            << std::endl;
  std::cout << "| Имя                                                          "
               "               |   Стаж   |   Оклад    | Результат  |"
            << std::endl;
  std::cout << "+--------------------------------------------------------------"
               "---------------+----------+------------+------------+"
            << std::endl;
  const std::uint64_t total{printRecursive(employees, mounth)};
  std::cout << "+--------------------------------------------------------------"
               "---------------+----------+------------+------------+"
            << std::endl;
  std::cout << "| ИТОГО:                                                       "
               "               |          |            |"
            << salary_to_string_formatted(total) << "|" << std::endl;
  std::cout << "+=============================================================="
               "===============+==========+============+============+"
            << std::endl;
  std::cout << std::endl;
}

int main(int, char **) {
  Factory factory;
  auto *d{factory.hire<Manager>(1000'00u, 0, "Гендиректор: Брателло")};
  factory.createSubordination(
      d, factory.hire<Worker>(100'00u, 12, "Секретарша: Залеткина"));
  factory.createSubordination(
      d, factory.hire<Worker>(150'00u, 2, "Менеджер по продажам: Втиралов"));
  factory.createSubordination(
      d,
      factory.hire<Worker>(
          150'00u, 2, "Менеджер по связям с общественностью: Треплова"));
  factory.createSubordination(
      d,
      factory.hire<Worker>(
          150'00u, 2, "Менеджер по работе с клиентами: Кидалов"));
  auto *dm{factory.hire<Foreman>(
      150'00u, 2, "Отдел маркетинга. Директор: Дизайнер")};
  factory.createSubordination(d, dm);
  factory.createSubordination(dm, factory.hire<Worker>(100'00u, 2, "Кульман"));
  factory.createSubordination(dm, factory.hire<Worker>(100'00u, 2, "Ватман"));
  factory.createSubordination(dm,
                              factory.hire<Worker>(100'00u, 2, "Фломастер"));
  //  Администратор: Криворучко
  //  Менеджер проекта: Маразматищев
  //  Руководитель аналитического отдела: Храпунов
  //  Эксперт-аналитик: Бездумов
  //  Специалисты аналитического отдела: Незнайкин
  //  Разработчики документации: Косноязыцкий, Неграмотнова
  //  Программисты: Разгильдяйцев, Бестолковченко, Халявин, Багов
  //  Руководитель горячей линии: Пофигидзе
  //  Горячая линия: Глухов, Молчалина, Офлайнер
  //  Руководитель отдела тестирования: Прозеващенко
  //  Отдел тестирования: Глупцов, Тупицын, Ламеркина
  //  Руководитель отдела внедрения: Внедрило-Невыполнявский
  //  Специалисты по внедрению: Недоездов, Потеряйкин, Истерикянц
  //  Охрана: Наливайко, Повторяйло, Пропускайчиков
  //  Сотрудники столовой: Помойкина, Холодных, Грязнова

  std::vector<Employee *> topLevel;
  for (auto *e : factory.employees()) {
    if (e->boss()) {
      continue;
    }
    topLevel.push_back(e);
  }
  sortList(topLevel);

  printTopLevel(topLevel, 16);
  printTopLevel(topLevel, 90);

  return 0;
}
