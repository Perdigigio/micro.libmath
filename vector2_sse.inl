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
	inline TVector2<double> __vectorcall operator+(TVector2<double> a,
						       TVector2<double> b) noexcept
	{
		_mm_storeu_pd(a.data, _mm_add_pd(_mm_loadu_pd(a.data),
						 _mm_loadu_pd(b.data)));
		return a;
	}

	inline TVector2<double> __vectorcall operator-(TVector2<double> a,
						       TVector2<double> b) noexcept
	{
		_mm_storeu_pd(a.data, _mm_sub_pd(_mm_loadu_pd(a.data),
						 _mm_loadu_pd(b.data)));
		return a;
	}

	inline TVector2<double> __vectorcall operator*(TVector2<double> a,
						       TVector2<double> b) noexcept
	{
		_mm_storeu_pd(a.data, _mm_mul_pd(_mm_loadu_pd(a.data),
						 _mm_loadu_pd(b.data)));
		return a;
	}

	inline TVector2<double> __vectorcall operator/(TVector2<double> a,
						       TVector2<double> b) noexcept
	{
		_mm_storeu_pd(a.data, _mm_div_pd(_mm_loadu_pd(a.data),
						 _mm_loadu_pd(b.data)));
		return a;
	}

	inline TVector2<double> __vectorcall operator*(TVector2<double> a, double s) noexcept
	{
		return a * TVector2<double>{s, s};
	}

	inline TVector2<double> __vectorcall operator/(TVector2<double> a, double s) noexcept
	{
		return a / TVector2<double>{s, s};
	}

	inline TVector2<double> __vectorcall operator*(double s, TVector2<double> a) noexcept
	{
		return TVector2<double>{s, s} * a;
	}

	inline TVector2<double> __vectorcall operator/(double s, TVector2<double> a) noexcept
	{
		return TVector2<double>{s, s} / a;
	}
}

#endif