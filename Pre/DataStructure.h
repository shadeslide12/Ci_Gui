#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include <QVector>
#include <QMap>
#include <QString>
#include <QStringList>

// Type 2 专用数据结构（径向剖面，X轴为半径）
struct MonitorType2Data {
    int radialPoints;                       // N: 径向点数
    int numBlocks;                          // 实际块数 (5-7+)
    QString identifier;                     // 文件标识
    
    // 固定顺序的变量（按需填充）
    QVector<double> r;                      // Block 1: 半径 (必有)
    QVector<double> rho;                    // Block 2: 密度 (必有)
    QVector<double> u;                      // Block 3: x方向速度 (必有)
    QVector<double> v;                      // Block 4: y方向速度 (必有)
    QVector<double> w;                      // Block 5: z方向速度 (必有)
    QVector<double> p;                      // Block 6: 静压 (可选)
    QVector<QVector<double>> turbVars;      // Block 7+: 湍流变量 (可选)
    
    void clear() {
        radialPoints = 0;
        numBlocks = 0;
        r.clear(); rho.clear(); u.clear(); v.clear(); w.clear(); p.clear();
        turbVars.clear();
    }
    
    // 根据实际块数返回可用变量名（不含 r，r 作为 X 轴）
    QStringList getAvailableVariables() const {
        QStringList vars = {"rho", "u", "v", "w"};
        if (numBlocks >= 6) vars << "p";
        for (int i = 0; i < turbVars.size(); ++i) {
            vars << QString("turb%1").arg(i + 1);
        }
        return vars;
    }
    
    // 获取带标识的变量名
    QString getDisplayName(const QString& varName) const {
        if (identifier.isEmpty()) {
            return varName;
        }
        return varName + "(" + identifier + ")";
    }
    
    // 获取所有带标识的变量名列表
    QStringList getDisplayNames() const {
        QStringList names;
        for (const QString& var : getAvailableVariables()) {
            names << getDisplayName(var);
        }
        return names;
    }
    
    // 根据变量名获取数据
    const QVector<double>* getVariableData(const QString& varName) const {
        if (varName == "rho") return &rho;
        if (varName == "u") return &u;
        if (varName == "v") return &v;
        if (varName == "w") return &w;
        if (varName == "p") return &p;
        if (varName.startsWith("turb")) {
            int idx = varName.mid(4).toInt() - 1;
            if (idx >= 0 && idx < turbVars.size()) {
                return &turbVars[idx];
            }
        }
        return nullptr;
    }
};

// 通用的 Monitor 文件数据结构 (支持 Type 1/3/4/5)
struct MonitorFileData {
    int monitorType;                        // Monitor 类型 (1, 3, 4, 5)
    int headerLines;                        // 头部行数 (Type 1/3/5: 2, Type 4: 7)
    QStringList variableNames;              // 变量名列表 (从文件头读取，不含 Iter)
    QMap<QString, QVector<double>> data;    // 变量名 -> 数据向量
    
    MonitorFileData() : monitorType(1), headerLines(2) {}
    
    void clear() {
        variableNames.clear();
        data.clear();
    }
};

// 保留原有结构用于 perf（固定的性能曲线）
struct Mon_Variable_Peform{
    QVector<double> pRatio;
    QVector<double> tRatio;
    QVector<double> efficiency;
    QVector<double> turning;
    QVector<double> qInlet;
    QVector<double> qOutlet;
};

struct MonitorVariableTable{
    // 固定的 perf 数据（性能曲线）
    Mon_Variable_Peform perform;
    
    // 动态 monitor 数据 (Type 1/3/5)
    QVector<MonitorFileData> monitors;

    void clearMonTable();
};


#endif