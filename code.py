B, L, D = [int(i) for i in input().split()]
books = [int(i) for i in input().split()]
new_scores = [0 for i in range(B)]
book_f = [0 for i in range(B)]
lib=[]

for _ in range(L):
	n, t, m = [int(i) for  i in input().split()]
	ids = [int(i) for i in input().split()]
	d={}
	d["n"]=n
	d["t"]=t
	d["m"]=m
	d["ids"]=ids
	d["score"]=0
	lib.append(d)
	for i in ids:
		book_f[i]+=1
for i in range(B):
	new_scores[i]=books[i]/max(book_f[i],1)

def value(elem):
	return new_scores[elem]

def rescore(library,days,ndone):
	largest=0
	for i in ndone:
		score=0
		library[i]["ids"].sort(key=value, reverse=True)
		# for k in library[i]:
			# print(k,library[i][k])
		nums=min((D-days-library[i]["t"])*library[i]["m"],library[i]["n"])
		for j in range(nums):
			score += new_scores[library[i]["ids"][j]]
		library[i]["score"]=score
		if (library[largest]["score"])**(1.5)/library[largest]["t"] < (library[i]["score"])**(1.5)/library[i]["t"]:
			largest = i
	return largest

def calc_scores(library,i,days):
	score=0
	library[i]["score"]=0
	ds=max(0,(D-days-library[i]["t"])*library[i]["m"])
	print(min(ds,library[i]["n"]))
	for j in range(library[i]["n"]):
		if j < ds:
			if(new_scores[library[i]["ids"][j]]>0):
				score += books[library[i]["ids"][j]]
			print(library[i]["ids"][j],end=' ')
			new_scores[library[i]["ids"][j]]=0
		else:
			k = library[i]["ids"][j]
			if new_scores[k]>0:
				new_scores[k]=books[k]/max(1,-1+books[k]/new_scores[k])
	print()
	return score

tots=0
passed=0
nd=set([i for i in range(L)])
print(L)
count=0
while passed <D:
	count+=1
	ind=rescore(lib,0,nd)
	nd.discard(ind)
	print(ind,end=' ')
	tots+=calc_scores(lib,ind,passed)
	passed+=lib[ind]["t"]
print(count,tots)