# rendering-engine
A rendering engine written in C++ using SDL2.0 for graphics


Cornell box: </br>
| 1 point light (500x500) | 2 point lights (250x250), 200 samples per pixel |
:-------------------------:|:-------------------------:
| ![img_cornell_box_500x500](https://github.com/Runtime-Learner/rendering-engine/blob/main/output_images/cornell-box-ptLight-500x500.jpg "500x500 render of the Cornell box. Pointlight. No indirect illumination") | ![img_cornell_box_250x250, 2 lights](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/cornell-box-two-ptLights-250x250_200samples.jpg) |

| 3 point lights (250x250), 50 samples per pixel |
:-------------------------:
|![img_cornell_box_250x250, 3 lights](https://github.com/Runtime-Learner/rendering-engine/blob/main/output_images/cornell-box-3-ptLights-250x250_50samples.jpg)  |

Bunny.obj (100x100): </br>
| face normals | normal w.r.t ray dir |
:-------------------------:|:-------------------------:
| ![face normals](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/bunny_normal_100x100.jpg) | ![normal cos ray](https://github.com/Runtime-Learner/rendering-engine/blob/generalize_classes/output_images/bunny_normalRay_100x100.jpg) |

