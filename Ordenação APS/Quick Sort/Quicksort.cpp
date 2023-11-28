#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <locale.h>
#include <iomanip>


using namespace std;
namespace fs = std::filesystem;

void quicksort(vector<int>& vec, int esq, int dir) {
    if (esq < dir) {
        int pivo = vec[dir];
        int i = esq - 1;
        for (int j = esq; j <= dir - 1; j++) {
            if (vec[j] < pivo) {
                i++;
                swap(vec[i], vec[j]);
            }
        }
        swap(vec[i + 1], vec[dir]);
        int pivoIndex = i + 1;
        quicksort(vec, esq, pivoIndex - 1);
        quicksort(vec, pivoIndex + 1, dir);
    }
}

int main() {
	setlocale(LC_ALL, "");
	clock_t inicio_total;
    clock_t total;
    inicio_total = clock();
	vector<int> numeros;
	double tempo_saida;
    ofstream arquivo_saida;
    ofstream registro_saida;
    clock_t final_local;
        
    string caminho_base = "C:\\Users\\nutty\\Downloads\\Ordenados\\Ordenados";
	
	registro_saida.open(caminho_base + "\\registro quick.txt");
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
            quicksort(numeros, 0, numeros.size() - 1);
			arquivo_saida.open(entry.path().string() + " ordenado quick.txt");
            //registro_saida.open(entry.path().parent_path().string() + "registro quick.txt", std::ios::app);
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
        	cout << texto_saida << tempo_saida << "s\n "<< endl;
    		arquivo_saida.close();
	        registro_saida << setprecision(5) << fixed;
			registro_saida << entry.path().filename().string() + ";" << tempo_saida << endl;
        }
    numeros.clear();
	}    
	clock_t final_total = clock() - inicio_total;
	double tempo_final = double(final_total)/CLOCKS_PER_SEC;
    cout << "Tempo de execução do programa: " << tempo_final <<"s" << endl;    
    registro_saida << endl << "Total Quick: " << tempo_final; 
	registro_saida.close();
	return 0;
}

