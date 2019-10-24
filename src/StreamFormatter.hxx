#ifndef    STREAM_FORMATTER_HXX
# define   STREAM_FORMATTER_HXX

# include "StreamFormatter.hh"

namespace utils {

  inline
  void
  StreamFormatter::setStreamColor(std::ostream& stream, const Color& color) const noexcept {
    stream << getFormatterForColor(color);
  }

  inline
  void
  StreamFormatter::clearStreamFormat(std::ostream& stream) const noexcept {
    stream << std::string("\033[0m");
  }

  inline
  std::string
  StreamFormatter::getStringForColor(const Color& color) const noexcept {
    std::string colorFormatter;

    switch (color) {
      case Color::Black:
        colorFormatter = "30";
        break;
      case Color::Red:
        colorFormatter = "31";
        break;
      case Color::Green:
        colorFormatter = "32";
        break;
      case Color::Yellow:
        colorFormatter = "33";
        break;
      case Color::Blue:
        colorFormatter = "34";
        break;
      case Color::Magenta:
        colorFormatter = "35";
        break;
      case Color::Cyan:
        colorFormatter = "36";
        break;
      case Color::White:
        colorFormatter = "37";
        break;
      case Color::Gray:
      default:
        colorFormatter = "90";
        break;
    }

    return colorFormatter;
  }

  inline
  std::string
  StreamFormatter::getFormatterForColor(const Color& color) const noexcept {
    return std::string("\033[1;") + getStringForColor(color) + "m";
  }

}

#endif    /* STREAM_FORMATTER_HXX */
