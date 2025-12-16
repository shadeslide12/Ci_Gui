#pragma once

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <vector>
#include <string>

/**
 * @brief 现代化的对象浏览器组件
 * 
 * 使用树形结构显示所有可视化对象，支持分组、展开/折叠、显示/隐藏控制
 */
class ObjectBrowser : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectBrowser(QWidget *parent = nullptr);
    ~ObjectBrowser();

    // 添加对象分组
    void addCategory(const QString &name, const QIcon &icon = QIcon());
    
    // 在指定分组下添加对象
    void addObject(const QString &categoryName, const QString &objectName, 
                   const QString &objectType, bool visible = true);
    
    // 清除所有对象
    void clearAll();
    
    // 设置对象可见性
    void setObjectVisible(const QString &categoryName, const QString &objectName, bool visible);
    
    // 获取选中的对象
    QStringList getSelectedObjects() const;
    
    // 展开/折叠所有分组
    void expandAll();
    void collapseAll();

signals:
    // 当对象可见性改变时发出
    void objectVisibilityChanged(const QString &categoryName, const QString &objectName, bool visible);
    
    // 当对象被选中时发出
    void objectSelected(const QString &categoryName, const QString &objectName);
    
    // 当对象被双击时发出（用于编辑属性）
    void objectDoubleClicked(const QString &categoryName, const QString &objectName);

private slots:
    void onItemChanged(QTreeWidgetItem *item, int column);
    void onItemClicked(QTreeWidgetItem *item, int column);
    void onItemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    QTreeWidget *treeWidget;
    QVBoxLayout *mainLayout;
    
    // 自定义项类型
    enum ItemType {
        CategoryItem = QTreeWidgetItem::UserType,
        ObjectItem = QTreeWidgetItem::UserType + 1
    };
    
    // 查找分组项
    QTreeWidgetItem* findCategoryItem(const QString &name);
    
    // 创建样式化的分组项
    QTreeWidgetItem* createCategoryItem(const QString &name, const QIcon &icon);
    
    // 创建样式化的对象项
    QTreeWidgetItem* createObjectItem(const QString &name, const QString &type, bool visible);
    
    // 初始化UI
    void setupUI();
    void setupConnections();
};
