# inputmethod

#### 介绍
基于Qt5，支持中文拼音输入、英文输入、数字输入、常用符号输入、手写输入、实体键盘同步

#### 软件架构
Q5虚拟键盘框架+VC手写输入扩展库


#### 安装教程

1.  下载源码，编译
2.  安装微软手写支持库_Getintopc.com_Tablet_PC_Software_Development_Kit_1.7.exe

#### 使用说明

声明：部分有参考csdn其他牛人的资料，现将代码共享，共同学习，来源于社会，回馈社会。

一、概述
有用过Qt虚拟键盘的同志都知道，Qt的虚拟键盘确实很强大，特别是Qt5自带的的虚拟键盘，支持多国语言输入，拼音自然不在话下，而且采用界面是采用qml来做的，美观、大方，但是也存在很多鸡肋的地方（商业版的Qt可能不存在，会更完善）。
 1. Qt自带的虚拟键盘支持手写输入，但是只有myscript，t9write，lipi-toolkit三种库，myscript，t9write很强大，支持多国语言手写输入，但是收费，要在Qt收费版中才能体验到；lipi-toolkit免费，Qt社区版已包含，但是只支持英文手写输入。
 2. Qt自带的虚拟键盘不支持实体键盘同步输入。
 
 介于这种情况呢，我们可以借助第三方手写支持来实现Qt的手写输入功能。

二、开发环境
 1. Windows操作系统
 2. Qt5.12.5
 3. Visual Studio 2019
 
三、主要功能 
 1. 中文拼音输入
 2. 英文输入
 3. 数字输入
 4. 常用符号输入
 5. 手写输入
 6. 实体键盘同步

四、使用
1、输入法使用
 (1) 下载源码，编译
 (2) 安装微软手写支持库_Getintopc.com_Tablet_PC_Software_Development_Kit_1.7.exe
 (3) 参照[testdemo](https://gitee.com/wangzhenglin/inputmethod/tree/master/src/testdemo)
 

```cpp
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("cqdlc"));

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
```
2、手写输入模块接口
手写输入模块是VC扩展库，在handinput工程里导出接口
```cpp
/////////////////////////////////////////////////////////
//                                          
// export API
//
//
/////////////////////////////////////////////////////////
extern "C" __declspec(dllexport) bool Init(long inputWinId)
{
	return CAdvRecoApp::Init(inputWinId);
}

extern "C" __declspec(dllexport) void SetBstrResultsCB(BstrResults pBstrResults)
{
	CAdvRecoApp::SetBstrResultsCB(pBstrResults);

	return;
}

extern "C" __declspec(dllexport) void Clear()
{
	CAdvRecoApp::Clear();

	return;
}
```


#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request


#### 码云特技

1.  使用 Readme\_XXX.md 来支持不同的语言，例如 Readme\_en.md, Readme\_zh.md
2.  码云官方博客 [blog.gitee.com](https://blog.gitee.com)
3.  你可以 [https://gitee.com/explore](https://gitee.com/explore) 这个地址来了解码云上的优秀开源项目
4.  [GVP](https://gitee.com/gvp) 全称是码云最有价值开源项目，是码云综合评定出的优秀开源项目
5.  码云官方提供的使用手册 [https://gitee.com/help](https://gitee.com/help)
6.  码云封面人物是一档用来展示码云会员风采的栏目 [https://gitee.com/gitee-stars/](https://gitee.com/gitee-stars/)
