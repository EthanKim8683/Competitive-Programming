#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100;
const I M=100;
tuple<I,I,I>exms[M];
vector<I>ress;
vector<I>adds[N];
I rems[N];
map<I,I>curs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(rems,n,-1);
  for(I i=0;i<m;i++){
    I s,d,c;cin>>s>>d>>c,s--,d--;
    exms[i]={s,d,c};
    adds[s].push_back(i),rems[d]=i;
  }
  for(I i=0;i<n;i++){
    for(auto j:adds[i]){
      auto[s,d,c]=exms[j];
      curs[d]=j;
    }
    if(rems[i]!=-1){
      if(get<2>(exms[rems[i]]))printf("-1"),exit(0);
      ress.push_back(m+1);
    }else{
      if(!curs.size()){ress.push_back(0);continue;}
      auto[d,j]=*curs.begin();
      if(--get<2>(exms[j])==0)curs.erase(d);
      ress.push_back(j+1);
    }
  }
  for(auto i:ress)printf("%i ",i);
}