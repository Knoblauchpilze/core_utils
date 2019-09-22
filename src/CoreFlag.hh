#ifndef    CORE_FLAG_HH
# define   CORE_FLAG_HH

# include <bitset>
# include <memory>
# include <string>
# include <iostream>
# include <unordered_map>

namespace utils {

  template <int N>
  class CoreFlag {
    public:

      /**
       * @brief - Create a new flag from the input value. The values of the individual
       *          bits will be equal in the created copy.
       * @param rhs - the flag value to copy.
       */
      CoreFlag(const CoreFlag& rhs) noexcept;

      /**
       * @brief- Destruction of the object.
       */
      ~CoreFlag() = default;

      /**
       * @brief - Retrieves the name of this flag.
       * @return - the name of this flag.
       */
      const std::string&
      getName() const noexcept;

      /**
       * @brief - Determines whether `this` and `rhs` are equal. We don't have a
       *          real semantic associated to each value of the flag at this level
       *          but we do compare that both pointers have the same length and
       *          that each individual flag value is set with the same vaule.
       * @param rhs - the other element to compare with `this`.
       * @return - `true` if both `this` and `rhs` have the same length and content
       *           for each value and `đalse` otherwise.
       */
      bool
      operator==(const CoreFlag& rhs) const noexcept;

      /**
       * @brief - Similar behavior to `operator==` but checks for difference between
       *          both `this` and `rhs`.
       * @param rhs - the other element to compare with `this`.
       * @return - `true` if both `this` and `rhs` are different and `false` otherwise.
       */
      bool
      operator!=(const CoreFlag& rhs) const noexcept;

      /**
       * @brief - Performs the bitwise AND operation between `this` and the `rhs` value.
       * @param rhs - the other element which should be ORed with `this`.
       * @return - a reference to `this` object once modified.
       */
      CoreFlag&
      operator|=(const CoreFlag& rhs) noexcept;

      /**
       * @brief - Performs the bitwise AND operation between `this` and the `rhs` value.
       * @param rhs - the other element which should be ANDed with `this`.
       * @return - a reference to `this` object once modified.
       */
      CoreFlag&
      operator&=(const CoreFlag& rhs) noexcept;

      /**
       * @brief - Performs the bitwise XOR operation between `this` and the `rhs` value.
       * @param rhs - the other element which should be XORed with `this`.
       * @return - a reference to `this` object once modified.
       */
      CoreFlag&
      operator^=(const CoreFlag& rhs) noexcept;

      /**
       * @brief - Performs the bitwise NOT operation on a temporary copy of `this`.
       * @return - a copy of `this` with all bits reversed.
       */
      CoreFlag
      operator~() const noexcept;

      /**
       * @brief - Represents the number of individual values available to build a value
       *          for this flag. Not all of them might be used, e.g. we always have the
       *          following property: `size() >= reserved()`.
       * @return - the maximum number of values possible to build a value for this flag.
       */
      int
      size() const noexcept;

      /**
       * @brief - Represents the number of individual values already registered to a
       *          named option. Typically a flag is an empty container which can be used
       *          in order to represent efficiently flag values: to use it the user needs
       *          to register each value possible for building a flag through dedicated
       *          handlers such as `addNamedBit` before being able to de/activate some
       *          with the `set` and `unset` methods.
       *          The value returned by this method represents the number of bits already
       *          assigned through this method. It is always smaller than the `size`
       *          value.
       * @return - the number of registered values to build a flag.
       */
      int
      reserved() const noexcept;

      /**
       * @brief - Resets all the bits of this flag to their default values.
       */
      void
      clear() noexcept;

      /**
       * @brief - Writes this flag as a human readable string where each activated bit is
       *          dumped by its name. We are guaranteed to be able to find a name for each
       *          bit as the only way to add them is through the `addNamedBit` method.
       *          Bits which are not active are not dumped.
       * @return - a string representing this flag's individual bits.
       */
      std::string
      toString() const noexcept;

    protected:

      /**
       * @brief - Creates a flag with the specified number of possible values. The
       *          actual `length` of the flag is specified by the template parameter
       *          and corresponds to the number of individual values which are 
       *          to build any value of the flag.
       *          This does not mean that the flag is limited to `length` values
       *          but rather than each possible value of the flag is made by doing
       *          composition of these individual values.
       *          Theoretically the number of possible values is thus `2^length`.
       * @param name - the name of this flag as a human readable string.
       */
      CoreFlag(const std::string& name);

      /**
       * @brief - Used to register a new bit with the specified `name` in this flag.
       *          The return value indicates the position of the named option in the
       *          internal bits array. An internal counter is used to determine which
       *          bits have already been registered to some values and if all the bits
       *          have already been used an error is raised.
       *          The user can specify the default value for this bit: this is used in
       *          the `clear` method to reset the flag to its initial value.
       * @param name - the name of the bit to add.
       * @param value - the default value to assign to this bit (will be assigned to the
       *                bit upon creating it)
       * @param defaultValue - the default value to assign to the bit when calling `clear`
       *                       method.
       * @return - an index representing the position of the bit in the internal bits
       *           array. This value is in the range `[0; size()]`.
       */
      int
      addNamedBit(const std::string& name,
                  bool value,
                  bool defaultValue = false);

      /**
       * @brief - Used to set the value of the individual flag value at `id` to active.
       *          Nothing happens if this value is already activated.
       *          An error is raised if the corresponding bit hasn't registered through
       *          the `addNamedBit` method beforehand.
       * @param id - the index of the individual flag to set.
       * @return - `true` if the value was effectively changed, `false` otherwise.
       */
      bool
      set(int id);

      /**
       * @brief - Used to set the value of the individual flag value at `id` to inactive.
       *          Nothing happens if this value is already deactivated.
       *          An error is raised if the corresponding bit hasn't registered through
       *          the `addNamedBit` method beforehand.
       * @param id - the index of the individual flag to unset.
       * @return - `true` if the value was effectively changed, `false` otherwise.
       */
      bool
      unset(int id);

      /**
       * @brief - Allows to check whether the bit at `id` is currently set or unset. Note
       *          that this method raises an error if the corresponding bit has not been
       *          registered through the `addNamedBit` method yet.
       * @param id - the index of the individual flag to query.
       * @return - `true` if the corresponding bit is registered and activated and `false`
       *           if is is registered but deactivated.
       */
      bool
      isSet(int id) const;

    private:

      /**
       * @brief - Convenience structure to describe a bit with its name and default value.
       */
      struct BitDesc {
        std::string name;
        bool defVal;
      };

      /**
       * @brief - Specialization needed to provide the `operator==` on `BitDesc` elements,
       *          needed by the `BitsNames::operator==` operator.
       */
      friend bool operator==(const BitDesc& lhs, const BitDesc& rhs) noexcept;

      using BitsNames = std::unordered_map<int, BitDesc>;

      /**
       * @brief - Convenience names to format core exception messages.
       */
      static const char* sk_serviceName;

      std::string m_name;
      std::bitset<N> m_bits;
      BitsNames m_descs;
  };

  template <int N>
  using CoreFlagShPtr = std::shared_ptr<CoreFlag<N>>;
}

/**
 * @brief - Performs the bitwise OR operation between `lhs` and the `rhs` value.
 * @param lhs - the first element to OR.
 * @param rhs - the second element to OR.
 * @return - a new flag with resulting of the OR operation.
 */
template <int N>
utils::CoreFlag<N>
operator|(const utils::CoreFlag<N>& lhs, const utils::CoreFlag<N>& rhs) noexcept;

/**
 * @brief - Performs the bitwise AND operation between `lhs` and the `rhs` value.
 * @param lhs - the first element to AND.
 * @param rhs - the second element to AND.
 * @return - a new flag with resulting of the AND operation.
 */
template <int N>
utils::CoreFlag<N>
operator&(const utils::CoreFlag<N>& lhs, const utils::CoreFlag<N>& rhs) noexcept;

/**
 * @brief - Performs the bitwise XOR operation between `lhs` and the `rhs` value.
 * @param lhs - the first element to XOR.
 * @param rhs - the second element to XOR.
 * @return - a new flag with resulting of the XOR operation.
 */
template <int N>
utils::CoreFlag<N>
operator^=(const utils::CoreFlag<N>& lhs, const utils::CoreFlag<N>& rhs) noexcept;

/**
 * @brief - Outputs the specified flag into the provided stream. Each named bit is
 *          dumped with its name if it is set.
 * @param f - the flag to output to a stream.
 * @param out - the stream into which the flag should be dumped.
 * @return - a reference to the modified stream.
 */
template <int N>
std::ostream&
operator<<(std::ostream& out, const utils::CoreFlag<N>& f) noexcept;

/**
 * @brief - Outputs the specified flag into the provided stream. Each named bit is
 *          dumped with its name if it is set.
 * @param f - the flag to output to a stream.
 * @param out - the stream into which the flag should be dumped.
 * @return - a reference to the modified stream.
 */
template <int N>
std::ostream&
operator<<(const utils::CoreFlag<N>& f, std::ostream& out) noexcept;

# include "CoreFlag.hxx"
# include "CoreFlag_specialization.hxx"

#endif    /* CORE_FLAG_HH */
