#include <iostream>
#include <fstream>

void input_Demention(unsigned int& M)
{
	std::cout << "\nEnter the quantity of unknown variables\n" << std::endl;
	std::cout << "Variables = ";
	std::cin >> M;
}

struct File_Reader
{
	std::ifstream fread;
	const char* file_Name;
	File_Reader(const char* _name)
	{
		file_Name = _name;
		fread.open(file_Name, std::ios::in);
		if(!fread.is_open())
		{
			std::cout << "Error";
		}
		else
		{
			std::cout << "It's OK \n";
		}
	}
	bool read_digit(int& digit)
       	{
		if(fread >> digit) 
		{
		        return true;
		}
	       	else
	       	{ 
			return false;
		}
	}
	~File_Reader()
       	{
		fread.close();
	}
};

struct Matrix
{
	float* array_A;
	float* array_B;
	unsigned int size;
	Matrix(const unsigned int M_size)
       	{
		size = M_size;
		array_A = new float [size * size];
		array_B = new float [size];
	}
	int get_Size()
       	{
		return size;
	}
	float& operator() (const unsigned int i, const unsigned j) 
	{
		return array_A[i * get_Size() + j];
	}
	float& operator() (const unsigned int i) 
	{
		return array_B[i];
	}
	~Matrix()
       	{
		delete [] array_A;
		delete [] array_B;
	}
};

void gauss_Method(Matrix& a, Matrix& b, Matrix& x, File_Reader& fa, File_Reader& fb)
{
	int digit = 0;
	float temp = 0, data = 0;
	for(int i = 0; i < a.get_Size(); ++i)
       	{
		for(int j = 0; j < a.get_Size(); ++j) 
		{
			fa.read_digit(digit);
			a(i, j) = digit;
			std::cout << a(i, j) << "\t";
		}
		fb.read_digit(digit);
		b(i) = digit;
		x(i) = 0;
		std::cout << "|  " << b(i) << "\n";
	}
	std::cout << "\n";
	for(int i = 0; i < a.get_Size(); ++i)
       	{
		for(int k = i + 1; k < a.get_Size(); ++k) 
		{
			float temp = a(k, i) / a(i, i);
			for(int j = 0; j < a.get_Size(); ++j) 
			{
				a(k, j) = a(k, j) - (temp * a(i, j));
			}
			b(k) = b(k) - (temp * b(i));
		}
	}
	for(int i = a.get_Size() - 1; i >= 0; --i)
       	{
		for(int k = i; k < a.get_Size(); ++k)
	       	{
			float save = a(i, k) * x(k);
			data = data + save;
		}
		x(i) = (b(i) - data)/(a(i, i));
	}
	for(int i = 0; i < a.get_Size(); ++i) 
	{
		std::cout << "X[" << i + 1 << "] = " << x(i) << "\n";
	}
	std::cout << "\n";
}

int main()
{
	std::cout.precision(2);
	std::cout.setf(std::ios::fixed);
	unsigned int M = 0;
	input_Demention(M);
	File_Reader fa("a.txt"), fb("b.txt");
	Matrix A(M), B(M), X(M), Y(M);
	gauss_Method(A, B, X, fa, fb);
	return 0;
}
