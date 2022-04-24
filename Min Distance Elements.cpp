#include <bits/stdc++.h>
using namespace std;
 
int minDist(int arr[], int n, int x, int y)
{
         
    //previous index and min distance
    int p = -1, min_dist = INT_MAX;
     
    for(int i=0 ; i<n ; i++)
    {
        if(arr[i]==x || arr[i]==y)
        {
            //we will check if p is not equal to -1 and
            //If the element at current index matches with
            //the element at index p , If yes then update
            //the minimum distance if needed
            if( p != -1 && arr[i] != arr[p])
                min_dist = min(min_dist , i-p);
              
            //update the previous index
            p=i;
        }
    }
    //If distance is equal to int max
    if(min_dist==INT_MAX)
        return -1;
 
    return min_dist;
}
 
/* Driver code */
int main()
{
    int arr[] = {3, 5, 4, 2, 6, 3, 0, 0, 5, 4, 8, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 3;
    int y = 6;
 
    cout << "Minimum distance between " << x <<
                        " and " << y << " is "<<
                        minDist(arr, n, x, y) << endl;
    return 0;
}