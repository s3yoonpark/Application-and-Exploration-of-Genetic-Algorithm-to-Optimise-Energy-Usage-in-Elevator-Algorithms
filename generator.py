from random import randint 

f = open("input.txt", "w") 
n = randint(1, 20) 
fl = randint(1, 25) 
f.write(f"{n} {fl}\n")
for i in range(n): 
    f.write(f"{randint(1, 25)} {randint(1, 25)}\n")
f.close() 