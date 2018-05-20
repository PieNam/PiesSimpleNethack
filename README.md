# PiesSimpleNethack
---
>About Pie's Simple NetHack.

##编译与运行

该NetHack游戏在Windows Visual Studio开发平台上（大材小用地）编写、编译。通过新建项目解决方案，逐一添加头文件以及源代码文件，再执行项目，由VS自动完成源文件的编译和链接，再进行调试与运行。

##玩法

Attention：请将程序运行窗口默认大小调至120x45以上再行运行，以防影响打印效果

Simple NetHack仿照经典游戏NetHack。主要游戏内容为玩家操控的角色在随机生成的地下城地图中进行探索和生存。基本功能和游戏思路上与NetHack一致。游戏背景和说明在起始页面已作出说明。

游戏中'@'代表玩家，'M'和'm'代表大小怪物，'.'代表地板，'^'代表路径，'#'代表墙壁。同时还有'o'、'!'、']' 分别代表药品、攻击力加成（武器）以及防御力加成（盔甲）。这些游戏元素可以简单地通过修改宏定义来改变表示方式。

游戏不是即时的，是“玩家走一步，怪物走一步”的方式。玩家可以通过英文键盘小写模式下 w e r s d f x c v 九个按键来控制角色八方向的移动和原地休息，键位和移动方向相一致。还可以通过英文键盘小写模式下u i o h k b n m 九个按键来控制角色进行把方向的攻击，键位与攻击方向相一致。

游戏中的角色状态在地图下方显示，每一次行为后都可以看到即时的血量、防御力、攻击力、等级、经验值等具体信息。游戏中大部分的行为信息都会在状态栏下方的Message栏显示，同时，状态栏下方还可以通过p键调出背包，查看角色已经获得的加成（武器装备）情况。

以上操作指令，可以在游戏中随时通过q键调出指令列表参照。
