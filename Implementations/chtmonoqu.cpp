#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
deque<pair<Lli,Lli>>stks;
Lli slv(pair<Lli,Lli>f1,pair<Lli,Lli>f2){
  Lli n=f2.second-f1.second,d=f1.first-f2.first;
  return n/d-((n^d)<0&&n%d);
}
void upd(pair<Lli,Lli>f){
  while(stks.size()>1&&slv(stks.end()[-1],f)<=slv(stks.end()[-1],stks.end()[-2]))stks.pop_back();
  stks.push_back(f);
}
Lli qry(Lli x){
  while(stks.size()>1&&slv(stks[0],stks[1])<x)stks.pop_front();
  auto[m,b]=stks.front();
  return m*x+b;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I q;cin>>q;
  while(q--){
    I t;cin>>t;
    if(t==1){
      Lli m,b;cin>>m>>b;
      upd({m,b});
    }
    if(t==2){
      Lli x;cin>>x;
      printf("%lli\n",qry(x));
    }
  }
}