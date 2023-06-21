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
    int sizeOfData, numberOfRedundantBits = 0;
    char *msg;

    Hamming(string data)
    {
        this->data = data;
        reverse(data.begin(), data.end());
        sizeOfData = data.size();
        int power = 1;

        while (power < (sizeOfData + numberOfRedundantBits + 1))
        {
            numberOfRedundantBits++;
            power *= 2;
        }

        msg = new char[sizeOfData + numberOfRedundantBits + 1];

        int curr = 0;
        for (int i = 1; i <= sizeOfData + numberOfRedundantBits; i++)
        {
            if (!isPowerOfTwo(i))
            {
                msg[i] = data[curr++];
            }
            else
            {
                msg[i] = 'n';
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
        return (number & (number - 1)) == 0;
    }

    void showMsg(const string &printMessage)
    {
        cout << printMessage;
        for (int i = sizeOfData + numberOfRedundantBits; i >= 1; i--)
        {
            cout << msg[i] << " ";
        }
        cout << endl;
    }

    void setRedundantBits()
    {
        int redundantBitPosition = 0;

        for (int redundantBit = 1; redundantBit <= sizeOfData + numberOfRedundantBits; redundantBit *= 2)
        {
            int count = 0;

            for (int dataBit = redundantBit + 1; dataBit <= sizeOfData + numberOfRedundantBits; dataBit++)
            {
                if ((dataBit & (1 << redundantBitPosition)) != 0)
                {
                    if (msg[dataBit] == '1')
                    {
                        count++;
                    }
                }
            }

            msg[redundantBit] = (count % 2 == 1) ? '1' : '0';
            redundantBitPosition++;
        }

        showMsg("The data packet to be sent is: ");
        addNoise();
    }

    void addNoise()
    {
        srand(time(0));

        for (int i = 1; i <= sizeOfData + numberOfRedundantBits; i++)
        {
            if (msg[i] == '0' || msg[i] == '1')
            {
                if ((rand() % 100) == 99)
                {
                    msg[i] = (msg[i] == '0') ? '1' : '0';
                }
            }
        }

        showMsg("Message after noise addition:  ");
        receiver();
    }

    // FIXME: receiver function only checks for one error; if there are more, it only returns the first found;
    void receiver()
    {
        string ans = "";
        int bit = 0;

        for (int i = 1; i <= sizeOfData + numberOfRedundantBits; i *= 2)
        {
            int count = 0;

            for (int j = i + 1; j <= sizeOfData + numberOfRedundantBits; j++)
            {
                if (j & (1 << bit))
                {
                    if (msg[j] == '1')
                    {
                        count++;
                    }
                }
            }

            if (count & 1)
            {
                ans.push_back((msg[i] == '1') ? '0' : '1');
            }
            else
            {
                ans.push_back((msg[i] == '0') ? '0' : '1');
            }
            bit++;
        }

        if (ans.find('1') != string::npos)
        {
            int power = 1;
            int wrongBit = 0;

            for (int i = 0; i < ans.size(); i++)
            {
                if (ans[i] == '1')
                {
                    wrongBit += power;
                }
                power *= 2;
            }

            cout << "Bit number " << wrongBit << " is wrong and has an error." << endl;
        }
        else
        {
            cout << "Correct data packet received." << endl;
        }
    }
};

int main()
{
    string data = "1011001";
    Hamming h(data);
    return 0;
}
