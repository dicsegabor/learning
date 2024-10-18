#pragma once

#include "Department.hpp"
#include <set>
#include <boost/serialization/set.hpp>
#include <string>

class Company
{
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &name;
        ar &departments;
    }

    std::string name;
    std::set<Department> departments;

  public:
    Company() {}
    Company(std::string name) : name(name)
    {
        departments = std::set<Department>();
    }

    void add_department(Department d);
    // Throws invalid_argument exception
    void add_employee(std::string department, std::string job, Employee e);

    void delete_department(std::string);
};