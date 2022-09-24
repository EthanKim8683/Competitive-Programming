#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

using I=int;
using S=string;

vector<pair<I,S>>pats;
vector<pair<I,S>>ress;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  if(m-1)pats.push_back({m-1,"R"});
  for(I i=0;i<n-1;i++){
    if(m-1)pats.push_back({m-1,"L"});
    pats.push_back({1,"D"});
    if(m-1)pats.push_back({m-1,"RUD"});
  }
  if(m-1)pats.push_back({m-1,"L"});
  if(n-1)pats.push_back({n-1,"U"});
  I tot=0;
  for(auto[i,s]:pats){
    I siz=s.size();
    if(tot+i*siz>k){
      I rem=k-tot,div=rem/siz,mod=rem%siz;
      if(div)ress.push_back({div,s});
      if(mod)ress.push_back({1,s.substr(0,mod)});
      tot+=rem;
      break;
    }
    ress.push_back({i,s});
    tot+=i*siz;
  }
  if(tot!=k)printf("NO\n"),exit(0);
  printf("YES\n");
  printf("%i\n",ress.size());
  for(auto[i,s]:ress)printf("%i %s\n",i,s.c_str());
  return 0;
}