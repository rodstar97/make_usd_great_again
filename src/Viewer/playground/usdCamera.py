from pxr import Gf, Usd, Sdf, UsdGeom

new_stage :Usd.Stage = Usd.Stage.CreateInMemory()




def create_camera(stage):
    usd_camera = UsdGeom.Camera.Define(stage , Sdf.Path("/Camera"))
    usd_camera.CreateProjectionAttr().Set(UsdGeom.Tokens.perspective)
    usd_camera.CreateFocalLengthAttr().Set(35)
    usd_camera.CreateHorizontalApertureAttr().Set(20.955)
    usd_camera.CreateVerticalApertureAttr().Set(15.2908)
    usd_camera.CreateClippingRangeAttr().Set((0.1,100000))
    return usd_camera


def get_camera(usd_geom_cam):
    return UsdGeom.Camera(usd_geom_cam)

#print(usd_camera.GetCamera())
#cam_prim.ApplyAPI("UsdGeomCamera")
usdcam = create_camera(new_stage)

test_cam = Gf.Camera()
#print(test_cam, id(test_cam))
# a = get_camera(test_cam)
# print((a), id(a))

print(new_stage.ExportToString())


usdcam.SetFromCamera(test_cam)

print(new_stage.ExportToString())
