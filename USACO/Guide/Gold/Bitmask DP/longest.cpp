#include<bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
using I=int;
const I N=1e5;
const I A=1<<20;
const I K=20;
const I MAX=1e9;
I a_arr[N];
I k_arr[N];
pair<I,I>pres[A][K/2+1];
I pars[N];
vector<I>ress;
template<class T>void cmb(T&a,T b){a=max(a,b);}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)cin>>k_arr[i];
  pair<I,I>res={0,MAX};
  for(I i=0;i<n;i++){
    I a=a_arr[i],k=k_arr[i];
    pair<I,I>pre={0,MAX};
    I upp=a>>(K/2)<<(K/2);
    for(I z=0;z<(1<<K);z+=1<<(K/2)){
      I msk=a^z,cnt=__builtin_popcount(upp&msk);
      if(k-cnt>=0&&k-cnt<=K/2)cmb(pre,pres[msk][k-cnt]);
    }
    pair<I,I>cur={pre.first+1,i};
    I low=a&((1<<(K/2))-1);
    for(I y=0;y<(1<<(K/2));y++){
      I msk=a^y,cnt=__builtin_popcount(low&msk);
      cmb(pres[msk][cnt],cur);
    }
    pars[i]=pre.second,cmb(res,cur);
  }
  auto[len,i]=res;
  for(;i!=MAX;i=pars[i])ress.push_back(i);
  printf("%i\n",len);
  for(I i=ress.size()-1;i>=0;i--)printf("%i ",ress[i]+1);
}