# miniRT
Resources:
- (https://www.scratchapixel.com/index.html)
- (https://learnopengl.com/Lighting/Basic-Lighting)

## introdution
In this exercice, we have to write a basic raytracer in C.
We need to support at least the following shapes:
- sphere
- plane
- cylinder

## parsing
We need to be able to parse files that contain the description of the scene we
need to render.

The grammar is roughly as follows:
FILE	:=	{LINE}  
LINE	:=	CAMERA | LIGHT | AMBIENT | CYLINDER | PLANE | SPHERE  
CAMERA	:=	"C" POSITION UNITVECTOR FOV  
LIGHT	:=	"L" POSITION RATIO COLOR  
AMBIENT :=	"A" RATIO COLOR  
CYLINDER	:= "cy" POSITION UNITVECTOR DIAMETER HEIGHT COLOR  
PLANE		:= "pl" POSITION UNITVECTOR COLOR  
SPHERE		:= "sp" POSITION DIAMETER COLOR  

Some extra validation needs to be done after verifying the grammar, for example,
there can only be one camera in the scene.

Here is an example of a valid scene containing 2 spheres:
```
A	0.2									255,255,255
C	0,0,0 0,0,1	70
L	-40,0,30		0.9					255,255,255
sp	10,0,51			10					250,100,200
sp	0,0,42			20					255,0,0
```
## rendering
The raytracing technique consists in computing rays starting from the camera
pinhole going through the pixels of the image we're rendering. By computing the
color of the object that ray intersects with, we get the color of that
corresponding pixel.
This technique allows us to realistically compute shadows and reflection.

### lighting
In this project, we use the ambiant, diffuse and specular lighting model.

## UI
In this project we are required to be able to move all objects in the scene.
This means we need to find a way for the user to interact with the objects and
change their coordinates.

## maths
In this project, we use a lot of operation between vectors.

