#pragma once
#ifndef UTILITIESGUIPRE_H
#define UTILITIESGUIPRE_H
#include<map>
#include<QString>
#include<vector>
#include<QLineEdit>
#include<QDoubleValidator>
#include<QIntValidator>
#include<QObject>
#include<QEvent>

extern std::map<std::string, int> GUI_BC_Normal_Map;
extern std::map<std::string, int> GUI_BC_Turbomachinery_Map;
extern std::map<int, std::string> GUI_Reverse_BC_Normal_Map;
extern std::map<int, std::string> GUI_Reverse_BC_Turbomachinery_Map;
extern std::map<std::string, std::vector<std::string>> flow_vars;
extern std::map<std::string, std::string> GUI_rans_model_dic;
extern std::map<std::string, std::string> GUI_rans_model_dic_R;
extern std::map<std::string, std::string> GUI_turbulence_model_dic;
extern std::map<std::string, std::string> GUI_turbulence_model_dic_R;

extern std::map<std::string, int> GUI_monitor_dict;
extern std::map<int, std::string> GUI_monitor_dict_R;
extern std::map<std::string, int> GUI_monitor_average;
extern std::map<int, std::string> GUI_monitor_average_R;

extern std::vector<QString> FilmCoolngVars;

void SetupDoubleLineEdit(QObject *receiver, QLineEdit *edt, double value);

void SetupIntLineEdit(QObject *receiver, QLineEdit *edt, int value);


class EditableLineEdit : public QLineEdit {
Q_OBJECT

public:
    EditableLineEdit(QWidget *parent = nullptr) : QLineEdit(parent) {
      setStyleSheet("QLineEdit { border: none; background: transparent; }");
      setFrame(false);
      setReadOnly(true);  // 初始化时设置为只读

      // 安装事件过滤器以处理双击事件
      installEventFilter(this);
    }

protected:
    bool eventFilter(QObject *obj, QEvent *event) override {
      if (obj == this && event->type() == QEvent::MouseButtonDblClick) {
        setReadOnly(false);  // 双击时设置为可编辑
        setStyleSheet("QLineEdit { background: white; }");  // 在编辑时显示背景
        return true;  // 表明事件已处理
      }
      return QLineEdit::eventFilter(obj, event);  // 对其他事件使用默认处理
    }

    void focusOutEvent(QFocusEvent *event) override {
      QLineEdit::focusOutEvent(event);
      setReadOnly(true);  // 失去焦点后设置为只读
      setStyleSheet("QLineEdit { border: none; background: transparent; }");  // 恢复“标签”外观
    }
};

#endif // BCEXTRA_H
