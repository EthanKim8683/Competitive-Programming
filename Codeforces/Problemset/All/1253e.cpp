#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=80;
const I M=100000;
const I MAX=1e9;
pair<I,I>ants[N];
I segs[N+1][2*(4*M+2)];
I m;
void upd(I t,I l,I r,I val){
  for(l+=m+(4*m+2),r+=m+(4*m+2);l<r;l>>=1,r>>=1){
    if(l&1)segs[t][l]=min(segs[t][l],val),l++;
    if(r&1)r--,segs[t][r]=min(segs[t][r],val);
  }
}
I qry(I t,I i){
  I res=MAX;
  for(i+=m+(4*m+2);i>0;i>>=1)res=min(res,segs[t][i]);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  fill(&segs[0][0],&segs[0][0]+(N+1)*(2*(4*M+2)),MAX);
  I n;cin>>n>>m;
  for(I i=0;i<n;i++){
    I x,s;cin>>x>>s,x--;
    ants[i]={x,s};
  }
  sort(ants,ants+n);
  upd(0,-m,0+1,0);
  for(I i=-m;i<m;i++)for(I j=0;j<n;j++){
    auto[x,s]=ants[j];
    upd(j+1,i,x+(x-i)+2,qry(j,i)+max((x-i)-s,0));
    upd(j+1,i,i+1,qry(j,i));
  }
  I res=MAX;
  for(I i=0;i<=n;i++)for(I j=m;j<3*m+2;j++)res=min(res,qry(i,j));
  printf("%i\n",res);
}