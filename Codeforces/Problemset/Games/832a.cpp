#include<bits/stdc++.h>
using namespace std;
using I=int;
using Lli=long long int;
using C=char;
I main(){
  cin.tie(0)->sync_with_stdio(0);
  Lli n,k;cin>>n>>k;
  printf("%s",(C*[]){"NO","YES"}[n/k%2]);
}
/*
it does not matter if a player removes k sticks from the left or right during
their turn, there still remains n - k sticks

therefore, the loser is the player whose turn has fewer than k sticks, equal to
Sasha if floor(n / k) % 2 = 0 and Lena if it's 1
*/