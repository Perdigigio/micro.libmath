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

volatile Matrix2x2 A = {+8.76085f, +7.25175f, +7.52586f, +7.35635f};
volatile Matrix2x2 B = {-2.96210f, +7.56585f, +6.22330f, +2.45801f};
volatile Matrix2x2 C = {-1.57743f, +6.25832f, +3.77043f, +6.71761f};

volatile Vector2 D = {-3.4071929039f, +8.3920351995f};
volatile Vector2 E = {+1.5835732239f, -4.3206156194f};

void test_add();
void test_mmm();
void test_mvm();
void test_sub();
void test_det();
void test_inv();

inline bool eq(Vector2 const &a,
	       Vector2 const &b) 
{
	auto A = std::max(std::abs(a.x()), std::abs(b.x()));
	auto B = std::max(std::abs(a.y()), std::abs(b.y()));
	auto x = std::abs(a.x() - b.x());
	auto y = std::abs(a.y() - b.y());

	return (x <= EPS || x <= A * EPS) &&
	       (y <= EPS || y <= B * EPS);
}

inline bool eq(Matrix2x2 const &a,
	       Matrix2x2 const &b) 
{
	return eq(a.data[0], b.data[0]) &&
	       eq(a.data[1], b.data[1]);
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
	auto a = const_cast<Matrix2x2 const &>(A);
	auto b = const_cast<Matrix2x2 const &>(B);
	auto c = const_cast<Matrix2x2 const &>(C);

	if (!eq(a + Matrix2x2{}, a) ||
	    !eq(b + Matrix2x2{}, b) ||
	    !eq(c + Matrix2x2{}, c) ||
	    !eq(Matrix2x2{} + a, a) ||
	    !eq(Matrix2x2{} + b, b) ||
	    !eq(Matrix2x2{} + c, c))
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
	if (!eq(a + (-a), Matrix2x2{}) ||
	    !eq(b + (-b), Matrix2x2{}) ||
	    !eq(c + (-c), Matrix2x2{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
**/
}

void test_mmm()
{
	auto a = const_cast<Matrix2x2 const &>(A);
	auto b = const_cast<Matrix2x2 const &>(B);
	auto c = const_cast<Matrix2x2 const &>(C);

	if (!eq(a * identity2x2<float>(), a) ||
	    !eq(b * identity2x2<float>(), b) ||
	    !eq(c * identity2x2<float>(), c) ||
	    !eq(identity2x2<float>() * a, a) ||
	    !eq(identity2x2<float>() * b, b) ||
	    !eq(identity2x2<float>() * c, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a * Matrix2x2{}, Matrix2x2{}) ||
	    !eq(b * Matrix2x2{}, Matrix2x2{}) ||
	    !eq(c * Matrix2x2{}, Matrix2x2{}) ||
	    !eq(Matrix2x2{} * a, Matrix2x2{}) ||
	    !eq(Matrix2x2{} * b, Matrix2x2{}) ||
	    !eq(Matrix2x2{} * c, Matrix2x2{}) ||
	    !eq(a * 0.f, Matrix2x2{}) ||
	    !eq(b * 0.f, Matrix2x2{}) ||
	    !eq(c * 0.f, Matrix2x2{}) ||
	    !eq(0.f * a, Matrix2x2{}) ||
	    !eq(0.f * b, Matrix2x2{}) ||
	    !eq(0.f * c, Matrix2x2{}))
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
	auto a = const_cast<Matrix2x2 const &>(A);
	auto b = const_cast<Matrix2x2 const &>(B);
	auto c = const_cast<Matrix2x2 const &>(C);

	if (!eq(a - Matrix2x2{}, a) ||
	    !eq(b - Matrix2x2{}, b) ||
	    !eq(c - Matrix2x2{}, c))
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
	auto a = const_cast<Matrix2x2 const &>(A);
	auto b = const_cast<Matrix2x2 const &>(B);
	auto c = const_cast<Matrix2x2 const &>(C);

	auto d = const_cast<Vector2 const &>(D);
	auto e = const_cast<Vector2 const &>(E);

	if (!eq(identity2x2<float>() * d, d) ||
	    !eq(identity2x2<float>() * e, e))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(Matrix2x2{} * d, Vector2{}) ||
	    !eq(Matrix2x2{} * e, Vector2{}))
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
	auto a = const_cast<Matrix2x2 const &>(A);
	auto b = const_cast<Matrix2x2 const &>(B);
	auto c = const_cast<Matrix2x2 const &>(C);

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
	auto a = const_cast<Matrix2x2 const &>(A);
	auto b = const_cast<Matrix2x2 const &>(B);
	auto c = const_cast<Matrix2x2 const &>(C);

	if (eq(det(a), 0) ||
	    eq(det(b), 0) || 
	    eq(det(c), 0))
	{
		std::cerr << "One of the matrices among a, b or c is singular, cannot test" << std::endl;
	}
	else
	{
		if (!eq(inverse(a) * a, identity2x2<float>()) ||
		    !eq(inverse(b) * b, identity2x2<float>()) ||
		    !eq(inverse(c) * c, identity2x2<float>()))
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