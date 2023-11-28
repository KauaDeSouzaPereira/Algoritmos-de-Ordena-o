#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <filesystem>

#include <dirent.h>
#include <sys/stat.h>
#include <locale.h>   


using namespace std;

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int main() {
    setlocale(LC_ALL, "");
    clock_t inicio_total = clock();
    std::vector<int> numeros;
	ofstream registro_saida;
	std::string file_name;
	
	string caminho_base = "C:\\Users\\nutty\\Downloads\\Ordenados\\Ordenados";
	
	registro_saida.open(caminho_base + "\\registro insertion.txt");
    string caminho = caminho_base + "\\10k";
	
    struct dirent* entry;
    DIR* dir = opendir(caminho.c_str());

    if (!dir) {
        perror("Falha ao abrir o diretório.");
        return 1;
    }

    while ((entry = readdir(dir)) != nullptr) {
    	clock_t inicio_local = clock();
        file_name = entry->d_name;
        std::string file_path = caminho + "\\" + file_name;

        if (file_name != "." && file_name != "..") {
            struct stat s;
            if (stat(file_path.c_str(), &s) == 0) {
                if (S_ISREG(s.st_mode) && file_path.substr(file_path.find_last_of(".") + 1) == "txt") {
                    std::ifstream arquivo(file_path);
                    std::cout << "Lendo o arquivo: " << file_name << endl;
                    int numero;

                    while (arquivo >> numero) {
                        numeros.push_back(numero);
                    }

                    insertionSort(numeros);

                    std::ofstream arquivo_saida;
                    arquivo_saida.open(file_path + "_ordenado InsertionSort.txt");

                    for (const auto& numero : numeros) {
                        arquivo_saida << numero << std::endl;
                    }

                    arquivo_saida.close();
                    double tempo_saida = double(clock() - inicio_local) / CLOCKS_PER_SEC;
                    cout << "Tempo de execução do arquivo: " << tempo_saida << "s\n" << endl;
					registro_saida << setprecision(5) << fixed;
					registro_saida << file_name + ";" << tempo_saida << endl;                	
				}
            }
        }
        numeros.clear();
    }

    closedir(dir);
	double tempo_final = double(clock() - inicio_total) / CLOCKS_PER_SEC;
    std::cout << "\nTempo de execução do programa: " << tempo_final << "s" << std::endl;
	registro_saida << endl << "Total InsertionSort: " << tempo_final; 
	registro_saida.close();
    return 0;
}