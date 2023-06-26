#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I M=20;
pair<I,I>boxs[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b;cin>>a>>b;
    boxs[i]={b,a};
  }
  sort(boxs,boxs+m);
  Lli res=0;
  for(I i=m-1;i>=0;i--){
    auto[b,a]=boxs[i];
    Lli dif=min(a,n);
    n-=dif,res+=b*dif;
  }
  printf("%lli\n",res);
}