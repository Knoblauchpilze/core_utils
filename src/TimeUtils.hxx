#ifndef    TIME_UTILS_HXX
# define   TIME_UTILS_HXX

# include "TimeUtils.hh"
# include <ctime>
# include <iomanip>
# include <sstream>

namespace utils {

  inline
  TimeStamp
  now() noexcept {
    return std::chrono::system_clock::now();
  }

  inline
  Duration
  toMilliseconds(int ms) noexcept {
    return Milliseconds(ms);
  }

  inline
  float
  toMilliseconds(const Duration& d) noexcept {
    // Convert to nanoseconds to keep as much precision
    // as possible and then convert back to float.
    auto s = std::chrono::duration_cast<Milliseconds>(d);
    int ms = s.count();

    return 1.0f * ms;
  }

  inline
  std::string
  timeToString(const TimeStamp& t) noexcept {
    // See here:
    // https://stackoverflow.com/questions/34857119/how-to-convert-stdchronotime-point-to-string/34858704
    // And here:
    // https://stackoverflow.com/questions/32873659/how-can-i-get-current-time-of-day-in-milliseconds-in-c/32874098#32874098
    std::time_t tt = std::chrono::system_clock::to_time_t(t);
    std::tm tm = *std::gmtime(&tt); //GMT (UTC)

    auto ms = std::chrono::duration_cast<Milliseconds>(t.time_since_epoch()) -
              std::chrono::duration_cast<std::chrono::seconds>(t.time_since_epoch());

    std::stringstream ss;
    ss << std::put_time( &tm, "UTC: %Y-%m-%d %H:%M:%S");
    ss << "." << ms.count() << "ms";

    return ss.str();
  }

  inline
  std::string
  durationToString(const Duration& d) noexcept {
    // See here:
    // https://stackoverflow.com/questions/22590821/convert-stdduration-to-human-readable-time
    auto s = std::chrono::duration_cast<Milliseconds>(d);
    int ms = s.count();

    return std::to_string(ms) + "ms";
  }

  inline
  float
  diffInMs(const TimeStamp& start, const TimeStamp& end) noexcept {
    auto elapsed = end - start;
    auto ms = std::chrono::duration_cast<Milliseconds>(elapsed);

    return ms.count();
  }

}

inline
std::ostream&
operator<<(std::ostream& out, const utils::TimeStamp& t) noexcept {
  // As per this link:
  // https://stackoverflow.com/questions/36963373/saving-and-loading-stdchronotime-point-to-file
  // We can serialize a timestamp by converting it to its
  // epoch representation.
  auto et = t.time_since_epoch().count();
  out.write(reinterpret_cast<const char*>(&et), sizeof(et));

  return out;
}

inline
std::istream&
operator>>(std::istream& in, utils::TimeStamp& t) noexcept {
  std::chrono::system_clock::rep et;

  t = utils::now();
  in.read(reinterpret_cast<char*>(&et), sizeof(et));
  if (in) {
    t = utils::TimeStamp(std::chrono::system_clock::duration{et});
  }

  return in;
}

#endif    /* TIME_UTILS_HXX */
