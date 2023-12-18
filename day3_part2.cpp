#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int main(){


    ifstream infile("input.txt");
    string line;

    vector<string> lines;

    while(getline(infile, line)){
        lines.emplace_back(line);
    }

    vector<float> valids;
    int pos[8][2] = {{-1,-1}, {1,0}, {0,1}, {-1,0}, {1,1}, {0,-1}, {-1,1}, {1, -1}};
    for(int i = 0; i < lines.size(); i++){
        for(int j = 0; j < lines[i].size(); j++){
            if(lines[i][j] == '*'){
                vector<int> visited;
                string value1;
                string value2;
                vector<int> heights;

                for(int adj = 0; adj < 8; adj++){
                    int i_adj = i + pos[adj][1];
                    int j_adj = j + pos[adj][0];
                    float size = lines[i].size();
                    float t = i_adj*size + j_adj;
                    auto it = find(heights.begin(), heights.end(), t);
                    if(i_adj >= 0 && i_adj < lines.size() && j_adj >= 0 && j_adj < size && (value1.size() == 0 || value2.size() == 0) && isdigit(lines[i_adj][j_adj]) && it == heights.end()) {
                        string left;
                        string right;
                        string cand;

                        int k = j_adj - 1;
                        while(k >= 0 && isdigit(lines[i_adj][k])){
                            k--;
                        }
                        for(int p = k+1; p < j_adj; p++){
                            left += lines[i_adj][p];
                            heights.emplace_back(i_adj*size + p);
                        }

                        int k1 = j_adj + 1;
                        while(k1 < lines[i_adj].size() && isdigit(lines[i_adj][k1])) {
                            k1++;
                        }
                        for(int p = j_adj+1; p < k1; p++) {
                            right += lines[i_adj][p];
                            heights.emplace_back(i_adj*size + p);
                        }

                        if(left.size() > right.size()){
                            cand = left;
                            cand += lines[i_adj][j_adj];
                        } else if(left.size() == right.size()) {
                            cand = left + lines[i_adj][j_adj] + right;
                        } else {
                            cand = lines[i_adj][j_adj];
                            cand += right;
                        }

                        if(value1.size() == 0){
                            value1 = cand;
                            heights.emplace_back(i_adj*size + j_adj);
                        } else if(value1.size() > 0) {
                            value2 = cand;
                            heights.emplace_back(i_adj*size + j_adj);
                        } 
                    }
                    if(value1.size() > 0 && value2.size() > 0){
                        break;
                    }
                }
                if(value1.size() > 0 && value2.size() > 0){
                    //cout << "multiplying : " << value1 << " * " << value2 << "\n";
                    valids.emplace_back(stoi(value1)*stoi(value2));
                }
            }
        }
    }

    float sum = 0;
    for(int i = 0; i < valids.size(); i++){
        sum += valids[i];
    }

    cout << sum << "\n";
    return 0;
}