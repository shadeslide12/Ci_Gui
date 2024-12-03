#pragma once

#include <vector>
#include <string>
#include <QStandardItem>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QInputDialog>
#include <QLineEdit>
#include <QLabel>

class PerformanceCurve {
public:
  PerformanceCurve()=default;
  ~PerformanceCurve()=default;

  void UpdateBackPressure(double new_p);

  void AppendNewPoint();

  void DrawPerformanceCurve();

  int n_points=0;
  std::vector<double> pressure_list;
  std::vector<std::string> case_list;
  double initial_p = 0.0;
  double target_p = 0.0;

};

class SaveFlowData : public QObject {
Q_OBJECT

public:
    SaveFlowData(QObject *parent) : QObject(parent), process(nullptr) {}
    void openFolderAndCopyFiles(const QString &filename);

private slots:
    void handleProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    QProcess *process;
};



class LoadFlowData : public QDialog {
Q_OBJECT

public:
    explicit LoadFlowData(QWidget *parent = nullptr,
                          const QString &flowFileName = tr("./AEAC.flow.hdf")) : QDialog(parent) {
      setWindowTitle(tr("Load Flow File"));

      setMinimumSize(400, 50);

      QVBoxLayout *mainLayout = new QVBoxLayout(this);

      // Common label width
      int labelWidth = 100;

      // Current flow file
      addFileParameter(mainLayout, labelWidth, tr("Current flow file:"), flowFileName);

      // OK button and Modify button in the same row
      QHBoxLayout *buttonLayout = new QHBoxLayout();

      modifyButton = new QPushButton(tr("Modify"), this);
      buttonLayout->addWidget(modifyButton);
      connect(modifyButton, &QPushButton::clicked, this, [this]() {
          QString fileName = QFileDialog::getOpenFileName(this, tr("Select Flow File"), "", tr("All Files (*)"));
          if (!fileName.isEmpty()) {
            parameterEdits[0]->setText(fileName);
          }
      });

      okButton = new QPushButton(tr("OK"), this);
      buttonLayout->addWidget(okButton);
      connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

      mainLayout->addLayout(buttonLayout);
    }

    QString getFlowFileName() const {
      return parameterEdits[0]->text();
    }

    QString getRelativeFlowFileName() const {
      QString absolutePath = parameterEdits[0]->text();
      QDir currentDir(QDir::currentPath());
      return currentDir.relativeFilePath(absolutePath);
    }

private:
    QList<QLineEdit*> parameterEdits;
    QPushButton *okButton;
    QPushButton *modifyButton;

    void addFileParameter(QVBoxLayout *mainLayout, int labelWidth, const QString &labelText, const QString &defaultValue);
};
