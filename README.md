注水算法：源自信息论，将值为1的总功率分给n个信道，使得总功率最大。总功率为∑log(ai+xi)，ai为已知条件。
利用c++，通过暴力搜索，解决下面的凸优化问题（注水问题）

![image-20240223000144689](README/image-20240223000144689.png)

该问题经过求解KKT条件后转化为：

![image-20240223000305557](README/image-20240223000305557.png)
如果有所帮助，请点一个小星星或者关注本人的GitHub，万分感谢。
If it helps, please click on starred or follow my GitHub, thank you very much.
