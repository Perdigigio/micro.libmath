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
	inline TMatrix2x2<double> operator*(TMatrix2x2<double> const &a,
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

	// ----------------------------------------------------------------- //

	inline void __vectorcall storeu(double dst[2][2], TMatrix2x2<double> const &src) noexcept
	{
		_mm_storeu_pd(dst[0], _mm_loadu_pd(src.data[0].data));
		_mm_storeu_pd(dst[1], _mm_loadu_pd(src.data[1].data));
	}

	inline void __vectorcall storea(double dst[2][2], TMatrix2x2<double> const &src) noexcept
	{
		_mm_store_pd(dst[0], _mm_loadu_pd(src.data[0].data));
		_mm_store_pd(dst[1], _mm_loadu_pd(src.data[1].data));
	}

	inline void __vectorcall stream(double dst[2][2], TMatrix2x2<double> const &src) noexcept
	{
		_mm_stream_pd(dst[0], _mm_loadu_pd(src.data[0].data));
		_mm_stream_pd(dst[1], _mm_loadu_pd(src.data[1].data));
	}

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

	inline TMatrix3x3<float> operator*(TMatrix3x3<float> const &a,
					   TMatrix3x3<float> const &b) noexcept
	{
		alignas(alignof(__m128)) float _0[4];
		alignas(alignof(__m128)) float _1[4];
		alignas(alignof(__m128)) float _2[4];

		auto const a0 = _mm_load_sd(reinterpret_cast<double const *>(a.data[0].data)); // xy
		auto const a1 = _mm_load_sd(reinterpret_cast<double const *>(a.data[1].data)); // xy
		auto const a2 = _mm_load_sd(reinterpret_cast<double const *>(a.data[2].data)); // xy
		auto const c0 = _mm_load_ss(a.data[0].data + 2);			       // z
		auto const c1 = _mm_load_ss(a.data[1].data + 2);			       // z
		auto const c2 = _mm_load_ss(a.data[2].data + 2);			       // z

		auto const b0 = _mm_load_sd(reinterpret_cast<double const *>(b.data[0].data)); // xy
		auto const b1 = _mm_load_sd(reinterpret_cast<double const *>(b.data[1].data)); // xy
		auto const b2 = _mm_load_sd(reinterpret_cast<double const *>(b.data[2].data)); // xy
		auto const d0 = _mm_load_ss(b.data[0].data + 2);			       // z
		auto const d1 = _mm_load_ss(b.data[1].data + 2);			       // z
		auto const d2 = _mm_load_ss(b.data[2].data + 2);			       // z

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
		const auto E = _mm_mul_ps(A, a);			      // X * a
		const auto F = _mm_mul_ps(B, b);			      // Y * b
		const auto G = _mm_mul_ps(C, c);			      // Z * c
		const auto H = _mm_mul_ps(D, d);			      // W * d
		const auto I = _mm_add_ps(E, G);			      // X * a + Z * c
		const auto J = _mm_add_ps(F, H);			      // Y * b + W * d
		const auto K = _mm_add_ps(I, J);			      // X * a + Z * c + Y * b + W * d

		return K;
	}

	inline TMatrix4x4<float> operator*(TMatrix4x4<float> const &a,
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
		auto const E = _mm_unpacklo_ps(A, B);	     // A11 A21 A12 A22
		auto const F = _mm_unpackhi_ps(A, B);	     // A13 A23 A14 A24
		auto const G = _mm_unpacklo_ps(C, D);	     // A31 A41 A32 A42
		auto const H = _mm_unpackhi_ps(C, D);	     // A33 A43 A34 A44

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