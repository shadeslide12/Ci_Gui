/**
 * @file MainWindow_Modern_Integration.cpp
 * @brief 现代化UI集成示例代码
 * 
 * 本文件展示如何将ObjectBrowser和PropertyPanel集成到现有的MainWindow中
 * 这是一个示例文件，不会直接编译，仅供参考
 */

#include "MainWindow.h"
#include "ObjectBrowser.h"
#include "PropertyPanel.h"
#include <QDockWidget>
#include <QFile>
#include <QDebug>

// ==================== 在MainWindow.h中添加 ====================
/*
private:
    // 现代化UI组件
    ObjectBrowser *objectBrowser = nullptr;
    PropertyPanel *propertyPanel = nullptr;
    QDockWidget *objectBrowserDock = nullptr;
    QDockWidget *propertyPanelDock = nullptr;
    
    // 新增的槽函数
private slots:
    void onObjectVisibilityChanged(const QString &categoryName, const QString &objectName, bool visible);
    void onObjectSelected(const QString &categoryName, const QString &objectName);
    void onObjectDoubleClicked(const QString &categoryName, const QString &objectName);
    void onPropertyValueChanged(const QString &propertyName, const QVariant &newValue);
    
    // 新增的辅助函数
private:
    void setupObjectBrowser();
    void setupPropertyPanel();
    void setupModernUIConnections();
    void updatePropertyPanel(const QString &categoryName, const QString &objectName);
    void loadModernStyle();
*/

// ==================== 在MainWindow构造函数中添加 ====================
void MainWindow_AddToConstructor()
{
    // 在原有的 ui->setupUi(this); 之后添加：
    
    // 加载现代化样式表
    QFile styleFile("ModernStyle.qss"); // 或使用资源文件 ":/styles/ModernStyle.qss"
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        qApp->setStyleSheet(styleSheet);
        styleFile.close();
    }
    
    // 初始化现代化UI组件
    setupObjectBrowser();
    setupPropertyPanel();
    setupModernUIConnections();
}

// ==================== 实现新增函数 ====================

void MainWindow::setupObjectBrowser()
{
    // 创建对象浏览器
    objectBrowser = new ObjectBrowser(this);
    
    // 创建停靠窗口
    objectBrowserDock = new QDockWidget(tr("对象浏览器"), this);
    objectBrowserDock->setWidget(objectBrowser);
    objectBrowserDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    objectBrowserDock->setFeatures(QDockWidget::DockWidgetMovable | 
                                   QDockWidget::DockWidgetFloatable);
    
    // 添加到主窗口左侧
    addDockWidget(Qt::LeftDockWidgetArea, objectBrowserDock);
    
    // 初始化基本分组
    objectBrowser->addCategory("显示对象");
    objectBrowser->addCategory("边界");
    objectBrowser->addCategory("特殊视图");
    
    // 添加默认对象（可以在后面根据加载的文件动态更新）
    objectBrowser->addObject("显示对象", "网格线", "Mesh", false);
    objectBrowser->addObject("显示对象", "等值线", "Contour", true);
    objectBrowser->addObject("显示对象", "阴影面", "Shade", true);
    objectBrowser->addObject("显示对象", "边缘线", "Edge", false);
    objectBrowser->addObject("显示对象", "向量场", "Vector", false);
}

void MainWindow::setupPropertyPanel()
{
    // 创建属性面板
    propertyPanel = new PropertyPanel(this);
    
    // 创建停靠窗口
    propertyPanelDock = new QDockWidget(tr("属性"), this);
    propertyPanelDock->setWidget(propertyPanel);
    propertyPanelDock->setAllowedAreas(Qt::LeftDockWidgetArea | 
                                       Qt::RightDockWidgetArea | 
                                       Qt::BottomDockWidgetArea);
    propertyPanelDock->setFeatures(QDockWidget::DockWidgetMovable | 
                                   QDockWidget::DockWidgetFloatable);
    
    // 添加到主窗口底部
    addDockWidget(Qt::BottomDockWidgetArea, propertyPanelDock);
    
    // 设置初始大小
    resizeDocks({objectBrowserDock}, {250}, Qt::Horizontal);
    resizeDocks({propertyPanelDock}, {180}, Qt::Vertical);
}

void MainWindow::setupModernUIConnections()
{
    // 连接对象浏览器信号
    connect(objectBrowser, &ObjectBrowser::objectVisibilityChanged,
            this, &MainWindow::onObjectVisibilityChanged);
    connect(objectBrowser, &ObjectBrowser::objectSelected,
            this, &MainWindow::onObjectSelected);
    connect(objectBrowser, &ObjectBrowser::objectDoubleClicked,
            this, &MainWindow::onObjectDoubleClicked);
    
    // 连接属性面板信号
    connect(propertyPanel, &PropertyPanel::propertyValueChanged,
            this, &MainWindow::onPropertyValueChanged);
}

void MainWindow::onObjectVisibilityChanged(const QString &categoryName, 
                                          const QString &objectName, 
                                          bool visible)
{
    qDebug() << "对象可见性改变:" << categoryName << "/" << objectName << "=" << visible;
    
    // 根据分组和对象名称控制显示
    if (categoryName == "显示对象") {
        if (objectName == "网格线") {
            // 调用原有的mesh checkbox逻辑
            ui->meshCheckBox->setChecked(visible); // 如果有这个checkbox
            meshCheckBoxTriggered(); // 触发原有的槽函数
        } 
        else if (objectName == "等值线") {
            ui->contourCheckBox->setChecked(visible);
            contourCheckBoxTriggered();
        }
        else if (objectName == "阴影面") {
            ui->shadeCheckBox->setChecked(visible);
            shadeCheckBoxTriggered();
        }
        else if (objectName == "边缘线") {
            ui->edgeCheckBox->setChecked(visible);
            edgeCheckBoxTriggered();
        }
        else if (objectName == "向量场") {
            ui->vectorCheckBox->setChecked(visible);
            vectorCheckBoxTriggered();
        }
    }
    else if (categoryName == "边界") {
        // 处理边界显示/隐藏
        // 查找对应的边界索引并调用showBoundaryActor
        for (int i = 0; i < qtvtkWindow->GetNumberOfBoundaries(); i++) {
            QString boundaryName = QString::fromStdString(
                qtvtkWindow->GetBoundaryName(i));
            if (boundaryName == objectName) {
                showBoundaryActor(i, 0, visible); // 假设使用zone 0
                break;
            }
        }
    }
    else if (categoryName == "特殊视图") {
        if (objectName.contains("经线面")) {
            ui->meridionalPlaneCheckBox->setChecked(visible);
            MeridionalCheckBoxTriggered();
        }
        else if (objectName.contains("等高面")) {
            ui->constHeightCheckBox->setChecked(visible);
            on_ConstHeightCheckBox_toggled(visible);
        }
    }
}

void MainWindow::onObjectSelected(const QString &categoryName, 
                                  const QString &objectName)
{
    qDebug() << "对象被选中:" << categoryName << "/" << objectName;
    
    // 更新属性面板显示该对象的属性
    updatePropertyPanel(categoryName, objectName);
}

void MainWindow::onObjectDoubleClicked(const QString &categoryName, 
                                       const QString &objectName)
{
    qDebug() << "对象被双击:" << categoryName << "/" << objectName;
    
    // 显示属性面板
    if (!propertyPanelDock->isVisible()) {
        propertyPanelDock->show();
    }
    
    // 聚焦属性面板
    propertyPanelDock->raise();
    propertyPanelDock->setFocus();
    
    // 更新属性
    updatePropertyPanel(categoryName, objectName);
}

void MainWindow::onPropertyValueChanged(const QString &propertyName, 
                                       const QVariant &newValue)
{
    qDebug() << "属性值改变:" << propertyName << "=" << newValue;
    
    // 根据属性名称应用更改
    if (propertyName == "透明度") {
        double opacity = newValue.toDouble();
        // TODO: 应用透明度到当前选中的对象
        // qtvtkWindow->SetOpacity(opacity);
    } 
    else if (propertyName == "颜色") {
        QColor color = newValue.value<QColor>();
        // TODO: 应用颜色
        // qtvtkWindow->SetColor(color.redF(), color.greenF(), color.blueF());
    }
    else if (propertyName == "线宽") {
        double lineWidth = newValue.toDouble();
        // TODO: 应用线宽
    }
    else if (propertyName == "点大小") {
        double pointSize = newValue.toDouble();
        // TODO: 应用点大小
    }
    
    // 刷新渲染
    qtvtkWindow->Update();
}

void MainWindow::updatePropertyPanel(const QString &categoryName, 
                                     const QString &objectName)
{
    // 清除现有属性
    propertyPanel->clearProperties();
    propertyPanel->setObjectName(objectName);
    
    // 根据对象类型添加相应的属性
    if (categoryName == "显示对象") {
        // 通用显示属性
        propertyPanel->addBoolProperty("可见", true);
        propertyPanel->addDoubleProperty("透明度", 1.0, 0.0, 1.0, 2);
        
        if (objectName == "网格线" || objectName == "边缘线") {
            propertyPanel->addColorProperty("颜色", QColor(0, 0, 0));
            propertyPanel->addDoubleProperty("线宽", 1.0, 0.1, 10.0, 1);
        }
        else if (objectName == "等值线" || objectName == "阴影面") {
            propertyPanel->addComboProperty("颜色方案", 
                {"Rainbow", "Blue-Red", "Grayscale", "Viridis"}, "Rainbow");
            propertyPanel->addIntProperty("等值线数", 10, 1, 50);
        }
        else if (objectName == "向量场") {
            propertyPanel->addDoubleProperty("缩放因子", 1.0, 0.1, 10.0, 2);
            propertyPanel->addIntProperty("箭头密度", 10, 1, 100);
            propertyPanel->addColorProperty("颜色", QColor(255, 0, 0));
        }
    }
    else if (categoryName == "边界") {
        propertyPanel->addBoolProperty("可见", true);
        propertyPanel->addComboProperty("渲染模式", 
            {"实体", "线框", "点", "实体+线框"}, "实体");
        propertyPanel->addDoubleProperty("透明度", 1.0, 0.0, 1.0, 2);
        propertyPanel->addColorProperty("颜色", QColor(180, 180, 180));
        propertyPanel->addDoubleProperty("线宽", 1.0, 0.1, 5.0, 1);
    }
    else if (categoryName == "特殊视图") {
        propertyPanel->addBoolProperty("可见", true);
        if (objectName.contains("经线面")) {
            propertyPanel->addDoubleProperty("位置", 0.0, -180.0, 180.0, 1);
        }
        else if (objectName.contains("等高面")) {
            propertyPanel->addDoubleProperty("高度", 0.0, -100.0, 100.0, 2);
        }
    }
}

// ==================== 修改现有的文件加载函数 ====================

void MainWindow::on_actionLoadMesh_triggered()
{
    // ... 原有的文件加载代码 ...
    
    // 文件加载成功后，更新对象浏览器
    if (objectBrowser != nullptr) {
        // 清除旧对象（保留分组）
        objectBrowser->clearAll();
        
        // 重新添加分组
        objectBrowser->addCategory("显示对象");
        objectBrowser->addCategory("边界");
        objectBrowser->addCategory("特殊视图");
        
        // 添加基本显示对象
        objectBrowser->addObject("显示对象", "网格线", "Mesh", false);
        objectBrowser->addObject("显示对象", "等值线", "Contour", true);
        objectBrowser->addObject("显示对象", "阴影面", "Shade", true);
        objectBrowser->addObject("显示对象", "边缘线", "Edge", false);
        objectBrowser->addObject("显示对象", "向量场", "Vector", false);
        
        // 添加边界对象（如果有的话）
        if (qtvtkWindow != nullptr) {
            int numBoundaries = qtvtkWindow->GetNumberOfBoundaries();
            for (int i = 0; i < numBoundaries; i++) {
                QString boundaryName = QString::fromStdString(
                    qtvtkWindow->GetBoundaryName(i));
                QString boundaryType = QString::fromStdString(
                    qtvtkWindow->GetBoundaryType(i));
                objectBrowser->addObject("边界", boundaryName, boundaryType, true);
            }
        }
        
        // 展开所有分组
        objectBrowser->expandAll();
    }
}

// ==================== 可选：添加菜单项控制面板显示 ====================

void MainWindow::createViewMenu()
{
    // 在View菜单中添加面板显示/隐藏选项
    QMenu *viewMenu = menuBar()->addMenu(tr("视图(&V)"));
    
    // 添加对象浏览器切换
    viewMenu->addAction(objectBrowserDock->toggleViewAction());
    objectBrowserDock->toggleViewAction()->setText(tr("对象浏览器"));
    objectBrowserDock->toggleViewAction()->setShortcut(Qt::CTRL + Qt::Key_1);
    
    // 添加属性面板切换
    viewMenu->addAction(propertyPanelDock->toggleViewAction());
    propertyPanelDock->toggleViewAction()->setText(tr("属性面板"));
    propertyPanelDock->toggleViewAction()->setShortcut(Qt::CTRL + Qt::Key_2);
    
    viewMenu->addSeparator();
    
    // 添加重置布局选项
    QAction *resetLayoutAction = new QAction(tr("重置布局"), this);
    connect(resetLayoutAction, &QAction::triggered, this, &MainWindow::resetLayout);
    viewMenu->addAction(resetLayoutAction);
}

void MainWindow::resetLayout()
{
    // 重置停靠窗口布局
    objectBrowserDock->setVisible(true);
    propertyPanelDock->setVisible(true);
    
    addDockWidget(Qt::LeftDockWidgetArea, objectBrowserDock);
    addDockWidget(Qt::BottomDockWidgetArea, propertyPanelDock);
    
    resizeDocks({objectBrowserDock}, {250}, Qt::Horizontal);
    resizeDocks({propertyPanelDock}, {180}, Qt::Vertical);
}

// ==================== 使用说明 ====================
/*
集成步骤总结：

1. 将本文件中标注的代码段添加到MainWindow.h和MainWindow.cpp中
2. 在MainWindow构造函数中调用新增的初始化函数
3. 在文件加载函数中更新对象浏览器
4. （可选）添加视图菜单控制面板显示
5. 编译并运行，查看现代化的界面效果

注意事项：
- 需要根据实际的成员变量名称调整代码（如ui->meshCheckBox）
- 某些函数调用需要根据实际的API进行调整
- 建议逐步集成，先测试基本功能，再添加高级特性
*/
