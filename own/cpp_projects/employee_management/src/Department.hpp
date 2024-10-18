#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>
#include <string>
#include <vector>

#include "Employee.hpp"
#include "Job.hpp"

class Department
{
    friend class boost::serialization::access;
    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &name;
        ar &jobs;
    }

    std::string name;
    std::vector<Job> jobs;

  public:
    Department() {}
    Department(const Department &other)
    {
        name = other.name;
        jobs = std::vector<Job>(other.jobs);
    }
    Department(std::string name) : name(name), jobs(std::vector<Job>()) {}

    void add_job(const Job &j) { jobs.push_back(j); }
    void add_employee(const std::string job, const Employee* e);

    const std::string get_name() const { return name; }

    // Needed fo set usage
    bool operator<(const Department &other) const { return name < other.name; }
};