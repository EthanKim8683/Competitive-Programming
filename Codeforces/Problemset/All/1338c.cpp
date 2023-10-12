#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
Lli dfs2(Lli,Lli);
Lli dfs1(Lli i,Lli siz){
  if(siz==1)return 0;
  return i>=siz/2?dfs2(i-siz/2,siz/2)^siz:dfs2(i,siz/2);
}
Lli dfs2(Lli i,Lli siz){
  if(siz==1)return 0;
  return i>=siz/2?dfs1(i-siz/2,siz/2)^(siz/4*3):dfs1(i,siz/2);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    Lli n;cin>>n,n--;
    Lli i=0,j=1;
    for(;i+j<=n/3;i+=j,j*=4);
    if(n%3==0){printf("%lli\n",n/3-i+j);continue;}
    Lli mid=dfs2(n/3-i,j)^(j*2);
    if(n%3==1){printf("%lli\n",mid);continue;}
    printf("%lli\n",(n/3-i+j)^mid);
  }
}