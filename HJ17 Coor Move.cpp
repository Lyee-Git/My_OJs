#include<bits/stdc++.h>
using namespace std;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(0),cout.tie(0);
    pair<int,int> p(0, 0);
    string s, t;
    while (getline(cin, s)) {
        stringstream ss(s);
        while(getline(ss, t, ';')) {
            if (t.empty())
                continue;
            string _ = t.substr(1);
            if (regex_match(_, regex("[0-9]*"))) 
            {
                switch(t[0]) {
                    case 'A': p.first -= stoi(_); break; //左移
                    case 'D': p.first += stoi(_); break; //右移
                    case 'W': p.second += stoi(_); break; //上移
                    case 'S': p.second -= stoi(_); break; //下移
                    default: break; //无效
                }           
            }
        }
    }
    cout << p.first << "," << p.second << endl;
    system("pause");
    return 0;
}