#include<bits/stdc++.h>

using namespace std;

using I=int;

const I N=1e5;

I a_arr[N];
vector<I>vals;

I main(){
  cin.tie(0)->sync_with_stdio(0);
  I t;cin>>t;
  while(t--){
    I n;cin>>n;
    vals.clear();
    for(I i=0;i<n;i++)cin>>a_arr[i];
    for(I i=0;i<n;i++){
      if(a_arr[i]!=-1)continue;
      if(i-1>=0&&a_arr[i-1]!=-1)vals.push_back(a_arr[i-1]);
      if(i+1<n&&a_arr[i+1]!=-1)vals.push_back(a_arr[i+1]);
    }
    if(!vals.size()){printf("0 0\n");continue;}
    I low=*min_element(vals.begin(),vals.end());
    I upp=*max_element(vals.begin(),vals.end());
    I mid=low+(upp-low)/2;
    for(I i=0;i<n;i++)if(a_arr[i]==-1)a_arr[i]=mid;
    I res=0;
    for(I i=0;i+1<n;i++)res=max(res,abs(a_arr[i]-a_arr[i+1]));
    printf("%i %i\n",res,mid);
  }
}