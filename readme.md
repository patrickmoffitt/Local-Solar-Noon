Local Solar Noon Calculators
------------------------------
Local Solar Noon is when the sun reaches its highest point in the sky for the
day. Depending on the season, your longitude, and your local time zone, there may
be more than an hour difference between Noon on your clock and Solar Noon. Since
you can't rely on your clock to tell you when it's Solar Noon you need a way to
calculate it. If you're merely curious, the good folks at the National Oceanic &
Atmospheric Administration (NOAA), Earth System Research Laboratory (ESRL),
Global Monitoring Division, have a nifty one
[online here](https://www.esrl.noaa.gov/gmd/grad/solcalc/). If you have a more
persistent interest in knowing where the shade will be on your party tent or sun
dial then you may want to read further.

This project borrows all its math from experts. The ever so grandly named
_Equation of Time_ was done using the Fourier Method
[shown here](https://equation-of-time.info/calculating-the-equation-of-time).
Despite sounding like a math lesson from a wizard in dark blue police box, that
formula isn't enough to very accurately determine Solar Noon. One must also
calculate the longitudinal offset for their location. I borrowed this math from
NOAA on page two of [this PDF](https://www.esrl.noaa.gov/gmd/grad/solcalc/solareqns.PDF).
The rest of the math just implements local and UTC date-times in the computer
languages I used.

Speaking of that. This project offers code to calculate Local Solar Noon from
the Equation of Time and Longitude Offset in
[JavaScript](https://github.com/patrickmoffitt/Local-Solar-Noon/tree/master/javascript/readme.md),
[Python 3.7](https://github.com/patrickmoffitt/Local-Solar-Noon/tree/master/python/readme.md),
and [C++11](https://github.com/patrickmoffitt/Local-Solar-Noon/tree/master/cplusplus/readme.md).
Click the preceding links to view the README file for each implementation.

Bugs, Issues and Pull Requests
------------------------------
If you find a bug please create an issue. If you'd like to contribute please
send a pull request.
