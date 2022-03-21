#include<iostream>
#include<string>
using namespace std;
#define OJ

string Units[4] = {"Billion", "Million", "Thousand", ""};
string Nums[20] = {"","One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
string Tens[10] = {" "," ","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};

void HandleThree(string &result, int num)
{
    if (num >= 100)
    {
        result += Nums[num / 100];
        result += " Hundred ";
        num %= 100;
    }
    if (!num)
        result.pop_back();
    else if (num >= 20)
    {
        result += Tens[num / 10];
        num %= 10;
        if (num)
        {
            result += " ";
            result += Nums[num];
        }
    }
    else // 1 ~ 19
        result += Nums[num];
}

int main()
{
    int num, m = 1, i = 1;
    cin >> num;
    int temp = num;
    if (!num)
    {
        cout << "Zero" << endl;
        return 0;
    }
    string result = "";
    while (temp /= 1000)
    {m *= 1000; i++;}
    for (i = 4 - i; i < 4; m /= 1000, i++)
    {
        temp = num / m;
        num %= m;
        HandleThree(result, temp);
        if (temp)
            result += i == 3 ? "" : " " + Units[i];
        result += " ";
    }
    cout << result << endl;
#ifndef OJ
    system("pause");
#endif
    return 0;
}