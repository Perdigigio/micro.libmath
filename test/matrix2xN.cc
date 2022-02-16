#include <matrix2x2.hh>

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

template <class T>
std::ostream & operator <<(std::ostream &s, TMatrix2x2<T> const &m)
{
	for (auto i = 0; i < 2; i++) std::cout << ' ' << m.data[0].data[i]; std::cout << '\n';
	for (auto i = 0; i < 2; i++) std::cout << ' ' << m.data[1].data[i]; std::cout << '\n';

	return s;
}

void test_1() noexcept
{
	// ------------------------------ Flt ------------------------------ //

	TMatrix2x2<float> const a = {1, 2, 3, 4};
	TMatrix2x2<float> const b = {1, 3, 2, 4};

	// ------------------------------ Dbl ------------------------------ //

	TMatrix2x2<double> const c = {1, 2, 3, 4};
	TMatrix2x2<double> const d = {1, 3, 2, 4};

	// ------------------------------ Res ------------------------------ //

	auto const e = transpose(a);
	auto const f = transpose(c);

	if (any(e != b))
	{
		std::cerr << "-------------- Flt -------------- \n";
		std::cerr << "-------------- Pre -------------- \n" << a << std::endl;
		std::cerr << "-------------- Exp -------------- \n" << b << std::endl;
		std::cerr << "-------------- Res -------------- \n" << e << std::endl;

		std::exit(-1);
	}

	if (any(f != d))
	{
		std::cerr << "-------------- Dbl -------------- \n";
		std::cerr << "-------------- Pre -------------- \n" << c << std::endl;
		std::cerr << "-------------- Exp -------------- \n" << d << std::endl;
		std::cerr << "-------------- Res -------------- \n" << f << std::endl;

		std::exit(-1);
	}
}


void test_2() noexcept
{
	// ------------------------------ Flt ------------------------------ //

	TMatrix2x2<float> const a = {1,  2,  3,  4};
	TMatrix2x2<float> const b = {1,  3,  2,  4};
	TMatrix2x2<float> const c = {5, 11, 11, 25};


	// ------------------------------ Dbl ------------------------------ //

	TMatrix2x2<double> const d = {1,  2,  3,  4};
	TMatrix2x2<double> const e = {1,  3,  2,  4};
	TMatrix2x2<double> const f = {5, 11, 11, 25};

	// ------------------------------ Res ------------------------------ //

	auto const g = a * b;
	auto const h = d * e;

	if (any(g != c))
	{
		std::cerr << "-------------- Flt -------------- \n";
		std::cerr << "-------------- Pre -------------- \n" << a << '\n' << b << std::endl;
		std::cerr << "-------------- Exp -------------- \n" << c << std::endl;
		std::cerr << "-------------- Res -------------- \n" << g << std::endl;

		std::exit(-1);
	}

	if (any(h != f))
	{
		std::cerr << "-------------- Dbl -------------- \n";
		std::cerr << "-------------- Pre -------------- \n" << d << '\n' << e << std::endl;
		std::cerr << "-------------- Exp -------------- \n" << f << std::endl;
		std::cerr << "-------------- Res -------------- \n" << h << std::endl;

		std::exit(-1);
	}
}