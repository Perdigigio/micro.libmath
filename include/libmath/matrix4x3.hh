#ifndef MICRO_LIBMATH_MATRIX4X3_HH__GUARD
#define MICRO_LIBMATH_MATRIX4X3_HH__GUARD

#include "vector3.hh"
#include "vector4.hh"

namespace micro::math
{
	template<class T,
		 class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TMatrix4x3
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TMatrix4x3(T _11 = {}, T _12 = {}, T _13 = {},
				     T _21 = {}, T _22 = {}, T _23 = {},
				     T _31 = {}, T _32 = {}, T _33 = {},
				     T _41 = {}, T _42 = {}, T _43 = {}) noexcept
		{
			data[0] = {_11, _12, _13};
			data[1] = {_21, _22, _23};
			data[2] = {_31, _32, _33};
			data[3] = {_41, _42, _43};
		}

		constexpr TMatrix4x3(TVector3<T> const &_1,
				     TVector3<T> const &_2,
				     TVector3<T> const &_3,
				     TVector3<T> const &_4) noexcept
		{
			data[0] = _1;
			data[1] = _2;
			data[2] = _3;
			data[3] = _4;
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
		constexpr type & _41() noexcept { return data[3].data[0]; }
		constexpr type & _42() noexcept { return data[3].data[1]; }
		constexpr type & _43() noexcept { return data[3].data[2]; }
		constexpr type const & _11() const noexcept { return data[0].data[0]; }
		constexpr type const & _12() const noexcept { return data[0].data[1]; }
		constexpr type const & _13() const noexcept { return data[0].data[2]; }
		constexpr type const & _21() const noexcept { return data[1].data[0]; }
		constexpr type const & _22() const noexcept { return data[1].data[1]; }
		constexpr type const & _23() const noexcept { return data[1].data[2]; }
		constexpr type const & _31() const noexcept { return data[2].data[0]; }
		constexpr type const & _32() const noexcept { return data[2].data[1]; }
		constexpr type const & _33() const noexcept { return data[2].data[2]; }
		constexpr type const & _41() const noexcept { return data[3].data[0]; }
		constexpr type const & _42() const noexcept { return data[3].data[1]; }
		constexpr type const & _43() const noexcept { return data[3].data[2]; }

		TVector3<T> data[4] = {};
	};

	// ------------------------- MV arithmetic ------------------------- //

	template <class T>
	inline TVector4<T> operator*(TMatrix4x3<T> const &l, TVector3<T> const &r) noexcept
	{
		return TVector4<T>{sum(l.data[0] * r),
				   sum(l.data[1] * r),
				   sum(l.data[2] * r),
				   sum(l.data[3] * r)};
	}

	// ------------------------- MM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix4x3<T> operator+(TMatrix4x3<T> const &l,
					  TMatrix4x3<T> const &r) noexcept
	{
		return TMatrix4x3<T>{l.data[0] + r.data[0],
				     l.data[1] + r.data[1],
				     l.data[2] + r.data[2],
				     l.data[3] + r.data[3]};
	}

	template <class T>
	constexpr TMatrix4x3<T> operator-(TMatrix4x3<T> const &l,
					  TMatrix4x3<T> const &r) noexcept
	{
		return TMatrix4x3<T>{l.data[0] - r.data[0],
				     l.data[1] - r.data[1],
				     l.data[2] - r.data[2],
				     l.data[3] - r.data[3]};
	}

	// ------------------------- SM arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix4x3<T> operator*(T s, TMatrix4x3<T> const &m) noexcept
	{
		return TMatrix4x3<T>{s * m.data[0],
				     s * m.data[1],
				     s * m.data[2],
				     s * m.data[3]};
	}

	template <class T>
	constexpr TMatrix4x3<T> operator/(T s, TMatrix4x3<T> const &m) noexcept
	{
		return TMatrix4x3<T>{s / m.data[0],
				     s / m.data[1],
				     s / m.data[2],
				     s / m.data[3]};
	}

	// ------------------------- MS arithmetic ------------------------- //

	template <class T>
	constexpr TMatrix4x3<T> operator*(TMatrix4x3<T> const &m, T s) noexcept
	{
		return TMatrix4x3<T>{m.data[0] * s,
				     m.data[1] * s,
				     m.data[2] * s,
				     m.data[3] * s};
	}

	template <class T>
	constexpr TMatrix4x3<T> operator/(TMatrix4x3<T> const &m, T s) noexcept
	{
		return TMatrix4x3<T>{m.data[0] / s,
				     m.data[1] / s,
				     m.data[2] / s,
				     m.data[3] / s};
	}

	// ----------------------------- Unary ----------------------------- //

	template <class T>
	constexpr TMatrix4x3<T> operator+(TMatrix4x3<T> const &a) noexcept
	{
		return a;
	}

	template <class T>
	constexpr TMatrix4x3<T> operator-(TMatrix4x3<T> const &a) noexcept
	{
		return TMatrix4x3<T>{} - a;
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TMatrix4x3<bool> operator<(TMatrix4x3<T> const &a,
					     TMatrix4x3<T> const &b) noexcept
	{
		return TMatrix4x3<bool>{a.data[0] < b.data[0],
					a.data[1] < b.data[1],
					a.data[2] < b.data[2],
					a.data[3] < b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x3<bool> operator>(TMatrix4x3<T> const &a,
					     TMatrix4x3<T> const &b) noexcept
	{
		return TMatrix4x3<bool>{a.data[0] > b.data[0],
					a.data[1] > b.data[1],
					a.data[2] > b.data[2],
					a.data[3] > b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x3<bool> operator>=(TMatrix4x3<T> const &a,
					      TMatrix4x3<T> const &b) noexcept
	{
		return TMatrix4x3<bool>{a.data[0] >= b.data[0],
					a.data[1] >= b.data[1],
					a.data[2] >= b.data[2],
					a.data[3] >= b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x3<bool> operator<=(TMatrix4x3<T> const &a,
					      TMatrix4x3<T> const &b) noexcept
	{
		return TMatrix4x3<bool>{a.data[0] <= b.data[0],
					a.data[1] <= b.data[1],
					a.data[2] <= b.data[2],
					a.data[3] <= b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x3<bool> operator==(TMatrix4x3<T> const &a,
					      TMatrix4x3<T> const &b) noexcept
	{
		return TMatrix4x3<bool>{a.data[0] == b.data[0],
					a.data[1] == b.data[1],
					a.data[2] == b.data[2],
					a.data[3] == b.data[3]};
	}

	template <class T>
	constexpr TMatrix4x3<bool> operator!=(TMatrix4x3<T> const &a,
					      TMatrix4x3<T> const &b) noexcept
	{
		return TMatrix4x3<bool>{a.data[0] != b.data[0],
					a.data[1] != b.data[1],
					a.data[2] != b.data[2],
					a.data[3] != b.data[3]};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TMatrix4x3<bool> operator&&(TMatrix4x3<bool> const &a,
					      TMatrix4x3<bool> const &b) noexcept
	{
		return TMatrix4x3<bool>{a.data[0] && b.data[0],
					a.data[1] && b.data[1],
					a.data[2] && b.data[2],
					a.data[3] && b.data[3]};
	}

	constexpr TMatrix4x3<bool> operator||(TMatrix4x3<bool> const &a,
					      TMatrix4x3<bool> const &b) noexcept
	{
		return TMatrix4x3<bool>{a.data[0] || b.data[0],
					a.data[1] || b.data[1],
					a.data[2] || b.data[2],
					a.data[3] || b.data[3]};
	}

	constexpr bool all(TMatrix4x3<bool> const &a) noexcept
	{
		return all(a.data[0]) &&
		       all(a.data[1]) &&
		       all(a.data[2]) &&
		       all(a.data[3]);
	}

	constexpr bool any(TMatrix4x3<bool> const &a) noexcept
	{
		return any(a.data[0]) ||
		       any(a.data[1]) ||
		       any(a.data[2]) ||
		       any(a.data[3]);
	}
}

#endif