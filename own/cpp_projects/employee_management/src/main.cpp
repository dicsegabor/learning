#include "Company.hpp"

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>

#include <boost/archive/archive_exception.hpp>
#include <iostream>

int main()
{
    // Create object
    Company c = Company("Company");
    c.add_department(Department("Accounting"));
    //c.add_employee("Accounting", Employee("Edgar", "Accountant", 56, 400));

    // Serialize object
    {
        std::ofstream ofs("db.db");
        boost::archive::text_oarchive oa(ofs);
        oa << c;
    }

    // Create object, with deserialization
    Company c2;
    {
        std::ifstream ifs("db.db");
        boost::archive::text_iarchive ia(ifs);
        ia >> c2;
    }

    // Print object data
    {
        boost::archive::text_oarchive oa(std::cout);
        oa << c2;
    }

    return 0;
}