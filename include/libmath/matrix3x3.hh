#ifndef MICRO_LIBMATH_MATRIX3X3_HH__GUARD
#define MICRO_LIBMATH_MATRIX3X3_HH__GUARD

#include "vector3.hh"

namespace micro::math
{
	template<class T,
		 class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TMatrix3x3
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TMatrix3x3(T _11 = {}, T _12 = {}, T _13 = {},
				     T _21 = {}, T _22 = {}, T _23 = {},
				     T _31 = {}, T _32 = {}, T _33 = {}) noexcept
		{
			data[0] = {_11, _12, _13};
			data[1] = {_21, _22, _23};
			data[2] = {_31, _32, _33};
		}

		constexpr TMatrix3x3(TVector3<T> const &_1,
				     TVector3<T> const &_2,
				     TVector3<T> const &_3) noexcept
		{
			data[0] = _1;
			data[1] = _2;
			data[2] = _3;
		}

		constexpr type & _11() noexcept { return data[0].data[0]; }
		constexpr type & _12() noexcept { return data[0].data[1]; }
		constexpr type & _13() noexcept { return data[0].data[2]; }
		constexpr type & _21() noexcept { return data[1].data[0]; }
		constexpr type & _22() noexcept { return data[1].data[1]; }
		constexpr type & _23() noexcept { return data[1].data[2]; }
		constexpr type & _31() noexcept { return data[2].data[0]; }
		constexpr type & _32() noexcept { return data[2].data[1]; }
		constexpr type & _33() noexcept { return data[2].data[2]; }
		constexpr type const & _11() const noexcept { return data[0].data[0]; }
		constexpr type const & _12() const noexcept { return data[0].data[1]; }
		constexpr type const & _13() const noexcept { return data[0].data[2]; }
		constexpr type const & _21() const noexcept { return data[1].data[0]; }
		constexpr type const & _22() const noexcept { return data[1].data[1]; }
		constexpr type const & _23() const noexcept { return data[1].data[2]; }
		constexpr type const & _31() const noexcept { return data[2].data[0]; }
		constexpr type const & _32() const noexcept { return data[2].data[1]; }
		constexpr type const & _33() const noexcept { return data[2].data[2]; }

		TVector3<T> data[3] = {};
	};

	// -------------------------- M identity  -------------------------- //

	template<class T>
	constexpr TMatrix3x3<T> identity3x3() noexcept
	{
		return TMatrix3x3<T>{T(1), T(0), T(0),
				     T(0), T(1), T(0),
				     T(0), T(0), T(1)};
	}

	// ------------------------- MV arithmetic ------------------------- //

	template <class T>
	inline TVector3<T> operator*(TMatrix3x3<T> const &l, TVector3<T> const &r) noexcept
	{
		return TVector3<T>{sum(l.data[0] * r),
				   sum(l.data[1] * r),
				   sum(l.data[2] * r)};
	}
	// ------------------------- MM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix3x3<T> operator+(TMatrix3x3<T> const &l,
					  TMatrix3x3<T> const &r) noexcept
	{
		return TMatrix3x3<T>{l.data[0] + r.data[0],
				     l.data[1] + r.data[1],
				     l.data[2] + r.data[2]};
	}

	template <class T>
	constexpr TMatrix3x3<T> operator-(TMatrix3x3<T> const &l,
					  TMatrix3x3<T> const &r) noexcept
	{
		return TMatrix3x3<T>{l.data[0] - r.data[0],
				     l.data[1] - r.data[1],
				     l.data[2] - r.data[2]};
	}

	template <class T>
	constexpr TMatrix3x3<T> operator*(TMatrix3x3<T> const &l,
					  TMatrix3x3<T> const &r) noexcept
	{
		auto const a = l._11() * r.data[0];
		auto const b = l._12() * r.data[1];
		auto const c = l._13() * r.data[2];
		auto const d = l._21() * r.data[0];
		auto const e = l._22() * r.data[1];
		auto const f = l._23() * r.data[2];
		auto const g = l._31() * r.data[0];
		auto const h = l._32() * r.data[1];
		auto const i = l._33() * r.data[2];

		return TMatrix3x3<T>{a + b + c,
				     d + e + f,
				     g + h + i};
	}

	// ------------------------- SM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix3x3<T> operator*(T s, TMatrix3x3<T> const &m) noexcept
	{
		return TMatrix3x3<T>{s * m.data[0],
				     s * m.data[1],
				     s * m.data[2]};
	}

	template <class T>
	constexpr TMatrix3x3<T> operator/(T s, TMatrix3x3<T> const &m) noexcept
	{
		return TMatrix3x3<T>{s / m.data[0],
				     s / m.data[1],
				     s / m.data[2]};
	}

	// ------------------------- MS arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix3x3<T> operator*(TMatrix3x3<T> const &m, T s) noexcept
	{
		return TMatrix3x3<T>{m.data[0] * s,
				     m.data[1] * s,
				     m.data[2] * s};
	}

	template <class T>
	constexpr TMatrix3x3<T> operator/(TMatrix3x3<T> const &m, T s) noexcept
	{
		return TMatrix3x3<T>{m.data[0] / s,
				     m.data[1] / s,
				     m.data[2] / s};
	}
	
	// ----------------------------- Unary ----------------------------- //

	template <class T>
	constexpr TMatrix3x3<T> operator+(TMatrix3x3<T> const &a) noexcept
	{
		return a;
	}

	template <class T>
	constexpr TMatrix3x3<T> operator-(TMatrix3x3<T> const &a) noexcept
	{
		return TMatrix3x3<T>{} - a;
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TMatrix3x3<bool> operator<(TMatrix3x3<T> const &a,
					     TMatrix3x3<T> const &b) noexcept
	{
		return TMatrix3x3<bool>{a.data[0] < b.data[0],
					a.data[1] < b.data[1],
					a.data[2] < b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x3<bool> operator>(TMatrix3x3<T> const &a,
					     TMatrix3x3<T> const &b) noexcept
	{
		return TMatrix3x3<bool>{a.data[0] > b.data[0],
					a.data[1] > b.data[1],
					a.data[2] > b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x3<bool> operator>=(TMatrix3x3<T> const &a,
					      TMatrix3x3<T> const &b) noexcept
	{
		return TMatrix3x3<bool>{a.data[0] >= b.data[0],
					a.data[1] >= b.data[1],
					a.data[2] >= b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x3<bool> operator<=(TMatrix3x3<T> const &a,
					      TMatrix3x3<T> const &b) noexcept
	{
		return TMatrix3x3<bool>{a.data[0] <= b.data[0],
					a.data[1] <= b.data[1],
					a.data[2] <= b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x3<bool> operator==(TMatrix3x3<T> const &a,
					      TMatrix3x3<T> const &b) noexcept
	{
		return TMatrix3x3<bool>{a.data[0] == b.data[0],
					a.data[1] == b.data[1],
					a.data[2] == b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x3<bool> operator!=(TMatrix3x3<T> const &a,
					      TMatrix3x3<T> const &b) noexcept
	{
		return TMatrix3x3<bool>{a.data[0] != b.data[0],
					a.data[1] != b.data[1],
					a.data[2] != b.data[2]};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TMatrix3x3<bool> operator&&(TMatrix3x3<bool> const &a,
					      TMatrix3x3<bool> const &b) noexcept
	{
		return TMatrix3x3<bool>{a.data[0] && b.data[0],
					a.data[1] && b.data[1],
					a.data[2] && b.data[2]};
	}

	constexpr TMatrix3x3<bool> operator||(TMatrix3x3<bool> const &a,
					      TMatrix3x3<bool> const &b) noexcept
	{
		return TMatrix3x3<bool>{a.data[0] || b.data[0],
					a.data[1] || b.data[1],
					a.data[2] || b.data[2]};
	}

	constexpr bool all(TMatrix3x3<bool> const &a) noexcept
	{
		return all(a.data[0]) &&
		       all(a.data[1]) &&
		       all(a.data[2]);
	}

	constexpr bool any(TMatrix3x3<bool> const &a) noexcept
	{
		return any(a.data[0]) ||
		       any(a.data[1]) ||
		       any(a.data[2]);
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr T det(TMatrix3x3<T> const &m) noexcept
	{
		return dot(m.data[0], m.data[1] ^ m.data[2]);
	}

	template <class T>
	constexpr TMatrix3x3<T> transpose(TMatrix3x3<T> const &m) noexcept
	{
		return TMatrix3x3<T>{m._11(), m._21(), m._31(),
				     m._12(), m._22(), m._32(),
				     m._13(), m._23(), m._33()};
	}

	template <class T>
	constexpr TMatrix3x3<T> adjoint(TMatrix3x3<T> const &m) noexcept
	{
		auto const A = m._22() * m._33() - m._23() * m._32();
		auto const B = m._23() * m._31() - m._21() * m._33();
		auto const C = m._21() * m._32() - m._22() * m._31();
		auto const D = m._13() * m._32() - m._12() * m._33();
		auto const E = m._11() * m._33() - m._13() * m._31();
		auto const F = m._12() * m._31() - m._11() * m._32();
		auto const G = m._12() * m._23() - m._13() * m._22();
		auto const H = m._13() * m._21() - m._11() * m._23();
		auto const I = m._11() * m._22() - m._12() * m._21();

		return TMatrix3x3<T>{A, D, G,
				     B, E, H,
				     C, F, I};
	}

	template <class T>
	constexpr TMatrix3x3<T> inverse(TMatrix3x3<T> const &m) noexcept
	{
		return adjoint(m) / det(m);
	}

	// ----------------------------------------------------------------- //

	template <class U,
		  class T>
	constexpr TMatrix3x3<U> matrix_cast(TMatrix3x3<T> const &src) noexcept
	{
		return TMatrix3x3<U>{vector_cast<U>(src.data[0]),
				     vector_cast<U>(src.data[1]),
				     vector_cast<U>(src.data[2])};
	}
}

#endif