#ifndef MICRO_LIBMATH_MATRIX4XN_TRANSFORM_HH__GUARD
#define MICRO_LIBMATH_MATRIX4XN_TRANSFORM_HH__GUARD

#include <cmath>

#include "matrix4x4.hh"

namespace micro::math
{
	// ----------------------------- Scale ----------------------------- //

	template <class T>
	constexpr TMatrix4x4<T> scale4x4(T x = T(1),
					 T y = T(1),
					 T z = T(1)) noexcept
	{
		return TMatrix4x4<T>{T(x), T(0), T(0), T(0),
				     T(0), T(y), T(0), T(0),
				     T(0), T(0), T(z), T(0),
				     T(0), T(0), T(0), T(1)};
	}

	// --------------------------- Translate --------------------------- //

	template <class T>
	constexpr TMatrix4x4<T> translate4x4(T x,
					     T y,
					     T z) noexcept
	{
		return TMatrix4x4<T>{T(1), T(0), T(0), T(x),
				     T(0), T(1), T(0), T(y),
				     T(0), T(0), T(1), T(z),
				     T(0), T(0), T(0), T(1)};
	}

	// ----------------------------- Rotate ---------------------------- //

	template<class T>
	inline TMatrix4x4<T> rotate4x4(TVector3<T> const &u, T angle) noexcept
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

		TMatrix4x4<T> const K{n, z, y, n,
				      x, n, d, n,
				      e, f, n, n,
				      n, n, n, n};

		//
		// RODRIGUES FORMULA
		//

		return identity4x4<T>() + s * K + (T(1) - c) * K * K;
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
	constexpr TMatrix4x4<T> lookto4x4(TVector3<T> const &top,
					  TVector3<T> const &fwd,
					  TVector3<T> const &eye) noexcept
	{
		auto const i = top ^ fwd;
		auto const j = top;
		auto const k = fwd;

		return TMatrix4x4<T>{i.x(), i.y(), i.z(), -dot(i, eye),
				     j.x(), j.y(), j.z(), -dot(j, eye),
				     k.x(), k.y(), k.z(), -dot(k, eye), T(0), T(0), T(0), T(1)};
	}

	template <class T>
	constexpr TMatrix4x4<T> lookat4x4(TVector3<T> const &top,
					  TVector3<T> const &pos,
					  TVector3<T> const &eye) noexcept
	{
		auto const fwd = normalize(pos - eye);
		auto const lft = normalize(top ^ fwd);

		//
		//

		return lookto4x4(fwd ^ lft, fwd, eye);
	}

	// --------------------------- Projection -------------------------- //

	template <class T>
	constexpr TMatrix4x4<T> projection4x4(T x, T X,
					      T y, T Y,
					      T z, T Z) noexcept
	{
		return TMatrix4x4<T>{T(x), T(0), T(0), T(X),
				     T(0), T(y), T(0), T(Y),
				     T(0), T(0), T(z), T(Z),
				     T(0), T(0), T(1), T(0)};
	}

	template <class T>
	constexpr TMatrix4x4<T> persp_projection4x4(T w, T h,
						    T n, T f) noexcept
	{
		auto const N =  n + n;
		auto const D =  f - n;
		auto const x =  N / w;
		auto const y =  N / h;
		auto const z =  f / D;
		auto const Z = -n * z;

		///
		/// Single point perspective matrix
		///

		return TMatrix4x4<T>{T(x), T(0), T(0), T(0),
				     T(0), T(y), T(0), T(0),
				     T(0), T(0), T(z), T(Z),
				     T(0), T(0), T(1), T(0)};
	}

	template <class T>
	constexpr TMatrix4x4<T> perspFOV_projection4x4(T a, T r,
						       T n, T f) noexcept
	{
		auto const h = n * std::tan(a / T(2));
		auto const w = h * r;

		///
		/// Single point perspective matrix
		///

		return persp_projection4x4(w, h, n, f);
	}
}

#endif