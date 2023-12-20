#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include<cstring>

using namespace std;


int main() {
    ifstream infile("input.txt");
    string line;
    vector<string> lines;

    while(getline(infile, line)) {
        lines.__emplace_back(line);
    }

    int adjacent[9][2] = {{-1,-1}, {-1,0}, {0,-1}, {0,0}, {1,0}, {0,1}, {1,1}, {1,-1}, {-1, 1}};
    vector<int> sums;
    for(int i = 0; i < lines.size(); i++) {
        for(int j = 0; j < lines[i].size(); j++) {
            string number1 = "";
            string number2 = "";
            if(lines[i][j] == '*') {
                cout << "main target is: i,j " << i << "," << j << ", with value: " << lines[i][j] << endl;

                for(int adj = 0; adj < 8; adj++){
                    int adj_i = i + adjacent[adj][1];
                    int adj_j = j + adjacent[adj][0];
                    cout << "adj_i: " << adj_i << ", " << "adj_j: " << adj_j << endl; 
                    if(adj_i >= 0 && adj_i < lines.size() && adj_j >= 0 && adj_j < lines[i].size() && isdigit(lines[adj_i][adj_j])) {
                        if(number1 == ""){
                            number1 += lines[adj_i][adj_j];
                        } else {
                            number2 += lines[adj_i][adj_j];
                        }
                        cout << "number1: " << number1 << ", number2: " << number2 << endl;
                        bool isFirst = number1.size() == 1;
                        int k;
                        if(adj_j <= j) {
                            k = -1;
                        } else {
                            k = 1;
                        }
                        while(isdigit(lines[adj_i][adj_j+k])){
                            cout << "in" << endl;
                            if(isFirst){
                                number1 += lines[adj_i][adj_j+k];
                                cout << "processing number1: " << number1 << endl;;
                            } else {
                                number2 += lines[adj_i][adj_j+k];
                                cout << "processing number2: " << number2 << endl;
                            }
                            if(adj_j <= j){
                                k--;
                            } else {
                                k++;
                            }
                        }

                        if(k < 0){
                            if(number1 != ""){
                                string temp;
                                for(int z = number1.size()-1; z >= 0; z--){
                                    temp += number1[z];
                                }
                                number1 = temp;
                                cout << "swapped number1 is now: " << number1 << endl;
                            } else if(number2 != ""){
                                string temp;
                                for(int z = number2.size()-1; z >= 0; z--){
                                    temp += number2[z];
                                }
                                number2 = temp;
                                cout << "swapped number2 is now: " << number2 << endl;
                            }
                        }

                    }
                }
                if(number1 == "" || number2 == ""){
                    number1 = "";
                    number2 = "";
                } else if(number1 != "" && number2 != ""){
                    cout << "about to multiply number1: " << number1 << " with number2: " << number2 << endl;
                    sums.__emplace_back(stoi(number1)*stoi(number2));
                }
            }
        }
    }

    for(int i = 0; i < sums.size(); i++) {
        cout << "valid sum: " << sums[i] << endl;
    }



    return 0;
}
