#ifndef MICRO_LIBMATH_VECTOR4_SSE_INL__GUARD
#define MICRO_LIBMATH_VECTOR4_SSE_INL__GUARD

#include <immintrin.h>

#ifndef MICRO_LIBMATH_VECTOR4_HH__GUARD
#	include "vector4.hh"
#endif

#ifndef _MSC_VER
#	define __vectorcall
#endif

namespace micro::math
{
	inline TVector4<float> __vectorcall operator+(TVector4<float> a,
						      TVector4<float> b) noexcept
	{
		_mm_storeu_ps(a.data, _mm_add_ps(_mm_loadu_ps(a.data),
						 _mm_loadu_ps(b.data)));
		return a;
	}

	inline TVector4<float> __vectorcall operator-(TVector4<float> a,
						      TVector4<float> b) noexcept
	{
		_mm_storeu_ps(a.data, _mm_sub_ps(_mm_loadu_ps(a.data),
						 _mm_loadu_ps(b.data)));
		return a;
	}

	inline TVector4<float> __vectorcall operator*(TVector4<float> a,
						      TVector4<float> b) noexcept
	{
		_mm_storeu_ps(a.data, _mm_mul_ps(_mm_loadu_ps(a.data),
						 _mm_loadu_ps(b.data)));
		return a;
	}

	inline TVector4<float> __vectorcall operator/(TVector4<float> a,
						      TVector4<float> b) noexcept
	{
		_mm_storeu_ps(a.data, _mm_div_ps(_mm_loadu_ps(a.data),
						 _mm_loadu_ps(b.data)));
		return a;
	}

	inline TVector4<float> __vectorcall operator*(TVector4<float> a, float s) noexcept
	{
		return a * TVector4<float>{s, s, s, s};
	}

	inline TVector4<float> __vectorcall operator/(TVector4<float> a, float s) noexcept
	{
		return a / TVector4<float>{s, s, s, s};
	}

	inline TVector4<float> __vectorcall operator*(float s, TVector4<float> a) noexcept
	{
		return TVector4<float>{s, s, s, s} * a;
	}

	inline TVector4<float> __vectorcall operator/(float s, TVector4<float> a) noexcept
	{
		return TVector4<float>{s, s, s, s} / a;
	}

	// ----------------------------------------------------------------- //

	inline TVector4<double> __vectorcall operator+(TVector4<double> a,
						       TVector4<double> b) noexcept
	{
		auto const A = _mm_loadu_pd(a.data + 0);
		auto const B = _mm_loadu_pd(b.data + 0);
		auto const C = _mm_loadu_pd(a.data + 2);
		auto const D = _mm_loadu_pd(b.data + 2);

		_mm_storeu_pd(a.data + 0, _mm_add_pd(A, B));
		_mm_storeu_pd(a.data + 2, _mm_add_pd(C, D));

		return a;
	}

	inline TVector4<double> __vectorcall operator-(TVector4<double> a,
						       TVector4<double> b) noexcept
	{
		auto const A = _mm_loadu_pd(a.data + 0);
		auto const B = _mm_loadu_pd(b.data + 0);
		auto const C = _mm_loadu_pd(a.data + 2);
		auto const D = _mm_loadu_pd(b.data + 2);

		_mm_storeu_pd(a.data + 0, _mm_sub_pd(A, B));
		_mm_storeu_pd(a.data + 2, _mm_sub_pd(C, D));

		return a;
	}

	inline TVector4<double> __vectorcall operator*(TVector4<double> a,
						       TVector4<double> b) noexcept
	{
		auto const A = _mm_loadu_pd(a.data + 0);
		auto const B = _mm_loadu_pd(b.data + 0);
		auto const C = _mm_loadu_pd(a.data + 2);
		auto const D = _mm_loadu_pd(b.data + 2);

		_mm_storeu_pd(a.data + 0, _mm_mul_pd(A, B));
		_mm_storeu_pd(a.data + 2, _mm_mul_pd(C, D));

		return a;
	}

	inline TVector4<double> __vectorcall operator/(TVector4<double> a,
						       TVector4<double> b) noexcept
	{
		auto const A = _mm_loadu_pd(a.data + 0);
		auto const B = _mm_loadu_pd(b.data + 0);
		auto const C = _mm_loadu_pd(a.data + 2);
		auto const D = _mm_loadu_pd(b.data + 2);

		_mm_storeu_pd(a.data + 0, _mm_div_pd(A, B));
		_mm_storeu_pd(a.data + 2, _mm_div_pd(C, D));

		return a;
	}

	inline TVector4<double> __vectorcall operator*(TVector4<double> a, double s) noexcept
	{
		return a * TVector4<double>{s, s, s, s};
	}

	inline TVector4<double> __vectorcall operator/(TVector4<double> a, double s) noexcept
	{
		return a / TVector4<double>{s, s, s, s};
	}

	inline TVector4<double> __vectorcall operator*(double s, TVector4<double> a) noexcept
	{
		return TVector4<double>{s, s, s, s} * a;
	}

	inline TVector4<double> __vectorcall operator/(double s, TVector4<double> a) noexcept
	{
		return TVector4<double>{s, s, s, s} / a;
	}
}

#endif