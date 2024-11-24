# 欢迎来到压缩工具

### 版本

1.0.2 完成了对文档的部分撰写

1.0.1 完成了哈夫曼解压的工作

1.0.0 完成了哈夫曼压缩的工作

### 编译代码

#### 环境准备

Win+R打开输入

```bash
cmake --version
mingw32-make --version
```

如果没有相应软件请自行下载并配置

#### 开始编译

打开powershell进入cppZipAlg_1.0.x_Windows文件夹

```powershell
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make.exe
```

### 运行程序

```powershell
cd ..
./ziptool.exe
```

### 注意事项

在运行之后可根据提示进行操作，注意：解压缩默认在files文件夹中进行。