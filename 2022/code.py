from functools import cmp_to_key
from random import randint
class cont:
    def __init__(self,name):
        self.name = name
        self.busy_till=0
        self.skill = {}

    def add_skill(self,skill, level):
        self.skill[skill] = level

    def set_busy_till(self,days):
        self.busy_till = days
    
    def upgrade_skill(self,skill):
        self.skill[skill] += 1
    
    def __repr__(self) -> str:
        return f'{self.name} has skill {self.skill} and is busy till {self.busy_till}'

class proj:
    def __init__(self,name, days, score,best ,Nroles):
        self.name = name
        self.days = days
        self.score = score
        self.best = best
        self.Nroles = Nroles
        self.roleorder = []
        self.contrib = []
        self.contribD={}
        self.roles = {}
        self.copy=[]
        self.maxLevel=0
        self.done= False

    def add_role(self,role, level):
            a= randint(0,1)
            self.maxLevel = max(self.maxLevel,level)
            self.roles[role+'%%'+str(level)+str(a)] = level
            self.roleorder.append(role+'%%'+str(level)+str(a))
            self.copy.append(role+'%%'+str(level)+str(a))


    def __repr__(self) -> str:
        return f'{self.name} has {self.roleorder} requires {self.roles} and has {self.contribD}'

def read_cont():
    c=input().split(' ')
    Co=cont(c[0])
    for i in range(int(c[1])):
        a = input().split()
        Co.add_skill(a[0],int(a[1]))
    return Co

def read_proj():
    c=input().split(' ')
    Pr=proj(c[0],int(c[1]),int(c[2]),int(c[3]),int(c[4]))
    for i in range(int(c[4])):
        a = input().split()
        Pr.add_role(a[0],int(a[1]))
    return Pr

def sort_function(a,b):
    if a.score > b.score:
        return -1
    elif a.score < b.score:
        return 1
    else:
        return 0

def sort_function2(a,b):
    if (a.maxLevel != b.maxLevel):
            return a.maxLevel - b.maxLevel
    elif a.score != b.score:
        return (a.score - b.score)
    if a.days != b.days:
        return a.days - b.days
    if (a.best != b.best):
        return a.best - b.best
    return -1

def sort_function3(a,b):
    if len(a.skill) > len(b.skill):
        return -1
    elif len(a.skill) < len(b.skill):
        return 1
    return 0    


def find_coders(proj,Co, day):
    # if proj.name == 'CollectionsNextv1':
        # print('----------------------------------------------------')
    if proj.done:
        return False
    for i in Co:
    #     if proj.name == 'CollectionsNextv1':
    #         print(i.name)
    #         print(proj)
        if i.busy_till <= day:
            for k in proj.roleorder:
                j = k.split('%%')
                if j[0] in i.skill and i.skill[j[0]] >= proj.roles[k]:
                    proj.contribD[k]=i
                    i.busy_till = day+proj.days
                    proj.roleorder.remove(k)
                    break
            if len(proj.roleorder) == 0:
                proj.done = True
                for j in proj.copy:
                    proj.contrib.append(proj.contribD[j])
                return True
    for i in proj.contribD:
        proj.contribD[i].busy_till = day
    proj.contribD = {}
    proj.roleorder = proj.copy[:]
    return False

def get_max_days(Po):
    max_days = 0
    for i in Po:
        max_days = max(max_days, i.days+i.score)
    return max_days

def get_day(Co):
    minn =1000000
    for i in Co:
        minn = min(minn, i.busy_till)
    return minn

def update_project(proj, days):
    for i in proj.contrib:
        i.set_busy_till(proj.days)
        for j in i.skill:
            if j in proj.roles:
                if i.skill[j] <= proj.roles[j]:
                    i.skill[j]+=1

def main():
    a,b=[int(i) for i in input().split()]
    Co=[]
    Po=[]
    for i in range(a):
        Co.append(read_cont())
    for i in range(b):
        Po.append(read_proj())
    Po= sorted(Po, key=cmp_to_key(sort_function))
    Co = sorted(Co, key=cmp_to_key(sort_function3))
    d=0
    outp=[]
    cont=0
    last=0
    days2= get_max_days(Po)
    while cont < len(Po) and d < days2:
        # print(d, days2)
        for i in Po:
            if find_coders(i,Co,d):
                cont+=1
                update_project(i,d+i.days)
                # print(i)
                outp.append(i.name)
                s=''
                for j in i.contrib:
                    s+=j.name+' '
                outp.append(s)
                last = d
        d+=1
        if d > 20*(1+last):
            break
                
    print(cont)
    for i in outp:
        print(i)

    

if __name__ == '__main__':
    main()