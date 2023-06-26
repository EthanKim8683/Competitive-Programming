#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=2e5;
I inds[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x;cin>>x;
    inds[x-1]=i;
  }
  I res=1;
  for(I i=0;i+1<n;i++)res+=inds[i+1]<inds[i];
  printf("%i\n",res);
}