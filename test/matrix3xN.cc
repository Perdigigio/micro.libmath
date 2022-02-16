#include <matrix3x3.hh>

#include <iostream>

using namespace micro::math;

void test_1() noexcept;
void test_2() noexcept;

int main()
{
	test_1();
	test_2();

	return 0;
}

std::ostream & operator <<(std::ostream &s, TMatrix3x3<float> const &m)
{
	for (auto i = 0; i < 3; i++) std::cout << ' ' << m.data[0].data[i]; std::cout << '\n';
	for (auto i = 0; i < 3; i++) std::cout << ' ' << m.data[1].data[i]; std::cout << '\n';
	for (auto i = 0; i < 3; i++) std::cout << ' ' << m.data[2].data[i]; std::cout << '\n';

	return s;
}

void test_1() noexcept
{
	// ------------------------------ Pre ------------------------------ //

	TMatrix3x3<float> const a = {1, 2, 3,
				     5, 6, 7,
				     1, 2, 3};

	// ------------------------------ Exp ------------------------------ //

	TMatrix3x3<float> const b = {1, 5, 1,
				     2, 6, 2,
				     3, 7, 3};

	// ------------------------------ Res ------------------------------ //

	TMatrix3x3<float> const c = transpose(a);

	// ----------------------------------------------------------------- //

	if (any(b != c))
	{
		std::cerr << "-------------- Pre -------------- \n" << a << std::endl;
		std::cerr << "-------------- Exp -------------- \n" << b << std::endl;
		std::cerr << "-------------- Res -------------- \n" << c << std::endl;

		std::exit(-1);
	}
}

void test_2() noexcept
{
	// ------------------------------ Pre ------------------------------ //

	TMatrix3x3<float> const a = {1, 8, 2,
				     8, 8, 4,
				     7, 4, 9};

	TMatrix3x3<float> const b = {5, 6, 9,
				     6, 2, 0,
				     7, 3, 3};


	// ------------------------------ Exp ------------------------------ //

	TMatrix3x3<float> const c = { 67, 28, 15,
				     116, 76, 84,
				     122, 77, 90};

	// ------------------------------ Res ------------------------------ //

	TMatrix3x3<float> const d = a * b;

	// ----------------------------------------------------------------- //

	if (any(c != d))
	{
		std::cerr << "-------------- Pre -------------- \n" << a << std::endl;
		std::cerr << "-------------- Exp -------------- \n" << b << std::endl;
		std::cerr << "-------------- Res -------------- \n" << c << std::endl;

		std::exit(-1);
	}
}