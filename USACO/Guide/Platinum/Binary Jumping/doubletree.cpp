#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=3e5;
const Lli MAX=1e18;
const I LOGN=19;
Lli w_arr[N];
vector<pair<I,I>>adjs[N];
pair<Lli,Lli>wgts[N-1];
pair<I,I>edgs[N-1];
I ancs[N][LOGN];
Lli accs[N][LOGN][2][2];
I tbgs[N],teds[N];
priority_queue<tuple<Lli,I,I>>ques;
I tim=0;
void add1(I i,Lli d){
  if(d<w_arr[i])w_arr[i]=d,ques.push({-d,1,i});
}
void add2(I i,Lli d){
  I i1=i/2,i2=i%2;
  auto[w1,w2]=wgts[i1];
  if(i2==0){
    if(d<w1)wgts[i1]={d,w2},ques.push({-d,0,i});
  }
  if(i2==1){
    if(d<w2)wgts[i1]={w1,d},ques.push({-d,0,i});
  }
}
void dfs(I a,I p=-1){
  tbgs[a]=tim++;
  for(auto[b,i]:adjs[a])if(b!=p){
    auto[w1,w2]=wgts[i];
    Lli w3=w_arr[a],w4=w_arr[b];
    ancs[b][0]=a;
    accs[b][0][0][0]=w1;
    accs[b][0][0][1]=min(w1+w3,w4+w2);
    accs[b][0][1][0]=min(w1+w4,w3+w2);
    accs[b][0][1][1]=w2;
    dfs(b,a);
  }
  teds[a]=tim;
}
B anc(I a,I b){
  return tbgs[a]<=tbgs[b]&&teds[a]>=teds[b];
}
I lca(I a,I b){
  if(anc(a,b))return a;
  if(anc(b,a))return b;
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a][i],b))a=ancs[a][i];
  return ancs[a][0];
}
Lli dis(I a,I b){
  I a1=a/2,a2=a%2,b1=b/2,b2=b%2;
  if(a1==b1)return a2!=b2?w_arr[a1]:0;
  static Lli diss1[2],diss2[2];
  fill_n(diss1,2,MAX),diss1[a2]=0;
  for(I i=LOGN-1;i>=0;i--)if(!anc(ancs[a1][i],b1)){
    diss2[0]=min(diss1[0]+accs[a1][i][0][0],diss1[1]+accs[a1][i][1][0]);
    diss2[1]=min(diss1[0]+accs[a1][i][0][1],diss1[1]+accs[a1][i][1][1]);
    a1=ancs[a1][i];
    swap(diss1,diss2);
  }
  return min(diss1[0]+accs[a1][0][0][b2],diss1[1]+accs[a1][0][1][b2]);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>w_arr[i];
  for(I i=0;i<n-1;i++){
    I x,y;Lli w1,w2;cin>>x>>y>>w1>>w2,x--,y--;
    adjs[x].push_back({y,i});
    adjs[y].push_back({x,i});
    wgts[i]={w1,w2};
    edgs[i]={x,y};
  }
  for(I i=0;i<n-1;i++){
    auto[w1,w2]=wgts[i];
    ques.push({-w1,0,i*2+0});
    ques.push({-w2,0,i*2+1});
  }
  for(I i=0;i<n;i++)ques.push({-w_arr[i],1,i});
  while(ques.size()){
    auto[w,t,i]=ques.top();ques.pop(),w=-w;
    if(t==0){
      I i1=i/2,i2=i%2;
      auto[w1,w2]=wgts[i1];
      auto[j,k]=edgs[i1];
      if(i2==0){
        if(w!=w1)continue;
        add1(j,w_arr[k]+w1+w2);
        add1(k,w_arr[j]+w1+w2);
      }
      if(i2==1){
        if(w!=w2)continue;
        add1(j,w_arr[k]+w1+w2);
        add1(k,w_arr[j]+w1+w2);
      }
    }
    if(t==1){
      if(w!=w_arr[i])continue;
      for(auto[j,k]:adjs[i]){
        auto[w1,w2]=wgts[k];
        add2(k*2+0,w2+w_arr[i]+w_arr[j]);
        add2(k*2+1,w1+w_arr[i]+w_arr[j]);
        add1(j,w_arr[i]+w1+w2);
      }
    }
  }
  dfs(0,0);
  for(I i=1;i<LOGN;i++)for(I j=0;j<n;j++){
    I k=ancs[j][i-1],l=ancs[k][i-1];
    ancs[j][i]=l;
    accs[j][i][0][0]=min(accs[j][i-1][0][0]+accs[k][i-1][0][0],accs[j][i-1][0][1]+accs[k][i-1][1][0]);
    accs[j][i][0][1]=min(accs[j][i-1][0][0]+accs[k][i-1][0][1],accs[j][i-1][0][1]+accs[k][i-1][1][1]);
    accs[j][i][1][0]=min(accs[j][i-1][1][0]+accs[k][i-1][0][0],accs[j][i-1][1][1]+accs[k][i-1][1][0]);
    accs[j][i][1][1]=min(accs[j][i-1][1][0]+accs[k][i-1][0][1],accs[j][i-1][1][1]+accs[k][i-1][1][1]);
  }
  I q;cin>>q;
  while(q--){
    I u,v;cin>>u>>v,u--,v--;
    I t=lca(u/2,v/2);
    printf("%lli\n",min(dis(u,2*t+0)+dis(v,2*t+0),dis(u,2*t+1)+dis(v,2*t+1)));
  }
}