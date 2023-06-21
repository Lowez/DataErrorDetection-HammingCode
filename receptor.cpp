#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
using namespace std;

void receiver(string data){
			//A variável 'ans' vai segurar o valor de bits redundantes, se ele estão certos e pares, eles vão segurar o valor 0, se existir um erro, vão segurar o valor 1
            string ans = "";
			int bit = 0;
            int rawDataSize = data.size(), bitsDeParidade = 0;

            int potencia = 1;
			while (potencia < (rawDataSize + bitsDeParidade + 1)){
				bitsDeParidade++;
				potencia*=2;
			}

			for(int i = 1 ; i <= rawDataSize + bitsDeParidade ; i*=2){
				int count = 0;
				for(int j = i + 1 ; j<= rawDataSize + bitsDeParidade ; j++){
					if(j & (1 << bit)){
						if(dadoFinal[j] == '1') count++;
					}
				}
				//incrementiando a variavel ans com a paridade do bit de redundancia
				// se está certo 0, se errado 1
				if(count & 1){
					if(dadoFinal[i] == '1') ans.push_back('0');
					else ans.push_back('1');
				}
				else{
					if(dadoFinal[i]=='0') ans.push_back('0');
					else ans.push_back('1');
				}
				bit++;
			}
            // se existe alguma ocorroencia do bit 1 então tem problema
			if(ans.find('1') != string::npos){
				int power = 1;
				int wrongbit = 0;
                //avaliando a expressão binaria da variavel ans
				for(int i = 0 ; i < ans.size() ; i++){
					if(ans[i]=='1') {
                        wrongbit+=power;
                        cout << "numero bit " << wrongbit << " está errado " << endl; 
                    }
					power*=2;
				}
				
			}
			// ise não há nenhuma ocorrencia de bits 1 então está certo
			else{
				cout << "pacode de dados foi recebido com sucesso! " << endl;
			}
	}

int main(){
	// freopen("input.in", "r", stdin);
	string data;

	getline(cin, data);
	// data = "1011001";

	receiver(data);
	return 0;
}
