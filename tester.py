import subprocess 

scan_list=[] 
main_list=[] 

for i in range(100):  
    subprocess.run(["python", "generator.py"])
    f=open("output.txt","r") 
    subprocess.run(["./scan.exe"])
    scan_list.append(int(f.readline())) 
    f.close() 
    subprocess.run(["./GA.exe"])
    f=open("output.txt", "r") 
    main_list.append(int(f.readline())) 
    f.close() 

print("SCAN:")
for i in scan_list: 
    print(i) 
print("MAIN:") 
for i in main_list: 
    print(i) 
print(sum(scan_list)-sum(main_list))