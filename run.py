import os
for i in range(5):
    command = "python sol.py < Input/" + str(i+1) + ".txt > " + str(i+1) + ".out"
    os.system(command)