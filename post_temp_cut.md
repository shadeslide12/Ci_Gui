# Btn_AddNew
```
void CutplaneDialog::createSignal()
{
    createFlag = true;
    // emit(createNewCutplane());
}
```
# Btn_ExtractSlice
```
void CutplaneDialog::onExtractSliceClicked()
{
    createFlag = true;
    emit(createNewCutplane());
}
```
# buttonBox
```
void CutplaneDialog::setParameters()
{
     curOrigin[0] = stod(ui->lineEdit_Origin_x->text().toStdString());
     curOrigin[1] = stod(ui->lineEdit_Origin_y->text().toStdString());
     curOrigin[2] = stod(ui->lineEdit_Origin_z->text().toStdString());
     curNormal[0] = stod(ui->lineEdit_Noraml_x->text().toStdString());
     curNormal[1] = stod(ui->lineEdit_Noraml_y->text().toStdString());
     curNormal[2] = stod(ui->lineEdit_Noraml_z->text().toStdString());
    std::cout<< "[Debug] CurrentIndex is :"<< ui->comboBox->currentIndex() << std::endl;
    emit(finishSetParameters(curOrigin, curNormal, ui->comboBox->currentIndex()));
    if (createFlag) emit(createNewCutplane());
}
```

# horizontalSlider
```
void CutplaneDialog::onSliderValueChanged(int value)
{
    double min = 0.0, max = 1.0;
    switch (currentAxis) {
        .........
    }    
    double range = max - min;
    double actualValue = min + (range * value / 100.0);
    updateValueLabel(actualValue);
    setPlanePosition(actualValue);
    emit sliceLocation(actualValue,currentAxis);
}
```



# setCutplaneDialog
```
void CutplaneDialog::setCutplaneDialog(vector<vtkSmartPointer<vtkPlane>> planes)
{
    int n = planes.size();
    for (int i = 1; i <= n; i++)
    {
        string name = "cutplane";
        name += std::to_string(i);
        ui->comboBox->addItem(name.c_str());

        origin.push_back(planes[i-1]->GetOrigin());
        normal.push_back(planes[i-1]->GetNormal());
    }
     ui->lineEdit_Origin_x->setText(std::to_string(origin[0][0]).c_str());
     ui->lineEdit_Origin_y->setText(std::to_string(origin[0][1]).c_str());
     ui->lineEdit_Origin_z->setText(std::to_string(origin[0][2]).c_str());
     ui->lineEdit_Noraml_x->setText(std::to_string(normal[0][0]).c_str());
     ui->lineEdit_Noraml_y->setText(std::to_string(normal[0][1]).c_str());
     ui->lineEdit_Noraml_z->setText(std::to_string(normal[0][2]).c_str());

    updateSliderRange();

}
```
构造函数  从MainWindows接受planes参数，而后对其进行遍历，将全部的plane放置对应的combox里，将具体的数值放置于origin 和 normal 两个vector里，而后将ui里的lineEdit设置为combox里第一个选项（即是plane【0】）的具体数值
再根据切换combox里选项时会触发changeCutplaneNumber，从而改变当前lineEdit的显示数值，最后当按下buttonbox里的确认按钮后，会触发setParameters函数，将ui里的lineEdit的数值读到curOrigin和Normal里然后再通过信号    emit(finishSetParameters(curOrigin, curNormal, ui->comboBox->currentIndex()))发送到主窗口去，同时如果之前按下buttonNew的话，会额外发送一个信号createNewCutplane。



# 主窗口
    connect(cutplaneDialog, SIGNAL(finishSetParameters(double*,double*,int)),this, SLOT(changeCutplane(double*,double*,int)));
    connect(cutplaneDialog, SIGNAL(createNewCutplane()), this, SLOT(makeNewCutplane()));

```
void MainWindow::changeCutplane(double* origin, double *normal, int cutplaneNumber)
{
    // cout << origin[0] << " " << origin[1] << " " << origin[2] << endl;
    // cout << normal[0] << " " << normal[1] << " " << normal[2] << endl;
    qtvtkWindow->SetCutplane(cutplaneNumber, origin,normal);
    ui->vtkBox->renderWindow()->Render();
}
```

```
void MainWindow::makeNewCutplane()
{
    qtvtkWindow->AddNewCutplane();
    selectBoundaryDialog->addCutplaneItem();
    cout << "add new cut plane" << endl;
}
```

# vtkDisplayWindow 类 
```
void vtkDisplayWindow::AddNewCutplane()
{
    auto totalMesh = aesReader.GetTotalGrid();
    vtkSmartPointer<vtkPlane> plane = vtkSmartPointer<vtkPlane>::New();
    vtkSmartPointer<vtkCutter> cutter = vtkSmartPointer<vtkCutter>::New();
    plane->SetOrigin(0,0,0);
    plane->SetNormal(1,0,0);
    cutter->SetInputData(totalMesh);
    cutter->SetCutFunction(plane);
    vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(cutter->GetOutputPort());
    auto scalarBar = aesReader.GetFlows()[curFlow].scalarBar;
    mapper->SetLookupTable(scalarBar->GetLookupTable());
    mapper->SetScalarRange(scalarBar->GetLookupTable()->GetRange());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    
    deriveds.cutplanes.emplace_back(plane);
    deriveds.cutters.emplace_back(cutter);
    deriveds.cutplaneActors.emplace_back(actor);
    renderer->AddActor(deriveds.cutplaneActors.back());
}
```

```
void vtkDisplayWindow::SetCutplane(int cutplaneNumber, double *origin, double *normal)
{
    deriveds.cutplanes[cutplaneNumber]->SetOrigin(origin);
    deriveds.cutplanes[cutplaneNumber]->SetNormal(normal);
    deriveds.cutters[cutplaneNumber]->Update();
}
```