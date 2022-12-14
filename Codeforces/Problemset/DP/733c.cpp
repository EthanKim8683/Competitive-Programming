#include<bits/stdc++.h>
using namespace std;
using I=int;
using C=char;
const I N=500;
const I K=N;
I a_arr[N];
I b_arr[K];
vector<pair<I,C>>ress;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  I k;cin>>k;
  for(I i=0;i<k;i++)cin>>b_arr[i];
  I j=0,k=0,sum=0;
  for(I i=0;i<n;i++){
    if(sum<b_arr[k]){sum+=a_arr[i];continue;}
    if(sum>b_arr[k])printf("NO\n"),exit(0);
    if(sum==b_arr[k]){
      if(i+1-j==1)continue;
      I low=*min_element(a_arr+j,a_arr+i+1);
      I upp=*max_element(a_arr+j,a_arr+i+1);
      if(low==upp)printf("NO\n"),exit(0);
      tuple<I,I,C>cur={-1,-1,-1};
      for(I o=j;o+1<=i;o++){
        I a=a_arr[o+0],b=a_arr[o+1];
        if(a==b)continue;
        if(a>b)cur=max(cur,{a+b,o+0,'R'});
        if(a<b)cur=max(cur,{a+b,o+1,'L'});
      }
      if(get<0>(cur)==-1)printf("NO\n"),exit(0);
      auto[sum,o,t]=cur;
      ress.push_back({o,t});
      
      j=i+1,k++;
    }
  }
}