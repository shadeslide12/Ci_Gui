# 现代化Post GUI集成指南

## 概述

本指南说明如何将新的现代化UI组件集成到Post GUI主窗口中，实现类似商业软件的专业界面。

## 新增组件

### 1. ModernStyle.qss
现代化的Qt样式表，提供：
- 清爽的配色方案
- 现代化的按钮和控件样式
- 平滑的过渡效果
- 专业的工具栏外观

### 2. ObjectBrowser（对象浏览器）
树形结构的对象管理器，替代原有的简单checkbox列表：
- 支持分层组织可视化对象
- 显示/隐藏控制
- 对象类型图标
- 双击编辑属性

### 3. PropertyPanel（属性面板）
动态属性编辑面板：
- 支持多种属性类型（字符串、数值、颜色、下拉框等）
- 实时属性修改
- 美观的表格显示

## 集成步骤

### 步骤1：更新MainWindow.h

在MainWindow类中添加新组件的成员变量：

```cpp
#include "ObjectBrowser.h"
#include "PropertyPanel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    // 现代化UI组件
    ObjectBrowser *objectBrowser = nullptr;
    PropertyPanel *propertyPanel = nullptr;
    
    // 停靠窗口
    QDockWidget *objectBrowserDock = nullptr;
    QDockWidget *propertyPanelDock = nullptr;
};
```

### 步骤2：在MainWindow构造函数中初始化

```cpp
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    // 加载现代化样式表
    QFile styleFile(":/styles/ModernStyle.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheet);
        styleFile.close();
    }
    
    // 创建对象浏览器
    setupObjectBrowser();
    
    // 创建属性面板
    setupPropertyPanel();
    
    // 连接信号槽
    setupModernUIConnections();
    
    // 初始化对象树
    initializeObjectTree();
}
```

### 步骤3：实现设置函数

```cpp
void MainWindow::setupObjectBrowser()
{
    // 创建对象浏览器
    objectBrowser = new ObjectBrowser(this);
    
    // 创建停靠窗口
    objectBrowserDock = new QDockWidget("对象浏览器", this);
    objectBrowserDock->setWidget(objectBrowser);
    objectBrowserDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    
    // 添加到主窗口左侧
    addDockWidget(Qt::LeftDockWidgetArea, objectBrowserDock);
}

void MainWindow::setupPropertyPanel()
{
    // 创建属性面板
    propertyPanel = new PropertyPanel(this);
    
    // 创建停靠窗口
    propertyPanelDock = new QDockWidget("属性", this);
    propertyPanelDock->setWidget(propertyPanel);
    propertyPanelDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);
    
    // 添加到主窗口底部
    addDockWidget(Qt::BottomDockWidgetArea, propertyPanelDock);
}

void MainWindow::setupModernUIConnections()
{
    // 对象可见性改变
    connect(objectBrowser, &ObjectBrowser::objectVisibilityChanged,
            this, &MainWindow::onObjectVisibilityChanged);
    
    // 对象选中
    connect(objectBrowser, &ObjectBrowser::objectSelected,
            this, &MainWindow::onObjectSelected);
    
    // 对象双击（编辑属性）
    connect(objectBrowser, &ObjectBrowser::objectDoubleClicked,
            this, &MainWindow::onObjectDoubleClicked);
    
    // 属性值改变
    connect(propertyPanel, &PropertyPanel::propertyValueChanged,
            this, &MainWindow::onPropertyValueChanged);
}

void MainWindow::initializeObjectTree()
{
    // 添加基本对象分组
    objectBrowser->addCategory("显示对象", QIcon(":/icons/display.png"));
    objectBrowser->addCategory("边界", QIcon(":/icons/boundary.png"));
    objectBrowser->addCategory("等值面", QIcon(":/icons/isosurface.png"));
    objectBrowser->addCategory("切片", QIcon(":/icons/slice.png"));
    objectBrowser->addCategory("向量场", QIcon(":/icons/vector.png"));
}
```

### 步骤4：实现信号槽响应函数

```cpp
void MainWindow::onObjectVisibilityChanged(const QString &categoryName, 
                                          const QString &objectName, 
                                          bool visible)
{
    qDebug() << "Object visibility changed:" << categoryName << "/" << objectName << visible;
    
    // 根据分组类型处理
    if (categoryName == "显示对象") {
        if (objectName.contains("Mesh")) {
            // 控制网格显示/隐藏
            qtvtkWindow->ShowMesh(visible);
        } else if (objectName.contains("Contour")) {
            // 控制等值线显示/隐藏
            qtvtkWindow->ShowContour(visible);
        } else if (objectName.contains("Shade")) {
            // 控制阴影显示/隐藏
            qtvtkWindow->ShowShade(visible);
        }
    } else if (categoryName == "边界") {
        // 处理边界显示/隐藏
        // TODO: 实现边界控制逻辑
    }
    
    // 刷新渲染
    qtvtkWindow->Update();
}

void MainWindow::onObjectSelected(const QString &categoryName, 
                                  const QString &objectName)
{
    qDebug() << "Object selected:" << categoryName << "/" << objectName;
    
    // 更新属性面板显示选中对象的属性
    updatePropertyPanel(categoryName, objectName);
}

void MainWindow::onObjectDoubleClicked(const QString &categoryName, 
                                       const QString &objectName)
{
    qDebug() << "Object double clicked:" << categoryName << "/" << objectName;
    
    // 显示属性面板（如果隐藏）
    if (propertyPanelDock->isHidden()) {
        propertyPanelDock->show();
    }
    
    // 更新并聚焦属性面板
    updatePropertyPanel(categoryName, objectName);
}

void MainWindow::onPropertyValueChanged(const QString &propertyName, 
                                       const QVariant &newValue)
{
    qDebug() << "Property changed:" << propertyName << "=" << newValue;
    
    // 根据属性名称应用更改
    if (propertyName == "透明度") {
        double opacity = newValue.toDouble();
        // TODO: 应用透明度
    } else if (propertyName == "颜色") {
        QColor color = newValue.value<QColor>();
        // TODO: 应用颜色
    }
    
    // 刷新渲染
    qtvtkWindow->Update();
}

void MainWindow::updatePropertyPanel(const QString &categoryName, 
                                     const QString &objectName)
{
    propertyPanel->clearProperties();
    propertyPanel->setObjectName(objectName);
    
    // 根据对象类型添加相应属性
    if (categoryName == "显示对象") {
        propertyPanel->addBoolProperty("可见", true);
        propertyPanel->addDoubleProperty("透明度", 1.0, 0.0, 1.0, 2);
        propertyPanel->addColorProperty("颜色", QColor(255, 0, 0));
    } else if (categoryName == "边界") {
        propertyPanel->addBoolProperty("可见", true);
        propertyPanel->addComboProperty("渲染模式", {"实体", "线框", "点"}, "实体");
        propertyPanel->addDoubleProperty("线宽", 1.0, 0.1, 10.0, 1);
    }
}
```

### 步骤5：在文件加载时更新对象树

```cpp
void MainWindow::on_actionLoadMesh_triggered()
{
    // ... 原有的文件加载代码 ...
    
    // 加载完成后，更新对象浏览器
    objectBrowser->clearAll();
    objectBrowser->addCategory("显示对象");
    objectBrowser->addCategory("边界");
    
    // 添加基本显示对象
    objectBrowser->addObject("显示对象", "网格线", "Mesh", true);
    objectBrowser->addObject("显示对象", "等值线", "Contour", true);
    objectBrowser->addObject("显示对象", "阴影面", "Shade", true);
    objectBrowser->addObject("显示对象", "边缘线", "Edge", false);
    objectBrowser->addObject("显示对象", "向量场", "Vector", false);
    
    // 添加边界对象
    for (int i = 0; i < qtvtkWindow->GetNumberOfBoundaries(); i++) {
        QString boundaryName = QString::fromStdString(
            qtvtkWindow->GetBoundaryName(i));
        objectBrowser->addObject("边界", boundaryName, "Boundary", true);
    }
}
```

## 样式表使用

样式表已经自动应用，但如果需要自定义某些组件，可以：

```cpp
// 单独为某个组件设置样式
myButton->setProperty("primary", true); // 设置为主按钮
myButton->style()->unpolish(myButton);
myButton->style()->polish(myButton);
```

## 布局建议

推荐的窗口布局：
- **左侧**：对象浏览器（宽度约200-250px）
- **中央**：VTK渲染窗口
- **右侧**：颜色条和图例
- **底部**：属性面板（高度约150-200px）
- **顶部**：工具栏和菜单栏

可通过以下代码设置初始大小：

```cpp
void MainWindow::InitializeMainWindow()
{
    // 设置初始窗口大小
    resize(1600, 900);
    
    // 设置停靠窗口初始大小
    resizeDocks({objectBrowserDock}, {250}, Qt::Horizontal);
    resizeDocks({propertyPanelDock}, {180}, Qt::Vertical);
}
```

## 进一步优化建议

1. **添加图标资源**
   - 创建resources.qrc文件
   - 添加工具栏图标、对象类型图标
   - 使用矢量图标（SVG）以支持高DPI

2. **状态栏增强**
   ```cpp
   statusBar()->showMessage("就绪");
   QLabel *coordLabel = new QLabel("坐标: (0, 0, 0)");
   statusBar()->addPermanentWidget(coordLabel);
   ```

3. **工具栏现代化**
   ```cpp
   QToolBar *mainToolBar = new QToolBar("主工具栏", this);
   mainToolBar->setIconSize(QSize(24, 24));
   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
   addToolBar(mainToolBar);
   ```

4. **添加快捷键**
   ```cpp
   objectBrowserDock->toggleViewAction()->setShortcut(Qt::CTRL + Qt::Key_1);
   propertyPanelDock->toggleViewAction()->setShortcut(Qt::CTRL + Qt::Key_2);
   ```

## 测试建议

1. 测试对象浏览器的展开/折叠功能
2. 测试属性面板的各种控件类型
3. 测试停靠窗口的拖拽和停靠
4. 测试在不同分辨率下的显示效果
5. 测试深色模式适配（如需要）

## 完成效果

完成集成后，Post GUI将具有：
- ✅ 现代化的外观和感觉
- ✅ 清晰的对象组织结构
- ✅ 直观的属性编辑
- ✅ 专业的工具栏和菜单
- ✅ 灵活的窗口布局

界面质量将大幅提升，达到商业软件水平！
