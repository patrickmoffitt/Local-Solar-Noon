Implementation Notes
--------------------------
You should run the program for your location. To do that first find your
longitude [using this tool](https://www.esrl.noaa.gov/gmd/grad/solcalc/). While
you are there note the times they give you for your longitude and query time. If
you need to know your time zone (UTC offset) you can
[look that up](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones) on
Wikipedia. Then update this tuple in 
[local_solar_noon.py](https://github.com/patrickmoffitt/Local-Solar-Noon/blob/master/python/local_solar_noon.py)
with your longitude and the time you're interested in.
```python
query = {
         'tm': {
               'tm_year': 2019,
               'tm_mon':  2,
               'tm_mday': 7,
               'tm_hour': 12
               },
         'longitude': -75.961103
         }
}
```
If the current time is alright just uncomment this line and use your longitude:
```python
#  query = solar.get_query_now(-75.961103)
```

If you want to test the program for a non-local timezone you will have to adjust
your system time zone preferences. Note the time zone you chose and lookup the
UTC offset in the Wikipedia article linked above.

Running the Project
--------------------------
Execute local_solar_noon.py with your local Python 3.7
```bash
$ python3 ./local_solar_noon.py
Local Time Zone UTC -5.0 hours.
Epoch 2000 Day: 6977.21
Equation of Time: -14.12
Longitude Offset Minutes: 17.97
Solar Noon: 12:17:58
```

Testing
--------------------------
The value you get for Solar Noon should be within 3 seconds of that provided by
NOAA. If it's not check that the UTC offset on the first line of the output
matches the published values. Be sure you entered this value into the NOAA tool.
For example (in February 2019) America/New_York is -5 and Australia/Darwin is
+9.5. Also check that the longitude has the correct value and sign for your location.
If the input is correct and the output is still wrong please open an issue with
the object you used and the output you got. Also include the time zone setting
you used in your system preferences.
