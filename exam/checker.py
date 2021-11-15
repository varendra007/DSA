file_name1=input("file1: ")
file_name2=input("file2: ")
f1=open(file_name1,"r")
f2=open(file_name2,"r")
r1=f1.readlines()
r2=f2.readlines()
d1={}
d2={}
for l1 in r1:
    arr=l1.strip().split()
    d1[int(arr[0])]=arr[1]
for l2 in r2:
    arr=l2.strip().split()
    d2[int(arr[0])]=arr[1]
if len(d1.keys())!=len(d2.keys()):
    print("not Same")
    exit(0)
for i in range(len(d1.keys())):
    if d1[i]!=d2[i]:
        print("not Same",i,"->",d1[i],"  ",i,"->",d2[i])
        exit(0)
print("File Match")