#ifndef MICRO_LIBMATH_VECTOR3_HH__GUARD
#define MICRO_LIBMATH_VECTOR3_HH__GUARD

#include <type_traits>

namespace micro::math
{
	template <class T,
		  class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TVector3
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TVector3(type x = {},
				   type y = {},
				   type z = {}) noexcept
		{
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}

		constexpr type &x() noexcept { return data[0]; }
		constexpr type &y() noexcept { return data[1]; }
		constexpr type &z() noexcept { return data[2]; }
		constexpr type const &x() const noexcept { return data[0]; }
		constexpr type const &y() const noexcept { return data[1]; }
		constexpr type const &z() const noexcept { return data[2]; }

		type data[3] = {};
	};

	// ------------------------- VV arithmetic ------------------------- //

	template <class T>
	constexpr TVector3<T> operator+(TVector3<T> const &a,
					TVector3<T> const &b) noexcept
	{
		return TVector3<T>{a.x() + b.x(),
				   a.y() + b.y(),
				   a.z() + b.z()};
	}

	template <class T>
	constexpr TVector3<T> operator-(TVector3<T> const &a,
					TVector3<T> const &b) noexcept
	{
		return TVector3<T>{a.x() - b.x(),
				   a.y() - b.y(),
				   a.z() - b.z()};
	}

	template <class T>
	constexpr TVector3<T> operator*(TVector3<T> const &a,
					TVector3<T> const &b) noexcept
	{
		return TVector3<T>{a.x() * b.x(),
				   a.y() * b.y(),
				   a.z() * b.z()};
	}

	template <class T>
	constexpr TVector3<T> operator/(TVector3<T> const &a,
					TVector3<T> const &b) noexcept
	{
		return TVector3<T>{a.x() / b.x(),
				   a.y() / b.y(),
				   a.z() / b.z()};
	}

	template <class T>
	constexpr TVector3<T> operator^(TVector3<T> const &a,
					TVector3<T> const &b) noexcept
	{
		return TVector3<T>{a.y() * b.z() - a.z() * b.y(),
				   a.z() * b.x() - a.x() * b.z(),
				   a.x() * b.y() - a.y() * b.x()};
	}

	// ----------------------------- Unary ----------------------------- //

	template <class T>
	constexpr TVector3<T> operator+(TVector3<T> const &a) noexcept
	{
		return a;
	}

	template <class T>
	constexpr TVector3<T> operator-(TVector3<T> const &a) noexcept
	{
		return TVector3<T>{} - a;
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TVector3<bool> operator<(TVector3<T> const &a,
					   TVector3<T> const &b) noexcept
	{
		return TVector3<bool>{a.x() < b.x(),
				      a.y() < b.y(),
				      a.z() < b.z()};
	}

	template <class T>
	constexpr TVector3<bool> operator>(TVector3<T> const &a,
					   TVector3<T> const &b) noexcept
	{
		return TVector3<bool>{a.x() > b.x(),
				      a.y() > b.y(),
				      a.z() > b.z()};
	}

	template <class T>
	constexpr TVector3<bool> operator>=(TVector3<T> const &a,
					    TVector3<T> const &b) noexcept
	{
		return TVector3<bool>{a.x() >= b.x(),
				      a.y() >= b.y(),
				      a.z() >= b.z()};
	}

	template <class T>
	constexpr TVector3<bool> operator<=(TVector3<T> const &a,
					    TVector3<T> const &b) noexcept
	{
		return TVector3<bool>{a.x() <= b.x(),
				      a.y() <= b.y(),
				      a.z() <= b.z()};
	}

	template <class T>
	constexpr TVector3<bool> operator==(TVector3<T> const &a,
					    TVector3<T> const &b) noexcept
	{
		return TVector3<bool>{a.x() == b.x(),
				      a.y() == b.y(),
				      a.z() == b.z()};
	}

	template <class T>
	constexpr TVector3<bool> operator!=(TVector3<T> const &a,
					    TVector3<T> const &b) noexcept
	{
		return TVector3<bool>{a.x() != b.x(),
				      a.y() != b.y(),
				      a.z() != b.z()};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TVector3<bool> operator&&(TVector3<bool> const &a,
					    TVector3<bool> const &b) noexcept
	{
		return TVector3<bool>{a.x() && b.x(),
				      a.y() && b.y(),
				      a.z() && b.z()};
	}

	constexpr TVector3<bool> operator||(TVector3<bool> const &a,
					    TVector3<bool> const &b) noexcept
	{
		return TVector3<bool>{a.x() || b.x(),
				      a.y() || b.y(),
				      a.z() || b.z()};
	}

	constexpr bool all(TVector3<bool> const &a) noexcept
	{
		return a.x() &&
		       a.y() &&
		       a.z();
	}

	constexpr bool any(TVector3<bool> const &a) noexcept
	{
		return a.x() ||
		       a.y() ||
		       a.z();
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr TVector3<T> lerp(TVector3<T> const &a,
				   TVector3<T> const &b, T f) noexcept
	{
		return a + f * (b - a);
	}

	// ------------------------- SV arithmetic ------------------------- //

	template <class T>
	constexpr TVector3<T> operator*(T s, TVector3<T> const &v) noexcept
	{
		return TVector3<T>{s * v.x(),
				   s * v.y(),
				   s * v.z()};
	}
	template <class T>
	constexpr TVector3<T> operator/(T s, TVector3<T> const &v) noexcept
	{
		return TVector3<T>{s / v.x(),
				   s / v.y(),
				   s / v.z()};
	}

	// ------------------------- VS arithmetic ------------------------- //

	template <class T>
	constexpr TVector3<T> operator*(TVector3<T> const &v, T s) noexcept
	{
		return TVector3<T>{v.x() * s,
				   v.y() * s,
				   v.z() * s};
	}

	template <class T>
	constexpr TVector3<T> operator/(TVector3<T> const &v, T s) noexcept
	{
		return TVector3<T>{v.x() / s,
				   v.y() / s,
				   v.z() / s};
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr T sum(TVector3<T> const &a) noexcept
	{
		return a.x() + a.y() + a.z();
	}

	// ----------------------------------------------------------------- //

	template <class U,
		  class T>
	constexpr TVector3<U> vector_cast(TVector3<T> const &src) noexcept
	{
		return TVector3<U>{static_cast<U>(src.data[0]),
				   static_cast<U>(src.data[1]),
				   static_cast<U>(src.data[2])};
	}
}

#endif