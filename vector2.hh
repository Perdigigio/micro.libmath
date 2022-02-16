#ifndef MICRO_LIBMATH_VECTOR2_HH__GUARD
#define MICRO_LIBMATH_VECTOR2_HH__GUARD

#include <type_traits>

#if !defined(_MICRO_HAS_SSE_INTRINSICS) && (defined(_M_AMD64) || defined(__amd64__))
#	define _MICRO_HAS_SSE_INTRINSICS 1
#endif

#if !defined(_MICRO_HAS_ARM_INTRINSICS) && (defined(_M_ARM64) || defined(_M_ARM) || defined(__ARM_NEON))
#	define _MICRO_HAS_ARM_INTRINSICS 1
#endif

namespace micro::math
{
	template <class T,
		  class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TVector2
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TVector2(type x = {},
				   type y = {}) noexcept
		{
			data[0] = x;
			data[1] = y;
		}

		constexpr type &x() noexcept { return data[0]; }
		constexpr type &y() noexcept { return data[1]; }
		constexpr type const &x() const noexcept { return data[0]; }
		constexpr type const &y() const noexcept { return data[1]; }

		type data[2] = {};
	};

	// ------------------------- VV arithmetic ------------------------- //

	template <class T>
	constexpr TVector2<T> operator+(TVector2<T> const &a,
					TVector2<T> const &b) noexcept
	{
		return TVector2<T>{a.x() + b.x(),
				   a.y() + b.y()};
	}

	template <class T>
	constexpr TVector2<T> operator-(TVector2<T> const &a,
					TVector2<T> const &b) noexcept
	{
		return TVector2<T>{a.x() - b.x(),
				   a.y() - b.y()};
	}

	template <class T>
	constexpr TVector2<T> operator*(TVector2<T> const &a,
					TVector2<T> const &b) noexcept
	{
		return TVector2<T>{a.x() * b.x(),
				   a.y() * b.y()};
	}

	template <class T>
	constexpr TVector2<T> operator/(TVector2<T> const &a,
					TVector2<T> const &b) noexcept
	{
		return TVector2<T>{a.x() / b.x(),
				   a.y() / b.y()};
	}

	// ----------------------------- Unary ----------------------------- //

	template <class T>
	constexpr TVector2<T> operator+(TVector2<T> const &a) noexcept
	{
		return a;
	}

	template <class T>
	constexpr TVector2<T> operator-(TVector2<T> const &a) noexcept
	{
		return TVector2<T>{} - a;
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TVector2<bool> operator<(TVector2<T> const &a,
					   TVector2<T> const &b) noexcept
	{
		return TVector2<bool>{a.x() < b.x(),
				      a.y() < b.y()};
	}

	template <class T>
	constexpr TVector2<bool> operator>(TVector2<T> const &a,
					   TVector2<T> const &b) noexcept
	{
		return TVector2<bool>{a.x() > b.x(),
				      a.y() > b.y()};
	}

	template <class T>
	constexpr TVector2<bool> operator>=(TVector2<T> const &a,
					    TVector2<T> const &b) noexcept
	{
		return TVector2<bool>{a.x() >= b.x(),
				      a.y() >= b.y()};
	}

	template <class T>
	constexpr TVector2<bool> operator<=(TVector2<T> const &a,
					    TVector2<T> const &b) noexcept
	{
		return TVector2<bool>{a.x() <= b.x(),
				      a.y() <= b.y()};
	}

	template <class T>
	constexpr TVector2<bool> operator==(TVector2<T> const &a,
					    TVector2<T> const &b) noexcept
	{
		return TVector2<bool>{a.x() == b.x(),
				      a.y() == b.y()};
	}

	template <class T>
	constexpr TVector2<bool> operator!=(TVector2<T> const &a,
					    TVector2<T> const &b) noexcept
	{
		return TVector2<bool>{a.x() != b.x(),
				      a.y() != b.y()};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TVector2<bool> operator&&(TVector2<bool> const &a,
					    TVector2<bool> const &b) noexcept
	{
		return TVector2<bool>{a.x() && b.x(),
				      a.y() && b.y()};
	}

	constexpr TVector2<bool> operator||(TVector2<bool> const &a,
					    TVector2<bool> const &b) noexcept
	{
		return TVector2<bool>{a.x() || b.x(),
				      a.y() || b.y()};
	}

	constexpr bool all(TVector2<bool> const &a) noexcept
	{
		return a.x() &&
		       a.y();
	}

	constexpr bool any(TVector2<bool> const &a) noexcept
	{
		return a.x() ||
		       a.y();
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr TVector2<T> lerp(TVector2<T> const &a,
				   TVector2<T> const &b, T f) noexcept
	{
		return a + f * (b - a);
	}

	// ------------------------- SV arithmetic ------------------------- //

	template <class T>
	constexpr TVector2<T> operator*(T s, TVector2<T> const &v) noexcept
	{
		return TVector2<T>{s * v.x(),
				   s * v.y()};
	}
	template <class T>
	constexpr TVector2<T> operator/(T s, TVector2<T> const &v) noexcept
	{
		return TVector2<T>{s / v.x(),
				   s / v.y()};
	}

	// ------------------------- VS arithmetic ------------------------- //

	template <class T>
	constexpr TVector2<T> operator*(TVector2<T> const &v, T s) noexcept
	{
		return TVector2<T>{v.x() * s,
				   v.y() * s};
	}

	template <class T>
	constexpr TVector2<T> operator/(TVector2<T> const &v, T s) noexcept
	{
		return TVector2<T>{v.x() / s,
				   v.y() / s};
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr T sum(TVector2<T> const &a) noexcept
	{
		return a.x() + a.y();
	}

	// ----------------------------------------------------------------- //

	template <class U,
		  class T>
	constexpr TVector2<U> vector_cast(TVector2<T> const &src) noexcept
	{
		return TVector2<U>{static_cast<U>(src.data[0]),
				   static_cast<U>(src.data[1])};
	}
}

#if _MICRO_HAS_SSE_INTRINSICS && _MICRO_HAS_ARM_INTRINSICS
#	error "Cannot define both _MICRO_HAS_SSE_INTRINSICS and _MICRO_HAS_ARM_INTRINSICS"
#elif _MICRO_HAS_SSE_INTRINSICS
#	include "vector2_sse.inl"
#elif _MICRO_HAS_ARM_INTRINSICS
#	include "vector2_arm.inl"
#endif
#endif