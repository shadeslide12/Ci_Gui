#include "ObjectBrowser.h"
#include <QHeaderView>
#include <QDebug>

ObjectBrowser::ObjectBrowser(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setupConnections();
}

ObjectBrowser::~ObjectBrowser()
{
}

void ObjectBrowser::setupUI()
{
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // 创建标题标签
    QLabel *titleLabel = new QLabel("对象浏览器", this);
    titleLabel->setStyleSheet("QLabel { font-weight: bold; padding: 8px; background-color: #f5f5f5; border-bottom: 1px solid #d0d0d0; }");
    mainLayout->addWidget(titleLabel);
    
    // 创建树形控件
    treeWidget = new QTreeWidget(this);
    treeWidget->setHeaderHidden(true);
    treeWidget->setColumnCount(1);
    treeWidget->setAlternatingRowColors(false);
    treeWidget->setAnimated(true);
    treeWidget->setIndentation(20);
    treeWidget->setExpandsOnDoubleClick(false); // 禁用双击展开，用于属性编辑
    
    mainLayout->addWidget(treeWidget);
    
    setLayout(mainLayout);
}

void ObjectBrowser::setupConnections()
{
    connect(treeWidget, &QTreeWidget::itemChanged, 
            this, &ObjectBrowser::onItemChanged);
    connect(treeWidget, &QTreeWidget::itemClicked, 
            this, &ObjectBrowser::onItemClicked);
    connect(treeWidget, &QTreeWidget::itemDoubleClicked, 
            this, &ObjectBrowser::onItemDoubleClicked);
}

void ObjectBrowser::addCategory(const QString &name, const QIcon &icon)
{
    // 检查分组是否已存在
    if (findCategoryItem(name) != nullptr) {
        return;
    }
    
    QTreeWidgetItem *categoryItem = createCategoryItem(name, icon);
    treeWidget->addTopLevelItem(categoryItem);
    categoryItem->setExpanded(true); // 默认展开
}

void ObjectBrowser::addObject(const QString &categoryName, const QString &objectName, 
                               const QString &objectType, bool visible)
{
    QTreeWidgetItem *categoryItem = findCategoryItem(categoryName);
    if (categoryItem == nullptr) {
        // 如果分组不存在，先创建
        addCategory(categoryName);
        categoryItem = findCategoryItem(categoryName);
    }
    
    QTreeWidgetItem *objectItem = createObjectItem(objectName, objectType, visible);
    categoryItem->addChild(objectItem);
}

void ObjectBrowser::clearAll()
{
    treeWidget->clear();
}

void ObjectBrowser::setObjectVisible(const QString &categoryName, const QString &objectName, bool visible)
{
    QTreeWidgetItem *categoryItem = findCategoryItem(categoryName);
    if (categoryItem == nullptr) {
        return;
    }
    
    for (int i = 0; i < categoryItem->childCount(); ++i) {
        QTreeWidgetItem *item = categoryItem->child(i);
        if (item->text(0) == objectName) {
            item->setCheckState(0, visible ? Qt::Checked : Qt::Unchecked);
            break;
        }
    }
}

QStringList ObjectBrowser::getSelectedObjects() const
{
    QStringList result;
    
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *categoryItem = treeWidget->topLevelItem(i);
        for (int j = 0; j < categoryItem->childCount(); ++j) {
            QTreeWidgetItem *objectItem = categoryItem->child(j);
            if (objectItem->checkState(0) == Qt::Checked) {
                result << categoryItem->text(0) + "/" + objectItem->text(0);
            }
        }
    }
    
    return result;
}

void ObjectBrowser::expandAll()
{
    treeWidget->expandAll();
}

void ObjectBrowser::collapseAll()
{
    treeWidget->collapseAll();
}

QTreeWidgetItem* ObjectBrowser::findCategoryItem(const QString &name)
{
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = treeWidget->topLevelItem(i);
        if (item->text(0) == name && item->type() == CategoryItem) {
            return item;
        }
    }
    return nullptr;
}

QTreeWidgetItem* ObjectBrowser::createCategoryItem(const QString &name, const QIcon &icon)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(CategoryItem);
    item->setText(0, name);
    if (!icon.isNull()) {
        item->setIcon(0, icon);
    }
    
    // 设置分组样式
    QFont font = item->font(0);
    font.setBold(true);
    item->setFont(0, font);
    item->setForeground(0, QBrush(QColor(0, 120, 212))); // 蓝色
    
    // 分组不可编辑和选择
    item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    
    return item;
}

QTreeWidgetItem* ObjectBrowser::createObjectItem(const QString &name, const QString &type, bool visible)
{
    QTreeWidgetItem *item = new QTreeWidgetItem(ObjectItem);
    item->setText(0, name + " (" + type + ")");
    item->setCheckState(0, visible ? Qt::Checked : Qt::Unchecked);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    
    // 根据类型设置不同的图标（这里用文字代替，实际可以加载图标文件）
    if (type == "Mesh") {
        item->setIcon(0, QIcon()); // 网格图标
    } else if (type == "Contour") {
        item->setIcon(0, QIcon()); // 等值线图标
    } else if (type == "Vector") {
        item->setIcon(0, QIcon()); // 向量场图标
    } else if (type == "Boundary") {
        item->setIcon(0, QIcon()); // 边界图标
    }
    
    // 存储对象名称和类型到数据中
    item->setData(0, Qt::UserRole, name);
    item->setData(0, Qt::UserRole + 1, type);
    
    return item;
}

void ObjectBrowser::onItemChanged(QTreeWidgetItem *item, int column)
{
    if (item->type() != ObjectItem) {
        return;
    }
    
    // 获取父分组名称
    QTreeWidgetItem *parent = item->parent();
    if (parent == nullptr) {
        return;
    }
    
    QString categoryName = parent->text(0);
    QString objectName = item->data(0, Qt::UserRole).toString();
    bool visible = (item->checkState(0) == Qt::Checked);
    
    emit objectVisibilityChanged(categoryName, objectName, visible);
}

void ObjectBrowser::onItemClicked(QTreeWidgetItem *item, int column)
{
    if (item->type() != ObjectItem) {
        return;
    }
    
    QTreeWidgetItem *parent = item->parent();
    if (parent == nullptr) {
        return;
    }
    
    QString categoryName = parent->text(0);
    QString objectName = item->data(0, Qt::UserRole).toString();
    
    emit objectSelected(categoryName, objectName);
}

void ObjectBrowser::onItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if (item->type() != ObjectItem) {
        return;
    }
    
    QTreeWidgetItem *parent = item->parent();
    if (parent == nullptr) {
        return;
    }
    
    QString categoryName = parent->text(0);
    QString objectName = item->data(0, Qt::UserRole).toString();
    
    emit objectDoubleClicked(categoryName, objectName);
}
