#include <algorithm>
#include <stdexcept>
#include <iostream>

#include <libmath/matrix.hh>
#include <libmath/vector.hh>

#ifdef WITH_SSE_INTRINSICS
#	include <libmath/simd/sse.hh>
#endif

#ifdef WITH_ARM_INTRINSICS
#	include <libmath/simd/arm.hh>
#endif

using namespace micro::math;
using namespace micro::math::simd;

constexpr float EPS = 4E-5f;

#define STRINGIFY(s) #s
#define STRINGIZE(s) STRINGIFY(s)

volatile Matrix4x4 A = {-3.66351f, -3.06202f, -3.03546f, -1.30268f,
			+2.29979f, -4.47526f, +1.08899f, -0.98770f,
			+4.14048f, -3.73218f, +1.79211f, -0.17394f,
			+4.88430f, -2.29981f, +3.70524f, +3.74895f};
volatile Matrix4x4 B = {+4.83619f, +4.98539f, -0.17637f, +2.76125f,
			-2.97871f, -4.30863f, +2.03865f, -3.83468f,
			+1.05912f, +0.16407f, +1.38260f, +1.55988f,
			+3.06189f, -1.23629f, -2.06381f, -4.00321f};
volatile Matrix4x4 C = {-1.17285f, -1.59538f, +3.99850f, +2.76362f,
			+0.31930f, +0.17729f, +0.65535f, -0.26558f,
			+3.61047f, +4.70021f, -2.69203f, -3.92890f,
			-1.29313f, +0.05713f, -1.51551f, -3.73744f};

volatile Vector4 D = {+7.84204f, -5.10382f, +0.24293f, +3.03839f};
volatile Vector4 E = {-2.36227f, +6.21765f, -6.89348f, -5.64642f};

void test_add();
void test_mmm();
void test_mvm();
void test_sub();
void test_det();
void test_inv();

inline bool eq(Vector4 const &a,
	       Vector4 const &b) 
{
	auto A = std::max(std::abs(a.x()), std::abs(b.x()));
	auto B = std::max(std::abs(a.y()), std::abs(b.y()));
	auto C = std::max(std::abs(a.z()), std::abs(b.z()));
	auto D = std::max(std::abs(a.w()), std::abs(b.w()));
	auto x = std::abs(a.x() - b.x());
	auto y = std::abs(a.y() - b.y());
	auto z = std::abs(a.z() - b.z());
	auto w = std::abs(a.w() - b.w());

	return (x <= EPS || x <= A * EPS) &&
	       (y <= EPS || y <= B * EPS) &&
	       (z <= EPS || z <= C * EPS) &&
	       (w <= EPS || w <= D * EPS);
}

inline bool eq(Matrix4x4 const &a,
	       Matrix4x4 const &b) 
{
	return eq(a.data[0], b.data[0]) &&
	       eq(a.data[1], b.data[1]) &&
	       eq(a.data[2], b.data[2]) &&
	       eq(a.data[3], b.data[3]);
}

inline bool eq(float a,
	       float b) noexcept
{
	return std::abs(a - b) <= EPS ||
	       std::abs(a - b) <= EPS * std::max(std::abs(a), std::abs(b));
}

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	try
	{
		test_add();
		test_mmm();
		test_mvm();
		test_sub();
		test_det();
		test_inv();
	}
	catch (std::exception const &e)
	{
		std::cerr << "=============================== CAUGHT EXCEPTION ===============================" << std::endl;
		std::cerr << e.what() << std::endl;
		std::cerr << "================================================================================" << std::endl;

		return 1;
	}

	return 0;
}

void test_add() 
{
	auto a = const_cast<Matrix4x4 const &>(A);
	auto b = const_cast<Matrix4x4 const &>(B);
	auto c = const_cast<Matrix4x4 const &>(C);

	if (!eq(a + Matrix4x4{}, a) ||
	    !eq(b + Matrix4x4{}, b) ||
	    !eq(c + Matrix4x4{}, c) ||
	    !eq(Matrix4x4{} + a, a) ||
	    !eq(Matrix4x4{} + b, b) ||
	    !eq(Matrix4x4{} + c, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a + (b + c), a + b + c) ||
	    !eq(b + (c + a), b + c + a) ||
	    !eq(c + (a + b), c + a + b))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
/**
	if (!eq(a + (-a), Matrix4x4{}) ||
	    !eq(b + (-b), Matrix4x4{}) ||
	    !eq(c + (-c), Matrix4x4{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
**/
}

void test_mmm()
{
	auto a = const_cast<Matrix4x4 const &>(A);
	auto b = const_cast<Matrix4x4 const &>(B);
	auto c = const_cast<Matrix4x4 const &>(C);

	if (!eq(a * identity4x4<float>(), a) ||
	    !eq(b * identity4x4<float>(), b) ||
	    !eq(c * identity4x4<float>(), c) ||
	    !eq(identity4x4<float>() * a, a) ||
	    !eq(identity4x4<float>() * b, b) ||
	    !eq(identity4x4<float>() * c, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a * Matrix4x4{}, Matrix4x4{}) ||
	    !eq(b * Matrix4x4{}, Matrix4x4{}) ||
	    !eq(c * Matrix4x4{}, Matrix4x4{}) ||
	    !eq(Matrix4x4{} * a, Matrix4x4{}) ||
	    !eq(Matrix4x4{} * b, Matrix4x4{}) ||
	    !eq(Matrix4x4{} * c, Matrix4x4{}) ||
	    !eq(a * 0.f, Matrix4x4{}) ||
	    !eq(b * 0.f, Matrix4x4{}) ||
	    !eq(c * 0.f, Matrix4x4{}) ||
	    !eq(0.f * a, Matrix4x4{}) ||
	    !eq(0.f * b, Matrix4x4{}) ||
	    !eq(0.f * c, Matrix4x4{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a * (b * c), (a * b) * c) ||
	    !eq(b * (c * a), (b * c) * a) ||
	    !eq(c * (a * b), (c * a) * b))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a * (b + c), a * b + a * c) ||
	    !eq(b * (c + a), b * c + b * a) ||
	    !eq(c * (a + b), c * a + c * b))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_sub()
{
	auto a = const_cast<Matrix4x4 const &>(A);
	auto b = const_cast<Matrix4x4 const &>(B);
	auto c = const_cast<Matrix4x4 const &>(C);

	if (!eq(a - Matrix4x4{}, a) ||
	    !eq(b - Matrix4x4{}, b) ||
	    !eq(c - Matrix4x4{}, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a - (b - c), a - b + c) ||
	    !eq(b - (c - a), b - c + a) ||
	    !eq(c - (a - b), c - a + b))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

/**
	if (!eq(Vector2{} - a, -a) ||
	    !eq(Vector2{} - b, -b) ||
	    !eq(Vector2{} - c, -c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
**/
}

void test_mvm()
{
	auto a = const_cast<Matrix4x4 const &>(A);
	auto b = const_cast<Matrix4x4 const &>(B);
	auto c = const_cast<Matrix4x4 const &>(C);

	auto d = const_cast<Vector4 const &>(D);
	auto e = const_cast<Vector4 const &>(E);

	if (!eq(identity4x4<float>() * d, d) ||
	    !eq(identity4x4<float>() * e, e))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(Matrix4x4{} * d, Vector4{}) ||
	    !eq(Matrix4x4{} * e, Vector4{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq((a * b) * d, a * (b * d)) ||
	    !eq((a * b) * e, a * (b * e)))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a * (d + e), a * d + a * e) ||
	    !eq(b * (d + e), b * d + b * e) ||
	    !eq(c * (d + e), c * d + c * e))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_det()
{
	auto a = const_cast<Matrix4x4 const &>(A);
	auto b = const_cast<Matrix4x4 const &>(B);
	auto c = const_cast<Matrix4x4 const &>(C);

	if (!eq(det(a * b), det(a) * det(b)) ||
	    !eq(det(b * c), det(b) * det(c)) ||
	    !eq(det(c * a), det(c) * det(a)))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(det(transpose(a)), det(a)) ||
	    !eq(det(transpose(b)), det(b)) ||
	    !eq(det(transpose(c)), det(c)))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_inv()
{
	auto a = const_cast<Matrix4x4 const &>(A);
	auto b = const_cast<Matrix4x4 const &>(B);
	auto c = const_cast<Matrix4x4 const &>(C);

	if (eq(det(a), 0) ||
	    eq(det(b), 0) || 
	    eq(det(c), 0))
	{
		std::cerr << "One of the matrices among a, b or c is singular, cannot test" << std::endl;
	}
	else
	{
		if (!eq(inverse(a) * a, identity4x4<float>()) ||
		    !eq(inverse(b) * b, identity4x4<float>()) ||
		    !eq(inverse(c) * c, identity4x4<float>()))
		{
			throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		}

		if (!eq(det(inverse(a)), 1 / det(a)) ||
		    !eq(det(inverse(b)), 1 / det(b)) ||
		    !eq(det(inverse(c)), 1 / det(c)))
		{
			throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		}

		if (!eq(inverse(3.f * a), inverse(a) / 3.f) ||
		    !eq(inverse(3.f * b), inverse(b) / 3.f) ||
		    !eq(inverse(3.f * c), inverse(c) / 3.f))
		{
			throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		}

		if (!eq(inverse(transpose(a)), transpose(inverse(a))) ||
		    !eq(inverse(transpose(b)), transpose(inverse(b))) ||
		    !eq(inverse(transpose(c)), transpose(inverse(c))))
		{
			throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		}

		if (!eq(inverse(a * b), inverse(b) * inverse(a)) ||
		    !eq(inverse(b * c), inverse(c) * inverse(b)) ||
		    !eq(inverse(c * a), inverse(a) * inverse(c)))
		{
			throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
		}
	}
}