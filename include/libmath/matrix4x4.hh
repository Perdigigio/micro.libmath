#ifndef MICRO_LIBMATH_MATRIX4X4_HH__GUARD
#define MICRO_LIBMATH_MATRIX4X4_HH__GUARD

#include "vector3.hh"
#include "vector4.hh"

namespace micro::math
{
	template <class T,
		  class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TMatrix4x4
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TMatrix4x4(T _11 = {}, T _12 = {}, T _13 = {}, T _14 = {},
				     T _21 = {}, T _22 = {}, T _23 = {}, T _24 = {},
				     T _31 = {}, T _32 = {}, T _33 = {}, T _34 = {},
				     T _41 = {}, T _42 = {}, T _43 = {}, T _44 = {}) noexcept
		{
			data[0] = {_11, _12, _13, _14};
			data[1] = {_21, _22, _23, _24};
			data[2] = {_31, _32, _33, _34};
			data[3] = {_41, _42, _43, _44};
		}

		constexpr TMatrix4x4(TVector4<T> const &_1,
				     TVector4<T> const &_2,
				     TVector4<T> const &_3,
				     TVector4<T> const &_4) noexcept
		{
			data[0] = _1;
			data[1] = _2;
			data[2] = _3;
			data[3] = _4;
		}

		constexpr type &_11() noexcept { return data[0].data[0]; }
		constexpr type &_12() noexcept { return data[0].data[1]; }
		constexpr type &_13() noexcept { return data[0].data[2]; }
		constexpr type &_14() noexcept { return data[0].data[3]; }
		constexpr type &_21() noexcept { return data[1].data[0]; }
		constexpr type &_22() noexcept { return data[1].data[1]; }
		constexpr type &_23() noexcept { return data[1].data[2]; }
		constexpr type &_24() noexcept { return data[1].data[3]; }
		constexpr type &_31() noexcept { return data[2].data[0]; }
		constexpr type &_32() noexcept { return data[2].data[1]; }
		constexpr type &_33() noexcept { return data[2].data[2]; }
		constexpr type &_34() noexcept { return data[2].data[3]; }
		constexpr type &_41() noexcept { return data[3].data[0]; }
		constexpr type &_42() noexcept { return data[3].data[1]; }
		constexpr type &_43() noexcept { return data[3].data[2]; }
		constexpr type &_44() noexcept { return data[3].data[3]; }
		constexpr type const &_11() const noexcept { return data[0].data[0]; }
		constexpr type const &_12() const noexcept { return data[0].data[1]; }
		constexpr type const &_13() const noexcept { return data[0].data[2]; }
		constexpr type const &_14() const noexcept { return data[0].data[3]; }
		constexpr type const &_21() const noexcept { return data[1].data[0]; }
		constexpr type const &_22() const noexcept { return data[1].data[1]; }
		constexpr type const &_23() const noexcept { return data[1].data[2]; }
		constexpr type const &_24() const noexcept { return data[1].data[3]; }
		constexpr type const &_31() const noexcept { return data[2].data[0]; }
		constexpr type const &_32() const noexcept { return data[2].data[1]; }
		constexpr type const &_33() const noexcept { return data[2].data[2]; }
		constexpr type const &_34() const noexcept { return data[2].data[3]; }
		constexpr type const &_41() const noexcept { return data[3].data[0]; }
		constexpr type const &_42() const noexcept { return data[3].data[1]; }
		constexpr type const &_43() const noexcept { return data[3].data[2]; }
		constexpr type const &_44() const noexcept { return data[3].data[3]; }

		TVector4<T> data[4] = {};
	};

	// -------------------------- M identity  -------------------------- //

	template <class T>
	constexpr TMatrix4x4<T> identity4x4() noexcept
	{
		return TMatrix4x4<T>{T(1), T(0), T(0), T(0),
				     T(0), T(1), T(0), T(0),
				     T(0), T(0), T(1), T(0),
				     T(0), T(0), T(0), T(1)};
	}

	// ------------------------- MV arithmetic ------------------------- //

	template <class T>
	inline TVector4<T> operator*(TMatrix4x4<T> const &l, TVector4<T> const &r) noexcept
	{
		return TVector4<T>{sum(l.data[0] * r),
				   sum(l.data[1] * r),
				   sum(l.data[2] * r),
				   sum(l.data[3] * r)};
	}

	// ------------------------- MM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix4x4<T> operator+(TMatrix4x4<T> const &l,
					  TMatrix4x4<T> const &r) noexcept
	{
		return TMatrix4x4<T>{l.data[0] + r.data[0],
				     l.data[1] + r.data[1],
				     l.data[2] + r.data[2],
				     l.data[3] + r.data[3]};
	}

	template <class T>
	constexpr TMatrix4x4<T> operator-(TMatrix4x4<T> const &l,
					  TMatrix4x4<T> const &r) noexcept
	{
		return TMatrix4x4<T>{l.data[0] - r.data[0],
				     l.data[1] - r.data[1],
				     l.data[2] - r.data[2],
				     l.data[3] - r.data[3]};
	}

	template <class T>
	constexpr TMatrix4x4<T> operator*(TMatrix4x4<T> const &l,
					  TMatrix4x4<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._14() * r.data[3];
		auto const E = l._21() * r.data[0];
		auto const F = l._22() * r.data[1];
		auto const G = l._23() * r.data[2];
		auto const H = l._24() * r.data[3];
		auto const I = l._31() * r.data[0];
		auto const J = l._32() * r.data[1];
		auto const K = l._33() * r.data[2];
		auto const L = l._34() * r.data[3];
		auto const M = l._41() * r.data[0];
		auto const N = l._42() * r.data[1];
		auto const O = l._43() * r.data[2];
		auto const P = l._44() * r.data[3];

		return TMatrix4x4<T>{A + B + C + D,
				     E + F + G + H,
				     I + J + K + L,
				     M + N + O + P};
	}

	// ------------------------- SM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix4x4<T> operator*(T s, TMatrix4x4<T> const &m) noexcept
	{
		return TMatrix4x4<T>{s * m.data[0],
				     s * m.data[1],
				     s * m.data[2],
				     s * m.data[3]};
	}

	template <class T>
	constexpr TMatrix4x4<T> operator/(T s, TMatrix4x4<T> const &m) noexcept
	{
		return TMatrix4x4<T>{s / m.data[0],
				     s / m.data[1],
				     s / m.data[2],
				     s / m.data[3]};
	}

	// ------------------------- MS arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix4x4<T> operator*(TMatrix4x4<T> const &m, T s) noexcept
	{
		return TMatrix4x4<T>{m.data[0] * s,
				     m.data[1] * s,
				     m.data[2] * s,
				     m.data[3] * s};
	}

	template <class T>
	constexpr TMatrix4x4<T> operator/(TMatrix4x4<T> const &m, T s) noexcept
	{
		return TMatrix4x4<T>{m.data[0] / s,
				     m.data[1] / s,
				     m.data[2] / s,
				     m.data[3] / s};
	}

	// ----------------------------- Unary ----------------------------- //

	template <class T>
	constexpr TMatrix4x4<T> operator+(TMatrix4x4<T> const &a) noexcept
	{
		return a;
	}

	template <class T>
	constexpr TMatrix4x4<T> operator-(TMatrix4x4<T> const &a) noexcept
	{
		return TMatrix4x4<T>{} - a;
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TMatrix4x4<bool> operator<(TMatrix4x4<T> const &a,
					     TMatrix4x4<T> const &b) noexcept
	{
		return TMatrix4x4<bool>{a.data[0] < b.data[0],
					a.data[1] < b.data[1],
					a.data[2] < b.data[2],
					a.data[3] < b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x4<bool> operator>(TMatrix4x4<T> const &a,
					     TMatrix4x4<T> const &b) noexcept
	{
		return TMatrix4x4<bool>{a.data[0] > b.data[0],
					a.data[1] > b.data[1],
					a.data[2] > b.data[2],
					a.data[3] > b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x4<bool> operator>=(TMatrix4x4<T> const &a,
					      TMatrix4x4<T> const &b) noexcept
	{
		return TMatrix4x4<bool>{a.data[0] >= b.data[0],
					a.data[1] >= b.data[1],
					a.data[2] >= b.data[2],
					a.data[3] >= b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x4<bool> operator<=(TMatrix4x4<T> const &a,
					      TMatrix4x4<T> const &b) noexcept
	{
		return TMatrix4x4<bool>{a.data[0] <= b.data[0],
					a.data[1] <= b.data[1],
					a.data[2] <= b.data[2],
					a.data[3] <= b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x4<bool> operator==(TMatrix4x4<T> const &a,
					      TMatrix4x4<T> const &b) noexcept
	{
		return TMatrix4x4<bool>{a.data[0] == b.data[0],
					a.data[1] == b.data[1],
					a.data[2] == b.data[2],
					a.data[3] == b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x4<bool> operator!=(TMatrix4x4<T> const &a,
					      TMatrix4x4<T> const &b) noexcept
	{
		return TMatrix4x4<bool>{a.data[0] != b.data[0],
					a.data[1] != b.data[1],
					a.data[2] != b.data[2],
					a.data[3] != b.data[3]};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TMatrix4x4<bool> operator&&(TMatrix4x4<bool> const &a,
					      TMatrix4x4<bool> const &b) noexcept
	{
		return TMatrix4x4<bool>{a.data[0] && b.data[0],
					a.data[1] && b.data[1],
					a.data[2] && b.data[2],
					a.data[3] && b.data[3]};
	}

	constexpr TMatrix4x4<bool> operator||(TMatrix4x4<bool> const &a,
					      TMatrix4x4<bool> const &b) noexcept
	{
		return TMatrix4x4<bool>{a.data[0] || b.data[0],
					a.data[1] || b.data[1],
					a.data[2] || b.data[2],
					a.data[3] || b.data[3]};
	}

	constexpr bool all(TMatrix4x4<bool> const &a) noexcept
	{
		return all(a.data[0]) &&
		       all(a.data[1]) &&
		       all(a.data[2]) &&
		       all(a.data[3]);
	}

	constexpr bool any(TMatrix4x4<bool> const &a) noexcept
	{
		return any(a.data[0]) ||
		       any(a.data[1]) ||
		       any(a.data[2]) ||
		       any(a.data[3]);
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr T det(TMatrix4x4<T> const &m) noexcept
	{
		auto const A = TVector3<T>(m._22(), m._23(), m._24());
		auto const B = TVector3<T>(m._32(), m._33(), m._34());
		auto const C = TVector3<T>(m._42(), m._43(), m._44());
		auto const D = TVector3<T>(m._21(), m._23(), m._24());
		auto const E = TVector3<T>(m._31(), m._33(), m._34());
		auto const F = TVector3<T>(m._41(), m._43(), m._44());
		auto const G = TVector3<T>(m._21(), m._22(), m._24());
		auto const H = TVector3<T>(m._31(), m._32(), m._34());
		auto const I = TVector3<T>(m._41(), m._42(), m._44());
		auto const J = TVector3<T>(m._21(), m._22(), m._23());
		auto const K = TVector3<T>(m._31(), m._32(), m._33());
		auto const L = TVector3<T>(m._41(), m._42(), m._43());

		//
		//

		return m._11() * dot(A, B ^ C) -
		       m._12() * dot(D, E ^ F) +
		       m._13() * dot(G, H ^ I) -
		       m._14() * dot(J, K ^ L);
	}

	template <class T>
	constexpr TMatrix4x4<T> transpose(TMatrix4x4<T> const &m) noexcept
	{
		return TMatrix4x4<T>{m._11(), m._21(), m._31(), m._41(),
				     m._12(), m._22(), m._32(), m._42(),
				     m._13(), m._23(), m._33(), m._43(),
				     m._14(), m._24(), m._34(), m._44()};
	}

	template <class T>
	constexpr TMatrix4x4<T> adjoint(TMatrix4x4<T> const &m) noexcept
	{
		auto const A = TVector3<T>(m._22(), m._23(), m._24());
		auto const B = TVector3<T>(m._32(), m._33(), m._34());
		auto const C = TVector3<T>(m._42(), m._43(), m._44());
		auto const D = TVector3<T>(m._21(), m._23(), m._24());
		auto const E = TVector3<T>(m._31(), m._33(), m._34());
		auto const F = TVector3<T>(m._41(), m._43(), m._44());
		auto const G = TVector3<T>(m._21(), m._22(), m._24());
		auto const H = TVector3<T>(m._31(), m._32(), m._34());
		auto const I = TVector3<T>(m._41(), m._42(), m._44());
		auto const J = TVector3<T>(m._21(), m._22(), m._23());
		auto const K = TVector3<T>(m._31(), m._32(), m._33());
		auto const L = TVector3<T>(m._41(), m._42(), m._43());
		auto const M = TVector3<T>(m._12(), m._13(), m._14());
		auto const N = TVector3<T>(m._11(), m._13(), m._14());
		auto const O = TVector3<T>(m._11(), m._12(), m._14());
		auto const P = TVector3<T>(m._11(), m._12(), m._13());

		//
		//

		return TMatrix4x4<T>{+dot(A, B ^ C), -dot(M, B ^ C), +dot(M, A ^ C), -dot(M, A ^ B),
				     -dot(D, E ^ F), +dot(N, E ^ F), -dot(N, D ^ F), +dot(N, D ^ E),
				     +dot(G, H ^ I), -dot(O, H ^ I), +dot(O, G ^ I), -dot(O, G ^ H),
				     -dot(J, K ^ L), +dot(P, K ^ L), -dot(P, J ^ L), +dot(P, J ^ K)};
	}

	template <class T>
	constexpr TMatrix4x4<T> inverse(TMatrix4x4<T> const &m) noexcept
	{
		return adjoint(m) / det(m);
	}

	// ----------------------------------------------------------------- //

	template <class U,
		  class T>
	constexpr TMatrix4x4<U> matrix_cast(TMatrix4x4<T> const &src) noexcept
	{
		return TMatrix4x4<U>{vector_cast<U>(src.data[0]),
				     vector_cast<U>(src.data[1]),
				     vector_cast<U>(src.data[2]),
				     vector_cast<U>(src.data[3])};
	}
}

#if (defined(WITH_SSE_INTRINSICS) && defined(WITH_ARM_INTRINSICS)) || \
    (defined(WITH_AVX_INTRINSICS) && defined(WITH_ARM_INTRINSICS))
#	error "Cannot define both WITH_SSE_INTRINSICS or WITH_AVX_INTRINSICS and WITH_ARM_INTRINSICS"
#elif defined(WITH_SSE_INTRINSICS) || defined(WITH_AVX_INTRINSICS)
#	include "matrix4x4_sse.inl"
#elif defined(WITH_ARM_INTRINSICS)
#	include "matrix4x4_arm.inl"
#endif
#endif