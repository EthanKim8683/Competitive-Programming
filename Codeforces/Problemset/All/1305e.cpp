#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=5000;
const I A=1e9;
vector<I>ress;
I main(){
  I n,m;cin>>n>>m;
  I i=1,pre=0;
  for(;i<=n&&pre<m;i++){
    I upp=i-1,low=upp%2;
    pre=(upp+low)*(upp-low)/4,ress.push_back(i);
  }
  if(pre<m)printf("-1"),exit(0);
  if(ress.size())ress.back()+=(pre-m)*2;
  for(I j=n-1-ress.size();j>=0;j--)ress.push_back(A-j*i);
  for(auto i:ress)printf("%i ",i);
}