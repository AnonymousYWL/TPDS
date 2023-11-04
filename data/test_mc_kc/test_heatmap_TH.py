import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np


f1 = open('test_mc_kc_TH.txt', 'r')
xy1=f1.read().split("\n")

x=[]
y=[]
count = 0
temp_y=[]

for item in xy1:
	arr = item.split(" ")
	if(len(arr) != 0 and arr[0]!= ''):
		count = count + 1
		temp_y.append(float(arr[2])/32/40.0 *100)
		if(count % 10 == 0):
			y.append(temp_y)
			temp_y=[]

#print(y)

sns.set()
plt.rcParams['font.sans-serif']='SimHei'#设置中文显示，必须放在sns.set之后
f, ax = plt.subplots(figsize=(7.5, 4.3))

#print(uniform_data[0])
#heatmap后第一个参数是显示值,vmin和vmax可设置右侧刻度条的范围,
#参数annot=True表示在对应模块中注释值
# 参数linewidths是控制网格间间隔
#参数cbar是否显示右侧颜色条，默认显示，设置为None时不显示
#参数cmap可调控热图颜色，具体颜色种类参考：https://blog.csdn.net/ztf312/article/details/102474190
ax=sns.heatmap(y, ax=ax,vmin=71,vmax=90,cmap='YlGnBu_r',fmt='.1f',annot=True,linewidths=2,cbar=True)

#ax.set_title('hello') #plt.title('热图'),均可设置图片标题
ax.set_ylabel('mc',fontsize=20,fontweight ='bold')  #设置纵轴标签
ax.set_xlabel('kc',fontsize=20,fontweight ='bold')  #设置横轴标签

#设置坐标字体方向，通过rotation参数可以调节旋转角度
yticks = ['32','64','96','128','160','192','224','256','288','320']
xticks = ['64','128','192','256','320','384','448','512','576','640']
ax.set_xticklabels(xticks, ha='center',fontsize=14)
ax.set_yticklabels(yticks, rotation=360, ha='center',fontsize=14)
#plt.yticks((0,1,2,3,4,5,6,7,8,9),(32,64,96,128,160,192,224,256,288,320),fontsize=14)
#plt.xticks((0,1,2,3,4,5,6,7,8,9),(64,128,192,256,320,384,448,512,576,640),fontsize=14)
#plt.setp(label_y, rotation=360, horizontalalignment='right')
#label_x = ax.get_xticklabels()
#plt.setp(label_x, rotation=45, horizontalalignment='right')


f.tight_layout()
plt.show()
f.savefig('test_mc_kc_TH.pdf', bbox_inches='tight')