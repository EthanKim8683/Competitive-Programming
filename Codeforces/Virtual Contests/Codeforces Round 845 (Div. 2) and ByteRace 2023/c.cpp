#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=1e5;
const I M=1e5;
const I A=1e5;
const I MAX=1e9;
I a_arr[N];
I sivs[A+1];
vector<I>facs[N];
map<I,I>cnts;
I tots[M+1];
I cnt=0;
I m;
void dfs(I i,map<I,I>::iterator it,I val=1){
  if(val>m)return;
  if(it==cnts.end()){facs[i].push_back(val);return;}
  for(I j=0;j<=it->second;j++)dfs(i,next(it),val),val*=it->first;
}
void add(I i){
  for(auto fac:facs[i]){
    if(tots[fac]==0)cnt++;
    tots[fac]++;
  }
}
void rem(I i){
  for(auto fac:facs[i]){
    tots[fac]--;
    if(tots[fac]==0)cnt--;
  }
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  for(I i=2;i<=A;i++)if(!sivs[i])for(I j=i;j<=A;j+=i)if(!sivs[j])sivs[j]=i;
  I t;cin>>t;
  while(t--){
    I n;cin>>n>>m;
    fill_n(tots,m,0),cnt=0;
    for(I i=0;i<n;i++)cin>>a_arr[i];
    sort(a_arr,a_arr+n);
    for(I i=0;i<n;i++){
      facs[i].clear(),cnts.clear();
      for(I a=a_arr[i];a>1;a/=sivs[a])cnts[sivs[a]]++;
      dfs(i,cnts.begin());
    }
    I l=0,r=0,res=MAX;
    while(l<r||r<n){
      if(r==n)rem(l++);
      else if(l==r)add(r++);
      else if(cnt>=m)rem(l++);
      else if(cnt<m)add(r++);
      if(cnt==m)res=min(res,a_arr[r-1]-a_arr[l]);
    }
    printf("%i\n",res==MAX?-1:res);
  }
}