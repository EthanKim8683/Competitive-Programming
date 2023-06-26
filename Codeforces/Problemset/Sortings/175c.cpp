#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100;
const I T=100;
pair<I,I>figs[N];
Lli p_arr[T+1];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I k,c;cin>>k>>c;
    figs[i]={c,k};
  }
  I t;cin>>t;
  for(I i=0;i<t;i++)cin>>p_arr[i+1];
  sort(figs,figs+n);
  Lli res=0,pre=0;
  for(I i=0,j=0;i<n;i++){
    auto[c,k]=figs[i];
    while(j<t&&k>0){
      Lli dif=min((Lli)k,p_arr[j+1]-p_arr[j]);
      p_arr[j]+=dif,k-=dif;
      res+=(Lli)c*dif*(j+1);
      if(p_arr[j]==p_arr[j+1])j++;
    }
    if(j==t)res+=(Lli)c*k*(t+1);
  }
  printf("%lli\n",res);
}