#define _USE_MATH_DEFINES
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <omp.h>
#include <ctime>
#include <unistd.h>

using namespace std;

int main() {

	// inicializiramo matriko A
	vector<vector<double>> A;

	// inicializiramo vektor b;
	vector<double> b;

	// podamo ime datoteke
	std::string filename = "./A_b.txt";

	// preberemo datoteko
	std::ifstream infile;
	infile.open(filename);

	// preberemo prvo vrstico, v kateri imamo podano velikost matrike A 
	std::string string_first_line;
	std::getline(infile, string_first_line);

	// string_first_line je enak 'A: n=256'
	// vemo, da je delimiter pri '=', lahko zamenjamo npr. z ' '
	std::replace(string_first_line.begin(), string_first_line.end(), '=', ' ');

	// definiramo stringstream, s katerim je nekoliko lazje shranjevati
	// podatke iz string-a, ce so loceni z ' '
	std::istringstream iss(string_first_line);
	std::string nepomemben_del1; // sem bomo dali string 'A:' iz prve vrstice
	std::string nepomemben_del2; // sem bomo dali string 'n' iz prve vrstice
	int n; // sem bomo dali velikost matrike A

	// istringstream loci glede na ' ', trenutno imamo 'A: n 256'
	iss >> nepomemben_del1;
	iss >> nepomemben_del2;
	iss >> n;

	std::cout << "Velikost matrike A: " << n << "x" << n << std::endl;; 
	A.reserve(n);

	// V naslednjih n vrsticah imamo elemente matrike A, zato naredimo
	// iteracijo, da preberemo in zafilamo matriko A
	std::string line;
	for (int iiA=0; iiA < n; iiA++)
	{
			// preberemo vrstico
			if (!getline(infile, line)) {
				cerr << "Error: Not enough lines in the file." << endl;
				break;
		}
		// std::getline(infile, line);
		// zamenjamo ';' s' ', saj istringstream loci glede na ' '
		// std::replace(line.begin(), line.end(), ';', ' ');

		// z istringstream ponovno pretvorimo string
		// std::istringstream iss_column(line);

		// definiramo nov vektor, da shranimo vrstico 
		vector<double> row;
		row.reserve(n);
		// sedaj lahko iteriramo po elementih v iss_column
		size_t start = 0, end = 0;
		for (int column = 0; column < n; column++) {
			end = line.find(';', start);
			double element_a = stod(line.substr(start, end - start)); // Convert substring to double
			row.emplace_back(element_a);
			start = (end == string::npos) ? end : end + 1; // Move to the next value
		}

		// ko imamo vektor za vrstico, ga damo v A
		A.emplace_back(move(row));

		if(iiA%500==0){
			std::cout<<"Matrix row: "<<iiA<<" read"<<std::endl;
		}
	}

	// sedaj imamo sestavljeno matriko A. Naslednja vrstica je prazna,
	// zato jo samo preberemo in ne naredimo nicesar. Poglejte v
	// datoteko datoteka_A_b.txt
	std::string empty_line;
	std::getline(infile, empty_line);

	// prebrati moramo se vektor b
	std::string string_line_b;
	std::getline(infile, string_line_b);

	// lahko uporabimo podoben trik kot pri prvi vrstici
	std::replace(string_line_b.begin(), string_line_b.end(), '>', ' ');
	std::istringstream iss_b(string_line_b);
	int n_b; // sem bomo dali velikost vektorja b (ki je identicna velikosti A)

	iss_b >> nepomemben_del1;
	iss_b >> nepomemben_del2;
	iss_b >> n_b;

	std::cout << "Velikost vektorja b: " << n_b << std::endl;; 

	// naredimo iteracijo po naslednjem n_b stevilu vrstic
	for (int iib=0; iib<n_b; iib++)
	{
		// preberemo vrstico in shranimo element v vrstici v vektor b
		std::string line_b_element;
		std::getline(infile, line_b_element);
		std::istringstream iss_b_element(line_b_element);

		double b_element=0;
		iss_b_element >> b_element;

		b.push_back(b_element);
	}

	// Sedaj imamo A in b. Lahko napisemo Gauss-Seidel metodo. Najprej
	// inicializiramo vektor resitve T, npr. na 100 stopinj.
	vector<double> T;
	for (int iiT=0; iiT<n_b; iiT++)
	{
		T.push_back(100);
	}

	//Smeni number of threads
	int max_threads = omp_get_max_threads();
	string res[max_threads];

	for(int i=1; i<=max_threads; i++){
		auto start_time = std::chrono::high_resolution_clock::now();
		vector<double> T;

		for (int iiT=0; iiT<n_b; iiT++)
			T.push_back(100);


		omp_set_num_threads(i);


		double d;
		int ii, jj;
		vector<double> Told = T;
		for (int iitt=0; iitt<1000; iitt++)
		{
			if(iitt%100==0)
				cout<<"Iteracija "<<iitt+1<<" so "<<i<<" threads"<<endl;
			Told = T;

			#pragma omp parallel shared(A, b, T, Told) private(jj, ii, d)
			{
				#pragma omp for
				for(jj=0; jj<n; jj++){
					d = b[jj];

					for(ii=0; ii<n; ii++){
						if(jj!=ii){
							d -= A[jj][ii] * T[ii];
						}
					}
					T[jj] = d / A[jj][jj];
				}
			}
		} 

		auto end_time = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_duration = end_time - start_time;
		string output = "Thread: "+to_string(i)+"\t duration "+to_string(time_duration.count())+" seconds\n";
		res[i-1]=output;
		std::cout << "Time of Gauss-Seidel: " << time_duration.count() << " seconds" << std::endl;


		double max_T = 0;
		for (int iiT=0; iiT<n_b; iiT++)
		{
			if (T[iiT] > max_T){
				max_T =T[iiT];
			}
		}
		std::cout << "Max. temperature: " << max_T << " degree C." << endl;

	}

	for(auto st: res)
		cout<<st;
	
	return 0;
}
