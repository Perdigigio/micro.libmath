#ifndef MICRO_LIBMATH_MATRIX2X2_SSE_INL__GUARD
#define MICRO_LIBMATH_MATRIX2X2_SSE_INL__GUARD

#include <immintrin.h>

#ifndef MICRO_LIBMATH_MATRIX2X2_HH__GUARD
#	include "matrix2x2.hh"
#endif

#ifndef _MSC_VER
#	define __vectorcall
#endif

namespace micro::math
{
	inline TMatrix2x2<double> operator *(TMatrix2x2<double> const &a,
					     TMatrix2x2<double> const &b) noexcept
	{
		alignas(alignof(__m128d)) TVector2<double> _0;
		alignas(alignof(__m128d)) TVector2<double> _1;

		auto const A = _mm_loadu_pd(a.data[0].data); // ab
		auto const B = _mm_loadu_pd(a.data[1].data); // cd
		auto const C = _mm_loadu_pd(b.data[0].data); // ef
		auto const D = _mm_loadu_pd(b.data[1].data); // gh

		auto const E = _mm_shuffle_pd(A, A, _MM_SHUFFLE2(1, 1)); // bb
		auto const F = _mm_shuffle_pd(B, B, _MM_SHUFFLE2(1, 1)); // dd

#ifdef __SSE3__
		auto const G = _mm_movedup_pd(A); // aa
		auto const H = _mm_movedup_pd(B); // cc
#else
		auto const G = _mm_shuffle_pd(A, A, _MM_SHUFFLE2(0, 0)); // aa
		auto const H = _mm_shuffle_pd(B, B, _MM_SHUFFLE2(0, 0)); // cc
#endif

		auto const I = _mm_mul_pd(G, C); // aa * ef
		auto const J = _mm_mul_pd(H, C); // cc * ef
		auto const K = _mm_mul_pd(E, D); // bb * gh
		auto const L = _mm_mul_pd(F, D); // dd * gh

		_mm_store_pd(_0.data, _mm_add_pd(I, K));
		_mm_store_pd(_1.data, _mm_add_pd(J, L));

		return {_0, _1};
	}

	// ----------------------------------------------------------------- //

	inline TMatrix2x2<double> __vectorcall transpose(TMatrix2x2<double> const &m) noexcept
	{
		TVector2<double> _0;
		TVector2<double> _1;

		auto const A = _mm_loadu_pd(m.data[0].data);
		auto const B = _mm_loadu_pd(m.data[1].data);
		auto const C = _mm_shuffle_pd(A, B, _MM_SHUFFLE2(0, 0));
		auto const D = _mm_shuffle_pd(A, B, _MM_SHUFFLE2(1, 1));

		_mm_storeu_pd(_0.data, C);
		_mm_storeu_pd(_1.data, D);

		return {_0, _1};
	}
}

#endif