# Ray Tracer (Qt / C++)

A physically based ray tracer with a Qt desktop UI, built for CSUF's computer graphics coursework.

It renders scenes of spheres and other primitives with cameras, lights, materials (BRDFs/BTDFs), samplers, procedural noise and textures (including wood), using a set of tracers that range from simple ray casting to recursive Whitted-style shading.

## Build

Open `raytracer_spheres.pro` in Qt Creator (Qt 6.6) and run, or from the command line:

```sh
qmake raytracer_spheres.pro && make
```

## Credits

The core rendering framework is based on the skeleton code from Kevin Suffern's *Ray Tracing from the Ground Up* (© Kevin Suffern 2000–2008). That code is for non-commercial use and is licensed under the GNU General Public License v2; the original copyright notices are kept in each file. The Qt interface (`UserInterface/`, `mainwindow.*`) and scene-building code were added for the course.
