#ifndef MICRO_LIBMATH_MATRIX3X2_HH__GUARD
#define MICRO_LIBMATH_MATRIX3X2_HH__GUARD

#include "vector2.hh"
#include "vector3.hh"

namespace micro::math
{
	template <class T,
		  class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TMatrix3x2
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TMatrix3x2(type _11 = {}, type _12 = {},
				     type _21 = {}, type _22 = {},
				     type _31 = {}, type _32 = {}) noexcept
		{
			data[0] = {_11, _12};
			data[1] = {_21, _22};
			data[2] = {_31, _32};
		}

		constexpr TMatrix3x2(TVector2<T> const &_1,
				     TVector2<T> const &_2,
				     TVector2<T> const &_3) noexcept
		{
			data[0] = _1;
			data[1] = _2;
			data[2] = _3;
		}

		constexpr type & _11() noexcept { return data[0].data[0]; }
		constexpr type & _12() noexcept { return data[0].data[1]; }
		constexpr type & _21() noexcept { return data[1].data[0]; }
		constexpr type & _22() noexcept { return data[1].data[1]; }
		constexpr type & _31() noexcept { return data[2].data[0]; }
		constexpr type & _32() noexcept { return data[2].data[1]; }
		constexpr type const & _11() const noexcept { return data[0].data[0]; }
		constexpr type const & _12() const noexcept { return data[0].data[1]; }
		constexpr type const & _21() const noexcept { return data[1].data[0]; }
		constexpr type const & _22() const noexcept { return data[1].data[1]; }
		constexpr type const & _31() const noexcept { return data[2].data[0]; }
		constexpr type const & _32() const noexcept { return data[2].data[1]; }

		TVector2<type> data[3] = {};
	};

	// ------------------------- MV arithmetic ------------------------- //

	template <class T>
	inline TVector3<T> operator*(TMatrix3x2<T> const &l, TVector2<T> const &r) noexcept
	{
		return TVector3<T>{sum(l.data[0] * r),
				   sum(l.data[1] * r),
				   sum(l.data[2] * r)};
	}

	// ------------------------- MM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix3x2<T> operator+(TMatrix3x2<T> const &l,
					  TMatrix3x2<T> const &r) noexcept
	{
		return TMatrix3x2<T>{l.data[0] + r.data[0],
				     l.data[1] + r.data[1]};
	}

	template <class T>
	constexpr TMatrix3x2<T> operator-(TMatrix3x2<T> const &l,
					  TMatrix3x2<T> const &r) noexcept
	{
		return TMatrix3x2<T>{l.data[0] - r.data[0],
				     l.data[1] - r.data[1]};
	}

	// ------------------------- SM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix3x2<T> operator*(T s, TMatrix3x2<T> const &m) noexcept
	{
		return TMatrix3x2<T>{s * m.data[0],
				     s * m.data[1]};
	}

	template <class T>
	constexpr TMatrix3x2<T> operator/(T s, TMatrix3x2<T> const &m) noexcept
	{
		return TMatrix3x2<T>{s / m.data[0],
				     s / m.data[1]};
	}

	// ------------------------- MS arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix3x2<T> operator*(TMatrix3x2<T> const &m, T s) noexcept
	{
		return TMatrix3x2<T>{m.data[0] * s,
				     m.data[1] * s};
	}

	template <class T>
	constexpr TMatrix3x2<T> operator/(TMatrix3x2<T> const &m, T s) noexcept
	{
		return TMatrix3x2<T>{m.data[0] / s,
				     m.data[1] / s};
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TMatrix3x2<bool> operator<(TMatrix3x2<T> const &a,
					     TMatrix3x2<T> const &b) noexcept
	{
		return TMatrix3x2<bool>{a.data[0] < b.data[0],
					a.data[1] < b.data[1],
					a.data[2] < b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x2<bool> operator>(TMatrix3x2<T> const &a,
					     TMatrix3x2<T> const &b) noexcept
	{
		return TMatrix3x2<bool>{a.data[0] > b.data[0],
					a.data[1] > b.data[1],
					a.data[2] > b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x2<bool> operator>=(TMatrix3x2<T> const &a,
					      TMatrix3x2<T> const &b) noexcept
	{
		return TMatrix3x2<bool>{a.data[0] >= b.data[0],
					a.data[1] >= b.data[1],
					a.data[2] >= b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x2<bool> operator<=(TMatrix3x2<T> const &a,
					      TMatrix3x2<T> const &b) noexcept
	{
		return TMatrix3x2<bool>{a.data[0] <= b.data[0],
					a.data[1] <= b.data[1],
					a.data[2] <= b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x2<bool> operator==(TMatrix3x2<T> const &a,
					      TMatrix3x2<T> const &b) noexcept
	{
		return TMatrix3x2<bool>{a.data[0] == b.data[0],
					a.data[1] == b.data[1],
					a.data[2] == b.data[2]};
	}

	template <class T>
	constexpr TMatrix3x2<bool> operator!=(TMatrix3x2<T> const &a,
					      TMatrix3x2<T> const &b) noexcept
	{
		return TMatrix3x2<bool>{a.data[0] != b.data[0],
					a.data[1] != b.data[1],
					a.data[2] != b.data[2]};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TMatrix3x2<bool> operator&&(TMatrix3x2<bool> const &a,
					      TMatrix3x2<bool> const &b) noexcept
	{
		return TMatrix3x2<bool>{a.data[0] && b.data[0],
					a.data[1] && b.data[1],
					a.data[2] && b.data[2]};
	}

	constexpr TMatrix3x2<bool> operator||(TMatrix3x2<bool> const &a,
					      TMatrix3x2<bool> const &b) noexcept
	{
		return TMatrix3x2<bool>{a.data[0] || b.data[0],
					a.data[1] || b.data[1],
					a.data[2] || b.data[2]};
	}

	constexpr bool all(TMatrix3x2<bool> const &a) noexcept
	{
		return all(a.data[0]) &&
		       all(a.data[1]) &&
		       all(a.data[2]);
	}

	constexpr bool any(TMatrix3x2<bool> const &a) noexcept
	{
		return any(a.data[0]) ||
		       any(a.data[1]) ||
		       any(a.data[2]);
	}
}

#endif