#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I X=1e6;
const I Y=1e6;
I pnts[2*N];
vector<tuple<I,I,I>>ques;
I fens[2*Y+2];
void upd(I i,I val){
  for(;i<=2*Y+1;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++){
    I x1,y1,x2,y2;cin>>x1>>y1>>x2>>y2;
    x1+=X,y1+=Y,x2+=X,y2+=Y;
    if(x1==x2){
      if(y1>y2)swap(y1,y2);
      ques.push_back({x1,2,i});
    }
    if(y1==y2){
      if(x1>x2)swap(x1,x2);
      ques.push_back({x1,1,i});
      ques.push_back({x2,3,i});
    }
    pnts[i*2]=y1,pnts[i*2+1]=y2;
  }
  sort(ques.begin(),ques.end());
  Lli res=0;
  for(auto[cur,t,i]:ques){
    if(t==1)upd(pnts[i*2]+1,1);
    if(t==3)upd(pnts[i*2+1]+1,-1);
    if(t==2)res+=qry(pnts[i*2+1]+1)-qry(pnts[i*2]);
  }
  printf("%lli\n",res);
}