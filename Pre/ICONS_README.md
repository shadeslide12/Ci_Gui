# 图标资源说明

## 概述

本文档说明Post GUI现代化界面所需的图标资源。

## 图标需求

### 1. 对象类型图标 (16x16 或 24x24 像素)

放置在 `GUI/Post/icons/` 目录下：

- **mesh.png** - 网格图标（可用网格图案）
- **contour.png** - 等值线图标（可用波浪线）
- **vector.png** - 向量场图标（可用箭头）
- **boundary.png** - 边界图标（可用边框图案）
- **display.png** - 显示对象图标（可用眼睛图标）
- **isosurface.png** - 等值面图标（可用3D表面）
- **slice.png** - 切片图标（可用切刀图案）

### 2. 工具栏图标 (24x24 或 32x32 像素)

- **open.png** - 打开文件（文件夹图标）
- **save.png** - 保存（软盘图标）
- **export.png** - 导出（向外箭头）
- **settings.png** - 设置（齿轮图标）
- **refresh.png** - 刷新（循环箭头）

### 3. 视图图标 (24x24 像素)

- **view_3d.png** - 3D视图（立方体）
- **view_xy.png** - XY平面视图
- **view_xz.png** - XZ平面视图
- **view_yz.png** - YZ平面视图

### 4. UI元素图标 (8x8 或 12x12 像素)

- **check.png** - 勾选标记
- **down-arrow.png** - 下拉箭头
- **branch-closed.png** - 树形折叠
- **branch-open.png** - 树形展开

## 图标来源建议

### 1. 免费图标库

推荐使用以下免费图标资源：

- **Material Design Icons**: https://materialdesignicons.com/
- **Font Awesome**: https://fontawesome.com/icons
- **Feather Icons**: https://feathericons.com/
- **Heroicons**: https://heroicons.com/
- **Ionicons**: https://ionic.io/ionicons

### 2. 创建自定义图标

可以使用以下工具创建简单图标：

- **Inkscape** (免费矢量图形编辑器)
- **GIMP** (免费图像编辑器)
- **Figma** (在线设计工具)

### 3. 临时占位符

在开发阶段，可以使用简单的纯色方块作为占位符：

```cpp
// 创建简单的占位符图标
QPixmap createPlaceholderIcon(const QColor &color, const QSize &size)
{
    QPixmap pixmap(size);
    pixmap.fill(color);
    
    QPainter painter(&pixmap);
    painter.setPen(Qt::white);
    painter.drawRect(0, 0, size.width()-1, size.height()-1);
    
    return pixmap;
}

// 使用示例
QIcon meshIcon(createPlaceholderIcon(QColor(100, 150, 200), QSize(16, 16)));
```

## 图标集成步骤

### 步骤1：准备图标文件

在 `GUI/Post/` 目录下创建 `icons/` 文件夹，并放入图标文件：

```
GUI/Post/
├── icons/
│   ├── mesh.png
│   ├── contour.png
│   ├── vector.png
│   ├── ...
├── ModernStyle.qss
├── modern_resources.qrc
└── ...
```

### 步骤2：更新资源文件

`modern_resources.qrc` 已经配置好，只需确保图标文件存在。

### 步骤3：重新编译资源

在CMakeLists.txt中添加资源文件：

```cmake
# 在 qt_post 目标中添加
add_library(qt_post 
    ${CMAKE_CURRENT_SOURCE_DIR}/../resources/resources.qrc
    ${CMAKE_CURRENT_SOURCE_DIR}/modern_resources.qrc  # 添加这行
)
```

### 步骤4：在代码中使用图标

```cpp
// 使用资源系统中的图标
QIcon meshIcon(":/icons/mesh.png");
objectBrowser->addCategory("显示对象", QIcon(":/icons/display.png"));

// 或者动态加载
QPixmap pixmap(":/icons/mesh.png");
if (!pixmap.isNull()) {
    QIcon icon(pixmap);
    // 使用图标...
}
```

## 图标设计规范

### 尺寸标准

- **小图标** (树形视图): 16x16 px
- **中图标** (工具栏): 24x24 px  
- **大图标** (主菜单): 32x32 px

### 风格指南

1. **一致性**: 所有图标使用相同的设计风格
2. **简洁性**: 图标应简单明了，易于识别
3. **对比度**: 确保在浅色背景下可见
4. **线宽**: 保持一致的线条粗细（推荐2px）

### 颜色建议

推荐使用以下配色方案（与ModernStyle.qss协调）：

- **主色**: #0078d4 (蓝色)
- **次色**: #666666 (深灰)
- **强调**: #d83b01 (橙红)
- **成功**: #107c10 (绿色)
- **中性**: #c0c0c0 (浅灰)

## 快速开始（无图标文件）

如果暂时没有图标文件，可以：

### 方案1：使用Qt内置图标

```cpp
// 使用Qt标准图标
QIcon openIcon = style()->standardIcon(QStyle::SP_DialogOpenButton);
QIcon saveIcon = style()->standardIcon(QStyle::SP_DialogSaveButton);
QIcon folderIcon = style()->standardIcon(QStyle::SP_DirIcon);
```

### 方案2：使用Unicode字符

```cpp
// 使用Unicode符号作为简单图标
QLabel *iconLabel = new QLabel("📁"); // 文件夹
QLabel *iconLabel2 = new QLabel("⚙️"); // 设置
QLabel *iconLabel3 = new QLabel("🔄"); // 刷新
```

### 方案3：创建代码生成的简单图标

```cpp
QIcon createSimpleIcon(const QString &text, const QColor &bgColor)
{
    QPixmap pixmap(24, 24);
    pixmap.fill(bgColor);
    
    QPainter painter(&pixmap);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 12, QFont::Bold));
    painter.drawText(pixmap.rect(), Qt::AlignCenter, text);
    
    return QIcon(pixmap);
}

// 使用
QIcon meshIcon = createSimpleIcon("M", QColor(100, 150, 200));
QIcon contourIcon = createSimpleIcon("C", QColor(200, 100, 150));
```

## 高级：SVG图标支持

SVG图标在缩放时不会失真，推荐用于现代化界面：

```cpp
// 加载SVG图标
QIcon icon(":/icons/mesh.svg");

// SVG可以动态改变颜色
QSvgRenderer renderer(":/icons/mesh.svg");
QPixmap pixmap(24, 24);
pixmap.fill(Qt::transparent);
QPainter painter(&pixmap);
renderer.render(&painter);
```

## 示例：完整的图标管理类

可以创建一个图标管理器来统一管理所有图标：

```cpp
class IconManager
{
public:
    static IconManager& instance() {
        static IconManager manager;
        return manager;
    }
    
    QIcon getIcon(const QString &name) {
        if (icons.contains(name)) {
            return icons[name];
        }
        
        // 尝试从资源加载
        QString path = QString(":/icons/%1.png").arg(name);
        if (QFile::exists(path)) {
            QIcon icon(path);
            icons[name] = icon;
            return icon;
        }
        
        // 返回默认图标
        return createDefaultIcon(name);
    }
    
private:
    QMap<QString, QIcon> icons;
    
    QIcon createDefaultIcon(const QString &name) {
        // 创建占位符图标
        return createSimpleIcon(name.left(1).toUpper(), QColor(150, 150, 150));
    }
};

// 使用
QIcon meshIcon = IconManager::instance().getIcon("mesh");
```

## 总结

图标是现代化界面的重要组成部分。本文档提供了多种获取和使用图标的方案：

1. ✅ 使用免费图标库（推荐）
2. ✅ Qt内置图标（快速开始）
3. ✅ Unicode字符（简单场景）
4. ✅ 代码生成（占位符）
5. ✅ 自定义SVG（专业方案）

选择适合项目需求和时间预算的方案即可！
