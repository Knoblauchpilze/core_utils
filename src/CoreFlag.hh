#ifndef    CORE_FLAG_HH
# define   CORE_FLAG_HH

# include <bitset>
# include <memory>
# include <string>
# include <iostream>
# include <type_traits>
# include <unordered_map>

namespace utils {

  /**
   * @brief - Used to retrieve a human readable name for the input key.
   *          The user should specialize this function for its own
   *          type in order to fully benefit from the `CoreFlag` type.
   * @param key - an enumeration value for which the name should be
   *              retrieved.
   * @return - a human readable string allowing to describe the input
   *           key value.
   */
  template <typename Enum>
  std::string
  getNameForKey(const Enum& key);

  template <typename Enum>
  class CoreFlag {

    static_assert(std::is_enum<Enum>::value, "Must be an enum type");

    public:

      /**
       * @brief - Creates a flag with the no individual bit set to active. All
       *          possible values of the flag will be registered and the flag
       *          can readily be used to include any value defined by the `Enum`
       *          type.
       */
      explicit
      CoreFlag();

      /**
       * @brief - Creates a flag with the specified value activated. All possible
       *          values of the flag will be registered and the flag can readily
       *          be used to include any value defined by the `Enum` type.
       * @param value - the value to assign to this flag.
       */
      explicit
      CoreFlag(const Enum& value);

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
       * @brief - Specialization of the `operator==` which allows to check directly
       *          a key of the base enumeration without having to create a flag.
       *          Somewhat quicker than the previous version but fundamentally does
       *          the same job.
       * @param key - an enumeration value which should be checked for unique existence
       *              in `this` flag.
       * @return - `true` if `this` flag only contains the input `key` value, and `false`
       *           otherwise.
       */
      bool
      operator==(const Enum& key) const noexcept;

      /**
       * @brief - Similar behavior to `operator==` but checks for difference between
       *          both `this` and `rhs`.
       * @param rhs - the other element to compare with `this`.
       * @return - `true` if both `this` and `rhs` are different and `false` otherwise.
       */
      bool
      operator!=(const CoreFlag& rhs) const noexcept;

      /**
       * @brief - Same as above but with a variant containing a single enumeration key
       *          rather than a fully fleshed flag.
       * @param key - the enumeration value which should be checked for unique existence
       *              in `this` flag.
       * @return - `true` if `this` does not only contain the input `key` value.
       */
      bool
      operator!=(const Enum& key) const noexcept;

      /**
       * @brief - Performs the bitwise AND operation between `this` and the `rhs` value.
       * @param rhs - the other element which should be ORed with `this`.
       * @return - a reference to `this` object once modified.
       */
      CoreFlag&
      operator|=(const CoreFlag& rhs) noexcept;

      /**
       * @brief - Same as above but performs the insertion of the input enumeration key
       *          without needed to create another flag. Basically equivalent to calling
       *          `set(key)` on `this` flag.
       * @param key - the enumeration value which should be ORed with `this` flag.
       * @return - a reference on `this` flag after inserting the `key` in it.
       */
      CoreFlag&
      operator|=(const Enum& key) noexcept;

      /**
       * @brief - Performs the bitwise AND operation between `this` and the `rhs` value.
       * @param rhs - the other element which should be ANDed with `this`.
       * @return - a reference to `this` object once modified.
       */
      CoreFlag&
      operator&=(const CoreFlag& rhs) noexcept;

      /**
       * @brief - Same as above but performs the logical AND between the input enumeration
       *          key and the existing value of `this` without needed to create another flag.
       * @param key - the enumeration value which should be ANDed with `this` flag.
       * @return - a reference on `this` flag after ANDing with the `key`.
       */
      CoreFlag&
      operator&=(const Enum& key) noexcept;

      /**
       * @brief - Performs the bitwise XOR operation between `this` and the `rhs` value.
       * @param rhs - the other element which should be XORed with `this`.
       * @return - a reference to `this` object once modified.
       */
      CoreFlag&
      operator^=(const CoreFlag& rhs) noexcept;

      /**
       * @brief - Same as above but performs the logical XOR between the input enumeration
       *          key and the existing value of `this` without crteating another flag.
       * @param key - the enumeration value which should be XORed with `this` flag.
       * @return - a reference on `this` flag after XORing with the `key`.
       */
      CoreFlag&
      operator^=(const Enum& key) noexcept;

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
       * @brief - Used to set the value of the individual flag value associated to
       *          the enumeration value `key`  to active.
       *          Nothing happens if this value is already activated.
       *          An error is raised if the corresponding bit hasn't been registered
       *          through the `addBit` method beforehand.
       * @param key - the enumeration value for which the associated bit should be
       *              set.
       * @return - `true` if the value was effectively changed, `false` otherwise.
       */
      bool
      set(const Enum& key);

      /**
       * @brief - Used to set the value of the individual flag value associated to
       *          the enumeration value `key` to inactive.
       *          Nothing happens if this value is already deactivated.
       *          An error is raised if the corresponding bit hasn't been registered
       *          through the `addBit` method beforehand.
       * @param id - the enumeration value for whichthe associated bit should be
       *             unset.
       * @return - `true` if the value was effectively changed, `false` otherwise.
       */
      bool
      unset(const Enum& key);

      /**
       * @brief - Allows to check whether the bit associated to the individual value
       *          `key` is currently set or unset. Note that this method raises an
       *          error if the corresponding bit has not been registered through the
       *          `addBit` method yet.
       * @param key - the enumeration key for which the bit should be checked.
       * @return - `true` if the corresponding bit is registered and activated and
       *           `false` if is is registered but deactivated.
       */
      bool
      isSet(const Enum& key) const;

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
       * @brief - Used to initialize the flag bits in order to be able to easily use all the
       *          values provided by the input enum. We traverse the enumeration by assuming
       *          that the available value range from `0` all the way up to `ValuesCount`.
       */
      void
      init();

      /**
       * @brief - Used to extract the name of the flag: we demangle the enum type so that we
       *          get a human readable string.
       * @return - the unmangled string representing the name of the enum used to create this
       *           flag.
       */
      std::string
      extractName() const noexcept;

      /**
       * @brief - Used to retrieve the index in the internal bitset for the input
       *          enumeration key. If no such index is defined `-1` is returned.
       * @param key - the enumeration value for which the index of the associated
       *              bit should be returned.
       * @return - the index of the bit corresponding to the input `key` or `-1`
       *           if no such bit exists.
       */
      int
      getIdFor(const Enum& key) const noexcept;

      /**
       * @brief - Used to register a new bit with the specified enumeration value
       *          `key` in this flag. The return value indicates the position of
       *          the key in the internal bits array. An internal counter is used
       *          to determine how many bits have already been registered to some
       *          values and if all the bits have already been used an error is
       *          raised.
       *          The user can specify the default value for this bit: this is used
       *          in the `clear` method to reset the flag to its initial value.
       * @param key - the enumeration value to register.
       * @param value - the default value to assign to this bit (will be assigned
       *                to the bit upon creating it).
       * @param defaultValue - the default value to assign to the bit when calling
       *                       `clear` method.
       * @return - an index representing the position of the bit in the internal
       *           bits array. This value is in the range `[0; size()]`.
       */
      int
      addBit(const Enum& key,
             bool value,
             bool defaultValue = false);

    private:

      using FlagType = std::underlying_type_t<Enum>;

      /**
       * @brief - Convenience structure to describe a bit with its name and default value.
       */
      struct BitDesc {
        int id;
        bool defVal;
      };

      using BitsIDs = std::unordered_map<Enum, BitDesc>;

      /**
       * @brief - Convenience names to format core exception messages.
       */
      static const char* sk_serviceName;

      std::string m_name;
      std::bitset<static_cast<FlagType>(Enum::ValuesCount)> m_bits;
      BitsIDs m_descs;
  };

  template <typename Enum>
  using CoreFlagShPtr = std::shared_ptr<CoreFlag<Enum>>;
}

/**
 * @brief - Performs the bitwise OR operation between `lhs` and the `rhs` value.
 * @param lhs - the first element to OR.
 * @param rhs - the second element to OR.
 * @return - a new flag with resulting of the OR operation.
 */
template <typename Enum>
utils::CoreFlag<Enum>
operator|(const utils::CoreFlag<Enum>& lhs, const utils::CoreFlag<Enum>& rhs) noexcept;

/**
 * @brief - Performs the bitwise AND operation between `lhs` and the `rhs` value.
 * @param lhs - the first element to AND.
 * @param rhs - the second element to AND.
 * @return - a new flag with resulting of the AND operation.
 */
template <typename Enum>
utils::CoreFlag<Enum>
operator&(const utils::CoreFlag<Enum>& lhs, const utils::CoreFlag<Enum>& rhs) noexcept;

/**
 * @brief - Performs the bitwise XOR operation between `lhs` and the `rhs` value.
 * @param lhs - the first element to XOR.
 * @param rhs - the second element to XOR.
 * @return - a new flag with resulting of the XOR operation.
 */
template <typename Enum>
utils::CoreFlag<Enum>
operator^=(const utils::CoreFlag<Enum>& lhs, const utils::CoreFlag<Enum>& rhs) noexcept;

/**
 * @brief - Outputs the specified flag into the provided stream. Each named bit is
 *          dumped with its name if it is set.
 * @param f - the flag to output to a stream.
 * @param out - the stream into which the flag should be dumped.
 * @return - a reference to the modified stream.
 */
template <typename Enum>
std::ostream&
operator<<(std::ostream& out, const utils::CoreFlag<Enum>& f) noexcept;

/**
 * @brief - Outputs the specified flag into the provided stream. Each named bit is
 *          dumped with its name if it is set.
 * @param f - the flag to output to a stream.
 * @param out - the stream into which the flag should be dumped.
 * @return - a reference to the modified stream.
 */
template <typename Enum>
std::ostream&
operator<<(const utils::CoreFlag<Enum>& f, std::ostream& out) noexcept;

# include "CoreFlag.hxx"

#endif    /* CORE_FLAG_HH */
