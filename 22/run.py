import os
for i in range(3):
    print(i)
    command = "./a.out < Input/" + \
        str(i+1) + ".in.txt > output/" + str(i+1) + ".txt"
    os.system(command)
