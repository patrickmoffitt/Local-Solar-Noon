//
// Created by Patrick Moffitt on 2019-02-04.
//

#include "solar.hpp"
using namespace std::chrono;

double solar::epoch_2k_day(query _query) {
    tm epoch_2k{
            .tm_year = 2000 - 1900, // Years since 1900
            .tm_mon  = 1 - 1,       // Months from index 0
            .tm_mday = 1,
            .tm_hour = 12
    };
    std::time_t e_t = mktime_gmt(&epoch_2k);

    auto& q = _query;
    std::time_t q_t = std::mktime(&q._tm);

    using namespace std::chrono;
    auto e_sc = system_clock::from_time_t(e_t);
    auto e_hrs = duration_cast<hours>(e_sc.time_since_epoch()).count();

    auto q_sc = system_clock::from_time_t(q_t);
    auto q_hrs = duration_cast<hours>(q_sc.time_since_epoch()).count();

    return  (q_hrs - e_hrs) / 24.0;
}

double solar::equation_of_time(double _days) {
    auto cycle = round(_days / 365.25);
    auto theta = 0.0172024 * (_days - 365.25 * cycle);
    auto amp1 = 7.36303 - cycle * 0.00009;
    auto amp2 = 9.92465 - cycle * 0.00014;
    auto rho1 = 3.07892 - cycle * 0.00019;
    auto rho2 = -1.38995 + cycle * 0.00013;
    // Equation Of Time (EOT)
    auto eot1 = amp1 * sin(1 * (theta + rho1));
    auto eot2 = amp2 * sin(2 * (theta + rho2));
    auto eot3 = 0.31730 * sin(3 * (theta - 0.94686));
    auto eot4 = 0.21922 * sin(4 * (theta - 0.60716));
    auto _eot = 0.00526 + eot1 + eot2 + eot3 + eot4;  // minutes
    return _eot;
}

double solar::float_to_fixed(double number, int width) {
    auto places = pow(10, width);
    return std::trunc(places * number) / places;
}

solar::query solar::get_query_now(double _longitude) {
    std::time_t t = std::time(nullptr);
    std::tm* _tm = std::localtime(&t);
    solar::query _query{ ._tm = *_tm, .longitude = _longitude };
    return _query;
}

solar::offset_t solar::get_utc_offset() {
    std::time_t t = std::time(nullptr);
    auto tm_utc = std::gmtime(&t);
    auto tm_local = localtime(&t);
    offset_t ts{};
    ts.day_ahead = tm_local->tm_yday - tm_utc->tm_yday;
    int days = (ts.day_ahead) * 24;
    int hours = tm_local->tm_hour - tm_utc->tm_hour + days;
    int minutes = tm_local->tm_min - tm_utc->tm_min;
    ts.hours = hours + (minutes / 60.0);
    ts.minutes = (hours * 60) + minutes;
    ts.seconds = ts.minutes * 60;
    return ts;
}

double solar::longitude_offset(double _eot, double _longitude) {
    auto ts = get_utc_offset();
    return -1 * (_eot + (4 * _longitude) - ts.minutes);
}

std::time_t solar::mktime_gmt(tm* time) {
    offset_t ts = get_utc_offset();
    return std::mktime(time) + ts.seconds;
}

solar::clock_time solar::minutes_to_clock(double _time) {
    auto hours = trunc(_time / 60);
    auto minutes = trunc(_time - (hours * 60));
    auto seconds = round(abs(_time - (hours * 60) - minutes) * 60);
    clock_time ct;
    ct.hours = zero_fill(hours, 2);
    ct.minutes = zero_fill(minutes, 2);
    ct.seconds = zero_fill(seconds, 2);
    return ct;
}

std::string solar::solar_noon(double longitude_offset) {
    int noon_minutes = 12 * 60;
    clock_time ct = minutes_to_clock(noon_minutes + longitude_offset);
    return ct.hours + ':' + ct.minutes + ':' + ct.seconds;
}

std::string solar::zero_fill(int number, int _width) {
    std::stringstream ss;
    if (_width <= 1) {
        ss << number;
        return ss.str();
    }
    ss << abs(number);
    auto pad = _width - ss.str().length();
    ss.str("");
    ss << number;
    auto ns = ss.str(); // numeric string (ns)
    ns.insert(ns.begin(), pad, '0');
    return ns;
}

std::string solar::zero_fill(double number, int _width) {
    std::stringstream ss;
    if (_width <= 1) {
        ss << number;
        return ss.str();
    }
    ss << trunc(abs(number));
    auto pad = _width - ss.str().length();
    ss.str("");
    ss << number;
    auto ns = ss.str(); // numeric string (ns)
    ns.insert(ns.begin(), pad, '0');
    return ns;
}
