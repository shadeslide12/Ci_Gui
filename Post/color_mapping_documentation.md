# Post模块颜色映射实现流程文档

## 1. 概述

本文档详细描述了CFD后处理软件中颜色映射的实现流程，包括主窗口和子午面（Meridional Plane）的颜色映射机制，以及如何同步更新这两个窗口的颜色映射。

## 2. 颜色映射的基本原理

颜色映射是将数值数据转换为颜色的过程，在CFD后处理中通常用于可视化流场数据。在本软件中，颜色映射主要通过以下组件实现：

- **vtkLookupTable**: 定义了如何将数值映射到颜色（从蓝到红的渐变）
- **ScalarRange**: 定义了颜色映射的最小值和最大值
- **vtkScalarBarActor**: 显示颜色条，帮助用户理解颜色与数值的对应关系

## 3. 主要类和函数

### 3.1 关键类

- **vtkAesReader**: 负责读取网格和流场数据
- **vtkDisplayWindow**: 管理渲染窗口和可视化对象
- **MainWindow**: 主界面类，管理用户交互

### 3.2 关键函数

- **vtkAesReader::UpdateFlow**: 初始化流场数据和颜色映射
- **vtkDisplayWindow::SetScalarBar**: 更新颜色映射范围和查找表
- **vtkDisplayWindow::ChangeMeridionalFlow**: 更新子午面的颜色映射
- **MainWindow::setColorBar**: 处理用户对颜色映射的修改请求

## 4. 颜色映射初始化流程

### 4.1 流场数据加载

当用户加载网格文件时，会触发以下流程：

1. `MainWindow::on_actionLoadMesh_triggered`函数被调用
2. 该函数调用`vtkDisplayWindow::ReadAesFile`读取网格和流场数据
3. `vtkAesReader::UpdateFlow`函数被调用，初始化流场数据和颜色映射

### 4.2 颜色映射初始化

在`vtkAesReader::UpdateFlow`函数中：

```cpp
void vtkAesReader::UpdateFlow(string flowFileName)
{
    // 创建查找表
    vtkSmartPointer<vtkLookupTable> lut = vtkSmartPointer<vtkLookupTable>::New();
    lut->SetNumberOfColors(10);
    lut->SetHueRange(0.6667, 0.0); // 蓝到红渐变
    lut->SetRange(flow.range);
    lut->Build();
    
    // 设置颜色条
    flow.scalarBar->SetLookupTable(lut);
}
```

这里创建了一个从蓝到红渐变的查找表，并将其应用到颜色条上。

## 5. 子午面（Meridional Plane）的颜色映射

### 5.1 子午面创建

当用户勾选子午面复选框时，会触发以下流程：

1. `MainWindow::MeridionalCheckBoxTriggered`函数被调用
2. 该函数调用`vtkDisplayWindow::CreateMeridionalPlane`创建子午面
3. `vtkDisplayWindow::ChangeMeridionalFlow`函数被调用，应用颜色映射

### 5.2 子午面颜色映射实现

在`vtkDisplayWindow::ChangeMeridionalFlow`函数中：

```cpp
std::vector<vtkSmartPointer<vtkActor>> vtkDisplayWindow::ChangeMeridionalFlow(int flowNumber)
{
    // ... 前面的代码省略 ...
    
    // 创建映射器并设置颜色映射
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(inter->GetOutputPort());
    mapper->SetLookupTable(Flow[flowNumber].scalarBar->GetLookupTable());
    mapper->SetScalarRange(Flow[flowNumber].range);
    mapper->Update();
    
    // 创建Actor
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    MeridionalPlaneActor.emplace_back(actor);

    return MeridionalPlaneActor;
}
```

这里设置了子午面的颜色映射，使用了与主窗口相同的查找表和标量范围。

## 6. 颜色映射范围的修改

### 6.1 用户交互

用户可以通过颜色条设置对话框修改颜色映射范围：

1. 用户点击"颜色条设置"按钮，触发`MainWindow::contourSettingButtonTriggered`函数
2. 该函数创建并显示`ColorBarDialog`对话框
3. 用户修改最小值和最大值，点击确定按钮
4. `ColorBarDialog::setParameters`函数被调用，发出`finishSetParameters`信号
5. 该信号连接到`MainWindow::setColorBar`函数

### 6.2 颜色映射范围更新

在`MainWindow::setColorBar`函数中：

```cpp
void MainWindow::setColorBar(double m, double M, int number, int flowNumber)
{
    qtvtkWindow->SetScalarBar(m,M,number,flowNumber);
    ui->vtkBox->renderWindow()->Render();
    
    // 如果子午面窗口可见，则刷新子午面的颜色映射
    if (ui->MeridionalcheckBox->isChecked() && !qtvtkWindow->MeridionalPlaneActor.empty())
    {
        ChangeMeridionalPlaneFlow(flowNumber);
    }
}
```

这里调用了`vtkDisplayWindow::SetScalarBar`更新主窗口的颜色映射，然后检查子午面是否可见，如果可见则调用`ChangeMeridionalPlaneFlow`更新子午面的颜色映射。

在`vtkDisplayWindow::SetScalarBar`函数中：

```cpp
void vtkDisplayWindow::SetScalarBar(double m, double M, int number, int flowNumber)
{
    aesReader.ChangeScalarBar(m,M,number,flowNumber);
    for (auto &x : boundarys)
    {
        for (auto &y : x)
        {
            y.contourActor->GetMapper()->GetInput()->GetPointData()->SetActiveScalars(aesReader.GetFlows()[flowNumber].name.c_str());
            y.contourActor->GetMapper()->SetScalarRange(m,M);
            y.contourActor->GetMapper()->SetLookupTable(aesReader.GetFlows()[flowNumber].scalarBar->GetLookupTable());
            y.contourActor->GetMapper()->Update();
        }
    }
    
    auxiliarys.scalarBarWidget->SetScalarBarActor(aesReader.GetFlows()[flowNumber].scalarBar);
    curFlow = flowNumber;
}
```

这里更新了主窗口中所有边界的颜色映射范围和查找表。

## 7. 同步更新子午面的颜色映射

为了确保子午面的颜色映射与主窗口同步更新，需要在`MainWindow::setColorBar`函数中添加对子午面的更新：

```cpp
void MainWindow::setColorBar(double m, double M, int number, int flowNumber)
{
    qtvtkWindow->SetScalarBar(m,M,number,flowNumber);
    ui->vtkBox->renderWindow()->Render();
    
    // 如果子午面窗口可见，则刷新子午面的颜色映射
    if (ui->MeridionalcheckBox->isChecked() && !qtvtkWindow->MeridionalPlaneActor.empty())
    {
        ChangeMeridionalPlaneFlow(flowNumber);
    }
}
```

这样，当用户修改颜色映射范围时，子午面的颜色映射也会同步更新。

## 8. 问题排查与解决

### 8.1 问题描述

在实际使用中，发现修改颜色条对话框中的最小值和最大值后，只有主窗口的图形更新了颜色映射范围，而子午面没有更新。

### 8.2 原因分析

问题出在`MainWindow::setColorBar`函数中，该函数只更新了主窗口的渲染，没有触发子午面的更新。子午面的颜色映射是在`vtkDisplayWindow::ChangeMeridionalFlow`函数中设置的，但这个函数没有在颜色映射范围修改后被调用。

### 8.3 解决方案

在`MainWindow::setColorBar`函数中添加对子午面的更新：

```cpp
void MainWindow::setColorBar(double m, double M, int number, int flowNumber)
{
    qtvtkWindow->SetScalarBar(m,M,number,flowNumber);
    ui->vtkBox->renderWindow()->Render();
    
    // 如果子午面窗口可见，则刷新子午面的颜色映射
    if (ui->MeridionalcheckBox->isChecked() && !qtvtkWindow->MeridionalPlaneActor.empty())
    {
        ChangeMeridionalPlaneFlow(flowNumber);
    }
}
```

这样，当用户修改颜色映射范围时，子午面的颜色映射也会同步更新。

## 9. 总结

颜色映射是CFD后处理软件中重要的可视化技术，本文档详细描述了该软件中颜色映射的实现流程，包括初始化、修改和同步更新。通过理解这些流程，可以更好地维护和扩展软件的颜色映射功能。

## 10. 参考资料

- VTK官方文档：https://vtk.org/documentation/
- 《VTK User's Guide》
- 《Visualization Toolkit: An Object-Oriented Approach to 3D Graphics》
