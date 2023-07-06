#include <iostream>
#include <stdio.h>
using namespace std;

//O(NlogN)

//with binary search we find, in case we are searching LDS, the position of the first element of m, which is >=val,
//and in case of LIS, the the position of the first element of m, which is <=val
int BS(int val, int lo, int hi, bool increasing, int *m) {
  bool comp; 
  int mid = (lo + hi) / 2, len = -1;
  
  while (lo <= hi) {
    if(increasing) comp=(val>m[mid]);
    else comp=(val<m[mid]);
    if (m[mid] >= 0 && comp) {
      lo = mid + 1;
      len = mid;
    } else
      hi = mid - 1;

    mid = (lo + hi) / 2;
  }
  return len + 1;
}


int main() {
  int maxval = 1000000000, len; //it is given that pi<10^9
  int N, K;
  cin >> N >> K;

  int initSeq[N + 1], m[N + 1], LDS_starting_at[N + 1];  //m array used for both LDS and LIS, it has at most 
                                                //size=N->N+1 (start counting from 1) when there are N list of size 1
  initSeq[0] = LDS_starting_at[0] = 0;          // start counting from 1

  m[0] = maxval; 
  for (int i = 1; i <= N; i++) {
    m[i] = LDS_starting_at[i] = 0;
    cin >> initSeq[i];
  }
  
  m[1] = initSeq[N], LDS_starting_at[N] = 1;  

  for (int i = N - 1; i > 0; i--) {

    len = BS(initSeq[i], 0, N - i, false, m); //start traversing initSeq from right to left
    m[len] = max(m[len], initSeq[i]);         //in the m array we keep the max element which starts a DS of length i,
    LDS_starting_at[i] = len;                 //for every initSeq[i] we find the maximum length of a DS starting at i
  }                                           //notice that m is by construction sorted, hence BS is possible
                                              //LDS_starting_at[i] stores this information


  m[0] = 0; // initialise again the m array, now used for LIS
  for (int i = 1; i <= N; i++)   m[i] = maxval;

  //m[i] stores the last, minimum possible element of an IS of length i

  int maxl = 0; //length of the LIS
  for (int i = 1; i <= N; i++) {    //start travesring initSeq from left to right

    len = BS(initSeq[i] + K, 0, i, true, m);    //find the first position len of m array, for which m[len]<=initSeq[i]+K
    maxl = max(maxl, len + LDS_starting_at[i] - 1);  //add the length to the length of the LDS starting at index i and keep track of the biggest valye found so far
    len = BS(initSeq[i], 0, len, true, m);  
    m[len] = min(m[len], initSeq[i]);
  }

  cout<<maxl<<endl;
}
