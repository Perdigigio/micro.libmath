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
	inline TVector4<float> __vectorcall operator+(TVector4<float> const &a,
						      TVector4<float> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<float> r;

		auto const A = _mm_loadu_ps(a.data);
		auto const B = _mm_loadu_ps(b.data);

		_mm_store_ps(r.data, _mm_add_ps(A, B));

		return r;
	}

	inline TVector4<float> __vectorcall operator-(TVector4<float> const &a,
						      TVector4<float> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<float> r;

		auto const A = _mm_loadu_ps(a.data);
		auto const B = _mm_loadu_ps(b.data);

		_mm_store_ps(r.data, _mm_sub_ps(A, B));

		return r;
	}

	inline TVector4<float> __vectorcall operator*(TVector4<float> const &a,
						      TVector4<float> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<float> r;

		auto const A = _mm_loadu_ps(a.data);
		auto const B = _mm_loadu_ps(b.data);

		_mm_store_ps(r.data, _mm_mul_ps(A, B));

		return r;
	}

	inline TVector4<float> __vectorcall operator/(TVector4<float> const &a,
						      TVector4<float> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<float> r;

		auto const A = _mm_loadu_ps(a.data);
		auto const B = _mm_loadu_ps(b.data);

		_mm_store_ps(r.data, _mm_div_ps(A, B));

		return r;
	}

	// ----------------------------------------------------------------- //

	inline TVector4<double> __vectorcall operator+(TVector4<double> const &a,
						       TVector4<double> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<double> r;

		auto const A = _mm_loadu_pd(a.data + 0);
		auto const B = _mm_loadu_pd(b.data + 0);
		auto const C = _mm_loadu_pd(a.data + 2);
		auto const D = _mm_loadu_pd(b.data + 2);

		_mm_store_pd(r.data + 0, _mm_add_pd(A, B));
		_mm_store_pd(r.data + 2, _mm_add_pd(C, D));

		return r;
	}

	inline TVector4<double> __vectorcall operator-(TVector4<double> const &a,
						       TVector4<double> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<double> r;

		auto const A = _mm_loadu_pd(a.data + 0);
		auto const B = _mm_loadu_pd(b.data + 0);
		auto const C = _mm_loadu_pd(a.data + 2);
		auto const D = _mm_loadu_pd(b.data + 2);

		_mm_store_pd(r.data + 0, _mm_sub_pd(A, B));
		_mm_store_pd(r.data + 2, _mm_sub_pd(C, D));

		return r;
	}

	inline TVector4<double> __vectorcall operator*(TVector4<double> const &a,
						       TVector4<double> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<double> r;

		auto const A = _mm_loadu_pd(a.data + 0);
		auto const B = _mm_loadu_pd(b.data + 0);
		auto const C = _mm_loadu_pd(a.data + 2);
		auto const D = _mm_loadu_pd(b.data + 2);

		_mm_storeu_pd(r.data + 0, _mm_mul_pd(A, B));
		_mm_storeu_pd(r.data + 2, _mm_mul_pd(C, D));

		return r;
	}

	inline TVector4<double> __vectorcall operator/(TVector4<double> const &a,
						       TVector4<double> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<double> r;

		auto const A = _mm_loadu_pd(a.data + 0);
		auto const B = _mm_loadu_pd(b.data + 0);
		auto const C = _mm_loadu_pd(a.data + 2);
		auto const D = _mm_loadu_pd(b.data + 2);

		_mm_store_pd(r.data + 0, _mm_div_pd(A, B));
		_mm_store_pd(r.data + 2, _mm_div_pd(C, D));

		return r;
	}

}

#endif