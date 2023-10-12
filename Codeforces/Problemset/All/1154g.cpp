#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e6;
const I A=1e7;
const Lli MAX=59604644783353249ll;
I a_arr[N];
I inds[A+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  fill_n(inds,A+1,-1);
  tuple<Lli,I,I>res={MAX,-1,-1};
  for(I i=0;i<n;i++){
    I a=a_arr[i],j=inds[a];
    if(j!=-1)res=min(res,{a,j,i});
    inds[a]=i;
  }
  for(Lli i=1;i<=A;i++){
    pair<Lli,I>low={MAX,-1};
    for(Lli j=i;j<=A;j+=i){
      I k=inds[j];
      if(k==-1)continue;
      auto[l,m]=low;
      if(m!=-1)res=min(res,{j*l/i,k,m});
      low=min(low,{j,k});
    }
  }
  auto[val,i,j]=res;
  if(i>j)swap(i,j);
  printf("%i %i\n",i+1,j+1);
}