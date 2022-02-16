#ifndef MICRO_LIBMATH_MATRIX3X3_ARM_INL__GUARD
#define MICRO_LIBMATH_MATRIX3X3_ARM_INL__GUARD

#include <arm_neon.h>

#ifndef MICRO_LIBMATH_MATRIX3X3_HH__GUARD
#	include "matrix3x3.hh"
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
	 * 
	 * @return r.x * a + r.y * b + r.z * c
	 */
	inline float32x4_t __vectorcall _m3x3_mul_ps(float32x4_t const r,
						     float32x4_t const a,
						     float32x4_t const b,
						     float32x4_t const c) noexcept
	{
		const auto A = vmulq_laneq_f32(a, r, 0);
		const auto B = vmulq_laneq_f32(b, r, 1);
		const auto C = vmulq_laneq_f32(c, r, 2);
		const auto E = vaddq_f32(A, C);
		const auto F = vaddq_f32(E, B);

		return F;
	}

	inline TMatrix3x3<float> operator *(TMatrix3x3<float> const &a,
					    TMatrix3x3<float> const &b) noexcept
	{
                auto const nil = vdup_n_f32(0);

		alignas(alignof(float32x4_t)) float _0[4];
		alignas(alignof(float32x4_t)) float _1[4];
		alignas(alignof(float32x4_t)) float _2[4];

		auto const A0 = vcombine_f32(vld1_f32(a.data[0].data), vld1_lane_f32(a.data[0].data + 2, nil, 0));
		auto const A1 = vcombine_f32(vld1_f32(a.data[1].data), vld1_lane_f32(a.data[1].data + 2, nil, 0));
		auto const A2 = vcombine_f32(vld1_f32(a.data[2].data), vld1_lane_f32(a.data[2].data + 2, nil, 0));
		auto const B0 = vcombine_f32(vld1_f32(b.data[0].data), vld1_lane_f32(b.data[0].data + 2, nil, 0));
		auto const B1 = vcombine_f32(vld1_f32(b.data[1].data), vld1_lane_f32(b.data[1].data + 2, nil, 0));
		auto const B2 = vcombine_f32(vld1_f32(b.data[2].data), vld1_lane_f32(b.data[2].data + 2, nil, 0));

		vst1q_f32(_0, _m3x3_mul_ps(A0, B0, B1, B2));
		vst1q_f32(_1, _m3x3_mul_ps(A1, B0, B1, B2));
		vst1q_f32(_2, _m3x3_mul_ps(A2, B0, B1, B2));

		return TMatrix3x3<float>{_0[0], _0[1], _0[2],
					 _1[0], _1[1], _1[2],
					 _2[0], _2[1], _2[2]};
	}
}

#endif