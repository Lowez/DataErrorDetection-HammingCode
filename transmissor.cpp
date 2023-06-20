#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class hamming{
	public:
		string data; //it is the raw data received
		int m , r = 0; // n is the length of raw data and r is the number of redundant bits
		char * msg; // it will store the all bits (data + redundant). We made it dynamic because at compile time we dont know how much redundant bits will be there, we will initialize memory to it once we know the number of redundant bits.
		hamming(string data){
			this->data = data;
			//reversing the data received
			reverse(data.begin(),data.end());
			m = data.size();
			int power = 1;

			//finding the number of redundant bits and storing them in r
			while(power < (m + r + 1)){
				r++;
				power*=2;
			}
			//Allocating memory to our dynamic msg array(Note we are using one based indexing).
			msg = new char[m+r+1];
			int curr = 0;

			//initializing the msg with data bits and for redundant bits, an initial value of n
			for(int i = 1 ; i <= m+r ; i++){
				if(i & (i-1)){
					msg[i] = data[curr++];
				}
				else msg[i] = 'n';
			}
			//function call to set the redundant bits
			setRedundantBits();
		}
		//function to show the whole msg
		void showmsg(){
			cout << "the data packet to be sent is : ";
			for(int i = m+r ; i >= 1 ; i--){
				cout << msg[i] << " ";
			}
			cout << endl;
		}
		void setRedundantBits(){
			int bit = 0;
            for (int i = 1; i <= m + r; i *= 2) {
                int count = 0;
                for (int j = i + 1; j <= m + r; j++) {
                    if (j & (1 << bit)) {
                        count += msg[j] == '1';
                    }
                }
                msg[i] = count & 1 ? '1' : '0';
                bit++;
            }
            showmsg();
		}
		void receiver(){
			//this ans will store the redundant bits, if they were right then according to even parity they will store 0 else if some error was made in a bit it will store 1
			string ans = "";
			int bit = 0;
			//this loop corresponds to the logic used in set redundant bits function
			for(int i = 1 ; i <= m+r ; i*=2){
				int count = 0;
				for(int j = i+1 ; j<=m+r ; j++){
					if(j & (1 << bit)){
						if(msg[j] == '1') count++;
					}
				}
				//incrementing the ans variable with the parity of redundant bit
				// if it was right then add 0 else 1
				if(count & 1){
					if(msg[i] == '1') ans.push_back('0');
					else ans.push_back('1');
				}
				else{
					if(msg[i]=='0') ans.push_back('0');
					else ans.push_back('1');
				}
				bit++;
			}
			// if the ans had any occurrence of 1 then there is some fault
			if(ans.find('1') != string::npos){
				int power = 1;
				int wrongbit = 0;
				//evaluating the binary expression of ans variable
				for(int i = 0 ; i < ans.size() ; i++){
					if(ans[i]=='1') wrongbit+=power;
					power*=2;
				}
				cout << "bit number " << wrongbit << " is wrong and having error " << endl;
			}
			// if the ans dont have any occurrence of 1 then it is correct
			else{
				cout << "correct data packet received " << endl;
			}
		}
};
int main(){
	string data = "1011001";
	hamming h(data);
	// manipulating any ith data bit to check if receiver is detecting a error in that bit. If you eliminate the following line then correct code will be sent to receiver following that no error is received
	
	//h.msg[i] == '0' ? h.msg[i] = '1' : h.msg[i] = '0';

	h.receiver();
	return 0;
}
//time complexity = O(nlogn) where , n = databits + redundant bits
//this code is contributed by Mayank Sharma.
