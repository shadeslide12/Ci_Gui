# Post蓝色主题使用指南

## ✅ 已完成的改动

### 1. 还原了共用的 `linux.qss`
- **文件**: `GUI/resources/qss/linux.qss`
- **说明**: 已还原为原始版本，不影响Pre部分

### 2. 创建了Post专用样式文件
- **文件**: `GUI/Post/post_blue_theme.qss`
- **说明**: Post独立的蓝色主题样式表

### 3. 添加了自定义蓝色标题栏
- 在工具栏上方添加了显示"CFD Post-processing Tool"的蓝色横栏
- 蓝色渐变效果 (#5a9fd4 → #4a8fc4)
- 白色粗体文字

### 4. 工具栏和状态栏
- **工具栏**: 蓝色渐变，白色图标和文字
- **状态栏**: 蓝色渐变，白色文字

## 🎨 效果说明

### 自定义标题栏
- 位置：工具栏上方
- 背景：蓝色渐变 (#5a9fd4 → #4a8fc4)
- 文字："CFD Post-processing Tool" 白色粗体
- 高度：30px

### 工具栏
- 背景：蓝色渐变 (#4a8fc4 → #3d87c2)
- 按钮：白色文字，悬停时半透明白色背景

### 状态栏
- 背景：蓝色渐变 (#3d87c2 → #2e6ca6)
- 文字：白色粗体

## 🚀 编译和使用

### 1. 编译项目

```bash
cd build
cmake ..
make
```

### 2. 复制样式文件到bin目录

**Linux/WSL:**
```bash
cp GUI/Post/post_blue_theme.qss build/bin/
```

**Windows:**
```powershell
copy GUI\Post\post_blue_theme.qss build\bin\
```

### 3. 运行程序

```bash
cd build/bin
./qt_post_standalone
```

## 📝 关于系统标题栏

**注意**: Windows/Linux的系统标题栏（最顶部的窗口标题栏）无法通过Qt样式表改变颜色，这是操作系统级别的限制。

我们添加的是一个**自定义标题栏**（在工具栏上方），它显示"CFD Post-processing Tool"，可以完全自定义颜色。

如果你想要：
- ✅ **保留系统标题栏** + 自定义蓝色栏（当前方案）
- ⚠️ **隐藏系统标题栏** + 只显示自定义标题栏（需要额外实现窗口拖动功能）

## 📁 文件结构

```
GUI/
├── resources/
│   └── qss/
│       └── linux.qss          # 已还原，Pre和Post共用
└── Post/
    ├── MainWindow.h           # 添加了customTitleBar
    ├── MainWindow.cpp         # 添加了CreateCustomTitleBar()
    ├── post_blue_theme.qss    # Post专用蓝色主题
    └── POST_BLUE_THEME_GUIDE.md  # 本文档
```

## 🎨 自定义颜色

如果想修改蓝色色调，编辑 `post_blue_theme.qss`：

### 标题栏颜色
在 `MainWindow.cpp` 的 `CreateCustomTitleBar()` 函数中修改：
```cpp
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
"                                stop:0 #你的颜色1, stop:1 #你的颜色2);"
```

### 工具栏颜色
在 `post_blue_theme.qss` 中修改：
```css
QToolBar {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                stop:0 #你的颜色1, stop:1 #你的颜色2);
}
```

### 状态栏颜色
```css
QStatusBar {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                stop:0 #你的颜色1, stop:1 #你的颜色2);
}
```

## 🔧 调试信息

运行程序时，终端会显示：
- `Post蓝色主题已加载！` - 样式表加载成功
- `自定义蓝色标题栏已创建！` - 标题栏创建成功

如果没有看到这些信息，检查：
1. `post_blue_theme.qss` 是否在可执行文件同目录
2. 编译是否成功

## ⚠️ 注意事项

1. **Pre部分不受影响** - 共用的 `linux.qss` 已还原
2. **Post专用样式** - 只有Post使用 `post_blue_theme.qss`
3. **标题栏是额外添加的** - 系统标题栏仍然存在
4. **样式文件需要复制** - 记得复制到bin目录

## 📷 效果对比

### 改进前
- 灰色工具栏
- 灰色状态栏
- 无自定义标题栏
- 黄白色背景

### 改进后
- ✅ **蓝色渐变自定义标题栏**（横跨顶部，显示"CFD Post-processing Tool"）
- ✅ **蓝色渐变工具栏**（白色图标和文字）
- ✅ **蓝色渐变状态栏**（底部，白色文字）
- ✅ **纯白色背景**（#ffffff）

## 🔧 最新修复 (v2)

### 修复的问题
1. ✅ **标题栏错位** - 现在正确显示在窗口最顶部（横向）
2. ✅ **状态栏颜色** - 底部状态栏现在是蓝色渐变
3. ✅ **背景颜色** - 整个界面改为纯白色，不再是黄白色

### 技术实现
- 自定义标题栏使用`QToolBar`方式插入到最顶部
- 状态栏样式显式设置，确保蓝色生效
- 全局背景设置为 `#ffffff` 纯白色

现在界面看起来更专业，与商业CFD软件风格一致！🎉
