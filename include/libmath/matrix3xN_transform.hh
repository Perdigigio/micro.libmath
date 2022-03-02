#ifndef MICRO_LIBMATH_MATRIX3XN_TRANSFORM_HH__GUARD
#define MICRO_LIBMATH_MATRIX3XN_TRANSFORM_HH__GUARD

#include <cmath>

#include "matrix3x3.hh"
#include "matrix3x4.hh"

namespace micro::math
{
	// ----------------------------- Scale ----------------------------- //

	template <class T>
	constexpr TMatrix3x3<T> scale3x3(T x = T(1),
					 T y = T(1),
					 T z = T(1)) noexcept
	{
		return TMatrix3x3<T>{T(x), T(0), T(0),
				     T(0), T(y), T(0),
				     T(0), T(0), T(z)};
	}

	template <class T>
	constexpr TMatrix3x4<T> scale3x4(T x = T(1),
					 T y = T(1),
					 T z = T(1)) noexcept
	{
		return TMatrix3x4<T>{T(x), T(0), T(0), T(0),
				     T(0), T(y), T(0), T(0),
				     T(0), T(0), T(z), T(0)};
	}

	// --------------------------- Translate --------------------------- //

	template <class T>
	constexpr TMatrix3x3<T> translate3x3(T x,
					     T y) noexcept
	{
		return TMatrix3x3<T>{T(1), T(0), T(x),
				     T(0), T(1), T(y),
				     T(0), T(0), T(1)};
	}

	template <class T>
	constexpr TMatrix3x3<T> translate3x4(T x,
					     T y,
					     T z) noexcept
	{
		return TMatrix3x4<T>{T(1), T(0), T(0), T(x),
				     T(0), T(1), T(0), T(y),
				     T(0), T(0), T(1), T(z)};
	}

	// ----------------------------- Rotate ---------------------------- //

	template<class T>
	inline TMatrix3x3<T> rotate3x3(TVector3<T> const &u, T angle) noexcept
	{
		auto const o = T(1);
		auto const n = T(0);
		auto const s = std::sin(angle);
		auto const c = std::cos(angle);

		auto const z = -u.z();
		auto const y = +u.y();
		auto const x = +u.z();
		auto const d = -u.x();
		auto const e = -u.y();
		auto const f = +u.x();

		TMatrix3x3<T> const K{n, z, y,
				      x, n, d,
				      e, f, n};

		//
		// RODRIGUES FORMULA
		//

		return identity3x3<T>() + s * K + (T(1) - c) * K * K;
	}

	// ------------------------------ View ----------------------------- //

	/**
	 * @brief Builds a 4x4 view matrix
	 * 
	 * @param top y axis vector, should be normalized
	 * @param fwd z axis vector, should be normalized
	 * @param eye eye position in world coordinates
	 * 
	 */
	template <class T>
	constexpr TMatrix3x4<T> lookto3x4(TVector3<T> const &top,
					  TVector3<T> const &fwd,
					  TVector3<T> const &eye) noexcept
	{
		auto const i = top ^ fwd;
		auto const j = top;
		auto const k = fwd;

		return TMatrix3x4<T>{i.x(), j.x(), k.x(), -dot(i, eye),
				     i.y(), j.y(), k.y(), -dot(j, eye),
				     i.z(), j.z(), k.z(), -dot(k, eye)};
	}

	template <class T>
	constexpr TMatrix3x4<T> lookat3x4(TVector3<T> const &top,
					  TVector3<T> const &pos,
					  TVector3<T> const &eye) noexcept
	{
		auto const fwd = normalize(pos - eye);
		auto const lft = normalize(top ^ fwd);

		//
		//

		return lookto3x4(fwd ^ lft, fwd, eye);
	}

}

#endif