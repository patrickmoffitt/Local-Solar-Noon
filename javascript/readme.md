Implementation Notes
--------------------------
You should run the program for your location. To do that first find your
longitude [using this tool](https://www.esrl.noaa.gov/gmd/grad/solcalc/). While
you are there note the times they give you for your longitude and query time. If
you need to know your time zone (UTC offset) you can
[look that up](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones) on
Wikipedia. Then update this object in index.htm with your longitude and the time
you're interested in.
```javascript
var query = {
  year: 2019,
  month: 2, // Normal month number NOT monthIndex
  day: 7,
  hour: 12,
  longitude: -75.96106
}
```
If the current time is alright just uncomment this line and use your longitude:
```javascript
// query = solar.getQueryNow(-75.96106)
```

If you want to test the program for a non-local timezone you will have to adjust
your system time zone preferences. Note the time zone you chose and lookup the
UTC offset in the Wikipedia article linked above.

Running the Project
--------------------------
To run the index.htm I use [GitHub Atom](https://github.com/atom/atom/releases/latest)
with the [Atom Live Server package](https://atom.io/packages/atom-live-server)

Testing
--------------------------
The value you get for Solar Noon should be within 3 seconds of that provided by
NOAA. If it's not check that the UTC offset on the first line of the output
matches the published values. Be sure you entered this value into the NOAA tool.
For example (in February 2019) America/New_York is -5 and Australia/Darwin is
+9.5. Also check that the longitude has the correct value and sign for the local.
If the input is correct and the output is still wrong please open an issue with
the object you used and the output you got. Also include the time zone setting
you used in your system preferences.
