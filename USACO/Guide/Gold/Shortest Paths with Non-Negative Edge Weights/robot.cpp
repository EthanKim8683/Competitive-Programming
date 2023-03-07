#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=100000;
const Lli MAX=1e18;
map<pair<I,I>,map<pair<I,I>,Lli>>adjs;
map<I,Lli>tots[N];
priority_queue<tuple<Lli,pair<I,I>>>ques;
map<pair<I,I>,Lli>diss;
void add(Lli dis,I a,I c){
  if(!diss.count({a,c}))diss[{a,c}]=MAX;
  if(dis>=diss[{a,c}])return;
  ques.push({-(diss[{a,c}]=dis),{a,c}});
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  for(I i=0;i<m;i++){
    I a,b,c,p;cin>>a>>b>>c>>p,a--,b--,c--;
    adjs[{a,c}][{b,c}]=adjs[{b,c}][{a,c}]=p;
    adjs[{a,m}][{b,c}]=adjs[{b,m}][{a,c}]=p;
    tots[a][c]+=p,tots[b][c]+=p;
  }
  add(0,0,m);
  while(ques.size()){
    auto[dis,stt1]=ques.top();ques.pop();
    if((dis=-dis)!=diss[stt1])continue;
    for(auto[stt2,p]:adjs[stt1]){
      auto[a,c1]=stt1;auto[b,c2]=stt2;
      if(c1==m){
        add(dis,b,c2);
        add(dis+min(p,tots[a][c2]-p),b,m);
      }else{
        add(dis+tots[a][c2]-p,b,m);
      }
    }
  }
  printf("%lli\n",diss.count({n-1,m})?diss[{n-1,m}]:-1);
}