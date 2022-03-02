#include <algorithm>
#include <stdexcept>
#include <iostream>

#include <libmath/vector.hh>

using namespace micro::math;

constexpr float EPS = 4E-5f;

#define STRINGIFY(s) #s
#define STRINGIZE(s) STRINGIFY(s)

volatile Vector2 A = {-3.4071929039f, +8.3920351995f};
volatile Vector2 B = {+1.5835732239f, -4.3206156194f};
volatile Vector2 C = {-1.2837562239f, -3.1506676193f};
volatile Vector2 I = {1, 0};
volatile Vector2 J = {0, 1};

void test_add();
void test_mul();
void test_sub();
void test_div();
void test_dot();
void test_len();

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
	auto a = const_cast<Vector2 const &>(A);
	auto b = const_cast<Vector2 const &>(B);
	auto c = const_cast<Vector2 const &>(C);

	if (!eq(a + Vector2{}, a) ||
	    !eq(b + Vector2{}, b) ||
	    !eq(c + Vector2{}, c) ||
	    !eq(Vector2{} + a, a) ||
	    !eq(Vector2{} + b, b) ||
	    !eq(Vector2{} + c, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a + (b + c), a + b + c) ||
	    !eq(b + (c + a), b + c + a) ||
	    !eq(c + (a + b), c + a + b))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a + (-a), Vector2{}) ||
	    !eq(b + (-b), Vector2{}) ||
	    !eq(c + (-c), Vector2{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_mul()
{
	auto a = const_cast<Vector2 const &>(A);
	auto b = const_cast<Vector2 const &>(B);
	auto c = const_cast<Vector2 const &>(C);

	if (!eq(a * Vector2{1.f, 1.f}, a) ||
	    !eq(b * Vector2{1.f, 1.f}, b) ||
	    !eq(c * Vector2{1.f, 1.f}, c) ||
	    !eq(Vector2{1.f, 1.f} * a, a) ||
	    !eq(Vector2{1.f, 1.f} * b, b) ||
	    !eq(Vector2{1.f, 1.f} * c, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a * Vector2{}, Vector2{}) ||
	    !eq(b * Vector2{}, Vector2{}) ||
	    !eq(c * Vector2{}, Vector2{}) ||
	    !eq(Vector2{} * a, Vector2{}) ||
	    !eq(Vector2{} * b, Vector2{}) ||
	    !eq(Vector2{} * c, Vector2{}) ||
	    !eq(a * 0.f, Vector2{}) ||
	    !eq(b * 0.f, Vector2{}) ||
	    !eq(c * 0.f, Vector2{}) ||
	    !eq(0.f * a, Vector2{}) ||
	    !eq(0.f * b, Vector2{}) ||
	    !eq(0.f * c, Vector2{}))
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
	auto a = const_cast<Vector2 const &>(A);
	auto b = const_cast<Vector2 const &>(B);
	auto c = const_cast<Vector2 const &>(C);

	if (!eq(a - Vector2{}, a) ||
	    !eq(b - Vector2{}, b) ||
	    !eq(c - Vector2{}, c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(a - (b - c), a - b + c) ||
	    !eq(b - (c - a), b - c + a) ||
	    !eq(c - (a - b), c - a + b))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(Vector2{} - a, -a) ||
	    !eq(Vector2{} - b, -b) ||
	    !eq(Vector2{} - c, -c))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}
}

void test_div()
{
	auto a = const_cast<Vector2 const &>(A);
	auto b = const_cast<Vector2 const &>(B);
	auto c = const_cast<Vector2 const &>(C);

	if (!eq(a / Vector2{1.f, 1.f}, a) ||
	    !eq(b / Vector2{1.f, 1.f}, b) ||
	    !eq(c / Vector2{1.f, 1.f}, c) ||
	    !eq(a / a, Vector2{1.f, 1.f}) ||
	    !eq(b / b, Vector2{1.f, 1.f}) ||
	    !eq(c / c, Vector2{1.f, 1.f}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq(Vector2{} / a, Vector2{}) ||
	    !eq(Vector2{} / b, Vector2{}) ||
	    !eq(Vector2{} / c, Vector2{}) ||
	    !eq(0.f / a, Vector2{}) ||
	    !eq(0.f / b, Vector2{}) ||
	    !eq(0.f / c, Vector2{}))
	{
		throw std::logic_error("@see " __FILE__ ":" STRINGIZE(__LINE__));
	}

	if (!eq((Vector2{1.f, 1.f} / a) * a, Vector2{1.f, 1.f}) ||
	    !eq((Vector2{1.f, 1.f} / b) * b, Vector2{1.f, 1.f}) ||
	    !eq((Vector2{1.f, 1.f} / c) * c, Vector2{1.f, 1.f}) ||
	    !eq(a * (Vector2{1.f, 1.f} / a), Vector2{1.f, 1.f}) ||
	    !eq(b * (Vector2{1.f, 1.f} / b), Vector2{1.f, 1.f}) ||
	    !eq(c * (Vector2{1.f, 1.f} / c), Vector2{1.f, 1.f}))
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
	auto a = const_cast<Vector2 const &>(A);
	auto b = const_cast<Vector2 const &>(B);
	auto c = const_cast<Vector2 const &>(C);
	auto i = const_cast<Vector2 const &>(I);
	auto j = const_cast<Vector2 const &>(J);

	if (!eq(dot(a, b), a.x() * b.x() + a.y() * b.y()) ||
	    !eq(dot(b, c), b.x() * c.x() + b.y() * c.y()) ||
	    !eq(dot(c, a), c.x() * a.x() + c.y() * a.y()) ||
	    !eq(dot(i, j), 0) ||
	    !eq(dot(j, i), 0))
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
	auto a = const_cast<Vector2 const &>(A);
	auto b = const_cast<Vector2 const &>(B);
	auto c = const_cast<Vector2 const &>(C);

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