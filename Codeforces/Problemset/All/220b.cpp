#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
const I M=1e5;
I a_arr[N];
vector<pair<I,I>>qrys[N];
vector<I>inds[N];
I fens[N+1];
I ress[M];
I n;
I tot=0;
void upd(I i,I val){
  tot+=val;
  for(i++;i<=n;i+=i&-i)fens[i]+=val;
}
I qry(I i){
  I res=0;
  for(;i>0;i-=i&-i)res+=fens[i];
  return res;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I m;cin>>n>>m;
  for(I i=0;i<n;i++){I a;cin>>a,a_arr[i]=a-1;}
  for(I i=0;i<m;i++){
    I l,r;cin>>l>>r;
    qrys[r-1].push_back({l-1,i});
  }
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a>=n)continue;
    inds[a].push_back(i);
  }
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a<n){
      I j=lower_bound(inds[a].begin(),inds[a].end(),i)-inds[a].begin();
      if(j-a-2>=0)upd(inds[a][j-a-2],1);
      if(j-a-1>=0)upd(inds[a][j-a-1],-2);
      if(j-a-0>=0)upd(inds[a][j-a-0],1);
    }
    for(auto[j,k]:qrys[i])ress[k]=tot-qry(j);
  }
  for(I i=0;i<m;i++)printf("%i\n",ress[i]);
}