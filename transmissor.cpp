#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
using namespace std;
class hamming{
	public:
		string data;
		int rawDataSize , bitsDeParidade = 0;
		string dadoFinal;

		hamming(string data){
			this->data = data;

			reverse(data.begin(),data.end());
			rawDataSize = data.size();
			int potencia = 1;

			// Determina a quantidade de bits de paridade que haverão no dado enviado
			/* 
				A cada iteração, a potencia é multiplicada por 2,
				até que seu valor seja maior que o tamanho do dado final
			*/
			while (potencia < (rawDataSize + bitsDeParidade + 1)){
				bitsDeParidade++;
				potencia*=2;
			}

			int dataBit = 0;

			// Preenche o dado final com os bits de paridade e os bits da raw data recebida
			for (int i = 1 ; i <= rawDataSize + bitsDeParidade ; i++){

				// Checa se i é potência de 2, caso seja, irá dar falso e no else a posição no dado final será salva para um bit de paridade
				/* 
					Caso i == 8, seu binario é 0b1000, e o binário de 8 - 1 é 0b0111
					Então: 0b1000 & 0b0111 = 0b0000 = false
				*/
				if(i & (i-1)){
					dadoFinal[i] = data[dataBit++];
				}
				else {
					dadoFinal[i] = 'n';
				}
			}

			determinaBitsDeParidade();
		}

		// Imprime cada bit da data
		void showmsg(){
			cout << "the data packet to be sent is : ";
			for(int i = rawDataSize + bitsDeParidade ; i >= 1 ; i--){
				cout << dadoFinal[i] << " ";
			}
			cout << endl;
		}

		// Determina os bits de paridade do dado final
		void determinaBitsDeParidade(){
			int bit = 0;
            for (int i = 1; i <= rawDataSize + bitsDeParidade; i *= 2) {
                int count = 0;
                for (int j = i + 1; j <= rawDataSize + bitsDeParidade; j++) {
                    if (j & (1 << bit)) {
                        count += dadoFinal[j] == '1';
                    }
                }
				// O for acima conta quantos bits 1 existem no dado, então, é definido o bit de paridade como 1 ou 0
				// Caso o número de bits 1 seja impar, será 1, caso seja par, será 0
                dadoFinal[i] = count % 2 != 0 ? '1' : '0';
                bit++;
            }
            showmsg();
		}
};
int main(){
	// freopen("input.in", "r", stdin);
	string data;

	getline(cin, data);
	// data = "1011001";

	hamming h(data);
	return 0;
}
