#include <iostream>
#include <string>
#include <random>
#include <fstream>

// range of values generated in the matrix
constexpr auto MIN_VALUE = -1.0;
constexpr auto MAX_VALUE = 1.0;

// functions declarations
float** allocateMatrix(size_t const m, size_t const n);
void freeMemory(float** matrix, size_t const m, size_t const n);
void generateValues(float** matrix, size_t const m, size_t const n);
void saveToFile(float** const matrix, size_t const m, size_t const n);

// ************** MAIN **************
int main()
{
	// polish fonts support
	setlocale(LC_ALL, "polish");

	bool repeat = false;

	do
	{
		// setting matrix size (m x n)
		// m - rows; n - columns
		int m, n;
		std::cout << "Podaj wymiary macierzy M x N: ";
		std::cin >> m >> n;

		// memory allocation for the matrix
		float** matrix = allocateMatrix(m, n);

		// fill the matrix with random values
		generateValues(matrix, m, n);

		// save matrix to the file
		saveToFile(matrix, m, n);

		// freeing memory after the matrix
		freeMemory(matrix, m, n);

		// ask if repetition needed
		char answer = 'n';
		std::cout << "Czy wygenerowaæ kolejn¹ macierz [t/n]? ";
		std::cin >> answer;
		repeat = (answer == 't') ? true : false;
		std::cout << std::endl;
	} while (repeat != false);

		return 0;
	}

	// functions definitions
float** allocateMatrix(size_t const m, size_t const n)
	{
		// allocate the memory for M x N matrix
	float** matrix = new float*[m];
		for (size_t i = 0; i < m; i++)
		{
			matrix[i] = new float[n];
		}

		return matrix;
	}

	void freeMemory(float** matrix, size_t const m, size_t const n)
	{
		// free all the memory allocated for the matrix
		for (size_t i = 0; i < m; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}

	void generateValues(float** matrix, size_t const m, size_t const n)
	{
		// RNG setup
		std::default_random_engine generator;
		std::uniform_real_distribution<float> distribution(MIN_VALUE, MAX_VALUE);

		// generate random matrix content
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				matrix[i][j] = distribution(generator);
			}
		}
	}

	void saveToFile(float** const matrix, size_t const m, size_t const n)
	{
		// get filename
		std::string fileName;
		std::cout << "Podaj nazwê pliku wynikowego: ";
		std::cin >> fileName;

		// open file
		std::fstream file;
		file.open(fileName, std::fstream::out);

		// save matrix to the file
		// matrix size
		file << m << " " << n << std::endl;

		// matrix content
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				file << matrix[i][j] << " ";
			}
			file << std::endl;
		}

		// close the file
		file.close();
}
