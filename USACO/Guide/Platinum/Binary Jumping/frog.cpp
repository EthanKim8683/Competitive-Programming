#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=1000000;
const I LOGN=20;
const Lli P=1e18;
Lli p_arr[N];
I rdjs[N];
vector<I>adjs[N];
I lens[N];
I diss[N];
I ancs[N][LOGN];
I n,k;
I fnd(I i){
  I l=max(i+k-(n-1),0),r=min(i,k);
  while(l<r){
    I m=l+(r-l)/2;
    p_arr[i]-p_arr[i-m]>=p_arr[i+k-m]-p_arr[i]?r=m:l=m+1;
  }
  I a=p_arr[i]-p_arr[i-l]>=p_arr[i+k-l]-p_arr[i]?i-l:i+k-l;
  l=max(i+k-(n-1),0),r=min(i,k);
  while(l<r){
    I m=l+(r-l+1)/2;
    p_arr[i]-p_arr[i-m]<=p_arr[i+k-m]-p_arr[i]?l=m:r=m-1;
  }
  I b=p_arr[i]-p_arr[i-l]>=p_arr[i+k-l]-p_arr[i]?i-l:i+k-l;
  return abs(p_arr[i]-p_arr[a])<=abs(p_arr[i]-p_arr[b])?a:b;
}
void dfs(I a,I d=0){
  diss[a]=d;
  for(auto b:adjs[a])if(!lens[b]){
    lens[b]=lens[a];
    dfs(b,d+1);
  }
}
void fld(I a){
  I b=a;
  I len=0;
  do{
    a=rdjs[a];
    b=rdjs[rdjs[b]];
    len++;
  }while(a!=b);
  do{
    lens[a]=len;
    a=rdjs[a];
  }while(a!=b);
  do{
    dfs(a);
    a=rdjs[a];
  }while(a!=b);
}
I jmp(I i,Lli j){
  for(I k=0;k<LOGN;k++)if(j>>k&1)i=ancs[i][k];
  return i;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli m;cin>>n>>k>>m;
  for(I i=0;i<n;i++)cin>>p_arr[i];
  for(I i=0;i<n;i++){
    I j=fnd(i);
    ancs[i][0]=rdjs[i]=j;
    adjs[j].push_back(i);
  }
  for(I i=0;i<n;i++)if(!lens[i])fld(i);
  for(I i=1;i<LOGN;i++)for(I j=0;j<n;j++)ancs[j][i]=ancs[ancs[j][i-1]][i-1];
  for(I i=0;i<n;i++){
    Lli d=min(m,(Lli)diss[i]);
    printf("%i ",jmp(jmp(i,d),(m-d)%lens[i])+1);
  }
}