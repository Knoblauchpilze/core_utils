#ifndef    CONVERSION_HH
# define   CONVERSION_HH

# include <string>

namespace utils {

  /**
   * @brief - Used to attempt to convert the input string to a valid integer value.
   *          Note that if the input string cannot be converted the returned value
   *          will be `0` and the `ok` boolean will be set to `false` if it is not
   *          set to `nullptr`.
   * @param input - the string to convert to an integer.
   * @param ok - a pointer which should be set if the user wants to know whether the
   *             input string could be successfully converted to an integer value.
   * @return - the integer represented by the input string or `0` if the string is
   *           not a valid number.
   */
  inline
  int
  convertToInt(const std::string& input,
                bool* ok = nullptr) noexcept;

  /**
   * @brief - Used to attempt to convert the input string to a valid float value.
   *          Note that if the input string cannot be converted the returned value
   *          will be `0.0` and the `ok` boolean will be set to `false` if it is
   *          not set to `nullptr`.
   * @param input - the string to convert to a float.
   * @param ok - a pointer which should be set if the user wants to know whether the
   *             input string could be successfully converted to a float value.
   * @return - the float represented by the input string or `0.0` if the string is
   *           not a valid number.
   */
  inline
  float
  convertToFloat(const std::string& input,
                  bool* ok = nullptr) noexcept;

  /**
   * @brief - Generic method allowing to convert a string to a certain value. This
   *          method uses the above definition but allows to not care about the
   *          actual type of the value to retrieve.
   *          The default template throws an error indicating an unsupported conv.
   * @param text - the text to convert.
   * @param def - the default value in case the value cannot be converted.
   * @param converted - `true` if the input `text` could be converted and `false`
   *                    in case it could not. In this case the return value is set
   *                    to be the `def` value.
   * @return - the value converted from the input `text` or the `def` value.
   */
  template <typename Type>
  Type
  convert(const std::string& text,
          Type def,
          bool& converted) noexcept;

}

# include "Conversion.hxx"

#endif    /* CONVERSION_HH */
