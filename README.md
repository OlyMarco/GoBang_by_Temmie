# Gobang_by_Temmie

![Screenshot](./images/main.png)

## 简介 (Introduction)

这是一款功能完整的桌面五子棋应用程序，展示了现代C++与Qt框架的综合应用。项目基于 **Qt 5.12 (C++11)** 开发，实现了人机对战、本地双人、局域网联机三种游戏模式。AI采用评分表算### Controls:
- Select the battle mode on the main screen.
- Make a move by clicking the mouse (hint marks will appear at possible move locations).
- In local battle mode, all operations can be performed using the mouse.
- In online battle mode, enter the server's IP address and port number.
- When creating a server, the window title will display the IPv4 address (if available), and the port number can be adjusted.



## 编译与运行 (Build & Run)

### 环境要求 (Requirements)
- **Qt**: 5.12+ (推荐 5.15)
- **编译器**: 
  - Windows: MSVC 2017+ / MinGW
  - Linux: GCC 7+
  - macOS: Clang
- **C++标准**: C++11

### 编译步骤 (Build Steps)

**方法一: Qt Creator**
```bash
1. 打开 Qt Creator
2. File → Open File or Project
3. 选择 GoBang_by_Temmie/GoBang_by_Temmie.pro
4. 配置 Kit (编译器和Qt版本)
5. 点击 Build 或按 Ctrl+B
6. 点击 Run 或按 Ctrl+R
```

**方法二: 命令行编译**
```bash
# 生成 Makefile
qmake GoBang_by_Temmie.pro

# Windows (MSVC)
nmake

# Windows (MinGW) / Linux / macOS
make

# 运行
./GoBang_by_Temmie  # Linux/macOS
GoBang_by_Temmie.exe  # Windows
```

### Windows 用户快速体验
📦 下载 [Release](../../releases) 中的预编译 `.exe` 文件，解压后直接运行。



## 项目特色 (Highlights)

### ✨ 代码质量
- ✅ 模块化设计，低耦合高内聚
- ✅ 清晰的命名规范和注释
- ✅ 合理使用STL容器和Qt容器
- ✅ 遵循Qt信号槽最佳实践
- ✅ 资源文件统一管理 (.qrc)

### 🎯 技术亮点
- **评分表AI**: 不依赖搜索树，性能优秀
- **TCP网络编程**: 完整的客户端-服务器架构
- **自定义绘图**: QPainter实现专业棋盘渲染
- **跨平台支持**: 基于Qt，一次编写多平台运行
- **事件驱动**: 利用Qt信号槽实现异步通信

### 📚 学习价值
适合学习以下技术点：
- Qt Widgets 界面开发
- Qt Network 网络编程
- C++ 面向对象设计
- 游戏逻辑与AI算法
- 自定义控件绘制
- 多模块项目组织




This is a feature-complete desktop Gobang (Five-in-a-Row) application demonstrating comprehensive use of modern C++ and Qt framework. Built with **Qt 5.12 (C++11)**, it implements three game modes: AI battle, local multiplayer, and LAN multiplayer. The AI uses a scoring table algorithm with 8-direction pattern recognition for intelligent moves, providing challenging gameplay without deep search algorithms.



## 技术栈 (Tech Stack)

### 核心技术 (Core Technologies)
- **语言 (Language)**: C++11
- **框架 (Framework)**: Qt 5.12
  - Qt Widgets (GUI)
  - Qt Network (TCP通信)
  - Qt Core (信号槽机制)
- **设计模式 (Design Patterns)**: 模块化架构、信号槽、MVC
- **网络协议 (Network)**: TCP/IP
- **构建系统 (Build)**: qmake

### 项目架构 (Architecture)
```
├── BoardParams      # 棋盘参数与常量定义
├── GameCore         # 游戏核心逻辑与状态管理
├── ScoreEngine      # AI评分引擎
├── GameWindow       # 游戏主窗口与棋盘渲染
├── LanBattle        # 局域网客户端
└── NetServer        # 网络服务器
```



## 核心功能 (Core Features)

### 🎮 三种游戏模式
1. **人机对战 (AI Mode)**: 基于评分表的智能AI对手
2. **本地双人 (Local Mode)**: 单机双人对战
3. **联网对战 (LAN Mode)**: 局域网多人在线对战

### 🤖 AI算法实现
- **算法类型**: 评分表法 (Scoring Table Algorithm)
- **核心策略**: 
  - 八方向全局扫描 (横、竖、斜 × 正反)
  - 棋型识别 (活二、活三、死三、活四、死四、活五)
  - 攻防评分机制
  - 动态最优落点选择
- **性能特点**: 
  - 无需深度搜索，响应迅速
  - 完全遍历评分，策略稳定
  - 适合15×15标准棋盘

### 🌐 网络功能
- **TCP/IP通信**: 使用QTcpSocket/QTcpServer
- **服务器模式**: 
  - 自动显示本机IPv4地址
  - 可自定义端口号
  - 支持多客户端连接管理
- **客户端模式**:
  - 连接指定服务器IP和端口
  - 实时棋步同步
  - 断线检测与处理

### 🎨 界面设计
- 自定义QPainter棋盘绘制
- 鼠标悬停提示
- 实时游戏状态显示
- 玩家信息展示
- 流畅的交互体验



## 技术实现细节 (Technical Implementation)

### 📊 AI评分算法详解

**评分规则表 (Scoring Rules)**:

| 棋型 | 连子数 | 空位情况 | 进攻分 | 防守分 | 描述 |
|------|--------|----------|--------|--------|------|
| 活五 | 4+ | - | 10100 | 10000 | 必胜棋型 |
| 活四 | 3 | 两端空 | 110 | 100 | 下一步成五 |
| 死四 | 3 | 一端空 | 60 | 55 | 需要封堵 |
| 活三 | 2 | 两端空 | 50 | 40 | 潜在威胁 |
| 死三 | 2 | 一端空 | 25 | 30 | 有限威胁 |
| 活二 | 1 | - | 10 | 10 | 初步形成 |

**算法流程**:
1. 遍历所有空位置 (O(n²))
2. 对每个位置进行八方向扫描
3. 统计连子数和空位数
4. 根据规则表累加分数
5. 选择最高分位置落子

**代码示例**:
```cpp
// 核心评分逻辑 (scoreEngine.cpp)
scoreMapVec = engine.calculateScoreEngine(gameMapVec, scoreMapVec);
// 遍历八方向，计算玩家威胁和AI优势
for (int y = -1; y <= 1; y++)
    for (int x = -1; x <= 1; x++)
        // 延伸4格，识别棋型
```

### 🏗️ 模块设计

**1. BoardParams - 参数配置层**
```cpp
const int ChessBoardSize = 15;      // 15×15标准棋盘
const int ChessBlockSize = 40;      // 格子大小
enum GameType { LOCAL_PERSON, NET_PERSON, BOT };
enum GameStatus { PLAYING, WIN, LOSE, DRAW, FREE };
```

**2. GameCore - 核心逻辑层**
- 状态管理: `std::vector<std::vector<int>> gameMapVec`
- 玩家系统: `user` 结构体封装玩家信息
- 胜负判断: 五方向连珠检测
- 模式切换: 支持三种游戏类型

**3. ScoreEngine - AI引擎层**
- 输入: 当前棋盘状态
- 输出: 评分地图
- 特点: 纯函数式设计，无状态依赖

**4. GameWindow - 视图层**
- 继承 `QMainWindow`
- 重写 `paintEvent` 自定义绘图
- 重写 `mouseMoveEvent`/`mouseReleaseEvent` 处理交互
- 使用 Qt 信号槽实现模块间通信

**5. 网络层 (LanBattle + NetServer)**
```cpp
// 服务器端
QTcpServer *m_s;
QVector<UserConnection*> Tcp_List;  // 连接管理

// 客户端
QTcpSocket *tcp;
// 数据序列化传输
```

### 🔄 数据流转

```
用户点击 → GameWindow::mouseReleaseEvent
    ↓
GameCore::actionByPerson/AI/Net
    ↓
updateGameMap (更新棋盘状态)
    ↓
isWin / isDraw (胜负判断)
    ↓
paintEvent (重绘界面)
```

**网络模式数据流**:
```
Client1 → LanBattle → TCP → NetServer → TCP → LanBattle → Client2
```



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

我学习了Qt平台的基础操作，如何进行多文件编程、网络编程，并加深了对C++类编程的理解。通过实现AI评分算法，掌握了游戏AI的基本思路；通过网络模块开发，理解了TCP通信和客户端-服务器架构；通过自定义绘图，学会了Qt的绘图系统。

I learned fundamental Qt operations, multi-file programming, and network programming, deepening my understanding of C++ OOP. By implementing the AI scoring algorithm, I grasped the basics of game AI; through network module development, I understood TCP communication and client-server architecture; through custom drawing, I mastered Qt's painting system.



## 演示视频 (Demo Videos)

- [观看演示视频 (Bilibili)](https://www.bilibili.com/video/BV1fs4y1r7XH)
- [Watch Demo Video (YouTube)](https://youtu.be/Ela0xCwen9Q)



## 项目统计 (Project Stats)

- **代码行数**: ~2000+ lines
- **模块数量**: 6 个核心模块
- **文件数量**: 24+ 个源文件
- **支持平台**: Windows / Linux / macOS
- **开发周期**: 2023年上半年
- **最后更新**: 2023/06/30



## 技术栈详细 (Tech Stack Details)

### Qt 模块使用
| 模块 | 用途 | 关键类 |
|------|------|--------|
| Qt Core | 核心功能、信号槽 | QObject, QString, QVector |
| Qt Widgets | GUI界面 | QMainWindow, QLabel, QPainter |
| Qt Network | 网络通信 | QTcpSocket, QTcpServer |
| Qt Gui | 事件处理 | QMouseEvent, QPaintEvent |

### C++ 特性应用
- **STL容器**: `std::vector`, `std::stack`, `std::string`
- **C++11**: `nullptr`, `auto`, `enum class`
- **OOP**: 继承、多态、封装
- **结构体**: `user` 数据封装



## 文件结构说明 (File Structure)

```
GoBang_by_Temmie/
├── main.cpp                    # 程序入口
├── mainwindow.{h,cpp,ui}       # 主窗口（模式选择）
├── icon.{qrc,rc}               # 图标资源
├── logo.ico                    # 应用图标
├── BoardParams/                # 参数模块
│   ├── boardParams.h           # 常量、枚举定义
│   └── boardParams.cpp
├── GameCore/                   # 核心逻辑
│   ├── gameCore.h              # 游戏状态、规则
│   └── gameCore.cpp            # 落子、判断逻辑
├── ScoreEngine/                # AI引擎
│   ├── scoreEngine.h           # 评分接口
│   └── scoreEngine.cpp         # 评分算法实现
├── GameWindow/                 # 游戏窗口
│   ├── gameWindow.h            # 界面、交互
│   └── gameWindow.cpp          # 绘图、事件处理
├── LanBattle/                  # 联网客户端
│   ├── lanBattle.{h,cpp,ui}    # 连接服务器
│   └── ...                     # TCP通信
├── NetServer/                  # 网络服务器
│   ├── netServer.{h,cpp,ui}    # 服务器管理
│   └── userConnection.{h,cpp}  # 连接管理
└── GoBang_by_Temmie.pro        # 项目配置文件
```



## 更新 (Updates)



### 模块更新历史

- **v1.0** (2023/06/30) - 初始版本发布
  - ✅ 完成三种游戏模式
  - ✅ 实现评分表AI
  - ✅ 完成局域网对战功能
  - ✅ 添加图标和资源文件

### 模块说明

- **BoardParams模块**: 棋盘和游戏参数配置中心
- **GameCore模块**: 核心游戏逻辑与状态机
- **GameWindow模块**: 主游戏界面与交互
- **LanBattle模块**: 局域网对战客户端
- **NetServer模块**: 网络服务器与连接管理
- **ScoreEngine模块**: AI评分表引擎



## 开源协议 (License)

本项目采用 **MIT License** 开源协议。

- ✅ 可自由使用、修改、分发
- ✅ 可用于商业用途
- ✅ 需保留原作者版权声明

详见 [LICENSE](./LICENSE) 文件。



## 联系方式 (Contact)

- **GitHub**: [@OlyMarco](https://github.com/OlyMarco)
- **项目地址**: [GoBang_by_Temmie](https://github.com/OlyMarco/GoBang_by_Temmie)


## 致谢 (Acknowledgments)

感谢 Qt 社区提供的优秀框架和文档支持！

Thanks to the Qt community for the excellent framework and documentation support!

<div align="center">

**⭐ 如果这个项目对您有帮助，请给个 Star！**

**⭐ If this project helps you, please give it a Star!**

Made with ❤️ by Temmie | 2023

</div>
