#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I K=500;
const I MAX=1e9+1;

I diss[K][K];
I typs[N];
I rots[N];
I c_arr[K];
I pars[N];

I fnd(I i){
  if(pars[i]<0)return i;
  return pars[i]=fnd(pars[i]);
}

void uni(I a,I b){
  if((a=fnd(a))==(b=fnd(b)))return;
  if(pars[a]>pars[b])swap(a,b);
  pars[a]+=pars[b],pars[b]=a;
}

I siz(I i){
  return -pars[fnd(i)];
}

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  fill_n(pars,n,-1);
  fill(&diss[0][0],&diss[0][0]+sizeof(diss)/sizeof(I),MAX);
  I cur=0;
  for(I i=0;i<k;i++){
    I c;cin>>c;
    c_arr[i]=c;
    for(I j=0;j<c;j++)typs[cur++]=i;
  }
  for(I i=0;i<m;i++){
    I u,v,x;cin>>u>>v>>x,u--,v--;
    if(!x)uni(u,v);
    I a=typs[u],b=typs[v];
    diss[a][b]=min(diss[a][b],x);
    diss[b][a]=min(diss[b][a],x);
  }
  for(I i=0;i<n;i++)if(i==fnd(i))rots[typs[i]]=i;
  for(I i=0;i<n;i++)if(rots[typs[i]]!=fnd(i))
    printf("No\n"),exit(0);
  for(I i=0;i<k;i++)diss[i][i]=0;
  for(I i=0;i<k;i++)for(I j=0;j<k;j++)for(I l=0;l<k;l++)
    diss[j][l]=min(diss[j][l],diss[j][i]+diss[i][l]);
  printf("Yes\n");
  for(I i=0;i<k;i++){
    for(I j=0;j<k;j++)printf("%i ",diss[i][j]==MAX?-1:diss[i][j]);
    printf("\n");
  }
}