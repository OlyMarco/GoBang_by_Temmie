# Gobang_by_Temmie

![Screenshot](./images/main.png)

## 简介 (Introduction)

这是一款桌面五子棋应用程序，旨在练习C++编程。项目基于 Qt 5.12 (C++11) 开发，AI使用评分表法，尽管没有使用深度搜索算法，依然能够提供不小的挑战。

This is a desktop Gobang (Five-in-a-Row) application, created as a C++ practice project. Developed with Qt 5.12 (C++11), the AI uses a scoring table method. Although deep search was not implemented, the AI remains challenging with its scoring-based strategy.

## 体验 (Experience)

### Windows用户:
可以下载已发布的 `.exe` 文件，直接运行。

### 编译源代码:
通过Qt打开源程序目录下的 `GoBang_by_Temmie.pro` 文件，直接编译运行。

### 操作说明 (Controls):
- 在主界面选择对战模式
- 落子：点击鼠标（落子点会有提示标记）
- 本地对战模式：使用鼠标完成所有操作
- 联网对战模式：输入服务器IP地址和端口号
- 服务器创建时，窗口标题显示IPv4地址（如果有），可以修改端口号

### Controls:
- Select the battle mode on the main screen.
- Make a move by clicking the mouse (hint marks will appear at possible move locations).
- In local battle mode, all operations can be performed using the mouse.
- In online battle mode, enter the server’s IP address and port number.
- When creating a server, the window title will display the IPv4 address (if available), and the port number can be adjusted.

## 我学到了什么？ (What I Learned)

我学习了Qt平台的基础操作，如何进行多文件编程、网络编程，并加深了对C++类编程的理解（该程序只是一个小的练手项目）。

I learned basic operations on the Qt platform, how to program with multiple files, network programming, and deepened my understanding of C++ class-based programming (this project is just a small practice).

## 演示视频 (Demo Videos)

- [观看演示视频](https://www.bilibili.com/video/BV1fs4y1r7XH)
- [Watch Demo Video](https://youtu.be/Ela0xCwen9Q)

## 更新 (Updates)

- **BoardParams模块**：棋盘和游戏参数 (Board and game parameters)
- **GameCore模块**：核心逻辑 (Core game logic)
- **GameWindow模块**：主界面 (Main interface)
- **LanBattle模块**：联网对战界面 (Online battle interface)
- **NetServer模块**：服务器创建界面 (Server creation interface)
- **ScoreEngine模块**：评分表API (Scoring table API)
