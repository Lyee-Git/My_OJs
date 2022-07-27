#include<iostream>
#include<algorithm>
#include<stack>
#include<string>
using namespace std;
//#define OJ

int main()
{
    string s;
    cin >> s;
    stack<int> st;
    st.emplace(-1);
    int result = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'M')
            st.emplace(i);
        else {
            if (st.top() != -1 && s[st.top()]  == 'M') {
                st.pop();
                result = max(result, i - st.top());
            }
            else
                st.emplace(i);
        }
    }
    cout << result << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}