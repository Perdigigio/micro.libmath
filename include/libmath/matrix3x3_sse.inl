#ifndef MICRO_LIBMATH_MATRIX3X3_SSE_INL__GUARD
#define MICRO_LIBMATH_MATRIX3X3_SSE_INL__GUARD

#include <immintrin.h>

#ifndef MICRO_LIBMATH_MATRIX3X3_HH__GUARD
#	include "matrix3x3.hh"
#endif

#ifndef _MSC_VER
#	define __vectorcall
#endif

namespace micro::math
{
	/**
	 * @brief Multiply a row from A matrix with all rows of B matrix
	 * 
	 * @param r A matrix row
	 * @param a B matrix 1st-row
	 * @param b B matrix 2nd-row
	 * @param c B matrix 3rd-row
	 * 
	 * @return r.x * a + r.y * b + r.z * c
	 */
	inline __m128 __vectorcall _m3x3_mul_ps(__m128 const r,
						__m128 const a,
						__m128 const b,
						__m128 const c) noexcept
	{
		const auto A = _mm_shuffle_ps(r, r, _MM_SHUFFLE(0, 0, 0, 0));
		const auto B = _mm_shuffle_ps(r, r, _MM_SHUFFLE(1, 1, 1, 1));
		const auto C = _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 2, 2, 2));
		const auto D = _mm_mul_ps(A, a);
		const auto E = _mm_mul_ps(B, b);
		const auto F = _mm_mul_ps(C, c);
		const auto G = _mm_add_ps(D, F);
		const auto H = _mm_add_ps(G, E);

		return H;
	}

	inline TMatrix3x3<float> operator *(TMatrix3x3<float> const &a,
					    TMatrix3x3<float> const &b) noexcept
	{
		alignas(alignof(__m128)) float _0[4];
		alignas(alignof(__m128)) float _1[4];
		alignas(alignof(__m128)) float _2[4];

		auto const a0 = _mm_load_sd(reinterpret_cast<double const *>(a.data[0].data)); // xy
		auto const a1 = _mm_load_sd(reinterpret_cast<double const *>(a.data[1].data)); // xy
		auto const a2 = _mm_load_sd(reinterpret_cast<double const *>(a.data[2].data)); // xy
		auto const c0 = _mm_load_ss(a.data[0].data + 2); // z
		auto const c1 = _mm_load_ss(a.data[1].data + 2); // z
		auto const c2 = _mm_load_ss(a.data[2].data + 2); // z

		auto const b0 = _mm_load_sd(reinterpret_cast<double const *>(b.data[0].data)); // xy
		auto const b1 = _mm_load_sd(reinterpret_cast<double const *>(b.data[1].data)); // xy
		auto const b2 = _mm_load_sd(reinterpret_cast<double const *>(b.data[2].data)); // xy
		auto const d0 = _mm_load_ss(b.data[0].data + 2); // z
		auto const d1 = _mm_load_ss(b.data[1].data + 2); // z
		auto const d2 = _mm_load_ss(b.data[2].data + 2); // z

		auto const A0 = _mm_movelh_ps(_mm_castpd_ps(a0), c0); // xyz0
		auto const A1 = _mm_movelh_ps(_mm_castpd_ps(a1), c1); // xyz0
		auto const A2 = _mm_movelh_ps(_mm_castpd_ps(a2), c2); // xyz0
		auto const B0 = _mm_movelh_ps(_mm_castpd_ps(b0), d0); // xyz0
		auto const B1 = _mm_movelh_ps(_mm_castpd_ps(b1), d1); // xyz0
		auto const B2 = _mm_movelh_ps(_mm_castpd_ps(b2), d2); // xyz0

		_mm_store_ps(_0, _m3x3_mul_ps(A0, B0, B1, B2));
		_mm_store_ps(_1, _m3x3_mul_ps(A1, B0, B1, B2));
		_mm_store_ps(_2, _m3x3_mul_ps(A2, B0, B1, B2));

		return TMatrix3x3<float>{_0[0], _0[1], _0[2],
					 _1[0], _1[1], _1[2],
					 _2[0], _2[1], _2[2]};
	}
}

#endif