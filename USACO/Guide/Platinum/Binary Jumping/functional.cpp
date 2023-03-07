#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1e5;
const I LOGN=17;
B viss[N];
vector<I>adjs[N];
I pars[N];
Lli pdss[N];
I coms[N],rots[N];
Lli diss[N];
Lli cdss[N],tots[N];
I inds[N],lens[N];
I tbgs[N],teds[N];
I ancs[N][LOGN];
I tim=0;
void dfs(I a,I p){
  tbgs[a]=tim++;
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  for(auto b:adjs[a])if(!viss[b]){
    viss[b]=1;
    diss[b]=diss[a]+pdss[b];
    rots[b]=rots[a];
    coms[b]=coms[a];
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
void fld(I x){
  I y=x;
  do{
    x=pars[x];
    y=pars[pars[y]];
  }while(x!=y);
  Lli tot=0;
  I len=0;
  do{
    cdss[x]=tot;
    inds[x]=len;
    viss[x]=1;
    tot+=pdss[x];
    len++;
    x=pars[x];
  }while(x!=y);
  do{
    tots[x]=tot;
    lens[x]=len;
    rots[x]=x;
    coms[x]=y;
    dfs(x,x);
    x=pars[x];
  }while(x!=y);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I a,b,ka,kb,la,lb;cin>>a>>b>>ka>>kb>>la>>lb;
  I n=a*b;
  for(I i=0;i<n;i++){
    I d=1;
    if(i%b==kb)d=lb;
    if(i%a==ka)d=la;
    I j=i-d,x=j/n,y=j%n;
    if(y<0)x--,y+=n;
    pars[i]=y,pdss[i]=-x;
    adjs[y].push_back(i);
  }
  for(I i=0;i<n;i++)if(!viss[i])fld(i);
  I q;cin>>q;
  while(q--){
    I x,y;cin>>x>>y;
    I x2=x%n,y2=y%n;Lli x1=x/n,y1=y/n;
    if(coms[x2]!=coms[y2]){
      printf("-1\n");
      continue;
    }
    I x4=rots[x2];Lli x3=x1-(diss[x2]-diss[x4]);
    I y4=rots[y2];Lli y3=y1-(diss[y2]-diss[y4]);
    if(x4==y4&&x3==y3){
      I x6=lca(x2,y2);Lli x5=x1-(diss[x2]-diss[x6]);
      Lli res=x5*n+x6;
      printf("%lli\n",res<=0?-1:res);
      continue;
    }
    Lli tot=tots[x4];
    I x6,y6;Lli x5,y5;
    if(inds[x4]<inds[y4]){
      x6=y4,x5=x3-(cdss[x6]-cdss[x4]);
      y6=x4,y5=y3-(cdss[y6]-cdss[y4]+tot);
    }else{
      y6=x4,y5=y3-(cdss[y6]-cdss[y4]);
      x6=y4,x5=x3-(cdss[x6]-cdss[x4]+tot);
    }
    Lli res=-1;
    if((x5-y3)%tot==0)res=max(res,min(x5*n+x6,y3*n+y4));
    if((y5-x3)%tot==0)res=max(res,min(y5*n+y6,x3*n+x4));
    printf("%lli\n",res<=0?-1:res);
  }
}