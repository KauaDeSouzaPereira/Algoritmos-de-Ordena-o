#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <filesystem>

#include <dirent.h>
#include <sys/stat.h>
#include <locale.h>   


using namespace std;

void selectionSort(vector<int>& arr) {
    // Implementação do Selection Sort
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        swap(arr[i], arr[min_index]);
    }
}

int main() {
    setlocale(LC_ALL, "");

    clock_t inicio_total = clock();
    ofstream registro_saida;
    string file_name;

    string caminho_base = "C:\\Users\\nutty\\Downloads\\Ordenados\\Ordenados";

    registro_saida.open(caminho_base + "\\registro_selection.txt");

    string caminho = caminho_base + "\\10k";
    DIR* dir = opendir(caminho.c_str());

    if (!dir) {
        perror("Falha ao abrir o diretório.");
        return 1;
    }

    while (dirent* entry = readdir(dir)) {
        file_name = entry->d_name;
        string file_path = caminho + "\\" + file_name;

        if (file_name != "." && file_name != "..") {
            struct stat s;
            if (stat(file_path.c_str(), &s) == 0 && S_ISREG(s.st_mode) && file_path.substr(file_path.find_last_of(".") + 1) == "txt") {
                ifstream arquivo(file_path);
                cout << "Lendo o arquivo: " << file_name << endl;
                vector<int> numeros;
                int numero;

                while (arquivo >> numero) {
                    numeros.push_back(numero);
                }

                clock_t inicio_local = clock();
                selectionSort(numeros);
                double tempo_saida = static_cast<double>(clock() - inicio_local) / CLOCKS_PER_SEC;

                ofstream arquivo_saida(file_path + "_ordenado_SelectionSort.txt");

                for (const auto& num : numeros) {
                    arquivo_saida << num << endl;
                }

                cout << "Tempo de execução do arquivo: " << tempo_saida << "s\n" << endl;
                registro_saida << fixed << setprecision(5) << file_name + ";" << tempo_saida << endl;
            }
        }
    }

    closedir(dir);

    double tempo_final = static_cast<double>(clock() - inicio_total) / CLOCKS_PER_SEC;
    cout << "\nTempo de execução do programa: " << tempo_final << "s" << endl;
    registro_saida << "\nTotal SelectionSort: " << tempo_final;
    registro_saida.close();

    return 0;
}
