#include<iostream>
//#include<chrono>
using namespace std;

bool is_valid_median(int c[], int N, int K, int mid){        //the function checks if temp is a median of a subarray with length>=K
    int sum[N], greater_mid[N], max_sum, firsts;
    sum[0]=(c[0]>=mid)?1:-1;
    for(int i=1; i<N; i++){
        if(c[i]>=mid) greater_mid[i]=1;
        else greater_mid[i]=-1;
        sum[i]=sum[i-1]+greater_mid[i];
    }
    max_sum=sum[K-1];                                       
    firsts=0;
    for(int i=K; i<N; i++){                                 //check the subarrays of length >=K
        firsts=min(firsts, sum[i-K]);
        max_sum=max(max_sum, sum[i]-firsts);
        if(max_sum>0) break;                              
    }
    if(max_sum>0) return true;                             //it means that mid is a median of a subarray with length>=K
    return false;
}



int main(){
    int N, K, l, r, temp, sol=-1;
    cin>>N>>K;
    int c[N];
    for(int i=0; i<N; i++) cin>>c[i];                        //c[i]<=N =>the median, which is one of the c[i]s, has value <=N
    //auto start=chrono :: steady_clock :: now();
    l=1; r=N+1;
    while(l<=r){
        temp=(l+r)/2;                                       //pick as "pivot" the middle of the possible values the median can take
        if(is_valid_median(c, N, K, temp)){                
            sol=temp;
            l=temp+1;                                       //i found a solution, looking for a bigger
        }
        else r=temp-1;
    }
    cout<<sol<<endl;
    /*
    auto end=chrono::steady_clock::now();
    auto diff=end-start;
    cout<< chrono::duration<double, milli>(diff).count() <<" ms";
    */
    return 0;
}
//O(logN*(N+(N-K))=O(NlogN)) time complexity, O(N+N+N)=O(N) space complexity