# 堆排序(heap sort)

### 步骤

- 首先对数组进行建堆，得到最大堆
- 取堆的根节点，也就是最大值
- 保持树的结构不变，将根节点与最后一个值交换，然后对根节点进行MAX-HEAPIFY，这样第二大的值就成为根节点，以此类推

![image-20211207163229950](C:\Users\dell\AppData\Roaming\Typora\typora-user-images\image-20211207163229950.png)

### 时间复杂度

​	O(nlogn)

### 稳定性

​	堆排序破坏了相对元素之间的相对次序，属于不稳定的排序算法