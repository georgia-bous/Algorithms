#include <stdio.h>
#include<iostream>
using namespace std;
//#include<chrono>

int main(){ 
  int N, K, minsol, temp, sum;
  cin>>N>>K;
  int pop[N], lengths[K+1];
  for (int i = 0; i < N; i++){
    cin>>pop[i];
    if (pop[i] == K){
      cout<<1<<endl;
      return 0;
    }
  }
  //auto start=chrono::steady_clock :: now();

  /* lengths[x]=y means that so far the smallest subarray with total sum x is of y length, initialised to N+1, since 
  smallest length is N, the value N+1 means that no subarray with sum x has been found */
  lengths[0] = 0;
  for (int i = 1; i <= K; i++) lengths[i] = N + 1;

  minsol=N+1; //my solution

  for (int l = 0; l < N; l++){
    /* find the length and the sum of every possible contiguous subarray left from l (i don't care about the ones with sum>K)
     the subarray from i to l-1 has length l-i */
		sum = 0;
    for (int i = l - 1; i >= 0; i--){
      sum += pop[i];
			if (sum >= K) break;
      temp = l - i;
      if (lengths[sum] > temp)  lengths[sum] = temp;
    }

		/* form all the possible contiguous subarrays from l and right from it (i don't care about the ones with sum>K),
    if the subarray has sum i need to know if there exists another subarray left from l with K-sum, if yes this is a possible solution,
     i add the lengths of the two subarrays and change the minsol if its less than the previous solution */
		sum = 0;
    for (int r = l; r < N; r++){
      sum += pop[r];
      if (sum > K) break;
      temp = lengths[K - sum] + r - l + 1;
      if (temp < minsol) minsol = temp;
    }
  }

  if (minsol == N + 1) minsol = -1;
  
  cout<<minsol<<endl;
 
  //auto end=chrono::steady_clock::now();
  //auto diff=end-start;
  //cout<< chrono::duration<double, milli>(diff).count() <<" ms";
  return 0;
}