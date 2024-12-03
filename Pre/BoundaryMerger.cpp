#include "BoundaryMerger.h"
#include "ui_BoundaryMerger.h"

BoundaryMerger::BoundaryMerger(PreProcessSettings *cfg_in, MergerCore *merger_in, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BoundaryMerger)
{
  cfg=cfg_in;
  merger=merger_in;
  ui->setupUi(this);
  ui->to_right_button->setEnabled(false);
//  ui->to_left_button->setEnabled(false);
  ViewRule();
  merger->GenStep1File(true);
  merger->GenerateStep2();
  merger->LoadStep2();
  ShowZoneList();

  connect(ui->zone_list,  &QListWidget::itemClicked, this, &BoundaryMerger::ViewSubgroups);
  connect(ui->to_left_button, &QPushButton::clicked, this, &BoundaryMerger::movetoleft);
  connect(ui->to_right_button, &QPushButton::clicked, this, &BoundaryMerger::movetoright);
  connect(ui->grouped, &QTreeWidget::itemSelectionChanged, this, &BoundaryMerger::onSelectionChanged);
  connect(ui->new_group_button, &QPushButton::clicked, this, &BoundaryMerger::addNewGroup);
  connect(ui->grouped, &QTreeWidget::currentItemChanged, [this](QTreeWidgetItem *current, QTreeWidgetItem *previous) {
      if (current) {
          selectedGroup = current->data(0, Qt::UserRole).toString();
      }
  });

  // 当右树的选中项改变时，更新选中的值
  connect(ui->ungrouped, &QTreeWidget::currentItemChanged, [this](QTreeWidgetItem *current, QTreeWidgetItem *previous) {
      if (current) {
      selectedValue = current->text(0);
  }
  });
 connect(ui->delete_button, &QPushButton::clicked, this, &BoundaryMerger::deleteGroup);
}

BoundaryMerger::~BoundaryMerger()
{
    delete ui;
}

void BoundaryMerger::ViewRule()
{
  ui->rule_tree->clear();
  for (const auto& pair : merger->rule_types) {
    if(pair.first == "ungrouped") continue;
    QTreeWidgetItem* treeItem= new QTreeWidgetItem();
    ui->rule_tree->addTopLevelItem(treeItem);


    QLineEdit *tarNameItem = new QLineEdit(this); // 使用 QLineEdit 代替 QLabel
    tarNameItem->setText(QString::fromStdString(pair.first));
    tarNameItem->setReadOnly(false);  // 初始为只读模式


    QComboBox *typeItem = new QComboBox(this);
    QLineEdit *ruleItem = new QLineEdit(this);
    QPushButton *deleteItem = new QPushButton(this);

    for (const auto &pair: GUI_BC_Turbomachinery_Map) {
      typeItem->addItem(QString::fromStdString(pair.first));
    }
    std::string currentType=GUI_Reverse_BC_Turbomachinery_Map.at(pair.second);
    typeItem->setCurrentText(QString::fromStdString(currentType));

    //rule_subgroups
    auto rules = merger->rule_subgroups.find(pair.first);
    QString final_string;
    QStringList multi_ruleList;
    if (rules != merger->rule_subgroups.end()) {
      for (const auto& ruleSet : rules->second) {
        QStringList ruleList;
        QString one_rule;
        for (const auto& rule : ruleSet) {
            ruleList << QString::fromStdString(rule);
        }
        one_rule=ruleList.join(", ");
        multi_ruleList << one_rule;
      }
      ruleItem->setText(multi_ruleList.join(";"));
    }

    deleteItem->setText("×");

    ui->rule_tree->setItemWidget(treeItem,0,tarNameItem);
    ui->rule_tree->setItemWidget(treeItem,1,typeItem);
    ui->rule_tree->setItemWidget(treeItem,2,ruleItem);
    ui->rule_tree->setItemWidget(treeItem,3,deleteItem);

   connect(deleteItem, &QPushButton::clicked,
           [this, typeItem, tarNameItem] {
               this->onRuleDelete(typeItem, tarNameItem);
           });


  }
  double totalWidth = ui->rule_tree->width();
  ui->rule_tree->setColumnWidth(3, totalWidth * 0.05);  // 第三列宽度为总宽度的20%


}

void BoundaryMerger::on_nextButton_clicked()
{
    UpdateGroupAndSubgroup();
//    merger->GenerateStep2();
    merger->UpdateSubgroupsStep2();
    merger->LoadStep2();
  PreMainModule SolverPre;
  SolverPre.LoadYAMLConfigs(2);
  SolverPre.ConvertStep2_3_yaml();

  this->close();
}

void BoundaryMerger::ShowZoneList() {

  ui->zone_list->clear();
  for (int i=0; i< cfg->mesh_files.size(); i++)
  {
    ui->zone_list->addItem(QString::fromStdString(cfg->mesh_files[i]));
  }
  if (ui->zone_list->count()>0)
  {
    ui->zone_list->setCurrentRow(0);
    ViewSubgroups();
  }
}

void BoundaryMerger::ViewSubgroups()
{
  if (previous_zone!=9999)
    UpdateGroupAndSubgroup();
  previous_zone = current_zone;
  int zone_id = ui->zone_list->currentRow();
  ui->grouped->setEditTriggers(QTreeWidget::DoubleClicked | QTreeWidget::SelectedClicked);
  current_zone = zone_id;
  ui->grouped->clear();
  ui->ungrouped->clear();
  ui->grouped->setColumnCount(2);
  ui->ungrouped->setColumnCount(1);

  for (const auto &pair : merger->zone_subgroups[zone_id]) {
    if (pair.first == "ungrouped") {
      for (int i=0; i< pair.second.size(); i++)
      {
        QTreeWidgetItem * item = new QTreeWidgetItem(ui->ungrouped, QStringList(QString::fromStdString(pair.second[i])));
        ui->ungrouped->addTopLevelItem(item);
      }
    }
    else {
      QTreeWidgetItem *bc_item = new QTreeWidgetItem(ui->grouped);
      bc_item->setFlags(bc_item->flags() | Qt::ItemIsEditable);
      ui->grouped->addTopLevelItem(bc_item);
      std::string currentType = GUI_Reverse_BC_Turbomachinery_Map.at(merger->zone_types[zone_id].at(pair.first));
      AddOneGroupItem(bc_item, pair.first, currentType);
//
      for(const auto &str: pair.second){
        // 在每个组下创建子项目并添加
        QTreeWidgetItem * item = new QTreeWidgetItem(bc_item, QStringList(QString::fromStdString(str)));
        bc_item->addChild(item);
      }
    }
  }
  ui->grouped->expandAll();

  ui->grouped->setSelectionMode(QAbstractItemView::ExtendedSelection);
  ui->ungrouped->setSelectionMode(QAbstractItemView::ExtendedSelection);

}

void BoundaryMerger::on_merge_subgroup_clicked() {
 // 清空 merger 的 rule_types 和 rule_subgroups
 merger->rule_types.clear();
 merger->rule_subgroups.clear();

 // 提取并保存 rule_tree 的内容
 for (int i = 0; i < ui->rule_tree->topLevelItemCount(); ++i) {
  QTreeWidgetItem* treeItem = ui->rule_tree->topLevelItem(i);

  // 获取每一列的 widget
  QLineEdit* tarNameItem = qobject_cast<QLineEdit*>(ui->rule_tree->itemWidget(treeItem, 0));
  QComboBox* typeItem = qobject_cast<QComboBox*>(ui->rule_tree->itemWidget(treeItem, 1));
  QLineEdit* ruleItem = qobject_cast<QLineEdit*>(ui->rule_tree->itemWidget(treeItem, 2));

  if (tarNameItem && typeItem && ruleItem) {
   // 读取 QLineEdit 和 QComboBox 的值
   std::string targetName = tarNameItem->text().toStdString();
   std::string targetType = typeItem->currentText().toStdString();
   merger->rule_types[targetName] = GUI_BC_Turbomachinery_Map.at(targetType);

   // 解析 ruleItem 的规则，去除每个规则项前后的空格
   QStringList ruleSets = ruleItem->text().split(";");
   std::vector<std::vector<std::string>> rules;
   for (QString& ruleSetString : ruleSets) {
    ruleSetString = ruleSetString.trimmed(); // 去除每个 ruleSetString 前后的空格
    QStringList ruleList = ruleSetString.split(",");
    std::vector<std::string> ruleVec;
    for (QString& rule : ruleList) {
     rule = rule.trimmed(); // 去除每个 rule 前后的空格
     ruleVec.push_back(rule.toStdString());
    }
    rules.push_back(ruleVec);
   }
   merger->rule_subgroups[targetName] = std::move(rules);
  }
 }

 // 输出 rule_types 内容以供检查
 for (const auto& pair : merger->rule_types) {
  std::cout << "Group: " << pair.first << ", Type: " << pair.second << std::endl;
 }

 // 然后进行后续的操作
 previous_zone = 9999;
 ui->grouped->clear();
 ui->ungrouped->clear();
 merger->GenStep1File(true);
 merger->GenerateStep2();
 merger->LoadStep2();
 ShowZoneList();
}
void BoundaryMerger::onBCComboChanged(QComboBox *cmb, QLineEdit *lineEdit)
{
  merger->rule_types.at(lineEdit->text().toStdString()) = GUI_BC_Turbomachinery_Map.at(cmb->currentText().toStdString());
}

void BoundaryMerger::onRuleDelete(QComboBox *cmb, QLineEdit *lineEdit)
{
  auto it = merger->rule_types.find(lineEdit->text().toStdString());
  auto it2 = merger->rule_subgroups.find(lineEdit->text().toStdString());
  if (it != merger->rule_types.end()) {
    merger->rule_types.erase(it); // 使用迭代器删除
  }
  if (it2 != merger->rule_subgroups.end()) {
    merger->rule_subgroups.erase(it2); // 使用迭代器删除
  }
  ViewRule();
}

void BoundaryMerger::onRuleEdit(QLineEdit *edt, QLineEdit *lineEdit)
{
  QString input = edt->text();
  QStringList groups = input.split(";");

  std::cout << edt->text().toStdString() << std::endl;
  // 准备std::vector容器
  std::vector<std::vector<std::string>> result;

  // 遍历每个分组
      foreach (const QString &group, groups) {
      // 按逗号分割
      QStringList items = group.split(",");

      // 准备内部vector
      std::vector<std::string> subResult;

      // 转换QString到std::string并存储
          foreach (const QString &item, items) {
          subResult.push_back(item.toStdString());
          std::cout << item.toStdString() << std::endl;
        }

      // 将此组的vector添加到结果vector
      result.push_back(subResult);
    }
  merger->rule_subgroups[lineEdit->text().toStdString()] = result;
  // ViewRule();
}

void BoundaryMerger::onTarNameEdit(QLineEdit *lineEdit, std::string oldName)
{
  std::string newName = lineEdit->text().toStdString();
  std::cout << oldName << "yes"<<std::endl;
  // 找到并更新对应的键值对（键转换）
  auto iter = merger->rule_types.find(oldName);
  if (iter != merger->rule_types.end()) {
    auto value = std::move(iter->second);   // 存储旧键的值
    merger->rule_types.erase(iter);         // 删除旧键值对
    merger->rule_types.emplace(newName, std::move(value)); // 使用新键插入新键值对
  }
  // 输出 rule_types 的内容
  std::cout << "Current rule_types content:" << std::endl;
  for (const auto &pair : merger->rule_types) {
    std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
  }


  // 更新 placeholderText
  lineEdit->setPlaceholderText(QString::fromStdString(newName));
}



void BoundaryMerger::addNewGroup() {
    newGroupCount++;  // 创建新组前, newGroupCount+1

    QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->grouped);
    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);

    AddOneGroupItem(newItem,
                    QString("new_group_%1").arg(newGroupCount).toStdString(),
                    "Invisid Wall");

//    // 将新的顶级项设置为当前选中项目
    ui->grouped->setCurrentItem(newItem);
    onSelectionChanged();
}

void BoundaryMerger::movetoleft() {
    // 获取所有选中的 values
    QList<QTreeWidgetItem*> selectedValues = ui->ungrouped->selectedItems();

    // 没有选择 value 或 group，返回
    if (selectedValues.isEmpty() || selectedGroup.isEmpty()) {
        return;
    }

    // 查找选择的 group
    QTreeWidgetItem *groupItem = nullptr;
    for (int i = 0; i < ui->grouped->topLevelItemCount(); ++i) {
        QTreeWidgetItem* item = ui->grouped->topLevelItem(i);
        // 使用 data(0, Qt::UserRole) 获取组名进行比较
        if (item->data(0, Qt::UserRole).toString() == selectedGroup) {
            groupItem = item;
            break;
        }
    }

// 如果找到了 group
    if (groupItem) {
        // 遍历所有选中的 value
        for (QTreeWidgetItem *valueItem : selectedValues) {
            // 从 ungrouped 中移除 value
            int valueIndex = ui->ungrouped->indexOfTopLevelItem(valueItem);
            ui->ungrouped->takeTopLevelItem(valueIndex);

            // 将 value 添加到 group 下面
            groupItem->addChild(valueItem);
        }
        // 添加子项后，设置 group 展开
        groupItem->setExpanded(true);
    }
}

void BoundaryMerger::movetoright() {
    // 获取左边的tree中所有选中的项
    QList<QTreeWidgetItem*> selectedItems = ui->grouped->selectedItems();

    // 遍历所有选中的项
    for (auto & item : selectedItems) {
        // 找到item在其父节点中的位置
        int index = item->parent()->indexOfChild(item);
        // 将此项从左边的tree中移除
        QTreeWidgetItem* removedItem = item->parent()->takeChild(index);
        // 将此项添加进右边的tree
        ui->ungrouped->addTopLevelItem(removedItem);
    }
}

void BoundaryMerger::onSelectionChanged() {
    // 获取所有在grouped tree中选中的项
    QList<QTreeWidgetItem*> selectedItems = ui->grouped->selectedItems();
    bool disableButton = false;

    // 遍历所有选中的项
    for (auto & item : selectedItems) {
        // 检查是否有组被选中（深度为0）
        if (item->parent() == NULL) {
            disableButton = true;
            break;
        }
    }

    // 如果有组（而非子项）被选中，禁用按钮，否则启用按钮
    ui->to_right_button->setDisabled(disableButton);
}

void BoundaryMerger::deleteGroup() {
    // 获取所有选中的 group
    QList<QTreeWidgetItem*> selectedGroups = ui->grouped->selectedItems();

    // 遍历所有选中的 group
    for (QTreeWidgetItem *selectedItem : selectedGroups) {

        // 获取选中 group 的父级项。如果是顶级项，则 parent 为 nullptr
        QTreeWidgetItem *parentItem = selectedItem->parent();

        // 如果是子项（即 value），则跳过
        if (parentItem != nullptr) {
            continue;
        }

        // 获取 group 的所有子项 (value)
        int childCount = selectedItem->childCount();

        // 如果 group 中有 value，将它们移动到 ungrouped
        if (childCount > 0) {
            for (int i = 0; i < childCount; ++i) {
                QTreeWidgetItem *childItem = selectedItem->takeChild(0); // 取出子项
                ui->ungrouped->addTopLevelItem(childItem); // 添加到 ungrouped
            }
        }

        // 从 grouped 中删除选中的 group
        int index = ui->grouped->indexOfTopLevelItem(selectedItem);
        delete ui->grouped->takeTopLevelItem(index);
    }
}

void BoundaryMerger::AddOneGroupItem(QTreeWidgetItem *bc_item, std::string group_label, std::string bc_string){
  bc_item->setFlags(bc_item->flags() | Qt::ItemIsEditable);
  ui->grouped->addTopLevelItem(bc_item);

  EditableLineEdit *bc_label = new EditableLineEdit();
  bc_label->setText(QString::fromStdString(group_label));

  // 设置 QTreeWidgetItem 的文本

  bc_item->setData(0, Qt::UserRole, QString::fromStdString(group_label));

 // 连接编辑完成信号到槽函数
 connect(bc_label, &QLineEdit::editingFinished, this, [this, bc_label, bc_item, group_label]() {
     this->onGroupNameEdit(bc_label, bc_item, group_label);
 });


  QComboBox *bc_type_combo = new QComboBox(this);
  for (const auto &pair: GUI_BC_Turbomachinery_Map) {
    bc_type_combo->addItem(QString::fromStdString(pair.first));
  }
  bc_type_combo->setCurrentText(QString::fromStdString(bc_string));
  ui->grouped->setItemWidget(bc_item, 0, bc_label);
  ui->grouped->setItemWidget(bc_item, 1, bc_type_combo);




};


void BoundaryMerger::onGroupNameEdit(EditableLineEdit *lineEdit, QTreeWidgetItem *item, const std::string &oldName) {
 std::string newName = lineEdit->text().toStdString();

 // 如果名称改变了，则更新存储结构
 if (newName != oldName) {
  // 更新 item 的 data
  item->setData(0, Qt::UserRole, QString::fromStdString(newName));

  // 更新 merger 数据结构
  auto &currentSubgroup = merger->zone_subgroups[current_zone];
  if (currentSubgroup.find(oldName) != currentSubgroup.end()) {
   std::vector<std::string> values = std::move(currentSubgroup[oldName]);
   currentSubgroup.erase(oldName);
   currentSubgroup[newName] = std::move(values);
  }

  if (merger->zone_types[current_zone].count(oldName) > 0) {
   int value = merger->zone_types[current_zone][oldName];
   merger->zone_types[current_zone].erase(oldName);
   merger->zone_types[current_zone][newName] = value;
  }

  // 更新 selectedGroup
  selectedGroup = QString::fromStdString(newName);

  // 保持当前选中状态
  ui->grouped->setCurrentItem(item);
 }
}


void BoundaryMerger::UpdateGroupAndSubgroup()
{

  // 检查是否有空的group存在，弹窗提醒是否继续，若是则往下执行，执行的时候跳过空的组，若否则返回
    bool emptyGroupFlag = false;
    for (int i = 0; i < ui->grouped->topLevelItemCount(); ++i) {
        QTreeWidgetItem* groupItem = ui->grouped->topLevelItem(i);
        if (groupItem->childCount() == 0) {
            emptyGroupFlag = true;
            break;
        }
    }

    if (emptyGroupFlag) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Empty group", "Empty group, continue?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }

  // 检查ungroup下是否有member，弹窗提醒是否继续，若是则往下执行，执行的时候跳过空的组，若否则返回

    bool ungroupFlag = ui->ungrouped->topLevelItemCount() > 0;
    if (ungroupFlag) {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Ungrouped", "Ungrouped member, continue?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }

    //  1. 获取当前选中的 zone
//    current_zone = ui->zone_list->currentRow();


  std::map<std::string,std::vector<std::string>> tree_subgroup;
  std::map<std::string,int> tree_type;
  //grouped组按照原来的数据结构写回，并赋予数据结构
  for (int i = 0; i < ui->grouped->topLevelItemCount(); ++i) {
    QTreeWidgetItem* groupItem = ui->grouped->topLevelItem(i);

    // 跳过空组
    if (groupItem->childCount() == 0 && emptyGroupFlag) {
        continue;
    }

    std::string groupName = groupItem->data(0, Qt::UserRole).toString().toStdString();

    std::vector<std::string> subgroups;
    for (int j = 0; j < groupItem->childCount(); ++j) {
        subgroups.push_back(groupItem->child(j)->text(0).toStdString());
//        std::cout<<groupItem->child(j)->text(0).toStdString()<<" ";
    }
//    std::cout<<std::endl;
    tree_subgroup.insert({groupName, subgroups});

    QComboBox* comboBox = qobject_cast<QComboBox*>(ui->grouped->itemWidget(groupItem, 1));
    std::string typeName = comboBox->currentText().toStdString();
    int type = GUI_BC_Turbomachinery_Map.at(typeName);

    //  3.2 更新 rule_types 和 rule_subgroups
    tree_type[groupName] = type;
  }

  if (ungroupFlag) {
      std::vector<std::string> ungroupedMembers;
      for (int i = 0; i < ui->ungrouped->topLevelItemCount(); ++i) {
          ungroupedMembers.push_back(ui->ungrouped->topLevelItem(i)->text(0).toStdString());
      }
      tree_subgroup.insert({"ungrouped", ungroupedMembers});
      tree_type.insert({"ungrouped", 2});
  }

  // 清理 merger中对应zone存组和边界条件类型的数据
  merger->zone_subgroups[current_zone].clear();
  merger->zone_types[current_zone].clear();

  merger->zone_subgroups[current_zone] = tree_subgroup;
  merger->zone_types[current_zone] = tree_type;

}
void BoundaryMerger::on_add_rule_clicked()
{
  add_rule_count+=1;
  std::string new_key = "NewRule-"+std::to_string(add_rule_count);
  std::vector<std::vector<std::string>> new_value={{"EDIT NEW RULES"}};
  merger->rule_subgroups.insert(std::pair
          <std::string, std::vector<std::vector<std::string>>>(new_key,new_value));
  merger->rule_types.insert(std::pair<std::string, int>(new_key,2));
  ViewRule();
}

