#ifndef    RNG_HH
# define   RNG_HH

# include <random>
# include <ostream>
# include <istream>
# include "CoreObject.hh"

namespace utils {

  class RNG: public CoreObject {
    public:

      /**
       * @brief - Create a new RNG with the specified seed. This
       *          is a convenient way to ensure that all needs
       *          for a random number are satisfied by a single
       *          class and thus ensure reproctability of runs
       *          within the application.
       * @param seed - the seed to use for this RNG.
       */
      RNG(int seed = 0);

      /**
       * @brief - Used to perform the creation of a random number
       *          generator initialized with some seed not known
       *          to the user. Compared to the canonical method
       *          above it avoid the user to care about generating
       *          a seed.
       * @return - the created RNG.
       */
      static
      RNG
      createRandomRNG() noexcept;

      /**
       * @brief - Used to generate a random number in the range
       *          defined by the input value.
       * @param min - the minimum value to generate.
       * @param max - the maximum value allowed to be generated.
       * @return - a random value in the range `[min; max]`.
       */
      int
      rndInt(int min, int max) noexcept;

      /**
       * @brief - Used to generate a random number in the range
       *          defined by the input value. Similar to the
       *          `rndInt` method but for floats.
       * @param min - the minimum value to generate.
       * @param max - the maximum value allowed to be generated.
       * @return - a random value in the range `[min; max]`.
       */
      float
      rndFloat(float min, float max) noexcept;

      /**
       * @brief - Used as a convenience method to generate a
       *          random angle in the range `[min; max]`.
       * @param min - the min angle that can be generated.
       *              Default value is `0`.
       * @param max - the max angle that can be generated.
       *              Default value is `2pi`.
       * @return - an value in the range `[min; max]`.
       */
      float
      rndAngle(float min = 0.0f, float max = 6.283185307f) noexcept;

      /**
       * @brief - Serialization operator to allow easy export
       *          of this object's data to any stream.
       * @param out - the stream to serialize into.
       * @return - the modified stream.
       */
      std::ostream&
      operator<<(std::ostream& out) const;

      /**
       * @brief - Deserialization operator allowing to load the
       *          properties to redefinan object from the input
       *          stream.
       * @param in - the input stream from which data should be
       *             read.
       * @return - the modified stream.
       */
      std::istream&
      operator>>(std::istream& in);

    private:

      /**
       * @brief - The actual RNG. It produces high quality random
       *          numbers in the range `[0; 2^32 - 1]` as defined
       *          in the CPP reference.
       */
      std::mt19937 m_rng;
  };

}

/**
 * @brief - Serialization function allowing to insert the representation
 *          of the `RNG` object to the stream.
 * @param out - the stream into which the RNG will be appended.
 * @param rng - the `RNG` object to serialize.
 * @return - the modified stream.
 */
std::ostream&
operator<<(std::ostream& out, const utils::RNG& rng) noexcept;

/**
 * @brief - Deserialization function allowing to extract the representation
 *          of the `RNG` object from the stream.
 * @param int - the stream from which the RNG will be generated.
 * @param rng - the `RNG` object into which the deserialization is performed.
 * @return - the modified stream.
 */
std::istream&
operator>>(std::istream& in, utils::RNG& rng) noexcept;

# include "RNG.hxx"

#endif    /* RNG_HH */
