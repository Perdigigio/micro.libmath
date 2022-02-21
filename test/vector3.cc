#include <algorithm>
#include <stdexcept>
#include <iostream>

#include <vector.hh>

using namespace micro::math;

constexpr float EPS = 4E-5f;

#define STRINGIFY(s) #s
#define STRINGIZE(s) STRINGIFY(s)

volatile Vector3 A = {-7.6548265723f, -9.3477503397f, -9.8338029653f};
volatile Vector3 B = {+0.5315814445f, +4.1306487267f, +2.4817865510f};
volatile Vector3 C = {-0.5119838287f, -6.0128490692f, -8.4552597952f};
volatile Vector3 I = {1, 0, 0};
volatile Vector3 J = {0, 1, 0};
volatile Vector3 K = {0, 0, 1};

void test_add();
void test_mul();
void test_sub();
void test_div();
void test_dot();
void test_len();
void test_crs();

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

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	try
	{
		test_add();
		test_mul();
		test_sub();
		test_div();
		test_dot();
		test_len();
		test_crs();
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
	auto a = const_cast<Vector3 const &>(A);
	auto b = const_cast<Vector3 const &>(B);
	auto c = const_cast<Vector3 const &>(C);

	if (!eq(a + Vector3{}, a) ||
	    !eq(b + Vector3{}, b) ||
	    !eq(c + Vector3{}, c) ||
	    !eq(Vector3{} + a, a) ||
	    !eq(Vector3{} + b, b) ||
	    !eq(Vector3{} + c, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a + (b + c), a + b + c) ||
	    !eq(b + (c + a), b + c + a) ||
	    !eq(c + (a + b), c + a + b))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a + (-a), Vector3{}) ||
	    !eq(b + (-b), Vector3{}) ||
	    !eq(c + (-c), Vector3{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_mul()
{
	auto a = const_cast<Vector3 const &>(A);
	auto b = const_cast<Vector3 const &>(B);
	auto c = const_cast<Vector3 const &>(C);

	if (!eq(a * Vector3{1.f, 1.f, 1.f}, a) ||
	    !eq(b * Vector3{1.f, 1.f, 1.f}, b) ||
	    !eq(c * Vector3{1.f, 1.f, 1.f}, c) ||
	    !eq(Vector3{1.f, 1.f, 1.f} * a, a) ||
	    !eq(Vector3{1.f, 1.f, 1.f} * b, b) ||
	    !eq(Vector3{1.f, 1.f, 1.f} * c, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a * Vector3{}, Vector3{}) ||
	    !eq(b * Vector3{}, Vector3{}) ||
	    !eq(c * Vector3{}, Vector3{}) ||
	    !eq(Vector3{} * a, Vector3{}) ||
	    !eq(Vector3{} * b, Vector3{}) ||
	    !eq(Vector3{} * c, Vector3{}) ||
	    !eq(a * 0.f, Vector3{}) ||
	    !eq(b * 0.f, Vector3{}) ||
	    !eq(c * 0.f, Vector3{}) ||
	    !eq(0.f * a, Vector3{}) ||
	    !eq(0.f * b, Vector3{}) ||
	    !eq(0.f * c, Vector3{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a * (b * c), a * b * c) ||
	    !eq(b * (c * a), b * c * a) ||
	    !eq(c * (a * b), c * a * b))
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
	auto a = const_cast<Vector3 const &>(A);
	auto b = const_cast<Vector3 const &>(B);
	auto c = const_cast<Vector3 const &>(C);

	if (!eq(a - Vector3{}, a) ||
	    !eq(b - Vector3{}, b) ||
	    !eq(c - Vector3{}, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a - (b - c), a - b + c) ||
	    !eq(b - (c - a), b - c + a) ||
	    !eq(c - (a - b), c - a + b))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(Vector3{} - a, -a) ||
	    !eq(Vector3{} - b, -b) ||
	    !eq(Vector3{} - c, -c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_div()
{
	auto a = const_cast<Vector3 const &>(A);
	auto b = const_cast<Vector3 const &>(B);
	auto c = const_cast<Vector3 const &>(C);

	if (!eq(a / Vector3{1.f, 1.f, 1.f}, a) ||
	    !eq(b / Vector3{1.f, 1.f, 1.f}, b) ||
	    !eq(c / Vector3{1.f, 1.f, 1.f}, c) ||
	    !eq(a / a, Vector3{1.f, 1.f, 1.f}) ||
	    !eq(b / b, Vector3{1.f, 1.f, 1.f}) ||
	    !eq(c / c, Vector3{1.f, 1.f, 1.f}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(Vector3{} / a, Vector3{}) ||
	    !eq(Vector3{} / b, Vector3{}) ||
	    !eq(Vector3{} / c, Vector3{}) ||
	    !eq(0.f / a, Vector3{}) ||
	    !eq(0.f / b, Vector3{}) ||
	    !eq(0.f / c, Vector3{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq((Vector3{1.f, 1.f, 1.f} / a) * a, Vector3{1.f, 1.f, 1.f}) ||
	    !eq((Vector3{1.f, 1.f, 1.f} / b) * b, Vector3{1.f, 1.f, 1.f}) ||
	    !eq((Vector3{1.f, 1.f, 1.f} / c) * c, Vector3{1.f, 1.f, 1.f}) ||
	    !eq(a * (Vector3{1.f, 1.f, 1.f} / a), Vector3{1.f, 1.f, 1.f}) ||
	    !eq(b * (Vector3{1.f, 1.f, 1.f} / b), Vector3{1.f, 1.f, 1.f}) ||
	    !eq(c * (Vector3{1.f, 1.f, 1.f} / c), Vector3{1.f, 1.f, 1.f}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq((b + c) / a, b / a + c / a) ||
	    !eq((c + a) / b, c / b + a / b) ||
	    !eq((a + b) / c, a / c + b / c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_dot()
{
	auto a = const_cast<Vector3 const &>(A);
	auto b = const_cast<Vector3 const &>(B);
	auto c = const_cast<Vector3 const &>(C);
	auto i = const_cast<Vector3 const &>(I);
	auto j = const_cast<Vector3 const &>(J);
	auto k = const_cast<Vector3 const &>(K);

	if (!eq(dot(a, b), a.x() * b.x() + a.y() * b.y() + a.z() * b.z()) ||
	    !eq(dot(b, c), b.x() * c.x() + b.y() * c.y() + b.z() * c.z()) ||
	    !eq(dot(c, a), c.x() * a.x() + c.y() * a.y() + c.z() * a.z()) ||
	    !eq(dot(i, j), 0) ||
	    !eq(dot(j, i), 0) ||
	    !eq(dot(i, k), 0) ||
	    !eq(dot(k, i), 0) ||
	    !eq(dot(j, k), 0) ||
	    !eq(dot(k, j), 0))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(dot(a, b), dot(b, a)) ||
	    !eq(dot(b, c), dot(c, b)) ||
	    !eq(dot(c, a), dot(a, c)))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	
	if (!eq(dot(a + b, c), dot(a, c) + dot(b, c)) ||
	    !eq(dot(b + c, a), dot(b, a) + dot(c, a)) ||
	    !eq(dot(c + a, b), dot(c, b) + dot(a, b)) ||
	    !eq(dot(a, b + c), dot(a, b) + dot(a, c)) ||
	    !eq(dot(b, c + a), dot(b, c) + dot(b, a)) ||
	    !eq(dot(c, a + b), dot(c, a) + dot(c, b)))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(dot(2.f * b, c), dot(b, 2.f * c)) ||
	    !eq(dot(2.f * c, a), dot(c, 2.f * a)) ||
	    !eq(dot(2.f * a, b), dot(a, 2.f * b)) ||
	    !eq(dot(2.f * b, c), 2.f * dot(b, c)) ||
	    !eq(dot(2.f * c, a), 2.f * dot(c, a)) ||
	    !eq(dot(2.f * a, b), 2.f * dot(a, b)) ||
	    !eq(dot(b, 2.f * c), 2.f * dot(b, c)) ||
	    !eq(dot(c, 2.f * a), 2.f * dot(c, a)) ||
	    !eq(dot(a, 2.f * b), 2.f * dot(a, b)))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_len()
{
	auto a = const_cast<Vector3 const &>(A);
	auto b = const_cast<Vector3 const &>(B);
	auto c = const_cast<Vector3 const &>(C);

	if (len(a) < 0 ||
	    len(b) < 0 ||
	    len(c) < 0)
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (len(a + b) > len(a) + len(b) ||
	    len(b + c) > len(b) + len(c) ||
	    len(c + a) > len(c) + len(a))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_crs()
{
	auto a = const_cast<Vector3 const &>(A);
	auto b = const_cast<Vector3 const &>(B);
	auto c = const_cast<Vector3 const &>(C);
	auto i = const_cast<Vector3 const &>(I);
	auto j = const_cast<Vector3 const &>(J);
	auto k = const_cast<Vector3 const &>(K);

	if (!eq(i ^ j, k) ||
	    !eq(j ^ k, i) ||
	    !eq(k ^ i, j))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq((a + b) ^ c, (a ^ c) + (b ^ c)) ||
	    !eq((b + c) ^ a, (b ^ a) + (c ^ a)) ||
	    !eq((c + a) ^ b, (c ^ b) + (a ^ b)) ||
	    !eq(a ^ (b + c), (a ^ b) + (a ^ c)) ||
	    !eq(b ^ (c + a), (b ^ c) + (b ^ a)) ||
	    !eq(c ^ (a + b), (c ^ a) + (c ^ b)))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}