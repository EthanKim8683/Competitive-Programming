#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using I128=__int128;
const I N=500;
const Lli BAS=87321;
const Lli MOD=(1ll<<61)-1;
I a_arr[N][N];
vector<I>ancs[N];
vector<I>inds[N];
I sals[N*N];
set<pair<I,I>>edgs;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)for(I j=0;j<n;j++)cin>>a_arr[i][j];
  I ind=0;
  for(I i=0;i<n;i++){
    for(I j=0;j<n;j++)ancs[i].push_back(a_arr[i][j]);
    sort(ancs[i].begin(),ancs[i].end());
    ancs[i].erase(unique(ancs[i].begin(),ancs[i].end()),ancs[i].end());
    inds[i].resize(ancs[i].size(),-1);
    sals[ind]=ancs[i][0],inds[i][0]=ind++;
  }
  for(I i=0;i<n;i++)for(I j=0;j<n;j++){
    I k=lower_bound(ancs[i].begin(),ancs[i].end(),a_arr[i][j])-ancs[i].begin();
    I l=lower_bound(ancs[j].begin(),ancs[j].end(),a_arr[i][j])-ancs[j].begin();
    if(inds[i][k]!=-1){inds[j][l]=inds[i][k];continue;}
    if(inds[j][l]!=-1){inds[i][k]=inds[j][l];continue;}
    sals[ind]=ancs[i][k],inds[i][k]=inds[j][l]=ind++;
  }
  for(I i=0;i<n;i++)for(I j=0;j+1<inds[i].size();j++)edgs.insert({inds[i][j],inds[i][j+1]});
  printf("%i\n",ind);
  for(I i=0;i<ind;i++)printf("%i ",sals[i]);
  printf("\n%i\n",inds[0].back()+1);
  for(auto[i,j]:edgs)printf("%i %i\n",i+1,j+1);
}
/*
since all non-lower-level employees have at least two subordinates, the set of
unique a[i][j] for a lower-level employee i describes the chain of supervisors
ending with employee i

we can use the provided lca salaries to assign indices to the superiors of
each lower-level employee, from which we can determine the remaining data to
answer the problem
*/