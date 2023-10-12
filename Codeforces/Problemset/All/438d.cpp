#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I K=58;
const I L=(N+K-1)/K;
I a_arr[N];
Lli sums[L],maxs[L];
I n;
void slv(I i){
  sums[i]=maxs[i]=0;
  for(I j=max(i*K,0);j<min((i+1)*K,n);j++){
    Lli a=a_arr[j];
    sums[i]+=a;
    maxs[i]=max(maxs[i],a);
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<=(n-1)/K;i++)slv(i);
  while(m--){
    I t;cin>>t;
    if(t==1){
      I l,r;cin>>l>>r,l--,r--;
      Lli res=0;
      for(I i=l/K+1;i<r/K;i++)res+=sums[i];
      I upp=min((l/K+1)*K,r+1),low=max(r/K*K,upp);
      for(I i=l;i<upp;i++)res+=a_arr[i];
      for(I i=low;i<=r;i++)res+=a_arr[i];
      printf("%lli\n",res);
    }
    if(t==2){
      I l,r,x;cin>>l>>r>>x,l--,r--;
      for(I i=l/K+1;i<r/K;i++)if(x<=maxs[i]){
        for(I j=i*K;j<(i+1)*K;j++)a_arr[j]%=x;
        slv(i);
      }
      I upp=min((l/K+1)*K,r+1),low=max(r/K*K,upp);
      for(I i=l;i<upp;i++)a_arr[i]%=x;
      for(I i=low;i<=r;i++)a_arr[i]%=x;
      slv(l/K);
      slv(r/K);
    }
    if(t==3){
      I k,x;cin>>k>>x,k--;
      a_arr[k]=x;
      slv(k/K);
    }
  }
}
/*
if an x is greater than a, the result of the modulo is a, if 2 * x is greater
than a, the result is a - x, otherwise, it's a % x

this means that each a only needs to be modulo'ed at most log2(a) times before
it must fall into the first case as each modulo results in a value less than
ceil(a / 2)

if we divide the array into blocks (square-root decomposition), each keeping
track of minimum value, we can check for the cases above on each affected
block per query of type 2

if one a requires modulo'ing per block update, each block goes through at most
K * log2(a) updates, where K is the block size, each costing K operations

for at most n / K blocks updated per query of type 2, at most n * K * log2(a)
operations happen in total

operations of type 1 sum at most n / K blocks, and operations of type 3
affect one block with of size K, each contributing n * n / K and n * K
operations total

K can be solved as follows:

n * K * log2(a) = n * n / K
K * K = n / log2(a)
K = sqrt(n / log2(a))
K = 58
*/