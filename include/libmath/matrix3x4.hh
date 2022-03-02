#ifndef MICRO_LIBMATH_MATRIX3X4_HH__GUARD
#define MICRO_LIBMATH_MATRIX3X4_HH__GUARD

#include "vector3.hh"
#include "vector4.hh"

namespace micro::math
{
	template<class T,
		 class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TMatrix3x4
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TMatrix3x4(T _11 = {}, T _12 = {}, T _13 = {}, T _14 = {},
				     T _21 = {}, T _22 = {}, T _23 = {}, T _24 = {},
				     T _31 = {}, T _32 = {}, T _33 = {}, T _34 = {}) noexcept
		{
			data[0] = {_11, _12, _13, _14};
			data[1] = {_21, _22, _23, _24};
			data[2] = {_31, _32, _33, _34};
		}

		constexpr TMatrix3x4(TVector4<T> const &_1,
				     TVector4<T> const &_2,
				     TVector4<T> const &_3) noexcept
		{
			data[0] = _1;
			data[1] = _2;
			data[2] = _3;
		}

		constexpr type & _11() noexcept { return data[0].data[0]; }
		constexpr type & _12() noexcept { return data[0].data[1]; }
		constexpr type & _13() noexcept { return data[0].data[2]; }
		constexpr type & _14() noexcept { return data[0].data[3]; }
		constexpr type & _21() noexcept { return data[1].data[0]; }
		constexpr type & _22() noexcept { return data[1].data[1]; }
		constexpr type & _23() noexcept { return data[1].data[2]; }
		constexpr type & _24() noexcept { return data[1].data[3]; }
		constexpr type & _31() noexcept { return data[2].data[0]; }
		constexpr type & _32() noexcept { return data[2].data[1]; }
		constexpr type & _33() noexcept { return data[2].data[2]; }
		constexpr type & _34() noexcept { return data[2].data[3]; }
		constexpr type const & _11() const noexcept { return data[0].data[0]; }
		constexpr type const & _12() const noexcept { return data[0].data[1]; }
		constexpr type const & _13() const noexcept { return data[0].data[2]; }
		constexpr type const & _14() const noexcept { return data[0].data[3]; }
		constexpr type const & _21() const noexcept { return data[1].data[0]; }
		constexpr type const & _22() const noexcept { return data[1].data[1]; }
		constexpr type const & _23() const noexcept { return data[1].data[2]; }
		constexpr type const & _24() const noexcept { return data[1].data[3]; }
		constexpr type const & _31() const noexcept { return data[2].data[0]; }
		constexpr type const & _32() const noexcept { return data[2].data[1]; }
		constexpr type const & _33() const noexcept { return data[2].data[2]; }
		constexpr type const & _34() const noexcept { return data[2].data[3]; }

		TVector4<T> data[3] = {};
	};

	// ------------------------- MV arithmetic ------------------------- //

	template <class T>
	inline TVector3<T> operator*(TMatrix3x4<T> const &l, TVector4<T> const &r) noexcept
	{
		return TVector3<T>{sum(l.data[0] * r),
				   sum(l.data[1] * r),
				   sum(l.data[2] * r)};
	}
	// ------------------------- MM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix3x4<T> operator+(TMatrix3x4<T> const &l,
					  TMatrix3x4<T> const &r) noexcept
	{
		return TMatrix3x4<T>{l.data[0] + r.data[0],
				     l.data[1] + r.data[1],
				     l.data[2] + r.data[2]};
	}

	template <class T>
	constexpr TMatrix3x4<T> operator-(TMatrix3x4<T> const &l,
					  TMatrix3x4<T> const &r) noexcept
	{
		return TMatrix3x4<T>{l.data[0] - r.data[0],
				     l.data[1] - r.data[1],
				     l.data[2] - r.data[2]};
	}

	// ------------------------- SM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix3x4<T> operator*(T s, TMatrix3x4<T> const &m) noexcept
	{
		return TMatrix3x4<T>{s * m.data[0],
				     s * m.data[1],
				     s * m.data[2]};
	}

	template <class T>
	constexpr TMatrix3x4<T> operator/(T s, TMatrix3x4<T> const &m) noexcept
	{
		return TMatrix3x4<T>{s / m.data[0],
				     s / m.data[1],
				     s / m.data[2]};
	}

	// ------------------------- MS arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix3x4<T> operator*(TMatrix3x4<T> const &m, T s) noexcept
	{
		return TMatrix3x4<T>{m.data[0] * s,
				     m.data[1] * s,
				     m.data[2] * s};
	}

	template <class T>
	constexpr TMatrix3x4<T> operator/(TMatrix3x4<T> const &m, T s) noexcept
	{
		return TMatrix3x4<T>{m.data[0] / s,
				     m.data[1] / s,
				     m.data[2] / s};
	}

	// ----------------------------- Unary ----------------------------- //

	template <class T>
	constexpr TMatrix3x4<T> operator+(TMatrix3x4<T> const &a) noexcept
	{
		return a;
	}

	template <class T>
	constexpr TMatrix3x4<T> operator-(TMatrix3x4<T> const &a) noexcept
	{
		return TMatrix3x4<T>{} - a;
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TMatrix3x4<bool> operator<(TMatrix3x4<T> const &a,
					     TMatrix3x4<T> const &b) noexcept
	{
		return TMatrix3x4<bool>{a.data[0] < b.data[0],
					a.data[1] < b.data[1],
					a.data[2] < b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x4<bool> operator>(TMatrix3x4<T> const &a,
					     TMatrix3x4<T> const &b) noexcept
	{
		return TMatrix3x4<bool>{a.data[0] > b.data[0],
					a.data[1] > b.data[1],
					a.data[2] > b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x4<bool> operator>=(TMatrix3x4<T> const &a,
					      TMatrix3x4<T> const &b) noexcept
	{
		return TMatrix3x4<bool>{a.data[0] >= b.data[0],
					a.data[1] >= b.data[1],
					a.data[2] >= b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x4<bool> operator<=(TMatrix3x4<T> const &a,
					      TMatrix3x4<T> const &b) noexcept
	{
		return TMatrix3x4<bool>{a.data[0] <= b.data[0],
					a.data[1] <= b.data[1],
					a.data[2] <= b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x4<bool> operator==(TMatrix3x4<T> const &a,
					      TMatrix3x4<T> const &b) noexcept
	{
		return TMatrix3x4<bool>{a.data[0] == b.data[0],
					a.data[1] == b.data[1],
					a.data[2] == b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x4<bool> operator!=(TMatrix3x4<T> const &a,
					      TMatrix3x4<T> const &b) noexcept
	{
		return TMatrix3x4<bool>{a.data[0] != b.data[0],
					a.data[1] != b.data[1],
					a.data[2] != b.data[2]};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TMatrix3x4<bool> operator&&(TMatrix3x4<bool> const &a,
					      TMatrix3x4<bool> const &b) noexcept
	{
		return TMatrix3x4<bool>{a.data[0] && b.data[0],
					a.data[1] && b.data[1],
					a.data[2] && b.data[2]};
	}

	constexpr TMatrix3x4<bool> operator||(TMatrix3x4<bool> const &a,
					      TMatrix3x4<bool> const &b) noexcept
	{
		return TMatrix3x4<bool>{a.data[0] || b.data[0],
					a.data[1] || b.data[1],
					a.data[2] || b.data[2]};
	}

	constexpr bool all(TMatrix3x4<bool> const &a) noexcept
	{
		return all(a.data[0]) &&
		       all(a.data[1]) &&
		       all(a.data[2]);
	}

	constexpr bool any(TMatrix3x4<bool> const &a) noexcept
	{
		return any(a.data[0]) ||
		       any(a.data[1]) ||
		       any(a.data[2]);
	}
}

#endif