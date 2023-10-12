#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
using Lli=long long int;
const I N=1e5;
const I M=1e5;
vector<I>rows[N];
vector<I>cols[M];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m,k;cin>>n>>m>>k;
  for(I i=0;i<k;i++){
    I x,y;cin>>x>>y,x--,y--;
    rows[x].push_back(y);
    cols[y].push_back(x);
  }
  I low1=-1,upp1=n,low2=-1,upp2=m;
  Lli len=1;
  B pre=0;
  for(I i=0,j=0;;){
    I t=upp2-1;
    for(auto k:rows[i])if(k>j)t=min(t,k-1);
    if(pre&&t-j==0)break;
    len+=t-j,j=t,low1=i,upp2=j,pre=1;
    t=upp1-1;
    for(auto k:cols[j])if(k>i)t=min(t,k-1);
    if(pre&&t-i==0)break;
    len+=t-i,i=t,upp2=j,upp1=i,pre=1;
    t=low2+1;
    for(auto k:rows[i])if(k<j)t=max(t,k+1);
    if(pre&&j-t==0)break;
    len+=j-t,j=t,upp1=i,low2=j,pre=1;
    t=low1+1;
    for(auto k:cols[j])if(k<i)t=max(t,k+1);
    if(pre&&i-t==0)break;
    len+=i-t,i=t,low2=j,low1=i,pre=1;
  }
  printf("%s\n",len==(Lli)n*m-k?"Yes":"No");
}
/*
the doll can never turn left, so its traversal starts on the outer-most cells
and goes inward

we can simulate the doll's path in O(N + M)
*/