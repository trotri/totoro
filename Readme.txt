1、依赖环境
Microsoft DirectX SDK (June 2010) 和 bass24

2、安装DirectX 和 bass24
bass24.zip安装包：...\totoro\Bin\setup\bass24.zip
DirectX安装包太大，不提交GitHub

安装地址：
C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)
C:\Windows\bass24 -- 直接解压

3、配置属性
常规 -> 输出目录 -> ..\Bin
常规 -> 字符集 -> 使用Unicode字符集
调试 -> 工作目录 -> ..\Bin
VC++目录 -> 包含目录 -> C:\Program Files %28x86%29\Microsoft DirectX SDK %28June 2010%29\Include 和 C:\Windows\bass24\c
VC++目录 -> 库目录 -> C:\Program Files %28x86%29\Microsoft DirectX SDK %28June 2010%29\Lib\x86 和 C:\Windows\bass24\c
