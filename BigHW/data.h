#ifndef DATA_H
#define DATA_H
#include <iostream>

struct Data
{
    public:
        std::string title;
        std::string type;
        std::string director;
        std::string country;
        std::string year;
        double user_rating;
        std::string status = "Unwatched";
        std::string tv_rating;
};

#endif // DATA_H
