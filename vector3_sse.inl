#ifndef MICRO_LIBMATH_VECTOR3_SSE_INL__GUARD
#define MICRO_LIBMATH_VECTOR3_SSE_INL__GUARD

#include <immintrin.h>

#ifndef MICRO_LIBMATH_VECTOR3_HH__GUARD
#	include "vector3.hh"
#endif

#ifndef _MSC_VER
#	define __vectorcall
#endif

namespace micro::math
{
	inline TVector3<float> __vectorcall operator^(TVector3<float> const &a,
						      TVector3<float> const &b) noexcept
	{
		auto const A = _mm_set_ps(0, a.data[2], a.data[1], a.data[0]);
		auto const B = _mm_set_ps(0, b.data[2], b.data[1], b.data[0]);
		auto const C = _mm_shuffle_ps(A, A, _MM_SHUFFLE(3, 0, 2, 1));
		auto const D = _mm_shuffle_ps(B, B, _MM_SHUFFLE(3, 1, 0, 2));
		auto const E = _mm_mul_ps(C, B);
		auto const F = _mm_mul_ps(C, D);
		auto const G = _mm_shuffle_ps(E, E, _MM_SHUFFLE(3, 0, 2, 1));
		auto const X = _mm_sub_ps(F, G);
		auto const Y = _mm_shuffle_ps(X, X, _MM_SHUFFLE(1, 1, 1, 1));
		auto const Z = _mm_shuffle_ps(X, X, _MM_SHUFFLE(2, 2, 2, 2));

		//
		//

		return {_mm_cvtss_f32(X),
			_mm_cvtss_f32(Y),
			_mm_cvtss_f32(Z)};
	}

	// ----------------------------------------------------------------- //

	inline float __vectorcall dot(TVector3<float> const &a,
				      TVector3<float> const &b) noexcept
	{
		auto const A = _mm_set_ps(0, a.data[2], a.data[1], a.data[0]); // a.xyz_
		auto const B = _mm_set_ps(0, b.data[2], b.data[1], b.data[0]); // b.xyz_
		auto const C = _mm_mul_ps(A, B); // (a * b)
		auto const D = _mm_shuffle_ps(C, C, _MM_SHUFFLE(1, 1, 1, 1)); // (a * b).yyyy
		auto const E = _mm_shuffle_ps(C, C, _MM_SHUFFLE(2, 2, 2, 2)); // (a * b).zzzz
		auto const F = _mm_add_ss(C, D); // (a * b).x + (a * b).y
		auto const G = _mm_add_ss(F, E); // (a * b).x + (a * b).y + (a * b).z

		//
		//

		return _mm_cvtss_f32(G);
	}
}

#endif