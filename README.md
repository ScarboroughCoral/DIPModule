# DIPModule

数字图像处理实验

:sparkles: 系列博客地址：[扶桑树叶之DIP](http://blog.scarboroughcoral.top/tags/DIP/)


## 实验内容

- [x] BMP 文件处理
  - [x] RGB 分离
  - [x] 24位彩色图像灰度化
  - [x] 对8位灰度图进行反色
- [x] 直方图处理
  - [x] 直方图统计
  - [x] 直方图均衡化
- [x] 空间域滤波（需对边界进行处理，2种方法）
  - [x] 平均处理（基于模板卷积运算）
  - [x] 中值滤波
- [x] 图像变换
  - [x] 图像缩放
  - [x] 图像平移
  - [x] 图像镜像
  - [x] 图像旋转
  - [ ] 透视变换（选做）
- [x] 阈值分割
  - [x]  给定阈值T
  - [ ] 双峰法（极小点阈值法）（选做——就是不做）
  - [x]  迭代阈值法
  - [x]  Otsu(大津算法)
- [ ] 基于区域的分割
- [ ] 边缘检测
  - [x] Prewitt
  - [x] Sobel
  - [ ] LOG
  - [ ] Canny（选做）
- [ ] Hough变换
- [ ] 区域标记与轮廓提取

## 关键文件目录结构

```
│  .gitignore
│  README.md
│
├─Debug
│
├─Graph
│  │  Algo.c                    //一些基础算法，eg.quicksort
│  │  Algo.h
│  │  BMP.c                     //BMP文件结构体定义及文件处理
│  │  BMP.h      
│  │  BMPHelper.h               //BMP文件处理集合
│  │  BMPUtil.c                 //BMP文件读写
│  │  BMPUtil.h
│  │  EdgeDetection.c           //边缘检测
│  │  EdgeDetection.h
│  │  Histogram.c               //直方图输出
│  │  Histogram.h
│  │  HistogramStatic.c         //直方图处理
│  │  Main.c                    //入口文件
│  │  RegionSegmentation.c      //区域划分
│  │  RegionSegmentation.h
│  │  SpatialDomainFilter.c     //空间域滤波处理
│  │  SpatialDomainFilter.h
│  │  ThresholdSegmentation.c   //阈值划分
│  │  ThresholdSegmentation.h
│  │  Transformation.c          //图像基本变换
│  │  Transformation.h
│  │
│  ├─Debug
│  │
│  └─x64
│      └─Debug
│
└─x64
    └─Debug
```
