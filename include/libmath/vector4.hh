#ifndef MICRO_LIBMATH_VECTOR4_HH__GUARD
#define MICRO_LIBMATH_VECTOR4_HH__GUARD

#include <type_traits>

namespace micro::math
{
	template <class T,
		  class F = std::enable_if_t<std::is_arithmetic_v<T>, int>>
	struct TVector4
	{
		typedef std::remove_reference_t<std::remove_cv_t<T>> type;

		//
		//

		constexpr TVector4(type x = {},
				   type y = {},
				   type z = {},
				   type w = {}) noexcept
		{
			data[0] = x;
			data[1] = y;
			data[2] = z;
			data[3] = w;
		}

		constexpr type &x() noexcept { return data[0]; }
		constexpr type &y() noexcept { return data[1]; }
		constexpr type &z() noexcept { return data[2]; }
		constexpr type &w() noexcept { return data[3]; }
		constexpr type const &x() const noexcept { return data[0]; }
		constexpr type const &y() const noexcept { return data[1]; }
		constexpr type const &z() const noexcept { return data[2]; }
		constexpr type const &w() const noexcept { return data[3]; }

		type data[4] = {};
	};

	// ------------------------- VV arithmetic ------------------------- //

	template <class T>
	constexpr TVector4<T> operator+(TVector4<T> const &a,
					TVector4<T> const &b) noexcept
	{
		return TVector4<T>{a.x() + b.x(),
				   a.y() + b.y(),
				   a.z() + b.z(),
				   a.w() + b.w()};
	}

	template <class T>
	constexpr TVector4<T> operator-(TVector4<T> const &a,
					TVector4<T> const &b) noexcept
	{
		return TVector4<T>{a.x() - b.x(),
				   a.y() - b.y(),
				   a.z() - b.z(),
				   a.w() - b.w()};
	}

	template <class T>
	constexpr TVector4<T> operator*(TVector4<T> const &a,
					TVector4<T> const &b) noexcept
	{
		return TVector4<T>{a.x() * b.x(),
				   a.y() * b.y(),
				   a.z() * b.z(),
				   a.w() * b.w()};
	}

	template <class T>
	constexpr TVector4<T> operator/(TVector4<T> const &a,
					TVector4<T> const &b) noexcept
	{
		return TVector4<T>{a.x() / b.x(),
				   a.y() / b.y(),
				   a.z() / b.z(),
				   a.w() / b.w()};
	}

	// ----------------------------- Unary ----------------------------- //

	template <class T>
	constexpr TVector4<T> operator+(TVector4<T> const &a) noexcept
	{
		return a;
	}

	template <class T>
	constexpr TVector4<T> operator-(TVector4<T> const &a) noexcept
	{
		return TVector4<T>{} - a;
	}

	// --------------------------- Relational -------------------------- //

	template <class T>
	constexpr TVector4<bool> operator<(TVector4<T> const &a,
					   TVector4<T> const &b) noexcept
	{
		return TVector4<bool>{a.x() < b.x(),
				      a.y() < b.y(),
				      a.z() < b.z(),
				      a.w() < b.w()};
	}

	template <class T>
	constexpr TVector4<bool> operator>(TVector4<T> const &a,
					   TVector4<T> const &b) noexcept
	{
		return TVector4<bool>{a.x() > b.x(),
				      a.y() > b.y(),
				      a.z() > b.z(),
				      a.w() > b.w()};
	}

	template <class T>
	constexpr TVector4<bool> operator>=(TVector4<T> const &a,
					    TVector4<T> const &b) noexcept
	{
		return TVector4<bool>{a.x() >= b.x(),
				      a.y() >= b.y(),
				      a.z() >= b.z(),
				      a.w() >= b.w()};
	}

	template <class T>
	constexpr TVector4<bool> operator<=(TVector4<T> const &a,
					    TVector4<T> const &b) noexcept
	{
		return TVector4<bool>{a.x() <= b.x(),
				      a.y() <= b.y(),
				      a.z() <= b.z(),
				      a.w() <= b.w()};
	}

	template <class T>
	constexpr TVector4<bool> operator==(TVector4<T> const &a,
					    TVector4<T> const &b) noexcept
	{
		return TVector4<bool>{a.x() == b.x(),
				      a.y() == b.y(),
				      a.z() == b.z(),
				      a.w() == b.w()};
	}

	template <class T>
	constexpr TVector4<bool> operator!=(TVector4<T> const &a,
					    TVector4<T> const &b) noexcept
	{
		return TVector4<bool>{a.x() != b.x(),
				      a.y() != b.y(),
				      a.z() != b.z(),
				      a.w() != b.w()};
	}

	// ---------------------------- Logical ---------------------------- //

	constexpr TVector4<bool> operator&&(TVector4<bool> const &a,
					    TVector4<bool> const &b) noexcept
	{
		return TVector4<bool>{a.x() && b.x(),
				      a.y() && b.y(),
				      a.z() && b.z(),
				      a.w() && b.w()};
	}

	constexpr TVector4<bool> operator||(TVector4<bool> const &a,
					    TVector4<bool> const &b) noexcept
	{
		return TVector4<bool>{a.x() || b.x(),
				      a.y() || b.y(),
				      a.z() || b.z(),
				      a.w() || b.w()};
	}

	constexpr bool all(TVector4<bool> const &a) noexcept
	{
		return a.x() &&
		       a.y() &&
		       a.z() &&
		       a.w();
	}

	constexpr bool any(TVector4<bool> const &a) noexcept
	{
		return a.x() ||
		       a.y() ||
		       a.z() ||
		       a.w();
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr TVector4<T> lerp(TVector4<T> const &a,
				   TVector4<T> const &b, T f) noexcept
	{
		return a + f * (b - a);
	}

	// ------------------------- SV arithmetic ------------------------- //

	template <class T>
	constexpr TVector4<T> operator*(T s, TVector4<T> const &v) noexcept
	{
		return TVector4<T>{s * v.x(),
				   s * v.y(),
				   s * v.z(),
				   s * v.w()};
	}
	template <class T>
	constexpr TVector4<T> operator/(T s, TVector4<T> const &v) noexcept
	{
		return TVector4<T>{s / v.x(),
				   s / v.y(),
				   s / v.z(),
				   s / v.w()};
	}

	// ------------------------- VS arithmetic ------------------------- //

	template <class T>
	constexpr TVector4<T> operator*(TVector4<T> const &v, T s) noexcept
	{
		return TVector4<T>{v.x() * s,
				   v.y() * s,
				   v.z() * s,
				   v.w() * s};
	}

	template <class T>
	constexpr TVector4<T> operator/(TVector4<T> const &v, T s) noexcept
	{
		return TVector4<T>{v.x() / s,
				   v.y() / s,
				   v.z() / s,
				   v.w() / s};
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr T sum(TVector4<T> const &a) noexcept
	{
		return a.x() + a.y() + a.z() + a.w();
	}

	// ----------------------------------------------------------------- //

	template <class U,
		  class T>
	constexpr TVector4<U> vector_cast(TVector4<T> const &src) noexcept
	{
		return TVector4<U>{static_cast<U>(src.data[0]),
				   static_cast<U>(src.data[1]),
				   static_cast<U>(src.data[2]),
				   static_cast<U>(src.data[3])};
	}
}

#if (defined(WITH_SSE_INTRINSICS) && defined(WITH_ARM_INTRINSICS)) || \
    (defined(WITH_AVX_INTRINSICS) && defined(WITH_ARM_INTRINSICS))
#	error "Cannot define both WITH_SSE_INTRINSICS or WITH_AVX_INTRINSICS and WITH_ARM_INTRINSICS"
#elif defined(WITH_SSE_INTRINSICS) || defined(WITH_AVX_INTRINSICS)
#	include "vector4_sse.inl"
#elif defined(WITH_ARM_INTRINSICS)
#	include "vector4_arm.inl"
#endif
#endif