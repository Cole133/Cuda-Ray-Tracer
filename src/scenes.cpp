#include "scenes.h"
#include "sphere.h"
#include "material.h"
#include "rtweekend.h"

scene make_book1_final(int image_width, int samples_per_pixel){
    scene s;
    s.name = "book1_final";

    auto ground_mat = make_shared<lambertian>(color(0.5,0.5,0.5));
    s.world.add(make_shared<sphere>(point3(0,-1000,0), 1000, ground_mat));

    for(int a = -11; a<11; a++){
        for(int b = -11; b<11; b++){
            auto choose_mat = random_double();
            point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if((center - point3(4,0.2,0)).length() > 0.9){
                shared_ptr<material> sphere_mat;

                if(choose_mat < 0.8){
                    // Diffuse
                    auto albedo = color::random() * color::random();
                    sphere_mat = make_shared<lambertian>(albedo);
                    s.world.add(make_shared<sphere>(center, 0.2, sphere_mat));
                }
                else if (choose_mat < 0.95){
                    // Metal
                    auto albedo = color::random(0.5,1);
                    auto fuzz = random_double(0,0.5);
                    sphere_mat = make_shared<metal>(albedo, fuzz);
                    s.world.add(make_shared<sphere>(center, 0.2, sphere_mat));
                }
                else {
                    // Glass
                    sphere_mat = make_shared<dielectric>(1.5);
                    s.world.add(make_shared<sphere>(center, 0.2, sphere_mat));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    s.world.add(make_shared<sphere>(point3(0,1,0), 1.0, material1));

    auto material2 = make_shared<lambertian>(color(0.4,0.2,0.1));
    s.world.add(make_shared<sphere>(point3(-4,1,0), 1.0, material2));

    auto material3 = make_shared<metal>(color(0.7,0.6,0.5), 0.0);
    s.world.add(make_shared<sphere>(point3(4,1,0), 1.0, material3));

    s.cam.aspect_ratio = 16.0 / 9.0;
    s.cam.image_width = image_width;
    s.cam.samples_per_pixel = samples_per_pixel;
    s.cam.max_depth = 50;

    s.cam.vfov = 20;
    s.cam.lookfrom = point3(13,2,3);
    s.cam.lookat = point3(0,0,0);
    s.cam.vup = vec3(0,1,0);

    s.cam.defocus_angle = 0.6;
    s.cam.focus_dist = 10.0;

    return s;
}