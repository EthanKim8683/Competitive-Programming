#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=100000;
const I Q=100000;
vector<pair<I,I>>plys[N];
pair<I,I>qrys[Q];
I ress[Q];
vector<I>inds[N];
map<pair<I,I>,I>pres;
I fens[N+1];
I n;
I gcd(I a,I b){
  return b?gcd(b,a%b):a;
}
void upd(I i,I x){
  for(i++;i<=n;i+=i&-i)fens[i]+=x;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  cin>>n;
  for(I i=0;i<n;i++){
    I k;cin>>k;
    for(I j=0;j<k;j++){
      I x,y;cin>>x>>y;
      plys[i].push_back({x,y});
    }
  }
  I q;cin>>q;
  for(I i=0;i<q;i++){
    I l,r;cin>>l>>r,l--,r--;
    qrys[i]={l,r};
    inds[r].push_back(i);
  }
  for(I i=0;i<n;i++){
    I k=plys[i].size();
    for(I j=0;j<k;j++){
      auto[x1,y1]=plys[i][j];auto[x2,y2]=plys[i][(j+1)%k];
      I dx=x1-x2,dy=y1-y2,den=abs(gcd(dx,dy));
      pair<I,I>slp={dx/den,dy/den};
      if(pres.count(slp))upd(pres[slp],-1);
      upd(pres[slp]=i,1);
    }
    for(auto ind:inds[i]){
      auto[l,r]=qrys[ind];
      ress[ind]=qry(r+1)-qry(l);
    }
  }
  for(I i=0;i<q;i++)printf("%i\n",ress[i]);
}