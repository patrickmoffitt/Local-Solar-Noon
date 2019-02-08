Building the Project With CMake
--------------------------
I develop on Mac OS X Mojave with an Intel Core i7. On my system you can build
and run this project like so:
```bash
$ cmake -B./cmake-build-debug -DCMAKE_BUILD_TYPE=Debug -G "CodeBlocks - Unix Makefiles" .
-- The C compiler identification is AppleClang 10.0.0.10001145
-- The CXX compiler identification is AppleClang 10.0.0.10001145
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++
-- Check for working CXX compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: ./cplusplus/cmake-build-debug
$ cmake --build ./cmake-build-debug --target local_solar_noon -- -j 4
Scanning dependencies of target local_solar_noon
[ 33%] Building CXX object CMakeFiles/local_solar_noon.dir/solar.cpp.o
[ 66%] Building CXX object CMakeFiles/local_solar_noon.dir/main.cpp.o
[100%] Linking CXX executable local_solar_noon
[100%] Built target local_solar_noon
$ ./cmake-build-debug/local_solar_noon
Local Time Zone UTC -5 hours.
Epoch 2000 Day: 6977.21
Equation of Time: -14.12
Longitude Offset Minutes: 17.96
Solar Noon: 12:17:58
```
Implementation Notes
--------------------------
You should run the program for your location. To do that first find your
longitude [using this tool](https://www.esrl.noaa.gov/gmd/grad/solcalc/). While
you are there note the times they give you for your longitude and query time. If
you need to know your time zone (UTC offset) you can
[look that up](https://en.wikipedia.org/wiki/List_of_tz_database_time_zones) on
Wikipedia. Then update this struct in main.cpp with your longitude and the time
you're interested in.
```c++
solar::query _query{
                   ._tm = {
                          .tm_year = 2019 - 1900, // Years since 1900
                          .tm_mon  = 2 - 1,       // Months from index 0
                          .tm_mday = 7,
                          .tm_hour = 12
                          },
                   .longitude = -75.961103
                   };
```
If the current time is alright just uncomment this line and use your longitude:
```c++
_query = solar.get_query_now(-75.961103);
```

If you want to test the program for a non-local timezone you don't have to adjust
your system time zone preferences. In main.cpp uncomment these lines:
```c++
// char tz[] = "TZ=America/New_York"; //"TZ=Australia/Darwin"; //"TZ=Asia/Kolkata";
// putenv(tz);
```
and change the timezone to one of the Canonical ones listed in the Wikipedia
article linked above.

Testing
--------------------------
The value you get for Solar Noon should be within 3 seconds of that provided by
NOAA. If it's not check that the UTC offset on the first line of the output
matches the published values. Be sure you entered this value into the NOAA tool.
For example (in February 2019) America/New_York is -5 and Australia/Darwin is
+9.5. Also check that the longitude has the correct value and sign for the local.
If the input is correct and the output is still wrong please open an issue with
the struct you used and the output you got.
