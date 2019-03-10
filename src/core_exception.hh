#ifndef    CORE_EXCEPTION_HH_
# define   CORE_EXCEPTION_HH_

# include <string>
# include <stdexcept>
# include "core_logger.hh"
# include "core_event.hh"

namespace core {

  class InternalException: public std::exception {
  public:

    /*
     * @brief - Builds an exception with the specified error message.
     * @param message - a string representing the error message.
     * @param module - the name of the module which produced the exception.
     * @param cause - the cause of the exception (empty if any).
     * @param level - the level of the exception.
     */
    explicit
    InternalException(const std::string&  message,
                      const std::string&  module,
                      const std::string&  cause = std::string(""),
                      const Level&        level = Level::Error) noexcept;

    /*
     * @brief - Retrieves the error message associated to this exception.
     * @return - a string representing the error message of this exception.
     */
    virtual const char*
    what() const noexcept;

  private:

    /*
     * @brief - Used to log the message associated to this error with the specified level.
     * @param level - the level of this error.
     * @param module - the name of the module which generated the exception.
     * @param cause - the cause of the exception (empty if none).
     */
    void
    logError(const Level&        level,
             const std::string&  module,
             const std::string&  cause) const;

    /*
     * @brief - Used to retrieve the curretn stack trace.
     * @return - a string representing the stack trace.
     */
    std::string
    retrieveStackTrace() const noexcept;

  private:

    /*
     * @brief - The maximum stack trace level handled by this kind of exceptions.
     */
    static const unsigned sk_stackTraceDepth;

    /*
     * @brief - The message associated to this error.
     */
    std::string m_message;

  };
}

# include "core_exception.hxx"

#endif    /*! CORE_EXCEPTION_HH_ */
