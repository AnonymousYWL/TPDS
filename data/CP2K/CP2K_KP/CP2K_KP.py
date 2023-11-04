import numpy as np
import matplotlib.pyplot as plt
 

f1 = open("blis_CP2K_KP.txt")
xy1 = f1.read().split("\n")

f2 = open('openblas_CP2K_KP.txt', 'r')
xy2=f2.read().split("\n")

f3 = open("armpl_CP2K_KP.txt")
xy3 = f3.read().split("\n")

f4 = open("libxsmm_CP2K_KP.txt")
xy4 = f4.read().split("\n")

f5 = open("blasfeo_CP2K_KP.txt")
xy5 = f5.read().split("\n")

f6 = open("NSMM_CP2K_KP.txt")
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

count=0
x=[]
for item in xy4:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y4.append(np.mean(mat))
		err4.append(np.std(mat))
		count = count +1
		x.append(count*8)

for item in xy5:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y5.append(np.mean(mat))
		err5.append(np.std(mat))

for item in xy6:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		mat = np.array((float(arr[3]), float(arr[4]), float(arr[5]), 
						float(arr[6]), float(arr[7])))
		y6.append(np.mean(mat))
		err6.append(np.std(mat))


font1 = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 16,
}


font2 = {'family' : 'Times New Roman',
'weight' : 'normal',
'size' : 14,
}


ind = np.arange(len(y1))  # the x locations for the groups
ind = 4.7* ind
width = 0.6  # the width of the bars

f, axs= plt.subplots(figsize=(6.6,3.3))
A=plt.bar(ind-2.5*width , y1, width, yerr=err1,color=(17/255,115/255,132/255),ecolor= 'black',label="BLIS",edgecolor='black')
B=plt.bar(ind-1.5 * width, y3, width, yerr=err3, color=(50/255,177/255,205/255),ecolor= 'black',label="ARMPL",edgecolor='black')
C=plt.bar(ind-0.5 * width , y2, width , yerr=err2, color=(66/255,165/255,48/255),ecolor= 'black',label="OpenBLAS",edgecolor='black')
D=plt.bar(ind+ 0.5*width, y5, width, yerr=err5,color=(170/255,170/255,170/255),ecolor= 'black',label="BLASFEO",edgecolor='black')
E=plt.bar(ind+ 1.5*width, y4, width, yerr=err4,color=(238/255,131/255,60/255),ecolor= 'black',label="LIBXSMM",edgecolor='black')
F=plt.bar(ind+ 2.5*width, y6, width, yerr=err6,color=(255/255,223/255,128/255),ecolor= 'black',label="LibShalom",edgecolor='black')

plt.xlim(-1.7,20.9)
#plt.ylabel('GFLOPS (FP64)', font1)
ind[1] = ind[1] - 0.4
ind[2] = ind[2] - 0.3
ind[4] = ind[4] + 0.1
plt.xticks(ind,("5x5x5","13x5x13","13x13x13","23x23x23","26x26x13"),
	fontsize=16)
plt.yticks((0,2,4,6,8,10,12),fontsize=20)
#plt.legend((A[0], B[0], C[0],D[0],E[0],F[0]), ('BLIS','ARMPL', 'OpenBLAS', 'BLASFEO','LIBXSMM','LibShalom'),
#		loc="upper right" , borderaxespad=0.,bbox_to_anchor=(0.84,0.97), columnspacing = 0.5,ncol=3,
#		frameon=False,fontsize=12)
#leg = plt.gca().get_legend()
#ltext = leg.get_texts()
#plt.setp(ltext, fontsize=12)

plt.tight_layout()
plt.show()

f.savefig('CP2K_KP.pdf', bbox_inches='tight')