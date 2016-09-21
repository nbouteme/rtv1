bl_info = {
    "name":         "RTV1",
    "author":       "nbouteme",
    "blender":      (2,6,2),
    "version":      (0,0,1),
    "location":     "File > Import-Export",
    "description":  "Export RTV1 scene",
    "category":     "Import-Export"
}

"""
Name: 'RTV1 scene'
Blender: 270
Group: 'Export'
Tooltip: 'RTV1 scene exporter'
"""
import bpy
from bpy_extras.io_utils import ExportHelper;
from mathutils import *;
from math import *
from mathutils import Vector;

class ExportMyFormat(bpy.types.Operator, ExportHelper):
    bl_idname       = "scene.rv1";
    bl_label        = "RTV1 Scene Exporter";
    bl_options      = {'PRESET'};
    
    filename_ext    = ".rv1";

    def execute(self, context):
        write(self.filepath);
        return {'FINISHED'}

def menu_func(self, context):
    self.layout.operator(ExportMyFormat.bl_idname, text="RTV1 Scene file (.rv1)");

def register():
    bpy.utils.register_module(__name__);
    bpy.types.INFO_MT_file_export.append(menu_func);
    
def unregister():
    bpy.utils.unregister_module(__name__);
    bpy.types.INFO_MT_file_export.remove(menu_func);

if __name__ == "__main__":
    register()

def float_to_str(f):
    s = "";
    s += str("%f" % f).rstrip("0");
    if s[-1] == ".":
        s += "0"
    return s;

def vec3_tostr(vec):
    return ("[" + float_to_str(vec[0]) + ", " + float_to_str(vec[1]) + ", " + float_to_str(vec[2]) + "]");

def write_type(out, obj):
    supp = ["sphere", "cone", "cylinder", "plane"]
    matching = [m for m in supp if m in obj.name.lower()]
    if len (matching) != 1:
        return
    matching = matching[0];
    out.write("\ttype: " + matching + ",\n\t");

def write_trans(out, obj):
    out.write("transform: {\n\t\tposition: " + vec3_tostr(obj.location) + ",\n\t\t");
    axis = obj.rotation_euler.to_quaternion().axis
    out.write("rot_axis: " + vec3_tostr(axis) + ",\n\t\t");
    out.write("rot_angle: " + str("%.9g" % degrees(obj.rotation_euler.to_quaternion().angle)) + ",\n\t\t");
    out.write("scale: " + vec3_tostr(obj.scale) + "\n\t},\n\t");
    
def write_material(out, obj):
    if len(obj.data.materials) != 0:
        out.write("material: {\n\t\tdiffuse: " + vec3_tostr(obj.data.materials[0].diffuse_color) + ",\n\t\t");
        out.write("ambiant: " + vec3_tostr(bpy.data.worlds[0].ambient_color) + ",\n\t\t");
        out.write("spec: " + str("%.9g" % obj.data.materials[0].specular_hardness) + "\n\t}\n");
    else:
        out.write("material: {\n\t\tdiffuse: [0.5, 0.5, 0.5],\n\t\t");
        out.write("ambiant: [0, 0, 0],\n\t\t");
        out.write("spec: 9999\n\t}\n");

def write(filename):
    out = open(filename, "w")
    sce = bpy.data.objects
    for ob in sce:
        if isinstance(ob.data, bpy.types.Camera):
            out.write("camera <- {\n\t")
            out.write("pos: " + vec3_tostr(ob.location) + ",\n\t");
            cup = ob.matrix_world.to_quaternion() * Vector((0.0, 1.0, 0.0))
            out.write("up: " + vec3_tostr(cup) + ",\n\t");
            direc = ob.matrix_world.to_quaternion() * Vector((0.0, 0.0, -1.0))
            out.write("dir: " + vec3_tostr(direc) + "\n}\n\n");
        elif isinstance(ob.data, bpy.types.PointLamp):
            out.write("spots <- {\n\t")
            out.write("pos: " + vec3_tostr(ob.location) + "\n}\n\n");
        elif isinstance(ob.data, bpy.types.Mesh):
            out.write("prims <- {\n")
            write_type(out, ob);
            write_trans(out, ob);
            write_material(out, ob);
            out.write("}\n\n");
    out.close()
