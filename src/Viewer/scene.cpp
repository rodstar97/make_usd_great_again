#include "scene.h"
#include <cstdio>
#include <QDebug>

#include <pxr/usd/usd/primRange.h>
#include <pxr/usd/usd/references.h>
#include <pxr/usd/usdGeom/camera.h>
#include <pxr/usd/usdGeom/xformCommonAPI.h>
#include "pxr/imaging/glf/simpleLightingContext.h"
#include <pxr/usd/usdGeom/xformCommonAPI.h>


#include <string>

Scene::Scene() :
    mWidth(0),
    mHeight(0)
{

    mStage = pxr::UsdStage::Open("/workspaces/make_usd_great_again/media/HelloWorld.usda");
    mRoot = mStage->GetPseudoRoot();
    auto cameraPrim = mStage->GetPrimAtPath(pxr::SdfPath("/off/Camera"));
    //mCamera = pxr::UsdGeomCamera(cameraPrim).GetCamera(pxr::UsdTimeCode::Default());
    create_view_camera(mStage);
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


void Scene::set_camera(QMatrix4x4 cam_matrix)
{
    //pxr::GfMatrix4d pre_pos = mCamera.GetTransform();
    // auto frustum = mCamera.GetFrustum();
    // auto view_matrix = frustum.ComputeViewMatrix();
    auto new_matrix = pxr::GfMatrix4d(
        static_cast<double>(cam_matrix(0, 0)), static_cast<double>(cam_matrix(0, 1)), static_cast<double>(cam_matrix(0, 2)), static_cast<double>(cam_matrix(0, 3)),
        static_cast<double>(cam_matrix(1, 0)), static_cast<double>(cam_matrix(1, 1)), static_cast<double>(cam_matrix(1, 2)), static_cast<double>(cam_matrix(1, 3)),
        static_cast<double>(cam_matrix(2, 0)), static_cast<double>(cam_matrix(2, 1)), static_cast<double>(cam_matrix(2, 2)), static_cast<double>(cam_matrix(2, 3)),
        static_cast<double>(cam_matrix(3, 0)), static_cast<double>(cam_matrix(3, 1)), static_cast<double>(cam_matrix(3, 2)), static_cast<double>(cam_matrix(3, 3))
    );
    mCamera.SetTransform(new_matrix);//mCamera.GetTransform() *
    // //auto new_matrix = pxr::GfMatrix4f(*cam_matrix.data());
    // pxr::GfMatrix4d viewMat = new_matrix ;//view_matrix * 
    // pxr::GfMatrix4d projMat = frustum.ComputeProjectionMatrix();
    // mRenderer.SetCameraState(
    //         viewMat,
    //         projMat
    //         );
    auto SpherePrim = mStage->GetPrimAtPath(pxr::SdfPath("/hello/world"));
    auto color_attr = SpherePrim.GetAttribute(pxr::TfToken{"primvars:displayColor"});
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    srand (static_cast <unsigned> (time(0)));

    float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    srand (static_cast <unsigned> (time(0)));

    float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    // color.Set(1.0,1.0,1.0);
    pxr::VtArray<pxr::GfVec3f> color {{r, g, b}};
    color_attr.Set(color);

    qDebug() << "Camera Update";
    
}

void Scene::create_view_camera(pxr::UsdStageRefPtr stage)
{
    pxr::UsdGeomCamera camera = pxr::UsdGeomCamera::Define(stage, pxr::SdfPath("/tmp/persp1"));
    camera.CreateProjectionAttr();
    //camera.AddTranslateOp
    pxr::UsdGeomXformCommonAPI xformAPI(camera);
    xformAPI.SetTranslate(pxr::GfVec3f(4.0f, 5.0f, 20.0f)); // Example translation

    mCamera = camera.GetCamera(pxr::UsdTimeCode::Default()) ;
}
// }