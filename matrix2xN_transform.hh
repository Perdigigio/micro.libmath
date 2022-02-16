#ifndef MICRO_LIBMATH_MATRIX2XN_TRANSFORM_HH__GUARD
#define MICRO_LIBMATH_MATRIX2XN_TRANSFORM_HH__GUARD

#include <cmath>

#include "matrix2x2.hh"
#include "matrix2x3.hh"

namespace micro::math
{
	// ----------------------------- Scale ----------------------------- //

	template <class T>
	constexpr TMatrix2x2<T> scale2x2(T x = T(1),
					 T y = T(1)) noexcept
	{
		return TMatrix2x2<T>{T(x), T(0),
				     T(0), T(y)};
	}

	template <class T>
	constexpr TMatrix2x3<T> scale2x3(T x = T(1),
					 T y = T(1)) noexcept
	{
		return TMatrix2x3<T>{T(x), T(0), T(0),
				     T(0), T(y), T(0)};
	}

	// --------------------------- Translate --------------------------- //


	template <class T>
	constexpr TMatrix2x3<T> translate2x3(T x,
					     T y) noexcept
	{
		return TMatrix2x3<T>{T(1), T(0), T(x),
				     T(0), T(1), T(y)};
	}

	// ----------------------------- Rotate ---------------------------- //

	template<class T>
	inline TMatrix2x2<T> rotate2x2(TVector3<T> const &u, T angle) noexcept
	{
		auto const s = std::sin(angle);
		auto const c = std::cos(angle);

		return TMatrix2x2<T>{+c, -s,
				     +s, +c};
	}

}

#endif