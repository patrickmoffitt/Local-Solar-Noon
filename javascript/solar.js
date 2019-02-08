var solar = (function () {
  // Days since Jan 1, 2000 12:00 UT
  function epoch2kDay (query) {
    var q = query
    var oneDay = 1000 * 60 * 60 * 24 // milliseconds
    var queryDate = new Date(q.year, (q.month - 1), q.day, q.hour).getTime()
    var epochYear = new Date(Date.UTC(2000, 0, 1, 12)).getTime()
    return (queryDate - epochYear) / oneDay
  }

  // System of equations based upon Fourier analysis of a large MICA data set.
  // Only valid from 2000 to 2050
  function equationOfTime (days) {
    var cycle = Math.round(days / 365.25)
    var theta = 0.0172024 * (days - 365.25 * cycle)
    var amp1 = 7.36303 - cycle * 0.00009
    var amp2 = 9.92465 - cycle * 0.00014
    var rho1 = 3.07892 - cycle * 0.00019
    var rho2 = -1.38995 + cycle * 0.00013
    // Equation Of Time (EOT)
    var eot1 = amp1 * Math.sin(1 * (theta + rho1))
    var eot2 = amp2 * Math.sin(2 * (theta + rho2))
    var eot3 = 0.31730 * Math.sin(3 * (theta - 0.94686))
    var eot4 = 0.21922 * Math.sin(4 * (theta - 0.60716))
    var eot = 0.00526 + eot1 + eot2 + eot3 + eot4 // minutes
    return eot
  }

  function floatToFixed (float, width = 2) {
    return Number(float).toFixed(width)
  }

  // Get the local offset from UTC in minutes.
  function getOffsetMinutes () {
    var utc = new Date().toLocaleString('en-US', { timeZone: 'UTC' })
    utc = new Date(utc)
    return Math.floor(((new Date()).getTime() - utc.getTime()) / 1000) / 60
  }

  function getQueryNow (longitude) {
    var t = new Date()
    return {
      year: t.getFullYear(),
      month: t.getMonth() + 1, // Normal month number NOT monthIndex
      day: t.getDate(),
      hour: t.getHours(),
      longitude: longitude
    }
  }

  // Adjust EOT for longitude and timezone.
  function longitudeOffset (eot, longitude) {
    return -1 * (eot + (4 * longitude) - getOffsetMinutes())
  }

  // Format decimal minutes to hours, minutes, and seconds text.
  function minutesToClock (time) {
    var hours = Math.trunc(time / 60)
    var minutes = Math.trunc(time - (hours * 60))
    var seconds = Math.round(Math.abs(time - (hours * 60) - minutes) * 60)
    return {
      'hours': zeroFill(hours, 2),
      'minutes': zeroFill(minutes, 2),
      'seconds': zeroFill(seconds, 2)
    }
  }

  function printSigned (number) {
    if (number > 0) {
      return '+' + number
    } else {
      return number.toString()
    }
  }

  function solarNoon (longitudeOffset) {
    var noonMinutes = 12 * 60
    var t = minutesToClock(noonMinutes + longitudeOffset)
    return t.hours + ':' + t.minutes + ':' + t.seconds
  }

  // Pad a number with leading zeros.
  function zeroFill (number, width) {
    var pad = width - Math.trunc(Math.abs(number)).toString().length + 1
    return new Array(pad).join('0') + number
  }

  return {
    epoch2kDay: epoch2kDay,
    equationOfTime: equationOfTime,
    floatToFixed: floatToFixed,
    getOffsetMinutes: getOffsetMinutes,
    getQueryNow: getQueryNow,
    longitudeOffset: longitudeOffset,
    minutesToClock: minutesToClock,
    printSigned: printSigned,
    solarNoon: solarNoon,
    zeroFill: zeroFill
  }
})()
