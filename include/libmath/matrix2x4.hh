#ifndef MICRO_LIBMATH_MATRIX2X4_HH__GUARD
#define MICRO_LIBMATH_MATRIX2X4_HH__GUARD

#include "vector2.hh"
#include "vector4.hh"

namespace micro::math
{
	template <class T,
		  class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TMatrix2x4
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TMatrix2x4(type _11 = {}, type _12 = {}, type _13 = {}, type _14 = {},
				     type _21 = {}, type _22 = {}, type _23 = {}, type _24 = {}) noexcept
		{
			data[0] = {_11, _12, _13, _14};
			data[1] = {_21, _22, _23, _24};
		}

		constexpr TMatrix2x4(TVector4<T> const &_1,
				     TVector4<T> const &_2) noexcept
		{
			data[0] = _1;
			data[1] = _2;
		}

		constexpr type & _11() noexcept { return data[0].data[0]; }
		constexpr type & _12() noexcept { return data[0].data[1]; }
		constexpr type & _13() noexcept { return data[0].data[2]; }
		constexpr type & _14() noexcept { return data[0].data[3]; }
		constexpr type & _21() noexcept { return data[1].data[0]; }
		constexpr type & _22() noexcept { return data[1].data[1]; }
		constexpr type & _23() noexcept { return data[1].data[2]; }
		constexpr type & _24() noexcept { return data[1].data[3]; }
		constexpr type const & _11() const noexcept { return data[0].data[0]; }
		constexpr type const & _12() const noexcept { return data[0].data[1]; }
		constexpr type const & _13() const noexcept { return data[0].data[2]; }
		constexpr type const & _14() const noexcept { return data[0].data[3]; }
		constexpr type const & _21() const noexcept { return data[1].data[0]; }
		constexpr type const & _22() const noexcept { return data[1].data[1]; }
		constexpr type const & _23() const noexcept { return data[1].data[2]; }
		constexpr type const & _24() const noexcept { return data[1].data[3]; }

		TVector4<type> data[2] = {};
	};

	// ------------------------- MV arithmetic ------------------------- //

	template <class T>
	inline TVector2<T> operator*(TMatrix2x4<T> const &l, TVector4<T> const &r) noexcept
	{
		return TVector2<T>{sum(l.data[0] * r),
				   sum(l.data[1] * r)};
	}

	// ------------------------- MM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix2x4<T> operator+(TMatrix2x4<T> const &l,
					  TMatrix2x4<T> const &r) noexcept
	{
		return TMatrix2x4<T>{l.data[0] + r.data[0],
				     l.data[1] + r.data[1]};
	}

	template <class T>
	constexpr TMatrix2x4<T> operator-(TMatrix2x4<T> const &l,
					  TMatrix2x4<T> const &r) noexcept
	{
		return TMatrix2x4<T>{l.data[0] - r.data[0],
				     l.data[1] - r.data[1]};
	}

	// ------------------------- SM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix2x4<T> operator*(T s, TMatrix2x4<T> const &m) noexcept
	{
		return TMatrix2x4<T>{s * m.data[0],
				     s * m.data[1]};
	}

	template <class T>
	constexpr TMatrix2x4<T> operator/(T s, TMatrix2x4<T> const &m) noexcept
	{
		return TMatrix2x4<T>{s / m.data[0],
				     s / m.data[1]};
	}

	// ------------------------- MS arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix2x4<T> operator*(TMatrix2x4<T> const &m, T s) noexcept
	{
		return TMatrix2x4<T>{m.data[0] * s,
				     m.data[1] * s};
	}

	template <class T>
	constexpr TMatrix2x4<T> operator/(TMatrix2x4<T> const &m, T s) noexcept
	{
		return TMatrix2x4<T>{m.data[0] / s,
				     m.data[1] / s};
	}

	// ----------------------------- Unary ----------------------------- //

	template <class T>
	constexpr TMatrix2x4<T> operator+(TMatrix2x4<T> const &a) noexcept
	{
		return a;
	}

	template <class T>
	constexpr TMatrix2x4<T> operator-(TMatrix2x4<T> const &a) noexcept
	{
		return TMatrix2x4<T>{} - a;
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TMatrix2x4<bool> operator<(TMatrix2x4<T> const &a,
					     TMatrix2x4<T> const &b) noexcept
	{
		return TMatrix2x4<bool>{a.data[0] < b.data[0],
					a.data[1] < b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x4<bool> operator>(TMatrix2x4<T> const &a,
					     TMatrix2x4<T> const &b) noexcept
	{
		return TMatrix2x4<bool>{a.data[0] > b.data[0],
					a.data[1] > b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x4<bool> operator>=(TMatrix2x4<T> const &a,
					      TMatrix2x4<T> const &b) noexcept
	{
		return TMatrix2x4<bool>{a.data[0] >= b.data[0],
					a.data[1] >= b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x4<bool> operator<=(TMatrix2x4<T> const &a,
					      TMatrix2x4<T> const &b) noexcept
	{
		return TMatrix2x4<bool>{a.data[0] <= b.data[0],
					a.data[1] <= b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x4<bool> operator==(TMatrix2x4<T> const &a,
					      TMatrix2x4<T> const &b) noexcept
	{
		return TMatrix2x4<bool>{a.data[0] == b.data[0],
					a.data[1] == b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x4<bool> operator!=(TMatrix2x4<T> const &a,
					      TMatrix2x4<T> const &b) noexcept
	{
		return TMatrix2x4<bool>{a.data[0] != b.data[0],
					a.data[1] != b.data[1]};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TMatrix2x4<bool> operator&&(TMatrix2x4<bool> const &a,
					      TMatrix2x4<bool> const &b) noexcept
	{
		return TMatrix2x4<bool>{a.data[0] && b.data[0],
					a.data[1] && b.data[1]};
	}

	constexpr TMatrix2x4<bool> operator||(TMatrix2x4<bool> const &a,
					      TMatrix2x4<bool> const &b) noexcept
	{
		return TMatrix2x4<bool>{a.data[0] || b.data[0],
					a.data[1] || b.data[1]};
	}

	constexpr bool all(TMatrix2x4<bool> const &a) noexcept
	{
		return all(a.data[0]) &&
		       all(a.data[1]);
	}

	constexpr bool any(TMatrix2x4<bool> const &a) noexcept
	{
		return any(a.data[0]) ||
		       any(a.data[1]);
	}
}

#endif