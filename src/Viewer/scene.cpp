#include "scene.h"
#include <cstdio>
#include <QDebug>

#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usd/references.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include "pxr/imaging/glf/simpleLightingContext.h"


#include <string>

Scene::Scene() :
    mWidth(0),
    mHeight(0)
{

    mStage = pxr::UsdStage::Open("/workspaces/make_usd_great_again/media/HelloWorld.usda");
    mRoot = mStage->GetPseudoRoot();
    auto cameraPrim = mStage->GetPrimAtPath(pxr::SdfPath("/off/Camera"));
    mCamera = pxr::UsdGeomCamera(cameraPrim).GetCamera(pxr::UsdTimeCode::Default());
    GLint major = 0;
    GLint minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    printf("OpenGL version is %i.%i\n", major, minor);
    
    pxr::GlfSimpleLight light;
    light.SetPosition(pxr::GfVec4f(8.0, 10.0, 6.0, 1.0));
    light.SetDiffuse(pxr::GfVec4f(2.0,2.0, 2.0, 1.0));
    pxr::GlfSimpleLightVector lights;
    lights.push_back(light);
    pxr::GlfSimpleMaterial material;
    pxr::GfVec4f ambient(0.1, 0.1, 0.1, 1.0);
    mRenderer.SetLightingState(lights, material, ambient);


    mParams.frame = 1.0;
    mParams.complexity = 1.1f;

    mParams.enableLighting = true;


}

void Scene::draw(int width, int height)

{
    mWidth = width;
    mHeight = height;
    auto frustum = mCamera.GetFrustum();
    pxr::GfMatrix4d viewMat = frustum.ComputeViewMatrix();
    pxr::GfMatrix4d projMat = frustum.ComputeProjectionMatrix();

    const pxr::GfVec4d viewport(0, 0, width, height);
    mRenderer.SetRenderViewport(viewport);
    
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);

    // float position[4] = { 0,10.5,2,0 };
    // glLightfv(GL_LIGHT0, GL_POSITION, position);
    // //mParams.showGuides = pxr:UsdIm
    //mRenderer.SetLightingStateFromOpenGL();
    mRenderer.SetCameraState(
            viewMat,
            projMat
            );
   
    // USD render.
    mRenderer.Render(mRoot, mParams);
    
    // Clear OpenGL errors. Because UsdImagingGL::TestIntersection prints them.
    while (glGetError() != GL_NO_ERROR) {
        printf("GL ERROR");
    }

}


// void Scene::set_camera()
// {
//     pxr::GfMatrix4d pre_pos = mCamera.GetTransform();
    




// }