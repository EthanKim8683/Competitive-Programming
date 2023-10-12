#include<bits/stdc++.h>
using namespace std;
using I=int;
const I K=1e6;
const I N=1000;
const I M=(N+N)*N;
const I MAX=1e9;
I a_arr[K];
I diss[M+M+1];
queue<I>ques;
vector<I>unqs;
void add(I d,I a){
  if(a==0)printf("%i\n",d),exit(0);
  if(a<-M||a>M||d>=diss[a+M])return;
  diss[a+M]=d,ques.push(a);
}
I main(){
  cin.tie(0)->sync_with_stdio(0);
  I n,k;cin>>n>>k;
  for(I i=0;i<k;i++)cin>>a_arr[i];
  for(I i=0;i<k;i++)unqs.push_back(a_arr[i]-n);
  sort(unqs.begin(),unqs.end());
  unqs.erase(unique(unqs.begin(),unqs.end()),unqs.end());
  fill_n(diss,M+M+1,MAX);
  for(I i=0;i<k;i++)add(1,a_arr[i]-n);
  while(ques.size()){
    I a=ques.front();ques.pop();
    for(auto b:unqs)add(diss[a+M]+1,a+b);
  }
  printf("-1");
}
/*
we can use math to first simplify the problem:
  (cnts[0] * a[0] + cnts[1] * a[1] + ... + cnts[k - 1] * a[k - 1]) / (cnts[0] +
  cnts[1] + ... cnts[k - 1]) / 1000 = n / 1000
= (cnts[0] * a[0] + cnts[1] * a[1] + ... + cnts[k - 1] * a[k - 1]) / (cnts[0] +
  cnts[1] + ... cnts[k - 1]) = n
= cnts[0] * a[0] + cnts[1] * a[1] + ... + cnts[k - 1] * a[k - 1] = (cnts[0] +
  cnts[1] + ... cnts[k - 1]) * n
= cnts[0] * a[0] + cnts[1] * a[1] + ... + cnts[k - 1] * a[k - 1] = cnts[0] * n
  + cnts[1] * n + ... cnts[k - 1] * n
= cnts[0] * (a[0] - n) + cnts[1] * (a[1] - n) + ... + cnts[k - 1] * (a[k - 1] -
  n) = 0

with this equation, it can be shown that the problem can always be solved
using at most 2000 liters:
  (lcm(a[0], a[1]) / a[0]) * a[0] - (lcm(a[0], a[1]) / a[1]) * a[1] = 0
  lcm(a[0], a[1]) / a[0] + lcm(a[0], a[1]) / a[1] <= 2000

and since at most 2000 liters may be used, the absolute linear combinations of
a[i] - n for all i cannot exceed 2000 * 1000 = 2000000

therefore, we can use breadth-first search to find the least number of liters
to produce any linear combination sum above

in addition, the number of rounds of searches required goes down as the number
of unique a increases, roughly equivalent to (1000 - |a|) * (1000 - |a|) * |a|
*/