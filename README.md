# SandRenderer

### **DirectX 11 Render Engine**

### 多相机的数据传输：

以`ShadowMap` 为例：

`ShadowMapCamera` 用于渲染阴影贴图

`MainCamera` 用于渲染最终显示的游戏场景

当使用`ShadowMapCamera`渲染`DisplacementMap`处理的图元时，

需要使用到`MainCamera`的`ViewPosition`

因此我们需要将`MainCamera`的`ViewPosition`传给`ShadowMapCamera`

该过程必须在`m_pScene->Update()`之后调用

因为只有当`m_pScene->Update()`调用完毕之后，各`Node`，`Entity`的坐标才更新完毕

而且必须在`m_pScene->Render`之前，因为进入`Render`之后，我们无法干涉。

因此可在其中间完成该过程。

`BaseCamera`类中添加`GetViewPosition()` ,`SetViewPosition()`函数，用于完成这一数据传递的过程。