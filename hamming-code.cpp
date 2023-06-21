#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class Hamming
{
public:
    string data;
    int rawDataSize, bitsDeParidade = 0;
    string dadoFinal;

    Hamming(string data)
    {
        this->data = data;
        reverse(data.begin(), data.end());
        rawDataSize = data.size();
        int potencia = 1;

        // Determina a quantidade de bits de paridade que haverão no dado enviado
        /* 
            A cada iteração, a potencia é multiplicada por 2,
            até que seu valor seja maior que o tamanho do dado final
        */
        while (potencia < (rawDataSize + bitsDeParidade + 1))
        {
            bitsDeParidade++;
            potencia *= 2;
        }

        int dataBit = 0;
        
        // Preenche o dado final com os bits de paridade e os bits da raw data recebida
        for (int i = 1; i <= rawDataSize + bitsDeParidade; i++)
        {

            // Checa se i é potência de 2, caso seja, irá dar falso e no else a posição no dado final será salva para um bit de paridade
            if (!isPowerOfTwo(i))
            {
                dadoFinal[i] = data[dataBit++];
            }
            else
            {
                dadoFinal[i] = 'n';
            }
        }

        setRedundantBits();
    }

    bool isPowerOfTwo(int number)
    {
        if (number <= 0)
        {
            return false;
        }
        /* 
            Caso i == 8, seu binario é 0b1000, e o binário de 8 - 1 é 0b0111
            Então: 0b1000 & 0b0111 = 0b0000 = false
        */
        return (number & (number - 1)) == 0;
    }


    // Imprime cada bit da data
    void showMsg(const string &printMessage)
    {
        cout << printMessage;
        for (int i = rawDataSize + bitsDeParidade; i >= 1; i--)
        {
            cout << dadoFinal[i] << " ";
        }
        cout << endl;
    }

    void setRedundantBits()
    {
        int redundantBitPosition = 0;

        for (int redundantBit = 1; redundantBit <= rawDataSize + bitsDeParidade; redundantBit *= 2)
        {
            int count = 0;

            for (int dataBit = redundantBit + 1; dataBit <= rawDataSize + bitsDeParidade; dataBit++)
            {
                if ((dataBit & (1 << redundantBitPosition)) != 0)
                {
                    if (dadoFinal[dataBit] == '1')
                    {
                        count++;
                    }
                }
            }

            dadoFinal[redundantBit] = (count % 2 == 1) ? '1' : '0';
            redundantBitPosition++;
        }

        showMsg("O pacote de dados enviado eh: ");
        addNoise();
    }

    void addNoise()
    {
        srand(time(0));

        for (int i = 1; i <= rawDataSize + bitsDeParidade; i++)
        {
            if (dadoFinal[i] == '0' || dadoFinal[i] == '1')
            {
                if ((rand() % 100) == 99)
                {
                    dadoFinal[i] = (dadoFinal[i] == '0') ? '1' : '0';
                }
            }
        }

        showMsg("Dados apos ruido:             ");
        receiver();
    }

    
    void receiver()
    {
        //A variável 'ans' vai segurar o valor de bits redundantes, se ele estão certos e pares, eles vão segurar o valor 0, se existir um erro, vão segurar o valor 1
        string ans = "";
        int bit = 0;

        for (int i = 1; i <= rawDataSize + bitsDeParidade; i *= 2)
        {
            int count = 0;

            for (int j = i + 1; j <= rawDataSize + bitsDeParidade; j++)
            {
                if (j & (1 << bit))
                {
                    if (dadoFinal[j] == '1')
                    {
                        count++;
                    }
                }
            }

            //incrementiando a variavel ans com a paridade do bit de redundancia
            // se está certo 0, se errado 1
            if (count & 1)
            {
                ans.push_back((dadoFinal[i] == '1') ? '0' : '1');
            }
            else
            {
                ans.push_back((dadoFinal[i] == '0') ? '0' : '1');
            }
            bit++;
        }

        // se existe alguma ocorroencia do bit 1 então tem problema
        if (ans.find('1') != string::npos)
        {
            int potencia = 1;
            int wrongBit = 0;

            //avaliando a expressão binaria da variavel ans
            for (int i = 0; i < ans.size(); i++)
            {
                if (ans[i] == '1')
                {
                    wrongBit += potencia;

                    cout << "Bit numero: " << wrongBit << " esta errado e tem um erro." << endl;
                }
                potencia *= 2;
            }
        }
        // ise não há nenhuma ocorrencia de bits 1 então está certo
        else
        {
            cout << "Pacote de dados corretamente recebido." << endl;
        }
    }
};

int main()
{
    // freopen("input.in", "r", stdin);
	string data;

	getline(cin, data);
	// data = "1011001";

    Hamming h(data);
    return 0;
}
