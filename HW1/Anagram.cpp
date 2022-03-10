#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#define OJ
using namespace std;

void QuickSort(string &s, int lo, int hi)
{
    if (lo >= hi)
        return;
    int i = lo, j = hi;
    char pivot = s[lo];
    while (lo < hi)
    {
        while (lo < hi)
        {
            if (s[hi] > pivot)
                hi--;
            else
            {
                s[lo++] = s[hi]; break;
            }
        }
        while (lo < hi)
        {
            if (s[lo] < pivot)
                lo++;
            else
            {
                s[hi--] = s[lo]; break;
            }
        }
    }
    s[lo] = pivot;
    QuickSort(s, i, lo - 1);
    QuickSort(s, lo + 1, j);
}

class Anagram_entry
{
public:
    string word; // word with lowest letter sequence
    int word_cnt; // count of anagram words
    ~Anagram_entry() {};
    Anagram_entry(string& _word, int _word_cnt = 1): word(_word), word_cnt(_word_cnt) {};
};

int main()
{
    map<string, Anagram_entry> Anagram;
    string s;
    int cnt = 0, n_words;
    cin >> n_words;
    cout << "wo yi yue du guan yu chao xi de shuo ming" << endl;
    while (n_words--)
    {
        cin >> s;
        string temp = s;
        QuickSort(temp, 0, temp.length() - 1);
        map<string, Anagram_entry>::iterator iter = Anagram.find(temp);
        if (iter != Anagram.end())
        {
            if (iter->second.word > s)
                iter->second.word = s;
            iter->second.word_cnt++;
            if (iter->second.word_cnt <= 2)
                cnt++;
        }
        else
            Anagram.insert(map<string, Anagram_entry>::value_type(temp, Anagram_entry(s, 1)));
    }
    cout << cnt << endl;
    // for (auto it : Anagram)
    //     cout << it.first << " " << it.second.word << " " << it.second.word_cnt << endl;
    vector<string> Anagrams_rep;
    for (map<string, Anagram_entry>::iterator it = Anagram.begin(); it != Anagram.end(); it++)
        if (it->second.word_cnt >= 2)
            Anagrams_rep.push_back(it->second.word);
    sort(Anagrams_rep.begin(), Anagrams_rep.end());
    for (vector<string>::iterator it = Anagrams_rep.begin(); it != Anagrams_rep.end(); it++)
        cout << *it << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}