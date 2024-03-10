from random import randint 

f = open("input.txt", "w") 
n = randint(1, 20) 
fl = randint(1, 50) 
f.write(f"{n} {fl}\n")
for i in range(n): 
    f.write(f"{randint(1, 50)} {randint(1, 50)}\n")
f.close()  
