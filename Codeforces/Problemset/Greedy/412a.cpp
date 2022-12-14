#include<bits/stdc++.h>
using namespace std;
using I=int;
using S=string;
using B=bool;
using C=char;
const I N=100;
B viss[N];
vector<pair<I,C>>ress;
I k;
S s;
void mov(I x){
  while(1){
    if(!viss[k])ress.push_back({2,s[k]});
    viss[k]=1;
    if(k==x)break;
    if(k>x)ress.push_back({0,-1}),k--;
    if(k<x)ress.push_back({1,-1}),k++;
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n>>k,k--;
  cin>>s;
  if(n-1-k<k-0)mov(n-1),mov(0);
  else mov(0),mov(n-1);
  for(auto[mov,chr]:ress){
    if(mov==0)printf("LEFT\n");
    if(mov==1)printf("RIGHT\n");
    if(mov==2)printf("PRINT %c\n",chr);
  }
}