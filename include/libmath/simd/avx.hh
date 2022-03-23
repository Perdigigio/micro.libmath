#ifndef MICRO_LIBMATH_SIMD_SSE_HH__GUARD
#define MICRO_LIBMATH_SIMD_SSE_HH__GUARD

#include <immintrin.h>

#include <libmath/vector2.hh>
#include <libmath/vector3.hh>
#include <libmath/vector4.hh>

#ifndef _MSC_VER
#	define __vectorcall
#endif

namespace micro::math::simd
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

	inline TVector3<float> __vectorcall operator^(TVector3<float> const &a,
						      TVector3<float> const &b) noexcept
	{
		alignas(alignof(__m128)) float l[4] = {a.y(), a.z(), a.x(), a.x()};
		alignas(alignof(__m128)) float r[4] = {b.x(), b.y(), b.z(), b.z()};
		alignas(alignof(__m128)) float o[4];

		auto const A = _mm_load_ps(l);
		auto const B = _mm_load_ps(r);
		auto const D = _mm_shuffle_ps(B, B, _MM_SHUFFLE(1, 1, 0, 2));
		auto const E = _mm_mul_ps(A, B);
		auto const F = _mm_mul_ps(A, D);
		auto const G = _mm_shuffle_ps(E, E, _MM_SHUFFLE(0, 0, 2, 1));

		_mm_store_ps(o, _mm_sub_ps(F, G));

		return {o[0], o[1], o[2]};
	}

	// ----------------------------------------------------------------- //

	inline float __vectorcall dot(TVector3<float> const &a,
				      TVector3<float> const &b) noexcept
	{
		alignas(alignof(__m128)) float l[4] = {a.x(), a.y(), a.z(), a.z()};
		alignas(alignof(__m128)) float r[4] = {b.x(), b.y(), b.z(), b.z()};

		auto const A = _mm_load_ps(l);
		auto const B = _mm_load_ps(r);
		auto const C = _mm_mul_ps(A, B);
		auto const D = _mm_shuffle_ps(C, C, _MM_SHUFFLE(0, 0, 0, 1)); // D = C.y
		auto const E = _mm_shuffle_ps(C, C, _MM_SHUFFLE(0, 0, 0, 2)); // E = C.z
		auto const F = _mm_add_ss(C, D);			      // F = C + D
		auto const G = _mm_add_ss(F, E);			      // G = F + E = C + D + E

		return _mm_cvtss_f32(G);
	}

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

// ------------------------------------------------------------------------- //

#include <libmath/matrix2x2.hh>
#include <libmath/matrix3x3.hh>
#include <libmath/matrix4x4.hh>

namespace micro::math::simd
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
		const auto E = _mm256_mul_pd(A, a);		      // X * a
		const auto F = _mm256_mul_pd(B, b);		      // Y * b
		const auto G = _mm256_mul_pd(C, c);		      // Z * c
		const auto H = _mm256_mul_pd(D, d);		      // W * d
		const auto I = _mm256_add_pd(E, G);		      // X * a + Z * c
		const auto J = _mm256_add_pd(F, H);		      // Y * b + W * d
		const auto K = _mm256_add_pd(I, J);		      // X * a + Z * c + Y * b + W * d

		return K;
	}

	inline TMatrix4x4<double> operator*(TMatrix4x4<double> const &a,
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

	// ----------------------------------------------------------------- //

	inline void __vectorcall storeu(double dst[4][4], TMatrix4x4<double> const &src) noexcept
	{
		_mm256_storeu_pd(dst[0], _mm256_loadu_pd(src.data[0].data));
		_mm256_storeu_pd(dst[1], _mm256_loadu_pd(src.data[1].data));
		_mm256_storeu_pd(dst[2], _mm256_loadu_pd(src.data[2].data));
		_mm256_storeu_pd(dst[3], _mm256_loadu_pd(src.data[3].data));
	}

	inline void __vectorcall storea(double dst[4][4], TMatrix4x4<double> const &src) noexcept
	{
		_mm256_store_pd(dst[0], _mm256_loadu_pd(src.data[0].data));
		_mm256_store_pd(dst[1], _mm256_loadu_pd(src.data[1].data));
		_mm256_store_pd(dst[2], _mm256_loadu_pd(src.data[2].data));
		_mm256_store_pd(dst[3], _mm256_loadu_pd(src.data[3].data));
	}

	inline void __vectorcall stream(double dst[4][4], TMatrix4x4<double> const &src) noexcept
	{
		_mm256_stream_pd(dst[0], _mm256_loadu_pd(src.data[0].data));
		_mm256_stream_pd(dst[1], _mm256_loadu_pd(src.data[1].data));
		_mm256_stream_pd(dst[2], _mm256_loadu_pd(src.data[2].data));
		_mm256_stream_pd(dst[3], _mm256_loadu_pd(src.data[3].data));
	}
}

#endif