import numpy as np
import math
import matplotlib.pyplot as plt
from matplotlib.font_manager import FontProperties
 
f1 = open('openblas_thread_KP_table.txt', 'r')
xy1=f1.read().split("\n")

f2 = open("blis_thread_KP_table.txt")
xy2 = f2.read().split("\n")

#f3 = open('emll_thread_NN_table.txt', 'r')
#xy3=f3.read().split("\n")

#f4 = open("armpl_thread_NN_table.txt")
#xy4 = f4.read().split("\n")

#f5 = open('eigen_thread_NN_table.txt', 'r')
#xy5=f5.read().split("\n")

f6 = open("NSMM_thread_KP_table.txt")
xy6 = f6.read().split("\n")

y1=[]
err1=[]
y2=[]
err2=[]
y3=[]
err3=[]
y4=[]
err4=[]
y5 = []
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
mean1 = np.sum(np.array(y1)) / 19
y1.append(mean1)

for item in xy2:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y2.append(np.mean(mat))
		err2.append(np.std(mat))
mean2 = np.sum(np.array(y2)) / 19
y2.append(mean2)
"""
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
		err5.append(np.std(mat))
"""
for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y6.append(np.mean(mat))
		err6.append(np.std(mat))
mean6 = np.sum(np.array(y6)) / 19
y6.append(mean6)


font1 = {'family' : 'Times New Roman',
'weight' : 'bold',
'size' : 15,
}

font = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 15,
}

f=plt.figure(figsize=(8,4))

x = []
x1=[]
for i in range(len(y1)):
	x1.append(i+1)
	x.append(i+1)
#plt.tick_params(labelsize=15)

l1,=plt.plot(x,y1,color=(66/255,165/255,48/255),label="OpenBLAS",marker="o",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l2,=plt.plot(x,y2,color=(17/255,115/255,132/255),label="BLIS",marker="p",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l3,=plt.plot(x,y3,color=(0/255,0/255,0/255),label="EMLL",marker="x",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l4,=plt.plot(x,y4,color=(50/255,177/255,205/255),label="ARMPL",marker="*",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
#l5,=plt.plot(x,y5,color=(158/255,71/255,13/255),label="Eigen",marker="d",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')
l6,=plt.plot(x,y6,color=(255/255,223/255,128/255),label="LibShalom",marker=">",linewidth=1.7,markersize=4,markerfacecolor='black',markeredgecolor='black')

plt.xlabel("The id of matrices in Table 1",fontsize=15)
plt.ylabel("GFLOPS (FP32)",font)
plt.grid(True,c="lightgrey",linestyle='--')
plt.xticks(x,
	['1','2','3','4','5','6','7','8','9','10',
	'11','12','13','14','15','16','17','18','19','avg'],fontsize=15)
plt.yticks((0,400,800,1200,1600,2000,2400),fontsize=15)
plt.xlim(0.8,20.2)


plt.legend([l1,l2, l6], [ 'OpenBLAS','BLIS', 'LibShalom'], ncol=3,
	loc="upper right" , borderaxespad=0.2,bbox_to_anchor=(0.88,1.13), columnspacing = 0.08, frameon=False,
	prop =font1)
plt.tight_layout()
plt.show()
f.savefig('thread_KP_table.pdf', bbox_inches='tight')