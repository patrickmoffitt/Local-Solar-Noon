from math import sin, trunc
from time import gmtime, localtime, struct_time
from datetime import datetime, timedelta, timezone


class Solar:
    # Days since Jan 1, 2000 12:00 UT
    def epoch_2k_day(self, _query):
        q = _query
        tz = self.get_utc_offset()
        query_date = datetime(q['tm']['tm_year'],
                              q['tm']['tm_mon'],
                              q['tm']['tm_mday'],
                              q['tm']['tm_hour'],
                              tzinfo=timezone(timedelta(minutes=tz['minutes'])))
        epoch_year = datetime(2000, 1, 1, 12, 0, 0, tzinfo=timezone.utc)
        return (query_date - epoch_year) / timedelta(days=1)

    # System of equations based upon Fourier analysis of a large MICA data set.
    # Only valid from 2000 to 2050.
    @staticmethod
    def equation_of_time(_days):
        cycle = round(_days / 365.25)
        theta = 0.0172024 * (_days - 365.25 * cycle)
        amp1 = 7.36303 - cycle * 0.00009
        amp2 = 9.92465 - cycle * 0.00014
        rho1 = 3.07892 - cycle * 0.00019
        rho2 = -1.38995 + cycle * 0.00013
        # Equation Of Time (EOT)
        eot1 = amp1 * sin(1 * (theta + rho1))
        eot2 = amp2 * sin(2 * (theta + rho2))
        eot3 = 0.31730 * sin(3 * (theta - 0.94686))
        eot4 = 0.21922 * sin(4 * (theta - 0.60716))
        _eot = 0.00526 + eot1 + eot2 + eot3 + eot4  # minutes
        return _eot

    @staticmethod
    def float_to_fixed(_float, width=2):
        return round(_float, width)

    @staticmethod
    def get_query_now(_longitude):
        _tm = struct_time(localtime())
        return {
               'tm': {
                     'tm_year': _tm.tm_year,
                     'tm_mon':  _tm.tm_mon,
                     'tm_mday': _tm.tm_mday,
                     'tm_hour': _tm.tm_hour
                     },
               'longitude': _longitude
               }

    # Get the local offset from UTC.
    @staticmethod
    def get_utc_offset():
        utc = struct_time(gmtime())
        local = struct_time(localtime())
        day_ahead = local.tm_yday - utc.tm_yday
        _days = day_ahead * 24
        hours = local.tm_hour - utc.tm_hour + _days
        minutes = local.tm_min - utc.tm_min
        return {
                'hours': hours + (minutes / 60.0),
                'minutes': (hours * 60) + minutes,
                'seconds': ((hours * 60) + minutes) * 60
                }

    # Adjust EOT for longitude and timezone.
    def longitude_offset(self, _eot, _longitude):
        tz = self.get_utc_offset()
        return -1 * (_eot + (4 * _longitude) - tz['minutes'])

    # Format decimal minutes to hours, minutes, and seconds text.
    def minutes_to_clock(self, _time):
        hours = trunc(_time / 60)
        minutes = trunc(_time - (hours * 60))
        seconds = round(abs(_time - (hours * 60) - minutes) * 60)
        return {
          'hours': self.zero_fill(hours, 2),
          'minutes': self.zero_fill(minutes, 2),
          'seconds': self.zero_fill(seconds, 2)
        }

    def solar_noon(self, longitude_offset):
        noon_minutes = 12 * 60
        t = self.minutes_to_clock(noon_minutes + longitude_offset)
        return t['hours'] + ':' + t['minutes'] + ':' + t['seconds']

    # Pad a number with leading zeros.
    @staticmethod
    def zero_fill(number, _width):
        pad = _width - len(str(trunc(abs(number)))) + 1
        return '{0:{fill}{width}}'.format(number, fill=0, width=pad)
