#ifndef    CONVERSION_HXX
# define   CONVERSION_HXX

# include "Conversion.hxx"
# include <stdexcept>
# include <sstream>
# include <cxxabi.h>
# include "CoreException.hh"

namespace utils {

  inline
  int
  convertToInt(const std::string& input,
                bool* ok) noexcept
  {
    // Use the dedicated conversion function.
    char* end = nullptr;
    int val = static_cast<int>(strtol(input.c_str(), &end, 10));

    // Analyze the result of the conversion.
    if (ok != nullptr) {
      *ok = (*end == '\0');
    }

    // Assign a `0` value in case the conversion failed.
    if (*end != '\0') {
      val = 0;
    }

    // Return the converted value.
    return val;
  }

  inline
  float
  convertToFloat(const std::string& input,
                  bool* ok) noexcept
  {
    // Use the dedicated conversion function.
    size_t end;
    bool scientific = false;
    float val;
    bool valid = true;

    try {
      val = std::stof(input.c_str(), &end);
    }
    catch (const std::invalid_argument& e) {
      // No conversion could be performed.
      valid = false;
    }
    catch (const std::out_of_range& e) {
      // The value seems to be valid but cannot be represented using a float value.
      valid = false;
    }

    // If the parsing was not valid it might mean that we're facing something written
    // with scientific notation. Let's try to convert it using a string stream. It
    // might allow for some more conversions even though after testing it seems that
    // the standard `stof` approach handles these cases just fine.
    if (!valid || end < input.size()) {
      std::stringstream stream(input);
      stream >> val;

      // Check whether the conversion did happen successfully.
      valid = !stream.fail();
      scientific = true;
    }

    // Analyze the result of the conversion.
    if (ok != nullptr) {
      *ok = valid && (scientific || end >= input.size());
    }

    // Assign a `0` value in case the conversion failed.
    if (!valid || (!scientific && end < input.size())) {
      val = 0;
    }

    // Return the converted value.
    return val;
  }

  template <>
  inline
  unsigned
  convert(const std::string& text,
          unsigned def,
          bool& converted) noexcept
  {
    // Use the dedicated handler to handle the conversion.
    bool valid = false;

    int conv = convertToInt(text, &valid);

    if (!valid || conv < 0) {
      converted = false;
      return def;
    }

    converted = true;
    return static_cast<unsigned>(conv);
  }

  template <>
  inline
  int
  convert(const std::string& text,
          int def,
          bool& converted) noexcept
  {
    // Use the dedicated handler to handle the conversion.
    bool valid = false;

    int conv = convertToInt(text, &valid);

    if (!valid || conv < 0) {
      converted = false;
      return def;
    }

    converted = true;
    return conv;
  }

  template <>
  inline
  float
  convert(const std::string& text,
          float def,
          bool& converted) noexcept
  {
    // Use the dedicated handler to handle the conversion.
    bool valid = false;

    float conv = convertToFloat(text, &valid);

    if (!valid || conv < 0) {
      converted = false;
      return def;
    }

    converted = true;
    return conv;
  }

  template <typename Type>
  inline
  Type
  convert(const std::string& text,
          Type def,
          bool& converted) noexcept
  {
    // Unsupported conversion: notify an error with the expected conversion.
    int status;
    std::string convType = abi::__cxa_demangle(typeid(Type).name(), 0, 0, &status);

    throw CoreException(
      std::string("Could not convert \"") + text + "\" to \"" + convType + "\"",
      std::string("conversion"),
      convType,
      std::string("Unsupported conversion")
    );
  }

}

#endif    /* CONVERSION_HXX */
