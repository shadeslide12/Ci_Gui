# 蓝色配色方案改进

## 改动说明

已将Post GUI改为蓝色配色方案，**不改变原有布局**，只优化颜色：

### ✅ 已完成的改进

1. **工具栏** - 蓝色渐变效果 (#3d87c2 → #2e6ca6)
   - 白色图标和文字
   - 半透明悬停效果

2. **状态栏** - 蓝色渐变效果 (#2e6ca6 → #1e5a96)
   - 白色文字
   - 粗体显示

3. **停靠窗口标题** - 蓝色渐变 (#5a9fd4 → #4a8fc4)
   - 白色文字

4. **按钮和菜单** - 浅蓝色悬停效果
   - 保持原有功能不变

### ❌ 已回退的改动

- 移除了左侧树形对象浏览器
- 移除了底部属性面板
- 保持原有的控制面板布局

## 使用方法

### 1. 重新编译

```bash
cd build
cmake ..
make
```

### 2. 复制样式表文件

样式表需要在可执行文件旁边：

**Linux/WSL:**
```bash
cp GUI/Post/ModernStyle.qss build/bin/
```

**Windows:**
```powershell
copy GUI\Post\ModernStyle.qss build\bin\
```

### 3. 运行程序

```bash
cd build/bin
./qt_post_standalone
```

## 效果预览

- ✅ 工具栏：蓝色渐变背景，白色图标
- ✅ 状态栏：蓝色渐变背景，白色文字
- ✅ 左侧控制面板：保持原样，不受影响
- ✅ 停靠窗口标题：蓝色渐变
- ✅ 按钮悬停：浅蓝色高亮

## 如果样式没有生效

### 方法1：检查样式表路径

在 `MainWindow.cpp` 第149-154行：

```cpp
// 加载现代化配色方案
QFile styleFile("ModernStyle.qss");
if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
    QString styleSheet = QLatin1String(styleFile.readAll());
    this->setStyleSheet(styleSheet);
    styleFile.close();
}
```

### 方法2：使用绝对路径（调试用）

临时修改为绝对路径：

```cpp
QFile styleFile("f:/Linux_Files/ZJU/zjui-cfd-pre-wsl/GUI/Post/ModernStyle.qss");
```

### 方法3：添加调试信息

在样式表加载后添加：

```cpp
if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
    QString styleSheet = QLatin1String(styleFile.readAll());
    this->setStyleSheet(styleSheet);
    qDebug() << "样式表加载成功！";
    styleFile.close();
} else {
    qDebug() << "样式表加载失败：" << styleFile.errorString();
}
```

## 如何进一步自定义颜色

编辑 `ModernStyle.qss` 文件：

### 改变工具栏颜色

```css
QToolBar {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                stop:0 #你的颜色1, stop:1 #你的颜色2);
}
```

### 改变状态栏颜色

```css
QStatusBar {
    background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                stop:0 #你的颜色1, stop:1 #你的颜色2);
}
```

### 推荐的蓝色色号

- **深蓝**: #1e5a96
- **中蓝**: #2e6ca6
- **浅蓝**: #3d87c2
- **亮蓝**: #5a9fd4
- **极浅蓝**: #e3f2fd

## 常见问题

### Q: 编译后样式没有应用？
A: 确保 `ModernStyle.qss` 文件在可执行文件同目录下。

### Q: 想要禁用蓝色主题？
A: 注释掉 `MainWindow.cpp` 中的样式表加载代码（149-154行）。

### Q: 某些控件没有变色？
A: 可能需要重启程序，Qt样式表在运行时加载。

## 总结

✅ **保持原有布局和功能**  
✅ **添加蓝色配色方案**  
✅ **工具栏和状态栏现代化**  
✅ **不影响现有操作**

现在的界面会更专业，同时保持原有的所有功能！
