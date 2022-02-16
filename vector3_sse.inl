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
		float l_lo[2];
		float l_hi[2];

		auto const A = _mm_load_sd(reinterpret_cast<double const *>(a.data)); /// ax ay
		auto const B = _mm_load_sd(reinterpret_cast<double const *>(b.data)); /// bx by
		auto const C = _mm_load_ss(a.data + 2); /// az 0
		auto const D = _mm_load_ss(b.data + 2); /// bz 0
		auto const E = _mm_movelh_ps(_mm_castpd_ps(A), C); /// ax ay az 0
		auto const F = _mm_movelh_ps(_mm_castpd_ps(B), D); /// bx by bz 0

		auto const G = _mm_shuffle_ps(E, E, _MM_SHUFFLE(3, 0, 2, 1)); /// ay az ax 0
		auto const H = _mm_shuffle_ps(F, F, _MM_SHUFFLE(3, 1, 0, 2)); /// bz bx by 0
		auto const I = _mm_mul_ps(G, F); /// (ay * bx) (az * by) (ax * bz) 0 
		auto const J = _mm_mul_ps(G, H); /// (ay * bz) (az * bx) (ax * by) 0 
		auto const K = _mm_shuffle_ps(I, I, _MM_SHUFFLE(3, 0, 2, 1)); /// (az * by) (ax * bz) (ay * bx) 0 
		auto const L = _mm_sub_ps(J, K);

		_mm_storel_pi(reinterpret_cast<__m64 *>(l_lo), L);
		_mm_storeh_pi(reinterpret_cast<__m64 *>(l_hi), L);

		//
		//

		return {l_lo[0], l_lo[1], l_hi[0]};
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