#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <locale.h>   

using namespace std;
namespace fs = std::filesystem;

void ordenarBubbleSort(vector<int>& V);

int main() {
    setlocale(LC_ALL, "");
    clock_t inicio_total;
    clock_t total;
    inicio_total = clock();
    vector<int> numeros;
	ofstream registro_saida;
	
	string caminho_base = "C:\\Users\\nutty\\Downloads\\Ordenados\\Ordenados";
	
	registro_saida.open(caminho_base + "\\registro bubble.txt");
    string caminho = caminho_base + "\\10k";
    for (const auto& entry : fs::directory_iterator(caminho)) {
        clock_t inicio_local = clock();
        if (entry.path().extension() == ".txt") {
            ifstream arquivo(entry.path());
            cout << "Lendo o arquivo: " << entry.path().filename() << endl;
            int numero;
            while (arquivo >> numero) {
                numeros.push_back(numero);
            }
            ordenarBubbleSort(numeros);
            ofstream arquivo_saida;
            arquivo_saida.open(entry.path().string() + " ordenado Bubble.txt");
            for (const auto& numero : numeros) {
            	arquivo_saida << numero << endl;
        		//cout << numero << endl;
    		}
    		
        	clock_t final_local = clock() - inicio_local;
        	string texto_saida;
        	double tempo_saida;
        	texto_saida = "Tempo de execução do arquivo: ";
        	tempo_saida = double(final_local)/CLOCKS_PER_SEC;
        	arquivo_saida << texto_saida <<tempo_saida << "s\n";
    		arquivo_saida.close();
        	cout << texto_saida << tempo_saida << "s\n "<< endl;
        	registro_saida << setprecision(5) << fixed;
			registro_saida << entry.path().filename().string() + ";" << tempo_saida << endl;
		}
        numeros.clear();
    }
    clock_t final_total = clock() - inicio_total;
    double tempo_final = double(final_total) / CLOCKS_PER_SEC;
    cout << "Tempo de execução do programa: " << tempo_final << "s" << endl;
    registro_saida << endl << "Total Bubble: " << tempo_final; 
	registro_saida.close();
    return 0;
}

void ordenarBubbleSort(vector<int>& V) {
    int aux;
    int tam = V.size();
    for (size_t i = 0; i < tam; i++) {
        for (size_t j = 0; j < tam - 1; j++) {
            if (V[j] > V[j + 1]) {
                aux = V[j];
                V[j] = V[j + 1];
                V[j + 1] = aux;
            }
        }
    }
}

