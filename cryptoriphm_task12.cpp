// cryptoriphm_task12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// 
// -- Написать программу решения математических ребусов,
// в которых зашифровано деление. 
//
// -- Написать программу,
// которая получает на входе математический ребус в виде трех слов и возвращает числа,
// которые были представлены этими словами, или сообщает о невозможности решения.


// Важно!!!
// -------- если хотите ввести новый крипторифм (три слова), смотрите на 126, 134, 173 - 180 строки кода!

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <ctime>
using namespace std;

///////////////////////////////////////////////////////////////////////////////

typedef string                     T_str;
typedef set        < T_str     >   T_solutions;
typedef set        < char      >   T_symb_set;

///////////////////////////////////////////////////////////////////////////////

int     get_num
(
	T_symb_set  const   &   letters,
	T_str       const   &   digits,
	T_str       const   &   word
)
{
	T_str   dig_word;

	transform
	(
		word.begin(),
		word.end(),
		back_inserter(dig_word),

		[=](char  letter)
	{
		auto    it = find
		(
			letters.begin(),
			letters.end(),
			letter
		);

		return  digits[
			distance
			(
				letters.begin(),
				it
			)
		];
	}
	);

	return  stoi(dig_word);
}

///////////////////////////////////////////////////////////////////////////////

void    print_all_solutions_of_rebus
(
	T_str   const   &   L_str,
	T_str   const   &   R_str,
	T_str   const   &   res_str
)
{
	T_symb_set      letters;
	T_solutions     solutions;

	letters.insert
	(
		L_str.begin(),
		L_str.end()
	);

	letters.insert
	(
		R_str.begin(),
		R_str.end()
	);

	letters.insert
	(
		res_str.begin(),
		res_str.end()
	);

	T_str   digits("0123456789");
	float     num_L{};
	float     num_R{};
	float     num_res{};

	do
	{
		num_L = get_num(
			letters,
			digits,
			L_str
		);

		num_R = get_num(
			letters,
			digits,
			R_str
		);

		num_res = get_num(
			letters,
			digits,
			res_str
		);

		if (
			num_L
			/ num_R					// <--- Знак нужно менять по условию задачи (+, -, *, /), работает не только для деления!

			== num_res
			)
		{
			ostringstream  sout;

			sout << num_L
				<< " / "			// <--- И здесь тоже знак нужно менят по соответствие условии задачи. (не принципиально, но желательно)
				<< num_R
				<< " = "
				<< num_res;

			if (
				solutions.insert(
					sout.str()
				)
				.second
				)
			{
				cout << "found "
					<< solutions.size()
					<< " solutions"
					<< endl;
			} //if
		} //if
	} while (
		next_permutation
		(
			digits.begin(),
			digits.end()
		)
		);

	copy
	(
		solutions.begin(),
		solutions.end(),
		ostream_iterator< T_str >(cout, "\n")
	);

}

///////////////////////////////////////////////////////////////////////////////

int     main()
{
	cout << "CRYPT >>> BCB / BA = AB" << endl;	// <--- Здесь нужно написать (исходное условие: криптарифм)
	clock_t a, b;
	a = clock();
	print_all_solutions_of_rebus
	(
		"BCB",			// <--- Вот здесь нужно написать первое слово (по латински)
		"BA",			// <--- Здесь нужно написать второе слово (по латински)
		"AB"			// <--- А здесь результат, т.е. третье слово.
	);

	b = clock();
	// обработка разницы
	cout << "time = " << ((b - a) / (1E-5));
	cout << "\nend"	<< endl;
}

/*
Крипторифмы: 
	на сложение:
		KOLA + KOLA = VODA
		UDAR + UDAR = DRAKA
		SEND + MORE = MONEY
		GERALD + DONALD = ROBERT
	на умножение:
		A * B = C
		TWO * TWO = THREE
		GOL * GOL = FUTBOL
		DVA * STO = DVESTI
	на деление:
			^	^	^
			|	|	|
		(можно использоват (умножение))
		MUHA / HA = UHA
		IKS / IGREK = ZET
*/