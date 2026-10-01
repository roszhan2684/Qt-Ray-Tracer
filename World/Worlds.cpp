#include "World/World.h"
#include "World_builder.h"
#include "Materials/Reflective.h"
#include "Materials/Transparent.h"

#include "Cameras/Fisheye.h"
#include "Cameras/Pinhole.h"
#include "Cameras/StereoCamera.h"
#include "Cameras/ThinLens.h"

#include "GeometricObjects/Instance.h"

#include "GeometricObjects/Primitives/Plane.h"

#include "GeometricObjects/BeveledObjects/BeveledBox.h"

#include "GeometricObjects/CompoundObjects/Box.h"
#include "GeometricObjects/CompoundObjects/Grid.h"
#include "GeometricObjects/CompoundObjects/RoundRimmedBowl.h"
#include "GeometricObjects/CompoundObjects/SolidCylinder.h"
#include "GeometricObjects/CompoundObjects/SolidCone.h"
#include "GeometricObjects/CompoundObjects/ThickRing.h"

#include "Lights/Directional.h"
#include "Lights/PointLight.h"

#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"

#include "Textures/Checker3D.h"
#include "Textures/ImageTexture.h"

#include "Samplers/MultiJittered.h"

#include "Tracers/RayCast.h"

#include "World/Worlds.h"


RGBColor lightRed(1, 0.4, 0.4);
RGBColor darkRed(0.9, 0.1, 0.1);

RGBColor brown(0.71, 0.40, 0.16);
RGBColor redBrown(0.85, 0.6, 0.2);


RGBColor orange(1, 0.6, 0.2);

RGBColor lemon(1, 1, 0.33);
RGBColor yellow(1, 1, 0);
RGBColor darkYellow(0.61, 0.61, 0);

RGBColor lightGreen(0.65, 0.8, 0.30);
RGBColor lightLightGreen(0.85, 1.0, 0.6);
RGBColor green(0, 0.6, 0.3);
RGBColor realGreen(0, 1.0, 0.1);
RGBColor darkGreen(0.0, 0.81, 0.41);

RGBColor  cyan(0, 1, 1);
RGBColor  blue_green(0.1, 1, 0.5);

RGBColor lightLightBlue(0.4, 0.64, 0.82);
RGBColor lightBlue(0.1, 0.4, 0.8);
RGBColor darkBlue(0.0, 0.0, 1.0);

RGBColor lightPurple(0.65, 0.3, 1);
RGBColor darkPurple(0.5, 0, 1);

RGBColor lightLightGrey(0.9);
RGBColor lightGrey(0.7);
RGBColor grey(0.25);
RGBColor darkDarkGrey(0.2, 0.2, 0.2);

RGBColor darkBlack(0, 0, 0);


struct ColorCenterRadius {
    RGBColor color;
    Point3D  center;
    int      radius;
};

void build_spheres_helper(World* w, const std::vector<ColorCenterRadius>& spheres) {
    for (const ColorCenterRadius& s : spheres) {
        add_sphere_helper(w, s.color, s.center, s.radius);
    }
}

void build_spheres(World* w) {
    std::vector<ColorCenterRadius> spheres =
        {
           { yellow,       Point3D(   5,  3,    0),   30 },
           { brown,        Point3D(  45, -7,  -60),   20 },
           { darkGreen,    Point3D(  40, 43, -100),   17 },
           { orange,       Point3D( -20, 28,  -15),   20 },
           { green,        Point3D( -25, -7,  -35),   27 },

           { lightGreen,   Point3D(  20, -27,  -35),  25 },
           { green,        Point3D(  35,  18,  -35),  22 },
           { brown,        Point3D( -57, -17,  -50),  15 },
           { lightGreen,   Point3D( -47,  16,  -80),  23 },
           { darkGreen,    Point3D( -15, -32,  -60),  22 },

           { darkYellow,   Point3D( -35, -37,  -80),  22 },
           { darkYellow,   Point3D(  10,  43,  -80),  22 },
           { darkYellow,   Point3D(  30,  -7,  -80),  10 },  // hidden
           { darkGreen,    Point3D( -40,  48, -110),  18 },
           { brown,        Point3D( -10,  53, -120),  18 },

           { lightPurple,  Point3D(-55, -52, -100),  10 },
           { brown,        Point3D(  5, -52, -100),  15 },
           { darkPurple,   Point3D(-20, -57, -120),  15 },
           { darkGreen,    Point3D( 55, -27, -100),  1 },
           { brown,        Point3D( 50, -47, -120),  15 },

           { lightPurple,  Point3D( 70, -42, -150),  10 },
           { lightPurple,  Point3D(  5,  73, -130),  12 },
           { darkPurple,   Point3D( 66,  21, -130),  13 },
           { lightPurple,  Point3D( 72, -12, -140),  12 },
           { green,        Point3D( 64,   5, -160),  11 },

           { lightPurple,  Point3D( 55,  38, -160),  12 },
           { lightPurple,  Point3D(-73,  -2, -160),  12 },
           { darkPurple,   Point3D( 30, -62, -140),  15 },
           { darkPurple,   Point3D( 25,  63, -140),  15 },
           { darkPurple,   Point3D(-60,  46, -140),  15 },

           { lightPurple,  Point3D(-30,  68, -130),  12 },
           { green,        Point3D( 58,  56, -180),  11 },
           { green,        Point3D(-63, -39, -180),  11 },
           { lightPurple,  Point3D( 46,  68, -200),  10 },
           { lightPurple,  Point3D( -3, -72, -130),  12 }
        };

    build_spheres_helper(w, spheres);
}

struct ColorBottomTop {
    RGBColor color;
    Point3D  bottom;
    Point3D  top;
};

void build_city_helper(World* w, const std::vector<ColorBottomTop>& buildings) {
    for (const ColorBottomTop& bldg : buildings) {
        add_bb_helper(w, bldg.color, bldg.bottom, bldg.top);
    }
}
void build_city(World* w) {
    std::vector<ColorBottomTop> buildings =
        { { yellow,      Point3D( 1,  1,  0),   Point3D( 2,  2, 60)  },
          { darkPurple,  Point3D( 0,  0,  0),   Point3D( 1,  1, 60)  },
          { grey,        Point3D(-2,  2,  0),   Point3D(-1,  3,  65) },
          { green,       Point3D(-4,  0,  0),   Point3D(-3,  1,  70) },
          { darkPurple,  Point3D( 3,  0,  0),   Point3D( 4,  1,  65) },

          { darkBlue,    Point3D( 3, -4,  0),   Point3D( 4, -3,  70) },
          { darkPurple,  Point3D(-3, -4,  0),   Point3D(-2, -3,  75) },
          { yellow,      Point3D( 3,  3,  0),   Point3D( 4,  4,  70) },
          { green,       Point3D( 0, -3,  0),   Point3D( 1, -2,  70) },
          { darkBlue,    Point3D( 0,  2,  0),   Point3D( 1,  3,  70) },

          { darkBlue,    Point3D(-2,  0,  0),   Point3D(-1,  1,  70) },
          { darkBlue,    Point3D(-4, -3,  0),   Point3D(-3, -3,  80) },
          { grey,        Point3D( 2, -2,  0),   Point3D( 3, -1,  60) },
          { red,         Point3D(-4,  3,  0),   Point3D(-3,  4,  65) },

          { darkBlue,    Point3D(-6, -5,  0),   Point3D(-5, -5,  80) },
          { green,       Point3D (0,  5,  0),   Point3D( 1,  6,  60) },
          { darkPurple,  Point3D( 3,  5,  0),   Point3D( 4,  6,  65) },
          { darkBlue,    Point3D( 4,  1,  0),   Point3D( 5,  2,  70) },
          { lightRed,    Point3D(-5, -3,  0),   Point3D(-4, -2,  75) },
          { green,       Point3D( 5, -2,  0),   Point3D( 6, -1,  60) },

          { green,       Point3D(-2,  4,  0),   Point3D(-1,  5,  70) },
          { darkBlue,    Point3D(-5,  2,  0),   Point3D(-4,  3,  70) },
          { darkBlue,    Point3D(-5,  5,  0),   Point3D(-4,  6,  60) },
          { darkPurple,  Point3D(-5, -2,  0),   Point3D(-4, -1,  60) },
          { green,       Point3D(-2,  -4,  0),  Point3D(-1, -3, 65) },
          { darkBlue,    Point3D(-2,  -2,  0),  Point3D(-1, -1, 70) },
          { darkBlue,    Point3D(-6,  -1,  0),  Point3D(-5,  0, 70) }
        };

    build_city_helper(w, buildings);
    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
    build_checkerboard(plane, grey, white, 2);
    w->add_object(plane);
}

#define SPACING 5
#define SIDE 1

void add_checkerboard(World* w, const RGBColor& c1, const RGBColor& c2, int size) {
    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
    build_checkerboard(plane, c1, c2, size);
    w->add_object(plane);
}

void build_practical(World *w) {
    for (int i = 0; i < 60; i += SPACING) {
        add_bb_helper(w, orange, Point3D( i, 0, 0),     SIDE, SIDE, 4);
        add_bb_helper(w, orange, Point3D( 0, 3 * SPACING + i, 0), SIDE, SIDE, 4);

        add_bb_helper(w, cyan, Point3D( i, SPACING, 0), SIDE, SIDE, 8);

        add_bb_helper(w, green, Point3D( i,  2 * SPACING, 0), SIDE, SIDE, 16);
    }

    // Instance* is = new Instance(new SolidCone(5, 1));
    // w->set_material(is, red);
    // is->rotate_x(90);
    // is->translate(Point3D(0, -1, 0));

    // w->add_object(is);

    add_checkerboard(w, lightGrey, white, 1);
}

void build_sphere_triangle_box(World* w) {    
    // TODO

    add_checkerboard(w, lightGrey, white, 1);
}

void build_olympics(World* w) {
    // TODO

    add_checkerboard(w, lightGrey, white, 1);
}


