# rendering-engine #
A rendering engine written in C++ using SDL2.0 for graphics

## Credit for the lodepng.cpp and lodepng.h files goes to Lode Vandevenne

## Features roadmap: ##

### Supported geometry: ###
- [x] add triangles
- [x] add spheres
- [ ] add boxes

### Supported light sources: ###
- [x] add quadlights 
- [ ] add spherelights

### Scenes: ###
- [x] support reading from obj files for vertex/face data
- [ ] support reading from obj files for vertex normal/texture data
- [ ] support reading from stl files

### General features: ###
- [ ] add a Bounding Volume Hierarchy (AABB)
- [x] add BRDF sampling
- [x] render each sample separately (faster output to screen)
- [ ] indirect lighting / global illumination
- [ ] vectorize intersection code for batch operations


## Current renderings: ##

### Primitives list (Triangle, Sphere) ###
![img_primitives](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/primitives_list.png) 

### Cornell box: ###
| 1 point light (512x512), 50 samples per pixel | 3 point lights (512x512), 18 samples per pixel |
:-------------------------:|:-------------------------:
| ![img_cornell_box_512x512](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/cornell-box-ptLight.png) | ![img_cornell_box_512x512, 3 lights](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/cornell-box-3-ptLights_18samples.png) |

| 1 quadlight (512x512), 30 samples per pixel  | 1 quadlight (250x250), 30 samples per pixel |
:-------------------------:|:-------------------------:
|![img_cornell_box_1 quadlight (512x512), 50 samples per pixel](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/cornell-box-1-quadlight_50samples.png)  | ![img_cornell_box_1 quadlight (250x250) soft shadow, 30 samples per pixel](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/cornell-box-1-quadlight-250x250_30samples.PNG)  |

### Bunny.obj (100x100): ###
| face normals | face normal * cos( ray dir ) |
:-------------------------:|:-------------------------:
| ![face normals](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/bunny_normal_100x100.png) | ![normal cos ray](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/bunny_normalRay_100x100.png) |

