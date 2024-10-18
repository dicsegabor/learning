#pragma once

#include <boost/serialization/access.hpp>

#include <string>

class Employee
{
  private:
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &name;
        ar &id;
        ar &age;
    }

    std::string name, id;
    int age;

    static int number;

  public:
    Employee() {}
    Employee(
        std::string name, std::string job_title,
        int age, int salary
    );

    int count() { return number; }

    void print_data() const;
};