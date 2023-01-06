#include<bits/stdc++.h>
using namespace std;
using I=int;
const I MAX=1e9;
I a_arr[3];
I b_arr[3];
I tmps1[3],tmps2[3];
vector<pair<I,I>>loss;
vector<pair<I,I>>wins;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n;cin>>n;
  for(I i=0;i<3;i++)cin>>a_arr[i];
  for(I i=0;i<3;i++)cin>>b_arr[i];
  for(I i=0;i<3;i++)for(I j=0;j<3;j++)(i==(j+2)%3?wins:loss).push_back({i,j});
  I res1=MAX,res2=0;
  sort(loss.begin(),loss.end());
  do{
    copy_n(a_arr,3,tmps1),copy_n(b_arr,3,tmps2);
    for(auto[i,j]:loss){
      I dif=min(tmps1[i],tmps2[j]);
      tmps1[i]-=dif,tmps2[j]-=dif;
    }
    I sum=0;
    for(auto[i,j]:wins)sum+=min(tmps1[i],tmps2[j]);
    res1=min(res1,sum);
  }while(next_permutation(loss.begin(),loss.end()));
  for(I i=0;i<3;i++)res2+=min(a_arr[i],b_arr[(i+1)%3]);
  printf("%i %i\n",res1,res2);
}