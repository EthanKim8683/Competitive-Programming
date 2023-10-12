#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=200;
const I LOGN=8;
const Lli MOD=1e9+7;
vector<I>adjs[N];
Lli facs[N+1];
Lli dp[N+1][N+1];
I ancs[N][LOGN];
I tbgs[N],teds[N];
I deps[N];
I tim=0;
I n;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  return facs[n]*inv(facs[n-k]*facs[k])%MOD;
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
void dfs(I a,I p,I d=0){
  ancs[a][0]=p;
  for(I i=1;i<LOGN;i++)ancs[a][i]=ancs[ancs[a][i-1]][i-1];
  deps[a]=d;
  tbgs[a]=tim++;
  for(auto b:adjs[a])if(b!=p)dfs(b,a,d+1);
  teds[a]=tim;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  cin>>n;
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  for(I i=0;i<=n;i++)for(I j=0;j<=n;j++)dp[i][j]=bin(i+j,i)*mpw(inv(2),i+j+1)%MOD;
  for(I i=0;i<=n;i++)for(I j=0;j+1<=n;j++)(dp[i][j+1]+=dp[i][j])%=MOD;
  Lli res=0;
  for(I r=0;r<n;r++){
    dfs(r,r);
    for(I a=0;a<n;a++)for(I b=0;b<a;b++){
      I c=lca(a,b);
      if(a==c){(res+=1)%=MOD;continue;}
      if(b==c){(res+=0)%=MOD;continue;}
      I x=deps[a]-deps[c]-1,y=deps[b]-deps[c]-1;
      (res+=dp[x][y])%=MOD;
    }
  }
  (res*=inv(n))%=MOD;
  printf("%lli\n",res);
}
/*
we can total the contribution of each inversion pair from all possible roots,
equivalent to the probability of a being marked before b where a > b

this can be checked by finding, from root r, the least common ancestor c of a
and b and, if a = c, then the contribution is 1, if b = c, it's 0

otherwise, we can denote the nodes between a and c (non-inclusive) X, and the
nodes between b and c (again, non-inclusive) Y

since the probability of a node in X being marked is equal to that of a node in
Y, there is a 1 / 2 probability of a step towards a, and a 1 / 2 probability of
a step towards b

therefore, the probability of a being marked before b is equal to the sum of
bin(|X| + j, |X|) * (1 / 2) ^ (|X| + j) * (1 / 2) for all j in [0, |Y|], since
we must mark all nodes in |X| and any number of nodes in |Y| in any order, but
the final mark must go to a itself
*/