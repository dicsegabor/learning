#include "Employee.hpp"

#include <iostream>

int Employee::number = 0;

Employee::Employee(
    std::string name, std::string job_title, int age,
    int salary
)
    : name(name), job_title(job_title), id(number++),
      age(age), salary(salary)
{
}

void Employee::print_data() const { std::cout << id << ". " << name; }