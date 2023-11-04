import numpy as np
import math
import matplotlib.pyplot as plt
 
f1 = open('openblas_thread_M32.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_thread_M32.txt")
xy2 = f2.read().split("\n")

f3 = open("emll_thread_NN_M32.txt")
xy3 = f3.read().split("\n")

f4 = open("armpl_thread_M32.txt")
xy4 = f4.read().split("\n")

f5 = open("NSMM_thread_M32.txt")
xy5 = f5.read().split("\n")

f6 = open("eigen_thread_NN_M32.txt")
xy6 = f6.read().split("\n")

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
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
	
		y1.append(np.mean(mat))
		err1.append(np.std(mat))



for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y2.append(np.mean(mat))
		err2.append(np.std(mat))

for item in xy3:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y3.append(np.mean(mat))
		err3.append(np.std(mat))

for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y4.append(np.mean(mat))
		err4.append(np.std(mat))

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y5.append(np.mean(mat))
		err2.append(np.std(mat))


for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y6.append(np.mean(mat))
		err6.append(np.std(mat))

f1 = open('openblas_thread_M64.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_thread_M64.txt")
xy2 = f2.read().split("\n")

f3 = open("emll_thread_NN_M64.txt")
xy3 = f3.read().split("\n")

f4 = open("armpl_thread_M64.txt")
xy4 = f4.read().split("\n")

f5 = open("NSMM_thread_M64.txt")
xy5 = f5.read().split("\n")

f6 = open("eigen_thread_NN_M64.txt")
xy6 = f6.read().split("\n")

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
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
	
		y11.append(np.mean(mat))
		err11.append(np.std(mat))



for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y22.append(np.mean(mat))
		err22.append(np.std(mat))


for item in xy3:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y33.append(np.mean(mat))
		err33.append(np.std(mat))

for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y44.append(np.mean(mat))
		err44.append(np.std(mat))

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y55.append(np.mean(mat))
		err55.append(np.std(mat))


for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y66.append(np.mean(mat))
		err66.append(np.std(mat))


f1 = open('openblas_thread_M128.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_thread_M128.txt")
xy2 = f2.read().split("\n")

f3 = open("emll_thread_NN_M128.txt")
xy3 = f3.read().split("\n")

f4 = open("armpl_thread_M128.txt")
xy4 = f4.read().split("\n")

f5 = open("NSMM_thread_M128.txt")
xy5 = f5.read().split("\n")

f6 = open("eigen_thread_NN_M128.txt")
xy6 = f6.read().split("\n")

y111=[]
err111=[]
y222=[]
err222=[]
y333=[]
err333=[]
y444 = []
err444=[]
y555=[]
err555=[]
y666=[]
err666=[]



for item in xy1:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
	
		y111.append(np.mean(mat))
		err111.append(np.std(mat))


for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y222.append(np.mean(mat))
		err222.append(np.std(mat))

for item in xy3:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y333.append(np.mean(mat))
		err333.append(np.std(mat))


for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y444.append(np.mean(mat))
		err444.append(np.std(mat))

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y555.append(np.mean(mat))
		err555.append(np.std(mat))

for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y666.append(np.mean(mat))
		err666.append(np.std(mat))

f1 = open('openblas_thread_M256.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_thread_M256.txt")
xy2 = f2.read().split("\n")

f3 = open("emll_thread_NN_M256.txt")
xy3 = f3.read().split("\n")

f4 = open("armpl_thread_M256.txt")
xy4 = f4.read().split("\n")

f5 = open("NSMM_thread_M256.txt")
xy5 = f5.read().split("\n")

f6 = open("eigen_thread_NN_M256.txt")
xy6 = f6.read().split("\n")



y1111=[]
err1111=[]
y2222=[]
err2222=[]
y3333=[]
err3333=[]
y4444 = []
err4444=[]
y5555=[]
err5555=[]
y6666=[]
err6666=[]


for item in xy1:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
	
		y1111.append(np.mean(mat))
		err1111.append(np.std(mat))


for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y2222.append(np.mean(mat))
		err2222.append(np.std(mat))

for item in xy3:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y3333.append(np.mean(mat))
		err3333.append(np.std(mat))

for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y4444.append(np.mean(mat))
		err4444.append(np.std(mat))

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y5555.append(np.mean(mat))
		err5555.append(np.std(mat))


for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y6666.append(np.mean(mat))
		err6666.append(np.std(mat))

fig, axs= plt.subplots(1, 4,figsize=(16,3))

x = []
x1=[]
for i in range(len(y2)):
	x1.append(2048 + 256 * i)
	x.append(2048 + 256 * i)
#plt.tick_params(labelsize=15)


font1 = {'family' : 'Times New Roman',
'weight' : 'bold',
'size' : 15,
}

font = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 15,
}



l1,=axs[0].plot(x,y1,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[0].plot(x,y2,color=(17/255,115/255,132/255),label="BLIS",marker="p",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l3,=axs[0,0].plot(x,y3,color=(0/255,0/255,0/255),label="EMLL",marker="x",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[0].plot(x,y4,color=(50/255,177/255,205/255),label="ARMPL",marker="*",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l6,=axs[0,0].plot(x,y6,color=(158/255,71/255,13/255),label="eigen",marker="d",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[0].plot(x,y5,color=(255/255,223/255,128/255),label="LibShalom2",marker=">",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')


axs[0].set_xlabel("N (M=32)",fontsize=15)
axs[0].set_ylabel("GFLOPS (FP32)",font)
axs[0].set_xlim(1700,12300)
axs[0].grid(True,c="lightgrey",linestyle='--')
axs[0].set_xticks((2000,4000,6000,8000,10000,12000),('2k','4k','6k','8k','10k','12k'),fontsize=15)
axs[0].set_yticks((0,100,200,300,400,500),fontsize=15)
axs[0].set_ylim(60,500)


l1,=axs[1].plot(x,y11,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[1].plot(x,y22,color=(17/255,115/255,132/255),label="BLIS",marker="p",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l3,=axs[0,1].plot(x,y33,color=(0/255,0/255,0/255),label="EMLL",marker="x",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[1].plot(x,y44,color=(50/255,177/255,205/255),label="ARMPL",marker="*",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l6,=axs[0,1].plot(x,y66,color=(158/255,71/255,13/255),label="eigen",marker="d",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[1].plot(x,y55,color=(255/255,223/255,128/255),label="LibShalom",marker=">",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')


axs[1].set_xlabel("N (M=64)",fontsize=15)
axs[1].grid(True,c="lightgrey",linestyle='--')
axs[1].set_xlim(1700,12300)
axs[1].set_xticks((2000,4000,6000,8000,10000,12000),('2k','4k','6k','8k','10k','12k'),fontsize=15)
axs[1].set_yticks((0,200,400,600,700),fontsize=15)
axs[1].set_ylim(60,720)


l1,=axs[2].plot(x,y111,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[2].plot(x,y222,color=(17/255,115/255,132/255),label="BLIS",marker="p",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l3,=axs[0,2].plot(x,y333,color=(0/255,0/255,0/255),label="EMLL",marker="x",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[2].plot(x,y444,color=(50/255,177/255,205/255),label="ARMPL",marker="*",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l6,=axs[0,2].plot(x,y666,color=(158/255,71/255,13/255),label="eigen",marker="d",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[2].plot(x,y555,color=(255/255,223/255,128/255),label="LibShalom",marker=">",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l4,=plt.plot(x4,y4,color="darkcyan",label="BLASFEO",marker="^")

axs[2].set_xlabel("N (M=128)",fontsize=15)
axs[2].grid(True,c="lightgrey",linestyle='--')
axs[2].set_xlim(1700,12300)
axs[2].set_xticks((2000,4000,6000,8000,10000,12000),('2k','4k','6k','8k','10k','12k'),fontsize=15)
axs[2].set_yticks((0,200,400,600,800),fontsize=15)
axs[2].set_ylim(60,840)


l1,=axs[3].plot(x,y1111,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[3].plot(x,y2222,color=(17/255,115/255,132/255),label="BLIS",marker="p",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l3,=axs[0,3].plot(x,y3333,color=(0/255,0/255,0/255),label="EMLL",marker="x",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[3].plot(x,y4444,color=(50/255,177/255,205/255),label="ARMPL",marker="*",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l6,=axs[0,3].plot(x,y6666,color=(158/255,71/255,13/255),label="eigen",marker="d",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[3].plot(x,y5555,color=(255/255,223/255,128/255),label="LibShalom2",marker=">",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l4,=plt.plot(x4,y4,color="darkcyan",label="BLASFEO",marker="^")

axs[3].set_xlabel("N (M=256)",fontsize=15)
axs[3].grid(True,c="lightgrey",linestyle='--')
axs[3].set_xlim(1700,12300)
axs[3].set_xticks((2000,4000,6000,8000,10000,12000),('2k','4k','6k','8k','10k','12k'),fontsize=15)
axs[3].set_yticks((0,200,400,600,800,900),fontsize=15)
axs[3].set_ylim(60,920)


fig.legend([l1,l2,l4,l5], [ 'OpenBLAS','BLIS','ARMPL','LibShalom2'], ncol=4,
	loc="upper right" , borderaxespad=0.,bbox_to_anchor=(0.42,1.015), columnspacing = 0.05, frameon=False,
	prop =font1)




"""
################################################

f1 = open('openblas_thread_N32.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_thread_N32.txt")
xy2 = f2.read().split("\n")

f3 = open("emll_thread_NN_N32.txt")
xy3 = f3.read().split("\n")

f4 = open("armpl_thread_N32.txt")
xy4 = f4.read().split("\n")

f5 = open("NSMM_thread_N32.txt")
xy5 = f5.read().split("\n")

f6 = open("eigen_thread_NN_N32.txt")
xy6 = f6.read().split("\n")

y21=[]
err21=[]
y22=[]
err22=[]
y23=[]
err23=[]
y24 = []
err24=[]
y25=[]
err25=[]
y26=[]
err26=[]

x=[]

for item in xy1:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
	
		y21.append(np.mean(mat))
		err21.append(np.std(mat))



for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y22.append(np.mean(mat))
		err22.append(np.std(mat))

for item in xy3:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y23.append(np.mean(mat))
		err23.append(np.std(mat))

for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y24.append(np.mean(mat))
		err24.append(np.std(mat))

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y25.append(np.mean(mat))
		err25.append(np.std(mat))

for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y26.append(np.mean(mat))
		err26.append(np.std(mat))


f1 = open('openblas_thread_N64.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_thread_N64.txt")
xy2 = f2.read().split("\n")

f3 = open("emll_thread_NN_N64.txt")
xy3 = f3.read().split("\n")

f4 = open("armpl_thread_N64.txt")
xy4 = f4.read().split("\n")

f5 = open("NSMM_thread_N64.txt")
xy5 = f5.read().split("\n")

f6 = open("eigen_thread_NN_N64.txt")
xy6 = f6.read().split("\n")


y211=[]
err211=[]
y222=[]
err222=[]
y233=[]
err233=[]
y244 = []
err244=[]
y255=[]
err255=[]
y266=[]
err266=[]


for item in xy1:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
	
		y211.append(np.mean(mat))
		err211.append(np.std(mat))


for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y222.append(np.mean(mat))
		err222.append(np.std(mat))


for item in xy3:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y233.append(np.mean(mat))
		err233.append(np.std(mat))

for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y244.append(np.mean(mat))
		err244.append(np.std(mat))

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y255.append(np.mean(mat))
		err255.append(np.std(mat))


for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y266.append(np.mean(mat))
		err266.append(np.std(mat))


f1 = open('openblas_thread_N128.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_thread_N128.txt")
xy2 = f2.read().split("\n")

f3 = open("emll_thread_NN_N128.txt")
xy3 = f3.read().split("\n")

f4 = open("armpl_thread_N128.txt")
xy4 = f4.read().split("\n")

f5 = open("NSMM_thread_N128.txt")
xy5 = f5.read().split("\n")

f6 = open("eigen_thread_NN_N128.txt")
xy6 = f6.read().split("\n")



y2111=[]
err2111=[]
y2222=[]
err2222=[]
y2333 = []
err2333=[]
y2444 = []
err2444=[]
y2555=[]
err2555=[]
y2666=[]
err2666=[]


for item in xy1:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
	
		y2111.append(np.mean(mat))
		err2111.append(np.std(mat))



for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y2222.append(np.mean(mat))
		err2222.append(np.std(mat))

for item in xy3:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y2333.append(np.mean(mat))
		err2333.append(np.std(mat))

for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y2444.append(np.mean(mat))
		err2444.append(np.std(mat))

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y2555.append(np.mean(mat))
		err2555.append(np.std(mat))

for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y2666.append(np.mean(mat))
		err2666.append(np.std(mat))



f1 = open('openblas_thread_N256.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_thread_N256.txt")
xy2 = f2.read().split("\n")

f3 = open("emll_thread_NN_N256.txt")
xy3 = f3.read().split("\n")

f4 = open("armpl_thread_N256.txt")
xy4 = f4.read().split("\n")

f5 = open("NSMM_thread_N256.txt")
xy5 = f5.read().split("\n")

f6 = open("eigen_thread_NN_N256.txt")
xy6 = f6.read().split("\n")


y21111=[]
err21111=[]
y22222=[]
err22222=[]
y23333=[]
err23333=[]
y24444 = []
err24444=[]
y25555=[]
err25555=[]
y26666=[]
err26666=[]



for item in xy1:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
	
		y21111.append(np.mean(mat))
		err21111.append(np.std(mat))



for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y22222.append(np.mean(mat))
		err22222.append(np.std(mat))

for item in xy3:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))

		y23333.append(np.mean(mat))
		err23333.append(np.std(mat))

for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y24444.append(np.mean(mat))
		err24444.append(np.std(mat))

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y25555.append(np.mean(mat))
		err25555.append(np.std(mat))

for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y26666.append(np.mean(mat))
		err26666.append(np.std(mat))


x = []
x1=[]
for i in range(len(y2)):
	x1.append(2048 + 256 * i)
	x.append(2048 + 256 * i)
#plt.tick_params(labelsize=15)

l1,=axs[1,0].plot(x,y21,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[1,0].plot(x,y22,color=(17/255,115/255,132/255),label="BLIS",marker="p",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l3,=axs[1,0].plot(x,y23,color=(0/255,0/255,0/255),label="EMLL",marker="x",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[1,0].plot(x,y24,color=(50/255,177/255,205/255),label="ARMPL",marker="*",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l6,=axs[1,0].plot(x,y26,color=(158/255,71/255,13/255),label="Eigen",marker="d",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[1,0].plot(x,y25,color=(255/255,223/255,128/255),label="LibShalom",marker=">",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l4,=plt.plot(x4,y4,color="darkcyan",label="BLASFEO",marker="^")

axs[1,0].set_xlabel("M (N=32)",fontsize=15)
axs[1,0].set_ylabel("GFLOPS",font)
axs[1,0].set_xlim(1700,12300)
axs[1,0].grid(True,c="lightgrey",linestyle='--')
axs[1,0].set_xticks((2000,4000,6000,8000,10000,12000),('2k','4k','6k','8k','10k','12k'),fontsize=15)
axs[1,0].set_yticks((0,200,400,600,700),fontsize=15)


l1,=axs[1,1].plot(x,y211,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[1,1].plot(x,y222,color=(17/255,115/255,132/255),label="BLIS",marker="p",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l3,=axs[1,1].plot(x,y233,color=(0/255,0/255,0/255),label="EMLL",marker="x",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[1,1].plot(x,y244,color=(50/255,177/255,205/255),label="ARMPL",marker="*",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l6,=axs[1,1].plot(x,y266,color=(158/255,71/255,13/255),label="Eigen",marker="d",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[1,1].plot(x,y255,color=(255/255,223/255,128/255),label="LibShalom",marker=">",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l4,=plt.plot(x4,y4,color="darkcyan",label="BLASFEO",marker="^")

axs[1,1].set_xlabel("M (N=64)",fontsize=15)
axs[1,1].grid(True,c="lightgrey",linestyle='--')
axs[1,1].set_xlim(1700,12300)
axs[1,1].set_xticks((2000,4000,6000,8000,10000,12000),('2k','4k','6k','8k','10k','12k'),fontsize=15)
axs[1,1].set_yticks((0,200,400,600,800,900),fontsize=15)


l1,=axs[1,2].plot(x,y2111,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[1,2].plot(x,y2222,color=(17/255,115/255,132/255),label="BLIS",marker="p",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l3,=axs[1,2].plot(x,y2333,color=(0/255,0/255,0/255),label="EMLL",marker="x",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[1,2].plot(x,y2444,color=(50/255,177/255,205/255),label="ARMPL",marker="*",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l6,=axs[1,2].plot(x,y2666,color=(158/255,71/255,13/255),label="Eigen",marker="d",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[1,2].plot(x,y2555,color=(255/255,223/255,128/255),label="LibShalom",marker=">",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l4,=plt.plot(x4,y4,color="darkcyan",label="BLASFEO",marker="^")

axs[1,2].set_xlabel("M (N=128)",fontsize=15)
axs[1,2].grid(True,c="lightgrey",linestyle='--')
axs[1,2].set_xlim(1700,12300)
axs[1,2].set_xticks((2000,4000,6000,8000,10000,12000),('2k','4k','6k','8k','10k','12k'),fontsize=15)
axs[1,2].set_yticks((0,200,400,600,800,900),fontsize=15)


l1,=axs[1,3].plot(x,y21111,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=axs[1,3].plot(x,y22222,color=(17/255,115/255,132/255),label="BLIS",marker="p",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l3,=axs[1,3].plot(x,y23333,color=(0/255,0/255,0/255),label="EMLL",marker="x",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l4,=axs[1,3].plot(x,y24444,color=(50/255,177/255,205/255),label="ARMPL",marker="*",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l6,=axs[1,3].plot(x,y26666,color=(158/255,71/255,13/255),label="Eigen",marker="d",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l5,=axs[1,3].plot(x,y25555,color=(255/255,223/255,128/255),label="LibShalom",marker=">",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l4,=plt.plot(x4,y4,color="darkcyan",label="BLASFEO",marker="^")

axs[1,3].set_xlabel("M (N=256)",fontsize=15)
axs[1,3].grid(True,c="lightgrey",linestyle='--')
axs[1,3].set_xlim(1700,12300)
axs[1,3].set_xticks((2000,4000,6000,8000,10000,12000),('2k','4k','6k','8k','10k','12k'),fontsize=15)
axs[1,3].set_yticks((0,200,400,600,800,1000),fontsize=15)

"""

fig.tight_layout()
plt.subplots_adjust(left=None, bottom=None, right=None, top=None, wspace =0.13, hspace =0.34)
plt.show()
fig.savefig('NN_thread_FT.pdf', bbox_inches='tight')