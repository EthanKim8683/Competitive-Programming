def bin(n,k):
  res=1
  for i in range(n-k+1,n+1):res*=i
  for i in range(1,k+1):res//=i
  return res
n=int(input())
print(bin(n,5)+bin(n,6)+bin(n,7))