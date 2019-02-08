#include <iostream>
#include "solar.hpp"

int main() {

    // char tz[] = "TZ=America/New_York"; //"TZ=Australia/Darwin"; //"TZ=Asia/Kolkata";
    // putenv(tz);

    solar::query _query{
                       ._tm = {
                              .tm_year = 2019 - 1900, // Years since 1900
                              .tm_mon  = 2 - 1,       // Months from index 0
                              .tm_mday = 7,
                              .tm_hour = 12
                              },
                       .longitude = -75.961103
                       };

    solar solar;

    //_query = solar.get_query_now(-75.961103);

    auto days = solar.epoch_2k_day(_query);
    auto ts = solar.get_utc_offset();
    auto eot = solar.equation_of_time(days);
    auto offset = solar.longitude_offset(eot, _query.longitude);
    auto solar_noon = solar.solar_noon(offset);

    std::cout.setf(std::ios_base::showpos);
    std::cout << "Local Time Zone UTC "        << ts.hours << " hours."          << std::endl;
    std::cout.unsetf(std::ios_base::showpos);

    std::cout << "Epoch 2000 Day: "           << days                            << std::endl;
    std::cout << "Equation of Time: "         << solar.float_to_fixed(eot, 2)    << std::endl;
    std::cout << "Longitude Offset Minutes: " << solar.float_to_fixed(offset, 2) << std::endl;
    std::cout << "Solar Noon: "               << solar_noon                      << std::endl;

    return 0;
}
