# neon_add
neon内嵌汇编实现数组相加

g++ ./testneon.cpp -O3 && ./a.out

分别以不同的方式事项两个数组相加，并打印耗时
- neon汇编，同时处理4或者16个浮点数
- neon内敛函数，同时处理16个浮点数
- navice基础实现
