#pragma once

#include "Employee.hpp"

class Job {
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &employee;
    }

    Employee* employee;
    std::string title, description;
    int id, salary;

    public:
    Job();
    Job(std::string title, std::string description, int salary);
};