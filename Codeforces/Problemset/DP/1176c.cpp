#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=5e5;

I a_arr[N];
I dgts[]{4,8,15,16,23,42};
I cnts[6];

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  for(I i=0;i<n;i++)a_arr[i]=find(dgts,dgts+6,a_arr[i])-dgts;
  I res=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a-1>=0&&cnts[a]+1>cnts[a-1]){res++;continue;}
    cnts[a]++;
  }
  I cur=*min_element(cnts,cnts+6);
  for(I i=0;i<6;i++)res+=cnts[i]-cur;
  printf("%i\n",res);
}