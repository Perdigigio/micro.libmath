#ifndef MICRO_LIBMATH_VECTOR_HH__GUARD
#define MICRO_LIBMATH_VECTOR_HH__GUARD

#include "vector2.hh"
#include "vector3.hh"
#include "vector4.hh"

#include <cmath>

namespace micro::math
{
	using std::sqrt;

	template <class V>
	constexpr auto is_vector_v = std::integral_constant<bool,
							    std::is_same_v<TVector2<typename V::type>, std::remove_reference_t<std::remove_cv_t<V>>> ||
							    std::is_same_v<TVector3<typename V::type>, std::remove_reference_t<std::remove_cv_t<V>>> ||
							    std::is_same_v<TVector4<typename V::type>, std::remove_reference_t<std::remove_cv_t<V>>>>::value;

	using Vector2 = TVector2<float>;
	using Vector3 = TVector3<float>;
	using Vector4 = TVector4<float>;

	// ----------------------------------------------------------------- //

	template<class V>
	inline auto dot(V const &a,
			V const &b) noexcept -> typename V::type
	{
		return sum(a * b);
	}

	template<class V>
	inline auto len(V const &a) noexcept -> typename V::type
	{
		return sqrt(sum(a * a));
	}

	template<class V>
	inline auto normalize(V const &a) noexcept -> V
	{
		return a / len(a);
	}

	template <class... T>
	inline auto rmul(T &&...m) noexcept { return (std::forward<T>(m) * ...); }
	template <class... T>
	inline auto radd(T &&...m) noexcept { return (std::forward<T>(m) + ...); }
	template <class... T>
	inline auto rsub(T &&...m) noexcept { return (std::forward<T>(m) - ...); }
}

namespace micro::math::simd
{
	// Empty
	//
}

#endif