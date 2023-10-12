#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
const Lli MOD=1e9+7;
Lli facs[N+1];
vector<I>adjs[N];
I sizs[N];
Lli res1=0,res2=0;
I n,k;
Lli mpw(Lli x,Lli y){
  Lli res=1;
  for(x%=MOD;y;y>>=1,(x*=x)%=MOD)if(y&1)(res*=x)%=MOD;
  return res;
}
Lli inv(Lli x){
  return mpw(x,MOD-2);
}
Lli bin(I n,I k){
  if(n<0||k<0||n-k<0)return 0;
  return facs[n]*inv(facs[k]*facs[n-k])%MOD;
}
void dfs(I a,I p=-1){
  sizs[a]=1;
  Lli pre1=0,pre2=0;
  B lea=1;
  for(auto b:adjs[a])if(b!=p){
    dfs(b,a);
    Lli cur1=bin(sizs[b],k/2),cur2=bin(sizs[b],k/2-1);
    (res1+=pre1*cur1)%=MOD;
    (res2+=pre1*cur2)%=MOD;
    (res2+=pre2*cur1)%=MOD;
    (pre1+=cur1)%=MOD;
    (pre2+=cur2)%=MOD;
    sizs[a]+=sizs[b];
    lea=0;
  }
  if(lea&&k/2-1==0)pre2=1;
  Lli cur1=bin(n-sizs[a],k/2),cur2=bin(n-sizs[a],k/2-1);
  (res1+=pre1*cur1)%=MOD;
  (res2+=pre1*cur2)%=MOD;
  (res2+=pre2*cur1)%=MOD;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  facs[0]=1;
  for(I i=1;i<=N;i++)facs[i]=facs[i-1]*i%MOD;
  cin>>n>>k;
  for(I i=0;i<n-1;i++){
    I u,v;cin>>u>>v,u--,v--;
    adjs[u].push_back(v);
    adjs[v].push_back(u);
  }
  if(k%2==1)printf("1"),exit(0);
  dfs(0);
  (res2*=inv(2))%=MOD;
  printf("%lli\n",((res1+res2)*inv(bin(n,k))+1)%MOD);
}
/*
if the number of friends f in a subtree of node a is greater than k / 2, a is
not good because LuoTianyi can move in the direction of said subtree,
decreasing the cost by f - (n - f), which will always be greater than 0 since
f > k / 2

this means if k is odd, there is always only one good node

if k is even, in addition to the default good node, nodes can be good if there
are exactly k / 2 friends in two different subtrees of a node
*/