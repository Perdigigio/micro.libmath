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
		auto const F = _mm_add_ss(C, D); // F = C + D
		auto const G = _mm_add_ss(F, E); // G = F + E = C + D + E

		return _mm_cvtss_f32(G);
	}
}

#endif