#ifndef MICRO_LIBMATH_MATRIX2X2_HH__GUARD
#define MICRO_LIBMATH_MATRIX2X2_HH__GUARD

#include "vector2.hh"

namespace micro::math
{
	template <class T,
		  class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TMatrix2x2
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TMatrix2x2(type _11 = {}, type _12 = {},
				     type _21 = {}, type _22 = {}) noexcept
		{
			data[0] = {_11, _12};
			data[1] = {_21, _22};
		}

		constexpr TMatrix2x2(TVector2<T> const &_1,
				     TVector2<T> const &_2) noexcept
		{
			data[0] = _1;
			data[1] = _2;
		}

		constexpr type &_11() noexcept { return data[0].data[0]; }
		constexpr type &_12() noexcept { return data[0].data[1]; }
		constexpr type &_21() noexcept { return data[1].data[0]; }
		constexpr type &_22() noexcept { return data[1].data[1]; }
		constexpr type const &_11() const noexcept { return data[0].data[0]; }
		constexpr type const &_12() const noexcept { return data[0].data[1]; }
		constexpr type const &_21() const noexcept { return data[1].data[0]; }
		constexpr type const &_22() const noexcept { return data[1].data[1]; }

		TVector2<type> data[2] = {};
	};

	// -------------------------- M identity  -------------------------- //

	template <class T>
	constexpr TMatrix2x2<T> identity2x2() noexcept
	{
		return TMatrix2x2<T>{T(1), T(0),
				     T(0), T(1)};
	}

	// ------------------------- MV arithmetic ------------------------- //

	template <class T>
	inline TVector2<T> operator*(TMatrix2x2<T> const &l, TVector2<T> const &r) noexcept
	{
		return TVector2<T>{sum(l.data[0] * r),
				   sum(l.data[1] * r)};
	}

	// ------------------------- MM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix2x2<T> operator+(TMatrix2x2<T> const &l,
					  TMatrix2x2<T> const &r) noexcept
	{
		return TMatrix2x2<T>{l.data[0] + r.data[0],
				     l.data[1] + r.data[1]};
	}

	template <class T>
	constexpr TMatrix2x2<T> operator-(TMatrix2x2<T> const &l,
					  TMatrix2x2<T> const &r) noexcept
	{
		return TMatrix2x2<T>{l.data[0] - r.data[0],
				     l.data[1] - r.data[1]};
	}

	template <class T>
	constexpr TMatrix2x2<T> operator*(TMatrix2x2<T> const &l,
					  TMatrix2x2<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._21() * r.data[0];
		auto const D = l._22() * r.data[1];

		return TMatrix2x2<T>{A + B,
				     C + D};
	}

	// ------------------------- SM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix2x2<T> operator*(T s, TMatrix2x2<T> const &m) noexcept
	{
		return TMatrix2x2<T>{s * m.data[0],
				     s * m.data[1]};
	}

	template <class T>
	constexpr TMatrix2x2<T> operator/(T s, TMatrix2x2<T> const &m) noexcept
	{
		return TMatrix2x2<T>{s / m.data[0],
				     s / m.data[1]};
	}

	// ------------------------- MS arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix2x2<T> operator*(TMatrix2x2<T> const &m, T s) noexcept
	{
		return TMatrix2x2<T>{m.data[0] * s,
				     m.data[1] * s};
	}

	template <class T>
	constexpr TMatrix2x2<T> operator/(TMatrix2x2<T> const &m, T s) noexcept
	{
		return TMatrix2x2<T>{m.data[0] / s,
				     m.data[1] / s};
	}

	// ----------------------------- Unary ----------------------------- //

	template <class T>
	constexpr TMatrix2x2<T> operator+(TMatrix2x2<T> const &a) noexcept
	{
		return a;
	}

	template <class T>
	constexpr TMatrix2x2<T> operator-(TMatrix2x2<T> const &a) noexcept
	{
		return TMatrix2x2<T>{} - a;
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TMatrix2x2<bool> operator<(TMatrix2x2<T> const &a,
					     TMatrix2x2<T> const &b) noexcept
	{
		return TMatrix2x2<bool>{a.data[0] < b.data[0],
					a.data[1] < b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x2<bool> operator>(TMatrix2x2<T> const &a,
					     TMatrix2x2<T> const &b) noexcept
	{
		return TMatrix2x2<bool>{a.data[0] > b.data[0],
					a.data[1] > b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x2<bool> operator>=(TMatrix2x2<T> const &a,
					      TMatrix2x2<T> const &b) noexcept
	{
		return TMatrix2x2<bool>{a.data[0] >= b.data[0],
					a.data[1] >= b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x2<bool> operator<=(TMatrix2x2<T> const &a,
					      TMatrix2x2<T> const &b) noexcept
	{
		return TMatrix2x2<bool>{a.data[0] <= b.data[0],
					a.data[1] <= b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x2<bool> operator==(TMatrix2x2<T> const &a,
					      TMatrix2x2<T> const &b) noexcept
	{
		return TMatrix2x2<bool>{a.data[0] == b.data[0],
					a.data[1] == b.data[1]};
	}

	template <class T>
	constexpr TMatrix2x2<bool> operator!=(TMatrix2x2<T> const &a,
					      TMatrix2x2<T> const &b) noexcept
	{
		return TMatrix2x2<bool>{a.data[0] != b.data[0],
					a.data[1] != b.data[1]};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TMatrix2x2<bool> operator&&(TMatrix2x2<bool> const &a,
					      TMatrix2x2<bool> const &b) noexcept
	{
		return TMatrix2x2<bool>{a.data[0] && b.data[0],
					a.data[1] && b.data[1]};
	}

	constexpr TMatrix2x2<bool> operator||(TMatrix2x2<bool> const &a,
					      TMatrix2x2<bool> const &b) noexcept
	{
		return TMatrix2x2<bool>{a.data[0] || b.data[0],
					a.data[1] || b.data[1]};
	}

	constexpr bool all(TMatrix2x2<bool> const &a) noexcept
	{
		return all(a.data[0]) &&
		       all(a.data[1]);
	}

	constexpr bool any(TMatrix2x2<bool> const &a) noexcept
	{
		return any(a.data[0]) ||
		       any(a.data[1]);
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr T det(TMatrix2x2<T> const &m) noexcept
	{
		return m._11() * m._22() -
		       m._12() * m._21();
	}

	template <class T>
	constexpr TMatrix2x2<T> transpose(TMatrix2x2<T> const &m) noexcept
	{
		return TMatrix2x2<T>{m._11(), m._21(),
				     m._12(), m._22()};
	}

	template <class T>
	constexpr TMatrix2x2<T> adjoint(TMatrix2x2<T> const &m) noexcept
	{
		return TMatrix2x2<T>{+m._22(), -m._12(),
				     -m._21(), +m._11()};
	}

	template <class T>
	constexpr TMatrix2x2<T> inverse(TMatrix2x2<T> const &m) noexcept
	{
		return adjoint(m) / det(m);
	}

	// ----------------------------------------------------------------- //

	template <class U,
		  class T>
	constexpr TMatrix2x2<U> matrix_cast(TMatrix2x2<T> const &src) noexcept
	{
		return TMatrix2x2<U>{vector_cast<U>(src.data[0]),
				     vector_cast<U>(src.data[1])};
	}
}

#endif