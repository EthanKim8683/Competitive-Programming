#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;

using I=int;
using B=bool;

const I N=1e5;
const I MIN=-1e9;
const I MAX=1e9;

I x_arr[N];
I mins[N];
I maxs[N];
B blks[N][3];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  fill_n(mins,n,MAX);
  fill_n(maxs,n,MIN);
  for(I i=0;i<k;i++){
    I x;cin>>x,x--;
    mins[x]=min(mins[x],i);
    maxs[x]=max(maxs[x],i);
  }
  I res=0;
  for(I i=0;i<n;i++){
    res+=i-1>=0&&maxs[i-1]<mins[i];
    res+=maxs[i]<mins[i];
    res+=i+1<n&&maxs[i+1]<mins[i];
  }
  printf("%i\n",res);
  return 0;
}