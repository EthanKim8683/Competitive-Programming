#include<bits/stdc++.h>
using namespace std;
using I=int;
using B=bool;
const I N=2e5;
I a_arr[N];
vector<I>stks;
I main(){
  I n;cin>>n;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  B res=1;
  for(I i=0;i<n;i++){
    while(stks.size()&&a_arr[i]>a_arr[stks.back()])stks.pop_back();
    I j=-1;
    if(stks.size()){
      j=stks.back();
      if(a_arr[i]==a_arr[stks.back()])stks.pop_back();
    }
    stks.push_back(i),res&=(i-j)%2;
  }
  stks.clear();
  for(I i=n-1;i>=0;i--){
    while(stks.size()&&a_arr[i]>a_arr[stks.back()])stks.pop_back();
    I j=n;
    if(stks.size()){
      j=stks.back();
      if(a_arr[i]==a_arr[stks.back()])stks.pop_back();
    }
    stks.push_back(i),res&=(j-i)%2;
  }
  printf("%s",res?"YES":"NO");
}