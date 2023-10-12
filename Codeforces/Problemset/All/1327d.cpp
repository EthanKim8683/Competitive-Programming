#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I MAX=1e9;
I p_arr[N];
I c_arr[N];
vector<I>facs[N+1];
B viss[N];
vector<I>ords;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=1;i<=N;i++)for(I j=2*i;j<=N;j+=i)facs[j].push_back(i);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    for(I i=0;i<n;i++)cin>>p_arr[i];
    for(I i=0;i<n;i++)cin>>c_arr[i];
    fill_n(viss,n,0);
    I res=MAX;
    for(I i=0;i<n;i++)if(!viss[i]){
      ords.clear();
      for(I j=i;!viss[j];j=p_arr[j]-1)ords.push_back(j),viss[j]=1;
      res=min(res,(I)ords.size());
      for(auto j:facs[ords.size()])for(I k=0;k<j;k++){
        I col=c_arr[ords[k]];B vld=1;
        for(I l=k+j;l<ords.size();l+=j)vld&=c_arr[ords[l]]==col;
        if(vld){res=min(res,j);break;}
      }
    }
    printf("%i\n",res);
  }
}