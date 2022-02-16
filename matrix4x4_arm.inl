#ifndef MICRO_LIBMATH_MATRIX4X4_ARM_INL__GUARD
#define MICRO_LIBMATH_MATRIX4X4_ARM_INL__GUARD

#include <arm_neon.h>

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
	 * 
	 * @return r.x * a + r.y * b + r.z * c + r.w * d
	 */
	inline float32x4_t __vectorcall _m4x4_mul_ps(float32x4_t const r,
						     float32x4_t const a,
						     float32x4_t const b,
						     float32x4_t const c,
						     float32x4_t const d) noexcept
	{
		const auto A = vmulq_laneq_f32(a, r, 0);
		const auto B = vmulq_laneq_f32(b, r, 1);
		const auto C = vmulq_laneq_f32(c, r, 2);
		const auto D = vmulq_laneq_f32(d, r, 3);
		const auto E = vaddq_f32(A, C);
		const auto F = vaddq_f32(B, D);
		const auto G = vaddq_f32(E, F);

		return G;
	}

	inline TMatrix4x4<float> operator *(TMatrix4x4<float> const &a,
					    TMatrix4x4<float> const &b) noexcept
	{
		TVector4<float> _0;
		TVector4<float> _1;
		TVector4<float> _2;
		TVector4<float> _3;

		auto const A0 = vld1q_f32(a.data[0].data);
		auto const A1 = vld1q_f32(a.data[1].data);
		auto const A2 = vld1q_f32(a.data[2].data);
		auto const A3 = vld1q_f32(a.data[3].data);
		auto const B0 = vld1q_f32(b.data[0].data);
		auto const B1 = vld1q_f32(b.data[1].data);
		auto const B2 = vld1q_f32(b.data[2].data);
		auto const B3 = vld1q_f32(b.data[3].data);

		vst1q_f32(_0.data, _m4x4_mul_ps(A0, B0, B1, B2, B3));
		vst1q_f32(_1.data, _m4x4_mul_ps(A1, B0, B1, B2, B3));
		vst1q_f32(_2.data, _m4x4_mul_ps(A2, B0, B1, B2, B3));
		vst1q_f32(_3.data, _m4x4_mul_ps(A3, B0, B1, B2, B3));

		return {_0, _1, _2, _3};
	}

	// ----------------------------------------------------------------- //

	inline TMatrix4x4<float> __vectorcall transpose(TMatrix4x4<float> const &m) noexcept
	{
		TVector4<float> _0;
		TVector4<float> _1;
		TVector4<float> _2;
		TVector4<float> _3;

		float32x4x4_t const l_matrix = {vld1q_f32(m.data[0].data),
						vld1q_f32(m.data[1].data),
						vld1q_f32(m.data[2].data),
						vld1q_f32(m.data[3].data)};

		vst4q_lane_f32(_0.data, l_matrix, 0);
		vst4q_lane_f32(_1.data, l_matrix, 1);
		vst4q_lane_f32(_2.data, l_matrix, 2);
		vst4q_lane_f32(_3.data, l_matrix, 3);

		return {_0, _1, _2, _3};
	}

	// ----------------------------------------------------------------- //

	inline void __vectorcall storea(float dst[4][4], TMatrix4x4<float> const &src) noexcept
	{
		float32x4x4_t const l_matrix = {vld1q_f32(src.data[0].data),
						vld1q_f32(src.data[1].data),
						vld1q_f32(src.data[2].data),
						vld1q_f32(src.data[3].data)};

		vst1q_f32_x4(dst[0], l_matrix);
	}

	// ---------------------------- Aliases ---------------------------- //

	constexpr auto storeu = storea;
	constexpr auto stream = storea;
}

#endif