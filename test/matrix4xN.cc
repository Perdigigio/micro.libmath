#include <matrix4x4.hh>

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

std::ostream & operator <<(std::ostream &s, TMatrix4x4<float> const &m)
{
	for (auto i = 0; i < 4; i++) std::cout << ' ' << m.data[0].data[i]; std::cout << '\n';
	for (auto i = 0; i < 4; i++) std::cout << ' ' << m.data[1].data[i]; std::cout << '\n';
	for (auto i = 0; i < 4; i++) std::cout << ' ' << m.data[2].data[i]; std::cout << '\n';
	for (auto i = 0; i < 4; i++) std::cout << ' ' << m.data[3].data[i]; std::cout << '\n';

	return s;
}

void test_1() noexcept
{
	// ------------------------------ Pre ------------------------------ //

	TMatrix4x4<float> const a = {1, 2, 3, 4,
				     5, 6, 7, 8,
				     1, 2, 3, 4,
				     5, 6, 7, 8};

	// ------------------------------ Exp ------------------------------ //

	TMatrix4x4<float> const b = {1, 5, 1, 5,
				     2, 6, 2, 6,
				     3, 7, 3, 7,
				     4, 8, 4, 8};

	// ------------------------------ Res ------------------------------ //

	TMatrix4x4<float> const c = transpose(a);

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

	TMatrix4x4<float> const a = {1, 8, 2, 8,
				     8, 8, 4, 8,
				     7, 4, 9, 9,
				     1, 0, 3, 7};

	TMatrix4x4<float> const b = {5, 6, 9, 2,
				     6, 2, 0, 9,
				     7, 3, 3, 3,
				     8, 4, 3, 0};


	// ------------------------------ Exp ------------------------------ //

	TMatrix4x4<float> const c = {131,  60,  39,  80,
				     180, 108, 108, 100,
				     194, 113, 117,  77,
				      82,  43,  39,  11};

	// ------------------------------ Res ------------------------------ //

	TMatrix4x4<float> const d = a * b;

	// ----------------------------------------------------------------- //

	if (any(c != d))
	{
		std::cerr << "-------------- Pre -------------- \n" << a << std::endl;
		std::cerr << "-------------- Exp -------------- \n" << b << std::endl;
		std::cerr << "-------------- Res -------------- \n" << c << std::endl;

		std::exit(-1);
	}
}