#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using B=bool;
const I N=2e5;
I v_arr[N];
I t_arr[N];
vector<I>adjs[N];
I cols[N];
B dfs(I a,I col=0){
  if(cols[a]!=-1)return cols[a]!=col;
  cols[a]=col;
  B res=0;
  for(auto b:adjs[a])res|=dfs(b,!col);
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n,m;cin>>n>>m;
    for(I i=0;i<n;i++)cin>>v_arr[i];
    for(I i=0;i<n;i++)cin>>t_arr[i];
    for(I i=0;i<n;i++)adjs[i].clear();
    for(I k=0;k<m;k++){
      I i,j;cin>>i>>j,i--,j--;
      adjs[i].push_back(j);
      adjs[j].push_back(i);
    }
    if((accumulate(v_arr,v_arr+n,0ll)+accumulate(t_arr,t_arr+n,0ll))%2){printf("NO\n");continue;}
    fill_n(cols,n,-1);
    if(dfs(0)){printf("YES\n");continue;}
    Lli acc=0;
    for(I i=0;i<n;i++){
      if(cols[i]==0)acc+=v_arr[i]-t_arr[i];
      if(cols[i]==1)acc+=t_arr[i]-v_arr[i];
    }
    printf("%s\n",acc==0?"YES":"NO");
  }
}
/*
given two nodes,
if odd distance, must add both
if even distance, must add one and subtract one

sum initial must have same parity as sum final

if odd-length cycle exists, any two nodes can add or subtract, meaning
that as long as above is satisfied, the answer is yes

if no odd-length cycle exists, graph can be two-colored, meaning that if
sum initial white - sum final white == sum initial black - sum final black,
the answer is also yes
*/