#include <algorithm>
#include <stdexcept>
#include <iostream>

#include <libmath/matrix.hh>
#include <libmath/vector.hh>

using namespace micro::math;

constexpr float EPS = 4E-5f;

#define STRINGIFY(s) #s
#define STRINGIZE(s) STRINGIFY(s)

volatile Matrix3x3 A = {+4.75825f, -3.16787f, +0.64979f,
			+0.36652f, +3.27509f, +4.73621f,
			-4.61847f, -4.58657f, +0.10632f};
volatile Matrix3x3 B = {-1.58074f, +4.76119f, +2.40566f,
			+3.91074f, -3.99176f, -4.34068f,
			+4.75782f, -3.12522f, -1.45449f};
volatile Matrix3x3 C = {-4.26499f, +4.07956f, -1.06460f,
			-2.61151f, +2.76133f, +1.95629f,
			-4.50569f, +1.04214f, -3.04545f};

volatile Vector3 D = {-7.99579f, -6.70711f, +3.67811f};
volatile Vector3 E = {+1.44233f, +8.45960f, -4.89515f};

void test_add();
void test_mmm();
void test_mvm();
void test_sub();
void test_det();
void test_inv();

inline bool eq(Vector3 const &a,
	       Vector3 const &b) 
{
	auto A = std::max(std::abs(a.x()), std::abs(b.x()));
	auto B = std::max(std::abs(a.y()), std::abs(b.y()));
	auto C = std::max(std::abs(a.z()), std::abs(b.z()));
	auto x = std::abs(a.x() - b.x());
	auto y = std::abs(a.y() - b.y());
	auto z = std::abs(a.z() - b.z());

	return (x <= EPS || x <= A * EPS) &&
	       (y <= EPS || y <= B * EPS) &&
	       (z <= EPS || z <= C * EPS);
}

inline bool eq(Matrix3x3 const &a,
	       Matrix3x3 const &b) 
{
	return eq(a.data[0], b.data[0]) &&
	       eq(a.data[1], b.data[1]) &&
	       eq(a.data[2], b.data[2]);
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
	auto a = const_cast<Matrix3x3 const &>(A);
	auto b = const_cast<Matrix3x3 const &>(B);
	auto c = const_cast<Matrix3x3 const &>(C);

	if (!eq(a + Matrix3x3{}, a) ||
	    !eq(b + Matrix3x3{}, b) ||
	    !eq(c + Matrix3x3{}, c) ||
	    !eq(Matrix3x3{} + a, a) ||
	    !eq(Matrix3x3{} + b, b) ||
	    !eq(Matrix3x3{} + c, c))
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
	if (!eq(a + (-a), Matrix3x3{}) ||
	    !eq(b + (-b), Matrix3x3{}) ||
	    !eq(c + (-c), Matrix3x3{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
**/
}

void test_mmm()
{
	auto a = const_cast<Matrix3x3 const &>(A);
	auto b = const_cast<Matrix3x3 const &>(B);
	auto c = const_cast<Matrix3x3 const &>(C);

	if (!eq(a * identity3x3<float>(), a) ||
	    !eq(b * identity3x3<float>(), b) ||
	    !eq(c * identity3x3<float>(), c) ||
	    !eq(identity3x3<float>() * a, a) ||
	    !eq(identity3x3<float>() * b, b) ||
	    !eq(identity3x3<float>() * c, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a * Matrix3x3{}, Matrix3x3{}) ||
	    !eq(b * Matrix3x3{}, Matrix3x3{}) ||
	    !eq(c * Matrix3x3{}, Matrix3x3{}) ||
	    !eq(Matrix3x3{} * a, Matrix3x3{}) ||
	    !eq(Matrix3x3{} * b, Matrix3x3{}) ||
	    !eq(Matrix3x3{} * c, Matrix3x3{}) ||
	    !eq(a * 0.f, Matrix3x3{}) ||
	    !eq(b * 0.f, Matrix3x3{}) ||
	    !eq(c * 0.f, Matrix3x3{}) ||
	    !eq(0.f * a, Matrix3x3{}) ||
	    !eq(0.f * b, Matrix3x3{}) ||
	    !eq(0.f * c, Matrix3x3{}))
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
	auto a = const_cast<Matrix3x3 const &>(A);
	auto b = const_cast<Matrix3x3 const &>(B);
	auto c = const_cast<Matrix3x3 const &>(C);

	if (!eq(a - Matrix3x3{}, a) ||
	    !eq(b - Matrix3x3{}, b) ||
	    !eq(c - Matrix3x3{}, c))
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
	auto a = const_cast<Matrix3x3 const &>(A);
	auto b = const_cast<Matrix3x3 const &>(B);
	auto c = const_cast<Matrix3x3 const &>(C);

	auto d = const_cast<Vector3 const &>(D);
	auto e = const_cast<Vector3 const &>(E);

	if (!eq(identity3x3<float>() * d, d) ||
	    !eq(identity3x3<float>() * e, e))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(Matrix3x3{} * d, Vector3{}) ||
	    !eq(Matrix3x3{} * e, Vector3{}))
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
	auto a = const_cast<Matrix3x3 const &>(A);
	auto b = const_cast<Matrix3x3 const &>(B);
	auto c = const_cast<Matrix3x3 const &>(C);

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
	auto a = const_cast<Matrix3x3 const &>(A);
	auto b = const_cast<Matrix3x3 const &>(B);
	auto c = const_cast<Matrix3x3 const &>(C);
	
	if (eq(det(a), 0) ||
	    eq(det(b), 0) || 
	    eq(det(c), 0))
	{
		std::cerr << "One of the matrices among a, b or c is singular, cannot test" << std::endl;
	}
	else
	{
		if (!eq(inverse(a) * a, identity3x3<float>()) ||
		    !eq(inverse(b) * b, identity3x3<float>()) ||
		    !eq(inverse(c) * c, identity3x3<float>()))
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