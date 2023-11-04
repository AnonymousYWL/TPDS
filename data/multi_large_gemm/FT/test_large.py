import numpy as np
import math
import matplotlib.pyplot as plt
 
f1 = open('openblas_NN_large_FT.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_NN_large_FT.txt")
xy2 = f2.read().split("\n")

f4 = open("armpl_NN_large_FT.txt")
xy4 = f4.read().split("\n")

f5 = open("NSMM_NN_large_FT.txt")
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
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		y5.append(float(arr[3]))



f1 = open('openblas_large_NN_thread_FT.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_large_NN_thread_FT.txt")
xy2 = f2.read().split("\n")

f4 = open("armpl_large_NN_thread_FT.txt")
xy4 = f4.read().split("\n")

f5 = open("LibShalom_large_NN_thread_FT.txt")
xy5 = f5.read().split("\n")

y11=[]
err11=[]
y22=[]
err22=[]
y33=[]
err33=[]
y44 = []
err44=[]
y55=[]
err55=[]
y66=[]
err66=[]


for item in xy1:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		y11.append(float(arr[3]))



for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		y22.append(float(arr[3]))

for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		y44.append(float(arr[3]))

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		y55.append(float(arr[3]))

fig, axs= plt.subplots(1, 2,figsize=(8,3))

x = []
x1=[]
for i in range(len(y2)):
	x1.append(1200 + 600 * i)
	x.append(1200 + 600 * i)
#plt.tick_params(labelsize=15)


font1 = {'family' : 'Times New Roman',
'weight' : 'bold',
'size' : 13,
}

font = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 15,
}





l1,=axs[0].plot(x,y1,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[0].plot(x,y2,color=(17/255,115/255,132/255),label="BLIS",marker="p",markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[0].plot(x,y4,color=(50/255,177/255,205/255),label="ARMPL",marker="*",markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[0].plot(x,y5,color=(255/255,223/255,128/255),label="LibShalom",marker=">",markersize=4,markerfacecolor='black',markeredgecolor='black')


axs[0].set_xlabel("M=N=K(single)",fontsize=14)
axs[0].set_ylabel("GFLOPS (FP32)",font)
axs[0].set_xlim(1200,12300)
axs[0].grid(True,c="lightgrey",linestyle='--')
axs[0].set_xticks((1000,3000,5000,7000,9000,11000),('1k','3k','5k','7k','9k','11k'),fontsize=14)
axs[0].set_yticks((4,8,12,14,16,18),('4','8','12','14','16','18'),fontsize=14)
axs[0].set_ylim(10,18.3)


l1,=axs[1].plot(x,y11,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[1].plot(x,y22,color=(17/255,115/255,132/255),label="BLIS",marker="p",markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[1].plot(x,y44,color=(50/255,177/255,205/255),label="ARMPL",marker="*",markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[1].plot(x,y55,color=(255/255,223/255,128/255),label="LibShalom",marker=">",markersize=4,markerfacecolor='black',markeredgecolor='black')


axs[1].set_xlabel("M=N=K(64 threads)",fontsize=14)
axs[1].grid(True,c="lightgrey",linestyle='--')
axs[1].set_xlim(1200,12300)
axs[1].set_xticks((1000,3000,5000,7000,9000,11000),('1k','3k','5k','7k','9k','11k'),fontsize=14)
axs[1].set_yticks((150, 300, 450, 600, 750, 900),('150', '300', '450', '600', '750','900'),fontsize=14)
axs[1].set_ylim(100,950)


fig.legend([l1,l2,l4,l5], [ 'OpenBLAS','BLIS','ARMPL','LibShalom2'], ncol=4,
	loc="upper right" , borderaxespad=0.,bbox_to_anchor=(0.72,1.025), columnspacing = 0.05, frameon=False,
	prop =font1)

fig.tight_layout()
#plt.subplots_adjust(left=None, bottom=None, right=None, top=None, wspace =0.13, hspace =0.34)
plt.show()
fig.savefig('large_gemm_FT.pdf', bbox_inches='tight')
