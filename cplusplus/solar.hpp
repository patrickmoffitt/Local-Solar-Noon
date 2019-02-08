//
// Created by Patrick Moffitt on 2019-02-07.
//

#ifndef MICRO_CONTROLLER_LOCAL_SOLAR_NOON_SOLAR_HPP
#define MICRO_CONTROLLER_LOCAL_SOLAR_NOON_SOLAR_HPP


#include <string>
#include <cmath>
#include <sstream>


class solar {
public:
    struct clock_time {
        std::string hours;
        std::string minutes;
        std::string seconds;
    };

    struct offset_t {
        int day_ahead;  // 1 if a day ahead of UTC day.
        double hours;   // Not all offsets are whole numbers of hours.
        int minutes;
        int seconds;
    };

    struct query {
        tm _tm;
        double longitude;
    };

    double epoch_2k_day(solar::query query);

    double equation_of_time(double _days);

    double float_to_fixed(double number, int width=2);

    solar::query get_query_now(double _longitude);

    offset_t get_utc_offset();

    double longitude_offset(double _eot, double _longitude);

    std::time_t mktime_gmt(tm* time);

    solar::clock_time minutes_to_clock(double _time);

    std::string solar_noon(double longitude_offset);

    std::string zero_fill(int number, int _width);

    std::string zero_fill(double number, int _width);
};



#endif //MICRO_CONTROLLER_LOCAL_SOLAR_NOON_SOLAR_HPP
