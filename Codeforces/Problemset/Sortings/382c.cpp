#include<bits/stdc++.h>
using namespace std;
using I=int;
const I N=1e5;
I nums[N];
map<I,I>cnts;
set<I>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>nums[i];
  sort(nums,nums+n);
  for(I i=0;i+1<n;i++)cnts[nums[i+1]-nums[i]]++;
  if(cnts.size()==0)printf("-1\n"),exit(0);
  if(cnts.size()==1){
    I dif=cnts.begin()->first;
    if(dif%2==1||n>2){
      ress.insert(nums[0]-dif);
      ress.insert(nums[n-1]+dif);
      printf("%i\n",ress.size());
      for(auto i:ress)printf("%i ",i);
      exit(0);
    }
    ress.insert(nums[0]-dif);
    ress.insert(nums[0]+dif/2);
    ress.insert(nums[1]+dif);
    printf("%i\n",ress.size());
    for(auto i:ress)printf("%i ",i);
    exit(0);
  }
  if(cnts.size()==2){
    I dif1=cnts.begin()->first,dif2=cnts.rbegin()->first;
    if(dif2!=dif1*2||cnts[dif2]>1){
      printf("0\n");
      exit(0);
    }
    for(I i=0;i+1<n;i++)if(nums[i+1]-nums[i]==dif2){
      ress.insert(nums[i]+dif1);
      printf("%i\n",ress.size());
      for(auto j:ress)printf("%i ",j);
      exit(0);
    }
  }
  printf("0\n");
}