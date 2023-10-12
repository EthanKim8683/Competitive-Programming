#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I M=1e5;
const Lli FAC=1e5;
const I MAX=1e9;
I diss[M+1];
I pars[M+1];
vector<I>inds[M+1];
queue<I>ques;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,m;cin>>n>>m;
  fill_n(diss,m+1,MAX),diss[0]=0;
  for(I i=0;i<n;i++){
    Lli t,x,y;cin>>t>>x>>y;
    for(I j=0;j<=m;j++)inds[j].clear();
    iota(pars,pars+m+1,0);
    if(t==1){
      for(I j=0;j<=m;j++){
        Lli k=j+(x+FAC-1)/FAC;
        if(k<=m)pars[k]=min(pars[k],pars[j]);
        inds[pars[j]].push_back(j);
      }
    }
    if(t==2){
      for(I j=0;j<=m;j++){
        Lli k=(j*x+FAC-1)/FAC;
        if(k<=m)pars[k]=min(pars[k],pars[j]);
        inds[pars[j]].push_back(j);
      }
    }
    for(I j=0;j<=m;j++){
      while(ques.size())ques.pop();
      for(I k=0;k<inds[j].size();k++){
        I l=inds[j][k];
        if(diss[l]!=MAX)ques.push(k+y);
        while(ques.size()&&ques.front()<k)ques.pop();
        if(ques.size())diss[l]=min(diss[l],i+1);
      }
    }
  }
  for(I i=1;i<=m;i++)printf("%i ",diss[i]==MAX?-1:diss[i]);
}
/*
if we form a graph containing all [0, m] with edges based on the values after
applying a single update, we form a chain

the chain makes it easy to determine what values can be made at any time,
since a queue can keep track of the last reachable value before the operation

if the last reachable value is less than or equal to y operations away, the
current value is also reachable after the current operation (if it isn't
already)
*/