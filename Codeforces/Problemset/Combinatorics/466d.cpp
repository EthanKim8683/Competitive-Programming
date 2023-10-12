#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
const I N=2000;
const Lli MOD=1e9+7;
I a_arr[N];
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,h;cin>>n>>h;
  for(I i=0;i<n;i++)cin>>a_arr[i];
  Lli res=1;
  I pre=h,cnt=0;
  for(I i=0;i<n;i++){
    I a=a_arr[i];
    if(a==pre-1)cnt++;
    else if(a==pre+1)(res*=cnt)%=MOD,cnt--;
    else if(a==pre)(res*=cnt+1)%=MOD;
    else res=0;
    if(cnt<0)res=0;
    pre=a;
  }
  if(h==pre-1)cnt++;
  else if(h==pre+1)(res*=cnt)%=MOD,cnt--;
  else if(h==pre)(res*=cnt+1)%=MOD;
  else res=0;
  if(cnt!=0)res=0;
  printf("%lli\n",res);
}
/*
at each index i (let a[-1] = h, a[n] = h):
- if a[i] == a[i - 1] - 1, we must begin a new segment
- else if a[i] == a[i - 1] + 1, we must end a segment
- else if a[i] == a[i - 1], we can replace a segment (or do nothing)
- otherwise, no combination of segments can make all elements equal h

if the number of segments is below 0 at any point, or not equal to 0 in the
end, no combination of segments can make all elements equal h
*/