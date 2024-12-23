#pragma once
#ifndef BOUNDARYMERGER_H
#define BOUNDARYMERGER_H

#include <QDialog>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QComboBox>
#include <QTreeWidgetItem>
#include <QListWidget>
#include <QListWidgetItem>
#include "ToolsWriteCGNS.h"
#include "PreProcessSettings.h"
#include "PreMainModules.h"
#include "InputParser.h"
#include "MergerCore.h"

namespace Ui {
class BoundaryMerger;
}


class BoundaryMerger : public QDialog
{
  Q_OBJECT

public:
  explicit BoundaryMerger(PreProcessSettings *cfg_in, MergerCore *merger_in, QWidget *parent = nullptr);
  ~BoundaryMerger();

  PreProcessSettings *cfg;


private slots:
//      void group_name_rule();

    void on_nextButton_clicked();

//    void showContextMenu(const QPoint &pos);

//    void deleteGroup();

  void ShowZoneList();


  void onGroupNameEdit(EditableLineEdit *lineEdit, QTreeWidgetItem *item, const std::string &oldName);


  void on_merge_subgroup_clicked();

  void onBCComboChanged(QComboBox *cmb, QLineEdit *lineEdit);

  void onRuleDelete(QComboBox *cmb, QLineEdit *lineEdit);

  void onRuleEdit(QLineEdit *cmb, QLineEdit *lineEdit);

  void onTarNameEdit(QLineEdit *lineEdit, std::string oldName);

//  void on_add_rule_clicked();

//  void updateButtonState();

//  void updatePushLeftButtonState();

//  bool SubgroupTreeCheckState();

//  bool UngroupListCheckState();

//  void on_push_right_button_clicked();

//  void on_push_left_button_clicked();

//  void on_new_group_button_clicked();

  void on_add_rule_clicked();

  private:
  Ui::BoundaryMerger *ui;

  void ViewRule();
  void ViewSubgroups();

  int newGroupCount = 1;
  QString selectedGroup;  // 左侧选中的组
  QString selectedValue;  // 右侧选中的值

  void addNewGroup();
  void movetoleft();
  void movetoright();
  void onSelectionChanged();
  void deleteGroup();
  void AddOneGroupItem(QTreeWidgetItem *bc_item, std::string group_label, std::string bc_string);

  void UpdateGroupAndSubgroup();

  int current_zone=0;
  int previous_zone=9999;

  int add_rule_count = 0;

  MergerCore *merger;

};

#endif // BOUNDARYMERGER_H
