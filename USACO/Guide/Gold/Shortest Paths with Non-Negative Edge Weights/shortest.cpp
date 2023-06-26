#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=2000;
const I K=N;
const Lli MAX=1e18;
Lli adjs[N][N];
I v_arr[N];
B invs[N][N];
I inds[N];
I rots[2][N];
Lli diss[2][N];
priority_queue<pair<Lli,I>>ques;
Lli segs[2*K];
I k;
void add(I t,I a,I p,Lli d){
  if(d>=diss[t][a])return;
  if(inds[a]==-1)rots[t][a]=rots[t][p];
  ques.push({-(diss[t][a]=d),a});
}
void upd(I l,I r,Lli v){
  for(l+=k,r+=k;l<r;l>>=1,r>>=1){
    if(l&1)segs[l]=min(segs[l],v),l++;
    if(r&1)r--,segs[r]=min(segs[r],v);
  }
}
Lli qry(I i){
  Lli res=MAX;
  for(i+=k;i>0;i>>=1)res=min(res,segs[i]);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&adjs[0][0],&adjs[0][0]+N*N,MAX);
  fill(&diss[0][0],&diss[0][0]+2*N,MAX);
  I n,m,a,b;cin>>n>>m>>a>>b,a--,b--;
  for(I i=0;i<m;i++){
    I u,v,w;cin>>u>>v>>w,u--,v--;
    adjs[u][v]=adjs[v][u]=w;
  }
  fill_n(inds,n,-1);
  cin>>k;
  for(I i=0;i<k;i++){
    I v;cin>>v,v--;
    v_arr[i]=v,inds[v]=i,rots[0][v]=rots[1][v]=v;
  }
  for(I i=0;i+1<k;i++){
    I u=v_arr[i],v=v_arr[i+1];
    invs[u][v]=invs[v][u]=1;
  }
  add(0,a,-1,0);
  while(ques.size()){
    auto[d,a]=ques.top();ques.pop();
    if((d=-d)!=diss[0][a])continue;
    for(I b=0;b<n;b++)add(0,b,a,d+adjs[a][b]);
  }
  add(1,b,-1,0);
  while(ques.size()){
    auto[d,a]=ques.top();ques.pop();
    if((d=-d)!=diss[1][a])continue;
    for(I b=0;b<n;b++)add(1,b,a,d+adjs[a][b]);
  }
  fill_n(segs,2*k,MAX);
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)if(!invs[i][j]){
    I p=rots[0][i],q=rots[1][j],r=inds[p],s=inds[q];
    if(r>=s)continue;
    upd(r,s,diss[0][i]+diss[1][j]+adjs[i][j]);
  }
  for(I i=0;i+1<k;i++){
    Lli res=qry(i);
    printf("%lli\n",res==MAX?-1:res);
  }
}