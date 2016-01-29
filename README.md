# SandRenderer

DirectX 11 Render Engine

多相机的数据传输：
以ShadowMap为例：
ShadowMapCamera用于渲染阴影贴图
MainCamera用于渲染最终显示的游戏场景

当使用ShadowMapCamera渲染DisplacementMap处理的图元时，
需要使用到MainCamera的ViewPosition

因此我们需要将MainCamera的ViewPosition传给ShadowMapCamera

该过程必须在m_pScene->Update()之后调用
因为只有当m_pScene->Update()调用完毕之后，各Node，Entity的坐标才更新完毕

而且必须在m_pScene->Render之前，因为进入Render之后，我们无法干涉。
因此可在其中间完成该过程。

BaseCamera类中添加GetViewPosition() , SetViewPosition()函数，用于完成这一数据传递的过程。

忘了上传cube.obj , 在此备注下~
