#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>

using namespace std;

using I=int;
using S=string;
using B=bool;
using Lli=long long int;
using C=char;

const I N=200;

vector<I>adjs[N];
vector<C>cycs[N];
B viss[N];
S s;

void dfs(I a,I r){
  if(viss[a])return;
  viss[a]=1;
  cycs[r].push_back(s[a]);
  for(auto b:adjs[a])dfs(b,r);
}

Lli gcd(Lli a,Lli b){
  while(b)a%=b,swap(a,b);
  return a;
}

Lli lcm(Lli a,Lli b){
  return a*b/gcd(a,b);
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    cin>>s;
    fill_n(viss,n,0);
    for(I i=0;i<n;i++)adjs[i].clear(),cycs[i].clear();
    for(I i=0;i<n;i++){I p;cin>>p,adjs[i].push_back(p-1);}
    Lli res=1;
    for(I i=0;i<n;i++){
      if(viss[i])continue;
      dfs(i,i);
      I siz=cycs[i].size();
      for(I j=1;j<=siz;j++){
        B vld=true;
        for(I k=0;k<siz&&vld;k++)
          vld&=cycs[i][k]==cycs[i][(k+j)%siz];
        if(vld){res=lcm(res,j);break;}
      }
    }
    printf("%lli\n",res);
  }
  return 0;
}