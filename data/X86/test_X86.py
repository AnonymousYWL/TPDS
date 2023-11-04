import numpy as np
import math
import matplotlib.pyplot as plt
 
f1 = open('OpenBLAS_X86_NGM.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("BLIS_X86_NGM.txt")
xy2 = f2.read().split("\n")

f4 = open("MKL_X86_NGM.txt")
xy4 = f4.read().split("\n")

f5 = open("Libshalom_X86_NGM.txt")
xy5 = f5.read().split("\n")

y1=[]
err1=[]
y2=[]
err2=[]
y3=[]
err3=[]
y4 = []
err4=[]
y5=[]
err5=[]
y6=[]
err6=[]

x=[]

for item in xy1:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		y1.append(float(arr[3]))

for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		y2.append(float(arr[3]))

for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		y4.append(float(arr[3]))


for item in xy5:
	arr = item.split()
	if(len(arr) != 0 and arr[0]!= ''):
		#print(float(arr[0]))
		y5.append(float(arr[0]))

fig = plt.figure(figsize=(6,3.2))

x = []
x1=[]
for i in range(len(y2)):
	x1.append(16 + 16 * i)
	x.append(16 + 16 * i)
#plt.tick_params(labelsize=15)


font1 = {'family' : 'Times New Roman',
'weight' : 'bold',
'size' : 12.5,
}

font = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 15,
}

l1,= plt.plot(x,y1,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,= plt.plot(x,y2,color=(17/255,115/255,132/255),label="BLIS",marker="p",markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,= plt.plot(x,y4,color=(255/255,0/255,0/255),label="MKL",marker="D",markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,= plt.plot(x,y5,color=(255/255,223/255,128/255),label="LibShalom2",marker=">",markersize=4,markerfacecolor='black',markeredgecolor='black')


plt.xlabel("M (N=K=9600)",fontsize=14)
plt.ylabel("GFLOPS (FP32)",font)
plt.xlim(10,520)
plt.grid(True,c="lightgrey",linestyle='--')
plt.xticks((64, 128, 192, 256, 320, 384, 448, 512),
				('64', '128', '192', '256', '320', '384', '448', '512'),fontsize=14)
plt.yticks((0, 500,1000,1500,2000,2500),('0','500','1000','1500','2000','2500'),fontsize=14)
plt.ylim(0,2700)

fig.legend([l1,l2,l4,l5], [ 'OpenBLAS','BLIS','MKL','LibShalom2'], ncol=4,
	loc="upper right" , borderaxespad=0.,bbox_to_anchor=(0.96,0.94), columnspacing = 0.05, frameon=False,
	prop =font1)

fig.tight_layout()
#plt.subplots_adjust(left=None, bottom=None, right=None, top=None, wspace =0.13, hspace =0.34)
plt.show()
fig.savefig('GEMM_X86_NGM.pdf', bbox_inches='tight')
