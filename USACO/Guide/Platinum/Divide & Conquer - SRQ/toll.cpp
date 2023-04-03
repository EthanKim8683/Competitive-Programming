#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=50000;
const I T=10000;
const I K=5;
const I MAX=1e9;
vector<pair<I,I>>incs[N],outs[N];
vector<I>diss[2*N][K];
priority_queue<pair<I,I>>ques;
I k,n;
void slv(I i=1,I l=0,I r=(n-1)/k){
  if(l>r)return;
  I m=l+(r-l)/2;
  for(I j=0;j<min(k,n-m*k);j++){
    I low=l*k,mid=m*k+j,upp=min((r+1)*k,n);
    auto add=[&](I a,I dis){
      if(dis>=diss[i][j][a])return;
      if(a<0||a>=upp-low)return;
      ques.push({-(diss[i][j][a]=dis),a});
    };
    diss[i][j].resize(upp-low);
    fill(diss[i][j].begin(),diss[i][j].end(),MAX);
    diss[i][j][mid-low]=0;
    ques.push({0,mid-low});
    while(ques.size()){
      auto[dis,a]=ques.top();ques.pop();
      if((dis=-dis)!=diss[i][j][a])continue;
      for(auto[b,t]:outs[a+low])add(b-low,dis+t);
    }
    ques.push({0,mid-low});
    while(ques.size()){
      auto[dis,a]=ques.top();ques.pop();
      if((dis=-dis)!=diss[i][j][a])continue;
      for(auto[b,t]:incs[a+low])add(b-low,dis+t);
    }
  }
  slv(i<<1,l,m-1),slv(i<<1|1,m+1,r);
}
I qry(I l1,I r1,I i=1,I l2=0,I r2=(n-1)/k){
  I m=l2+(r2-l2)/2;
  if(r1/k<m)return qry(l1,r1,i<<1,l2,m-1);
  if(l1/k>m)return qry(l1,r1,i<<1|1,m+1,r2);
  I res=MAX;
  for(I j=0;j<min(k,n-m*k);j++){
    I low=l2*k,upp=min((r2+1)*k,n);
    res=min(res,diss[i][j][l1-low]+diss[i][j][r1-low]);
  }
  return res==MAX?-1:res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m,o;cin>>k>>n>>m>>o;
  for(I i=0;i<m;i++){
    I a,b,t;cin>>a>>b>>t;
    outs[a].push_back({b,t});
    incs[b].push_back({a,t});
  }
  slv();
  while(o--){
    I a,b;cin>>a>>b;
    printf("%i\n",qry(a,b));
  }
}