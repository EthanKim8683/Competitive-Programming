#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
const I A=2e5;
I a_arr[N];
vector<I>adjs[N];
I eras[A+1];
I sizs[N];
B viss[N];
map<I,I>accs,curs;
I res=0;
I gcd(I a,I b){
  return b?gcd(b,a%b):a;
}
I dfs1(I a,I p=-1){
  sizs[a]=1;
  for(auto b:adjs[a])if(b!=p&&!viss[b])sizs[a]+=dfs1(b,a);
  return sizs[a];
}
I dfs2(I a,I siz,I p=-1){
  for(auto b:adjs[a])if(b!=p&&!viss[b]&&2*sizs[b]>siz)return dfs2(b,siz,a);
  return a;
}
void dfs4(I a,I g,I dis,I p=-1){
  for(I i=g;i>1;i/=eras[i]){
    I fac=eras[i];
    curs[fac]=max(curs[fac],dis);
  }
  for(auto b:adjs[a])if(b!=p&&!viss[b])dfs4(b,gcd(g,a_arr[b]),dis+1,a);
}
void dfs3(I a){
  a=dfs2(a,dfs1(a));
  viss[a]=1;
  accs.clear();
  for(I i=a_arr[a];i>1;i/=eras[i])accs[eras[i]]=0,res=max(res,1);
  for(auto b:adjs[a])if(!viss[b]){
    curs.clear();
    dfs4(b,gcd(a_arr[a],a_arr[b]),1,a);
    for(auto[fac,dis]:curs){
      if(accs.count(fac))res=max(res,accs[fac]+1+dis);
      accs[fac]=max(accs[fac],dis);
    }
  }
  for(auto b:adjs[a])if(!viss[b])dfs3(b);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(eras,eras+A+1,0);
  for(I i=2;i*i<=A;i++)if(eras[i]==i)for(I j=i*i;j<=A;j+=i)eras[j]=min(eras[j],i);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n-1;i++){
    I x,y;cin>>x>>y,x--,y--;
    adjs[x].push_back(y);
    adjs[y].push_back(x);
  }
  dfs3(0);
  printf("%i\n",res);
}