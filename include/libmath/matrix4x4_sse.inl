#ifndef MICRO_LIBMATH_MATRIX4X4_SSE_INL__GUARD
#define MICRO_LIBMATH_MATRIX4X4_SSE_INL__GUARD

#include <immintrin.h>

#ifndef MICRO_LIBMATH_MATRIX4X4_HH__GUARD
#	include "matrix4x4.hh"
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
	 * @param d B matrix 4th-row
	 */
	inline __m128 __vectorcall _m4x4_mul_ps(__m128 const r,
						__m128 const a,
						__m128 const b,
						__m128 const c,
						__m128 const d) noexcept
	{
		const auto A = _mm_shuffle_ps(r, r, _MM_SHUFFLE(0, 0, 0, 0)); // X
		const auto B = _mm_shuffle_ps(r, r, _MM_SHUFFLE(1, 1, 1, 1)); // Y
		const auto C = _mm_shuffle_ps(r, r, _MM_SHUFFLE(2, 2, 2, 2)); // Z
		const auto D = _mm_shuffle_ps(r, r, _MM_SHUFFLE(3, 3, 3, 3)); // W
		const auto E = _mm_mul_ps(A, a); // X * a
		const auto F = _mm_mul_ps(B, b); // Y * b
		const auto G = _mm_mul_ps(C, c); // Z * c
		const auto H = _mm_mul_ps(D, d); // W * d
		const auto I = _mm_add_ps(E, G); // X * a + Z * c
		const auto J = _mm_add_ps(F, H); // Y * b + W * d
		const auto K = _mm_add_ps(I, J); // X * a + Z * c + Y * b + W * d

		return K;
	}

	inline TMatrix4x4<float> operator *(TMatrix4x4<float> const &a,
					    TMatrix4x4<float> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<float> _0;
		alignas(alignof(__m128)) TVector4<float> _1;
		alignas(alignof(__m128)) TVector4<float> _2;
		alignas(alignof(__m128)) TVector4<float> _3;

		auto const A0 = _mm_loadu_ps(a.data[0].data);
		auto const A1 = _mm_loadu_ps(a.data[1].data);
		auto const A2 = _mm_loadu_ps(a.data[2].data);
		auto const A3 = _mm_loadu_ps(a.data[3].data);
		auto const B0 = _mm_loadu_ps(b.data[0].data);
		auto const B1 = _mm_loadu_ps(b.data[1].data);
		auto const B2 = _mm_loadu_ps(b.data[2].data);
		auto const B3 = _mm_loadu_ps(b.data[3].data);

		_mm_store_ps(_0.data, _m4x4_mul_ps(A0, B0, B1, B2, B3));
		_mm_store_ps(_1.data, _m4x4_mul_ps(A1, B0, B1, B2, B3));
		_mm_store_ps(_2.data, _m4x4_mul_ps(A2, B0, B1, B2, B3));
		_mm_store_ps(_3.data, _m4x4_mul_ps(A3, B0, B1, B2, B3));

		return {_0, _1, _2, _3};
	}

#ifdef __AVX__
	/**
	 * @brief Multiply a row from A matrix with all rows of B matrix
	 * 
	 * @param r A matrix row
	 * @param a B matrix 1st-row
	 * @param b B matrix 2nd-row
	 * @param c B matrix 3rd-row
	 * @param d B matrix 4th-row
	 */
	inline __m256d __vectorcall _m4x4_mul_pd(__m256d const r,
						 __m256d const a,
						 __m256d const b,
						 __m256d const c,
						 __m256d const d) noexcept
	{
		const auto A = _mm256_permute2f128_pd(r, r, 0b00'00); // X
		const auto B = _mm256_permute2f128_pd(r, r, 0b01'01); // Y
		const auto C = _mm256_permute2f128_pd(r, r, 0b10'10); // Z
		const auto D = _mm256_permute2f128_pd(r, r, 0b11'11); // W
		const auto E = _mm256_mul_pd(A, a); // X * a
		const auto F = _mm256_mul_pd(B, b); // Y * b
		const auto G = _mm256_mul_pd(C, c); // Z * c
		const auto H = _mm256_mul_pd(D, d); // W * d
		const auto I = _mm256_add_pd(E, G); // X * a + Z * c
		const auto J = _mm256_add_pd(F, H); // Y * b + W * d
		const auto K = _mm256_add_pd(I, J); // X * a + Z * c + Y * b + W * d

		return K;
	}

	inline TMatrix4x4<double> operator *(TMatrix4x4<double> const &a,
					     TMatrix4x4<double> const &b) noexcept
	{
		alignas(alignof(__m128)) TVector4<double> _0;
		alignas(alignof(__m128)) TVector4<double> _1;
		alignas(alignof(__m128)) TVector4<double> _2;
		alignas(alignof(__m128)) TVector4<double> _3;

		auto const A0 = _mm256_loadu_pd(a.data[0].data);
		auto const A1 = _mm256_loadu_pd(a.data[1].data);
		auto const A2 = _mm256_loadu_pd(a.data[2].data);
		auto const A3 = _mm256_loadu_pd(a.data[3].data);
		auto const B0 = _mm256_loadu_pd(b.data[0].data);
		auto const B1 = _mm256_loadu_pd(b.data[1].data);
		auto const B2 = _mm256_loadu_pd(b.data[2].data);
		auto const B3 = _mm256_loadu_pd(b.data[3].data);

		_mm256_store_pd(_0.data, _m4x4_mul_pd(A0, B0, B1, B2, B3));
		_mm256_store_pd(_1.data, _m4x4_mul_pd(A1, B0, B1, B2, B3));
		_mm256_store_pd(_2.data, _m4x4_mul_pd(A2, B0, B1, B2, B3));
		_mm256_store_pd(_3.data, _m4x4_mul_pd(A3, B0, B1, B2, B3));

		return {_0, _1, _2, _3};
	}
#endif

	// ----------------------------------------------------------------- //

	inline TMatrix4x4<float> __vectorcall transpose(TMatrix4x4<float> const &m) noexcept
	{
		alignas(alignof(__m128)) TVector4<float> _0;
		alignas(alignof(__m128)) TVector4<float> _1;
		alignas(alignof(__m128)) TVector4<float> _2;
		alignas(alignof(__m128)) TVector4<float> _3;

		auto const A = _mm_loadu_ps(m.data[0].data); // A11 A12 A13 A14
		auto const B = _mm_loadu_ps(m.data[1].data); // A21 A22 A23 A24
		auto const C = _mm_loadu_ps(m.data[2].data); // A31 A32 A33 A34
		auto const D = _mm_loadu_ps(m.data[3].data); // A41 A42 A43 A44
		auto const E = _mm_unpacklo_ps(A, B); // A11 A21 A12 A22
		auto const F = _mm_unpackhi_ps(A, B); // A13 A23 A14 A24
		auto const G = _mm_unpacklo_ps(C, D); // A31 A41 A32 A42
		auto const H = _mm_unpackhi_ps(C, D); // A33 A43 A34 A44

		_mm_store_ps(_0.data, _mm_movelh_ps(E, G)); // A11 A21 A31 A41 
		_mm_store_ps(_1.data, _mm_movehl_ps(G, E)); // A12 A22 A32 A42
		_mm_store_ps(_2.data, _mm_movelh_ps(F, H)); // A13 A23 A33 A43
		_mm_store_ps(_3.data, _mm_movehl_ps(H, F)); // A14 A24 A34 A44

		return {_0, _1, _2, _3};
	}

	// ----------------------------------------------------------------- //

	inline void __vectorcall storeu(float dst[4][4], TMatrix4x4<float> const &src) noexcept
	{
		_mm_storeu_ps(dst[0], _mm_loadu_ps(src.data[0].data));
		_mm_storeu_ps(dst[1], _mm_loadu_ps(src.data[1].data));
		_mm_storeu_ps(dst[2], _mm_loadu_ps(src.data[2].data));
		_mm_storeu_ps(dst[3], _mm_loadu_ps(src.data[3].data));
	}

	inline void __vectorcall storea(float dst[4][4], TMatrix4x4<float> const &src) noexcept
	{
		_mm_store_ps(dst[0], _mm_loadu_ps(src.data[0].data));
		_mm_store_ps(dst[1], _mm_loadu_ps(src.data[1].data));
		_mm_store_ps(dst[2], _mm_loadu_ps(src.data[2].data));
		_mm_store_ps(dst[3], _mm_loadu_ps(src.data[3].data));
	}

	inline void __vectorcall stream(float dst[4][4], TMatrix4x4<float> const &src) noexcept
	{
		_mm_stream_ps(dst[0], _mm_loadu_ps(src.data[0].data));
		_mm_stream_ps(dst[1], _mm_loadu_ps(src.data[1].data));
		_mm_stream_ps(dst[2], _mm_loadu_ps(src.data[2].data));
		_mm_stream_ps(dst[3], _mm_loadu_ps(src.data[3].data));
	}

}

#endif