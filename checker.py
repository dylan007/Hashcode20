scores=[int(i) for i in input().split()]
libs = int(input())
s=set()
final=0
for _ in range(libs):
	a,b=[int(i) for i in input().split()]
	for i in input().split():
		final+=scores[i]
		scores[i]=0