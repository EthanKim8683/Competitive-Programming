#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=1e5;
const I M=1e5;
const I A=1e7;
I a_arr[N];
I b_arr[M];
I eras[A+1];
I cnts[A+1];
vector<I>pros[2];
vector<I>ress[2];
void add(I i,I j){
  if(!ress[i].size())ress[i].push_back(1);
  if((Lli)ress[i].back()*j>A)ress[i].push_back(j);
  else ress[i].back()*=j;
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  iota(eras,eras+A+1,0);
  for(I i=2;i*i<=A;i++)if(eras[i]==i)for(I j=i*i;j<=A;j+=i)eras[j]=min(eras[j],i);
  I n,m;cin>>n>>m;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<m;i++)cin>>b_arr[i];
  for(I i=0;i<n;i++)for(I a=a_arr[i],prm;a>1;a/=prm)cnts[prm=eras[a]]++,pros[0].push_back(prm);
  for(I i=0;i<m;i++)for(I b=b_arr[i],prm;b>1;b/=prm)cnts[prm=eras[b]]--,pros[1].push_back(prm);
  for(auto i:pros[0])if(cnts[i]>0)add(0,i),cnts[i]--;
  for(auto i:pros[1])if(cnts[i]<0)add(1,i),cnts[i]++;
  for(I i=0;i<2;i++)if(!ress[i].size())add(i,1);
  printf("%i %i\n",ress[0].size(),ress[1].size());
  for(I i=0;i<2;i++){
    for(auto j:ress[i])printf("%i ",j);
    printf("\n");
  }
}