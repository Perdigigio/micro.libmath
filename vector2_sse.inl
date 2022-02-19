#ifndef MICRO_LIBMATH_VECTOR2_SSE_INL__GUARD
#define MICRO_LIBMATH_VECTOR2_SSE_INL__GUARD

#include <immintrin.h>

#ifndef MICRO_LIBMATH_VECTOR2_HH__GUARD
#	include "vector2.hh"
#endif

#ifndef _MSC_VER
#	define __vectorcall
#endif

namespace micro::math
{
	inline TVector2<double> __vectorcall operator+(TVector2<double> const &a,
						       TVector2<double> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector2<double> r;

		auto const A = _mm_loadu_pd(a.data);
		auto const B = _mm_loadu_pd(b.data);

		_mm_store_pd(r.data, _mm_add_pd(A, B));

		return r;
	}

	inline TVector2<double> __vectorcall operator-(TVector2<double> const &a,
						       TVector2<double> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector2<double> r;

		auto const A = _mm_loadu_pd(a.data);
		auto const B = _mm_loadu_pd(b.data);

		_mm_store_pd(r.data, _mm_sub_pd(A, B));

		return r;
	}

	inline TVector2<double> __vectorcall operator*(TVector2<double> const &a,
						       TVector2<double> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector2<double> r;

		auto const A = _mm_loadu_pd(a.data);
		auto const B = _mm_loadu_pd(b.data);

		_mm_store_pd(r.data, _mm_mul_pd(A, B));

		return r;
	}

	inline TVector2<double> __vectorcall operator/(TVector2<double> a,
						       TVector2<double> b) noexcept
	{
		alignas(alignof(__m128)) TVector2<double> r;

		auto const A = _mm_loadu_pd(a.data);
		auto const B = _mm_loadu_pd(b.data);

		_mm_store_pd(r.data, _mm_div_pd(A, B));

		return r;
	}
}

#endif