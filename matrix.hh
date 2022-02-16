#ifndef MICRO_LIBMATH_MATRIX_HH__GUARD
#define MICRO_LIBMATH_MATRIX_HH__GUARD

#include "matrix2x2.hh"
#include "matrix2x3.hh"
#include "matrix2x4.hh"
#include "matrix3x2.hh"
#include "matrix3x3.hh"
#include "matrix3x4.hh"
#include "matrix4x2.hh"
#include "matrix4x3.hh"
#include "matrix4x4.hh"

#include "matrix2xN_transform.hh"
#include "matrix3xN_transform.hh"
#include "matrix4xN_transform.hh"

namespace micro::math
{
	template <class M>
	constexpr auto is_matrix_v = std::integral_constant<bool,
							    std::is_same_v<TMatrix2x2<typename M::type>, std::remove_reference_t<std::remove_cv_t<M>>> ||
							    std::is_same_v<TMatrix2x3<typename M::type>, std::remove_reference_t<std::remove_cv_t<M>>> ||
							    std::is_same_v<TMatrix2x4<typename M::type>, std::remove_reference_t<std::remove_cv_t<M>>> ||
							    std::is_same_v<TMatrix3x2<typename M::type>, std::remove_reference_t<std::remove_cv_t<M>>> ||
							    std::is_same_v<TMatrix3x3<typename M::type>, std::remove_reference_t<std::remove_cv_t<M>>> ||
							    std::is_same_v<TMatrix3x4<typename M::type>, std::remove_reference_t<std::remove_cv_t<M>>> ||
							    std::is_same_v<TMatrix4x2<typename M::type>, std::remove_reference_t<std::remove_cv_t<M>>> ||
							    std::is_same_v<TMatrix4x3<typename M::type>, std::remove_reference_t<std::remove_cv_t<M>>> ||
							    std::is_same_v<TMatrix4x4<typename M::type>, std::remove_reference_t<std::remove_cv_t<M>>>>::value;

	using Matrix2x2 = TMatrix2x2<float>;
	using Matrix2x3 = TMatrix2x3<float>;
	using Matrix2x4 = TMatrix2x4<float>;
	using Matrix3x2 = TMatrix3x2<float>;
	using Matrix3x3 = TMatrix3x3<float>;
	using Matrix3x4 = TMatrix3x4<float>;
	using Matrix4x2 = TMatrix4x2<float>;
	using Matrix4x3 = TMatrix4x3<float>;
	using Matrix4x4 = TMatrix4x4<float>;

	// ----------------------------- 2 x 2 ----------------------------- //

	template <class T>
	constexpr TMatrix2x3<T> operator*(TMatrix2x2<T> const &l,
					  TMatrix2x3<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._11() * r.data[0];
		auto const D = l._12() * r.data[1];

		return TMatrix2x3<T>{A + B,
				     C + D};
	}

	template <class T>
	constexpr TMatrix2x4<T> operator*(TMatrix2x2<T> const &l,
					  TMatrix2x4<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._11() * r.data[0];
		auto const D = l._12() * r.data[1];

		return TMatrix2x4<T>{A + B,
				     C + D};
	}

	// ----------------------------- 2 x 3 ----------------------------- //

	template <class T>
	constexpr TMatrix2x2<T> operator*(TMatrix2x3<T> const &l,
					  TMatrix3x2<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];

		return TMatrix2x2<T>{A + B + C,
				     D + E + F};
	}

	template <class T>
	constexpr TMatrix2x3<T> operator*(TMatrix2x3<T> const &l,
					  TMatrix3x3<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];

		return TMatrix2x3<T>{A + B + C,
				     D + E + F};
	}

	template <class T>
	constexpr TMatrix2x4<T> operator*(TMatrix2x3<T> const &l,
					  TMatrix3x4<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];

		return TMatrix2x4<T>{A + B + C,
				     D + E + F};
	}

	// ----------------------------- 2 x 4 ----------------------------- //

	template <class T>
	constexpr TMatrix2x2<T> operator*(TMatrix2x4<T> const &l,
					  TMatrix4x2<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];

		return TMatrix2x2<T>{A + B + C,
				     D + E + F};
	}

	template <class T>
	constexpr TMatrix2x3<T> operator*(TMatrix2x4<T> const &l,
					  TMatrix4x3<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];

		return TMatrix2x2<T>{A + B + C,
				     D + E + F};
	}

	template <class T>
	constexpr TMatrix2x4<T> operator*(TMatrix2x4<T> const &l,
					  TMatrix4x4<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];

		return TMatrix2x2<T>{A + B + C,
				     D + E + F};
	}

	// ----------------------------- 3 x 2 ----------------------------- //

	template <class T>
	constexpr TMatrix3x2<T> operator*(TMatrix3x2<T> const &l,
					  TMatrix2x2<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._21() * r.data[0];
		auto const D = l._22() * r.data[1];
		auto const E = l._31() * r.data[0];
		auto const F = l._32() * r.data[1];

		return TMatrix3x2<T>{A + B,
				     C + D,
				     E + F};
	}

	template <class T>
	constexpr TMatrix3x3<T> operator*(TMatrix3x2<T> const &l,
					  TMatrix2x3<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._21() * r.data[0];
		auto const D = l._22() * r.data[1];
		auto const E = l._31() * r.data[0];
		auto const F = l._32() * r.data[1];

		return TMatrix3x3<T>{A + B,
				     C + D,
				     E + F};
	}

	template <class T>
	constexpr TMatrix3x4<T> operator*(TMatrix3x2<T> const &l,
					  TMatrix2x4<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._21() * r.data[0];
		auto const D = l._22() * r.data[1];
		auto const E = l._31() * r.data[0];
		auto const F = l._32() * r.data[1];

		return TMatrix3x4<T>{A + B,
				     C + D,
				     E + F};
	}

	// ----------------------------- 3 x 3 ----------------------------- //

	template <class T>
	constexpr TMatrix3x2<T> operator*(TMatrix3x3<T> const &l,
					  TMatrix3x2<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];
		auto const G = l._31() * r.data[0];
		auto const H = l._32() * r.data[1];
		auto const I = l._33() * r.data[2];

		return TMatrix3x2<T>{A + B + C,
				     D + E + F,
				     G + H + I};
	}

	template <class T>
	constexpr TMatrix3x4<T> operator*(TMatrix3x3<T> const &l,
					  TMatrix3x4<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];
		auto const G = l._31() * r.data[0];
		auto const H = l._32() * r.data[1];
		auto const I = l._33() * r.data[2];

		return TMatrix3x2<T>{A + B + C,
				     D + E + F,
				     G + H + I};
	}

	// ----------------------------- 3 x 4 ----------------------------- //

	template <class T>
	constexpr TMatrix3x2<T> operator*(TMatrix3x4<T> const &l,
					  TMatrix4x2<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._14() * r.data[3];
		auto const E = l._21() * r.data[0];
		auto const F = l._22() * r.data[1];
		auto const G = l._23() * r.data[2];
		auto const H = l._24() * r.data[3];
		auto const I = l._31() * r.data[0];
		auto const J = l._32() * r.data[1];
		auto const K = l._33() * r.data[2];
		auto const L = l._34() * r.data[3];

		return TMatrix3x2<T>{A + B + C + D,
				     E + F + G + H,
				     I + J + K + L};
	}

	template <class T>
	constexpr TMatrix3x3<T> operator*(TMatrix3x4<T> const &l,
					  TMatrix4x3<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._14() * r.data[3];
		auto const E = l._21() * r.data[0];
		auto const F = l._22() * r.data[1];
		auto const G = l._23() * r.data[2];
		auto const H = l._24() * r.data[3];
		auto const I = l._31() * r.data[0];
		auto const J = l._32() * r.data[1];
		auto const K = l._33() * r.data[2];
		auto const L = l._34() * r.data[3];

		return TMatrix3x3<T>{A + B + C + D,
				     E + F + G + H,
				     I + J + K + L};
	}

	template <class T>
	constexpr TMatrix3x4<T> operator*(TMatrix3x4<T> const &l,
					  TMatrix4x4<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._14() * r.data[3];
		auto const E = l._21() * r.data[0];
		auto const F = l._22() * r.data[1];
		auto const G = l._23() * r.data[2];
		auto const H = l._24() * r.data[3];
		auto const I = l._31() * r.data[0];
		auto const J = l._32() * r.data[1];
		auto const K = l._33() * r.data[2];
		auto const L = l._34() * r.data[3];

		return TMatrix3x4<T>{A + B + C + D,
				     E + F + G + H,
				     I + J + K + L};
	}

	// ----------------------------- 4 x 2 ----------------------------- //

	template <class T>
	constexpr TMatrix4x2<T> operator*(TMatrix4x2<T> const &l,
					  TMatrix2x2<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._21() * r.data[0];
		auto const D = l._22() * r.data[1];
		auto const E = l._31() * r.data[0];
		auto const F = l._32() * r.data[1];
		auto const G = l._41() * r.data[0];
		auto const H = l._42() * r.data[1];

		return TMatrix4x2<T>{A + B,
				     C + D,
				     E + F,
				     G + H};
	}

	template <class T>
	constexpr TMatrix4x3<T> operator*(TMatrix4x2<T> const &l,
					  TMatrix2x3<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._21() * r.data[0];
		auto const D = l._22() * r.data[1];
		auto const E = l._31() * r.data[0];
		auto const F = l._32() * r.data[1];
		auto const G = l._41() * r.data[0];
		auto const H = l._42() * r.data[1];

		return TMatrix4x3<T>{A + B,
				     C + D,
				     E + F,
				     G + H};
	}

	template <class T>
	constexpr TMatrix4x4<T> operator*(TMatrix4x2<T> const &l,
					  TMatrix2x4<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._21() * r.data[0];
		auto const D = l._22() * r.data[1];
		auto const E = l._31() * r.data[0];
		auto const F = l._32() * r.data[1];
		auto const G = l._41() * r.data[0];
		auto const H = l._42() * r.data[1];

		return TMatrix4x4<T>{A + B,
				     C + D,
				     E + F,
				     G + H};
	}

	// ----------------------------- 4 x 3 ----------------------------- //

	template <class T>
	constexpr TMatrix4x2<T> operator*(TMatrix4x3<T> const &l,
					  TMatrix3x2<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];
		auto const G = l._31() * r.data[0];
		auto const H = l._32() * r.data[1];
		auto const I = l._33() * r.data[2];
		auto const J = l._41() * r.data[0];
		auto const K = l._42() * r.data[1];
		auto const L = l._43() * r.data[2];

		return TMatrix4x2<T>{A + B + C,
				     D + E + F,
				     G + H + I,
				     J + K + L};
	}

	template <class T>
	constexpr TMatrix4x3<T> operator*(TMatrix4x3<T> const &l,
					  TMatrix3x3<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];
		auto const G = l._31() * r.data[0];
		auto const H = l._32() * r.data[1];
		auto const I = l._33() * r.data[2];
		auto const J = l._41() * r.data[0];
		auto const K = l._42() * r.data[1];
		auto const L = l._43() * r.data[2];

		return TMatrix4x3<T>{A + B + C,
				     D + E + F,
				     G + H + I,
				     J + K + L};
	}

	template <class T>
	constexpr TMatrix4x4<T> operator*(TMatrix4x3<T> const &l,
					  TMatrix3x4<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._21() * r.data[0];
		auto const E = l._22() * r.data[1];
		auto const F = l._23() * r.data[2];
		auto const G = l._31() * r.data[0];
		auto const H = l._32() * r.data[1];
		auto const I = l._33() * r.data[2];
		auto const J = l._41() * r.data[0];
		auto const K = l._42() * r.data[1];
		auto const L = l._43() * r.data[2];

		return TMatrix4x4<T>{A + B + C,
				     D + E + F,
				     G + H + I,
				     J + K + L};
	}

	// ----------------------------- 4 x 4 ----------------------------- //

	template <class T>
	constexpr TMatrix4x2<T> operator*(TMatrix4x4<T> const &l,
					  TMatrix4x2<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._14() * r.data[3];
		auto const E = l._21() * r.data[0];
		auto const F = l._22() * r.data[1];
		auto const G = l._23() * r.data[2];
		auto const H = l._24() * r.data[3];
		auto const I = l._31() * r.data[0];
		auto const J = l._32() * r.data[1];
		auto const K = l._33() * r.data[2];
		auto const L = l._34() * r.data[3];
		auto const M = l._41() * r.data[0];
		auto const N = l._42() * r.data[1];
		auto const O = l._43() * r.data[2];
		auto const P = l._44() * r.data[3];

		return TMatrix4x2<T>{A + B + C + D,
				     E + F + G + H,
				     I + J + K + L,
				     M + N + O + P};
	}

	template <class T>
	constexpr TMatrix4x3<T> operator*(TMatrix4x4<T> const &l,
					  TMatrix4x3<T> const &r) noexcept
	{
		auto const A = l._11() * r.data[0];
		auto const B = l._12() * r.data[1];
		auto const C = l._13() * r.data[2];
		auto const D = l._14() * r.data[3];
		auto const E = l._21() * r.data[0];
		auto const F = l._22() * r.data[1];
		auto const G = l._23() * r.data[2];
		auto const H = l._24() * r.data[3];
		auto const I = l._31() * r.data[0];
		auto const J = l._32() * r.data[1];
		auto const K = l._33() * r.data[2];
		auto const L = l._34() * r.data[3];
		auto const M = l._41() * r.data[0];
		auto const N = l._42() * r.data[1];
		auto const O = l._43() * r.data[2];
		auto const P = l._44() * r.data[3];

		return TMatrix4x3<T>{A + B + C + D,
				     E + F + G + H,
				     I + J + K + L,
				     M + N + O + P};
	}

	// ----------------------------------------------------------------- //

	template <class T>
	constexpr TMatrix3x2<T> transpose(TMatrix2x3<T> const &m) noexcept
	{
		return TMatrix3x2<T>{m._11(), m._21(),
				     m._12(), m._22(),
				     m._13(), m._23()};
	}

	template <class T>
	constexpr TMatrix4x2<T> transpose(TMatrix2x4<T> const &m) noexcept
	{
		return TMatrix4x2<T>{m._11(), m._21(),
				     m._12(), m._22(),
				     m._13(), m._23(),
				     m._14(), m._24()};
	}

	template <class T>
	constexpr TMatrix2x3<T> transpose(TMatrix3x2<T> const &m) noexcept
	{
		return TMatrix2x3<T>{m._11(), m._21(), m._31(),
				     m._12(), m._22(), m._32()};
	}

	template <class T>
	constexpr TMatrix4x3<T> transpose(TMatrix3x4<T> const &m) noexcept
	{
		return TMatrix4x3<T>{m._11(), m._21(), m._31(),
				     m._12(), m._22(), m._32(),
				     m._13(), m._23(), m._33(),
				     m._14(), m._24(), m._34()};
	}

	template <class T>
	constexpr TMatrix2x4<T> transpose(TMatrix4x2<T> const &m) noexcept
	{
		return TMatrix2x4<T>{m._11(), m._21(), m._31(), m._41(),
				     m._12(), m._22(), m._32(), m._42()};
	}

	template <class T>
	constexpr TMatrix3x4<T> transpose(TMatrix4x3<T> const &m) noexcept
	{
		return TMatrix3x4<T>{m._11(), m._21(), m._31(), m._41(),
				     m._12(), m._22(), m._32(), m._42(),
				     m._13(), m._23(), m._33(), m._43()};
	}
}

#endif