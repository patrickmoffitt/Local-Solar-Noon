#
# Created by Patrick Moffitt on 2019-02-04.
#

from solar import Solar

query = {
         'tm': {
               'tm_year': 2019,
               'tm_mon':  2,
               'tm_mday': 7,
               'tm_hour': 12
               },
         'longitude': -75.961103
         }

solar = Solar()

#  query = solar.get_query_now(-75.961103)

tz = solar.get_utc_offset()
days = solar.epoch_2k_day(query)
eot = solar.equation_of_time(days)
offset = solar.longitude_offset(eot, query['longitude'])
solar_noon = solar.solar_noon(offset)

print("Local Time Zone UTC %.1f hours." % tz['hours'])
print('Epoch 2000 Day: %.2f' % days)
print('Equation of Time: %.2f' % eot)
print('Longitude Offset Minutes: %.2f' % solar.float_to_fixed(offset))
print('Solar Noon: %s' % solar_noon)
