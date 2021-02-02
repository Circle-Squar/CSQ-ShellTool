# CSQ-ShellTools

<div>Circle-Squar</div>

### 关于

---

​	为了改善在终端环境下的使用体验，我制作了这些工具，这里是源代码。该仓库没什么规矩，源代码可以随意使用。（不过应该不会有人愿意看我这菜鸡的代码吧 =w=）

---

### 这里都有什么

cmgen 初始化一个CMake工程的工具

cmgen [-l c/j (c/c++/java) ] [-n] ProjectName [-v Project version] [-f] [-i]
cmgen: 
  -h 帮助菜单
  -l 编程语言: c / j (默认: C/C++)
  -n 项目名称
  -v 项目版本
  -f 强制生成（在有CMakeLists.txt 的情况下依旧生成）

EXP: cmgen HelloWorld -lc -v1.0 -i