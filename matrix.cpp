#include <iostream>
#include "matrix.h"
#include "tester.h"

#define MinVal -2000000000



matrix& matrix::operator+(const matrix* n)
{
	matrix* sum = new matrix(this->getRows(), this->getColumns());
	*sum = this->add(*n);
	return *sum;
}

matrix& matrix::operator-(const matrix* n)
{
	matrix* sum = new matrix(this->getRows(), this->getColumns());
	*sum = this->sub(*n);
	return *sum;
}


matrix& matrix::operator*(const matrix* N)
{
	matrix* prod = new matrix(this->getRows(), N->getColumns());
	*prod = this->mult(*N);
	return *prod;
}


matrix::matrix(int _m, int _n)
{
	m = _m; n = _n;
		matr = new int* [m];
		for (int i = 0; i < m; i++)
			matr[i] = new int[n];
}


void matrix::init()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matr[i][j] = 0;
		}
	}
}

void matrix::ranInit(int maxVal)
{
	srand(time(NULL));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//tester tester;
			//matr[i][j] = tester.ranValue();
			
			matr[i][j] = (rand()%maxVal - rand()%maxVal);	//sowohl pos, als auch neg. Zahlen zw. -maxVal und maxVal
		}
	}
}


void matrix::print()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (matr[i][j] >= 0)
				std::cout << " ";	//damit in einer Reihe, weil sonst ja -
			std::cout << matr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void matrix::input()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			std::cin >> matr[i][j];
		}
	}
}

void matrix::input(int* input_string)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matr[i][j] = *(input_string +  i * n + j);	
		}
	}
}



int matrix::getRows() const	//m Zeilen
{
	return m;
}
int matrix::getColumns() const //n Spalten
{
	return n;
}

int matrix::getElement(int i, int j)
{
	return matr[i][j];
}

void matrix::writeElement(int i, int j, int value)
{
	this->matr[i][j] = value;
}




bool quadratisch(matrix m)
{
	return m.getRows() == m.getColumns();
}

bool multiplizierbar(matrix m, matrix n)
{
	return m.getRows() == n.getColumns();
}


matrix matrix::merge(matrix& a, matrix& b, matrix& c, matrix& d)
{
	/*
	m = (a b)
		(c d)
	*/
	int n = a.getRows() * 2;
	matrix* m = new matrix(n, n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i < n / 2 && j < n / 2)
			{	//a
				m->writeElement(i, j, a.getElement(i, j));
			}
			if (i < n / 2 && j >= n / 2)
			{
				m->writeElement(i, j, b.getElement(i, j - n / 2));
			}
			if (i >= n / 2 && j < n / 2)
			{
				m->writeElement(i, j, c.getElement(i - n / 2, j));
			}
			if (i >= n / 2 && j >= n / 2)
			{
				m->writeElement(i, j, d.getElement(i - n / 2, j - n / 2));
			}
		}
	}
	return *m;
}

void matrix::part(matrix& a, matrix& b, matrix& c, matrix& d)
{
	/*
	m ~> (a b)
		 (c d)
	*/
	int n = a.getRows() * 2;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i < n / 2 && j < n / 2)
			{	
				a.writeElement(i, j, this->getElement(i, j));
			}
			if (i < n / 2 && j >= n / 2)
			{
				b.writeElement(i, j - n / 2, this->getElement(i, j));
			}
			if (i >= n / 2 && j < n / 2)
			{
				c.writeElement(i - n / 2, j, this->getElement(i, j));
			}
			if (i >= n / 2 && j >= n / 2)
			{
				d.writeElement(i - n / 2, j - n / 2, this->getElement(i, j));
			}
		}
	}

}



matrix matrix::add(matrix _M)
{
	int m = this->getRows(), n = this->getColumns();
	int s = 0;
	matrix sum(m, n);
	if (_M.getRows() != m || _M.getColumns() != n)
		std::cout << "ERR, MATR NICHT KOMPATIBEL" << std::endl;
	else
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				s = _M.getElement(i, j) + this->getElement(i, j);
				sum.writeElement(i, j, s);
			}
		}
	}
	return sum;
}

matrix matrix::sub(matrix _M)
{
	int m = this->getRows(), n = this->getColumns();
	int d = 0;
	matrix dif(m, n);
	if (_M.getRows() != m || _M.getColumns() != n)
		std::cout << "ERR, MATR NICHT KOMPATIBEL" << std::endl;
	else
	{
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				d = this->getElement(i, j) - _M.getElement(i, j);
				dif.writeElement(i, j, d);
			}
		}
	}
	return dif;
}




matrix matrix::mult(matrix _M)
{
	int m = this->getRows(), n = this->getColumns(), l = _M.getColumns();
	int Cik = 0;	//Cik = S(Aij*Bjk), einzelnes Element
	matrix prod(m, l);	//(m x n) * (n x l) = (m x l)
	prod.init();

	//tester tester;
	//tester.beginTest();

	if (!multiplizierbar(*this, _M))
		std::cout << "ERR, MATR NICHT KOMPATIBEL" << std::endl;
	else
	{
		for (int i = 0; i < m; i++)
		{
			for (int k = 0; k < l; k++)
			{
				for (int j = 0; j < n; j++)
				{
					Cik += this->getElement(i, j) * _M.getElement(j, k);
		//			tester++;
				}
				prod.writeElement(i, k, Cik);
				Cik = 0;
			}
		}
	}

	//tester.endTest();



	return prod;
}

matrix matrix::fast_mult(matrix* N)
{
	int n = this->getColumns();
	matrix* O = new matrix(n, n);
	matrix* O11 = new matrix(n/2, n/2);
	matrix* O12 = new matrix(n / 2, n / 2);
	matrix* O21 = new matrix(n / 2, n / 2);
	matrix* O22 = new matrix(n / 2, n / 2);

	matrix* M11 = new matrix(n / 2, n / 2);
	matrix* M12 = new matrix(n / 2, n / 2);
	matrix* M21 = new matrix(n / 2, n / 2);
	matrix* M22 = new matrix(n / 2, n / 2);

	matrix* N11 = new matrix(n / 2, n / 2);
	matrix* N12 = new matrix(n / 2, n / 2);
	matrix* N21 = new matrix(n / 2, n / 2);
	matrix* N22 = new matrix(n / 2, n / 2);

	matrix* H1 = new matrix(n / 2, n / 2);
	matrix* H2 = new matrix(n / 2, n / 2);
	matrix* H3 = new matrix(n / 2, n / 2);
	matrix* H4 = new matrix(n / 2, n / 2);
	matrix* H5 = new matrix(n / 2, n / 2);
	matrix* H6 = new matrix(n / 2, n / 2);
	matrix* H7 = new matrix(n / 2, n / 2);
	

	this->part(*M11, *M12, *M21, *M22);
	N->part(*N11, *N12, *N21, *N22);


	if (n / 2 == 1)
	{
		*H1 = (*M11 + M22) * &(*N11 + N22);
		*H2 = (*M21 + M22) * N11;
		*H3 = (*M11) * &(*N12 - N22);
		*H4 = (*M22) * &(*N21 - N11);
		*H5 = (*M11 + M12) * N22;
		*H6 = (*M21 - M11) * &(*N11 + N12);
		*H7 = (*M12 - M22) * &(*N21 + N22);
	}
	else
	{
		*H1 = (*M11 + M22).fast_mult(&(*N11 + N22));
		*H2 = (*M21 + M22).fast_mult( N11);
		*H3 = (*M11).fast_mult( &(*N12 - N22));
		*H4 = (*M22).fast_mult( &(*N21 - N11));
		*H5 = (*M11 + M12).fast_mult( N22);
		*H6 = (*M21 - M11).fast_mult(&(*N11 + N12));
		*H7 = (*M12 - M22).fast_mult(&(*N21 + N22));
	}

	*O11 = ((*H1 + H4) - H5) + H7;
	*O12 = (*H3 + H5);
	*O21 = (*H2 + H4);
	*O22 = (((*H1 - H2) + H3) + H6);

	*O = merge(*O11, *O12, *O21, *O22);

	return *O;
}



/*


Fhelerbehandlung fuer fast_mult
if (!quadratisch(N) || !quadratisch(*this) || !multiplizierbar(N, *this))
	{
	
	}
	else
	{
		for (int i = 0; i < n / 2 + 1; i++)
		{
			if (!(N.getRows % pow(2, i)))	//wenn n kein vielfaches von 2^i
				break;
		}

	}*/


/*
int matrix::maxTeilSum()
{
	int s, max = MinVal, aktSum = 0;
	int El_value = 0;

	int start_i = 0, start_j = 0, end_i = 0, end_j = 0;
	int max_start_i = 0, max_start_j = 0, max_end_i = 0, max_end_j = 0;

	matrix* marker = new matrix(m, n); //Layer ueber anzuschauende Matrix, speichert ob zu TS gehoert

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			El_value = getElement(i, j);
			s = aktSum + El_value;
			if (s > El_value)
			{
				aktSum = s;
				end_i = i;
				end_j = j;
			}
			else
			{
				aktSum = El_value;
				start_i = end_i = i; //neu anfangen
				start_j = end_j = j;
			}

			if (aktSum > max)	//altes Maximum durch neues ersetzen
			{
				max = aktSum;
				max_start_i = start_i;
				max_start_j = start_j;
				max_end_i = end_i;
				max_end_j = end_j;
			}
				
		}
	}
	std::cout << "Start zeile: " << max_start_i << "   Start spalte: " << max_start_j << std::endl;
	std::cout << "Ende zeile: " << max_end_i << "   Ende  spalte: " << max_end_j << std::endl;
	std::cout << "Max TS = " << max << std::endl;

 	return max;
}*/

/*Bei linearen problemen im algortihmus wichtig:
	- vorstellung: fuer n Elemente gelöst
	- was passiert wenn neues dazu kommt?
=> bei 2D: fuer mxn elemente geloest...
	=>hier:
	schauen: gehoere ich dazu? 
	ja => 
 		- schaue nach oben: gehoert El in Zeile ueber mir dazu? (gehoert es mit mir dazu => iterativ nach oben durchgehen??(fuck))
			nein => 
																	
																
																*/





int matrix::maxTeilSum()
{
	int testSum, max = MinVal, aktSum = 0;
	int El_value = 0;

	int start_i = 0, start_j = 0, end_i = 0, end_j = 0;
	int max_start_i = 0, max_start_j = 0, max_end_i = 0, max_end_j = 0;

	int i_count = 0, j_count = 0;	//wo wir uns gerade befinden

	while (i_count < n && i_count >= 0)
	{

	}

	return 0;

}