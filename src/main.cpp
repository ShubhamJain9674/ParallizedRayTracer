#include "utility.h"
#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <fstream>

color ray_color(const ray& r){
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

void ray_trace()
{
    
    
    // Image
    std::ofstream image_file("image.ppm");
    
    if(!image_file){
        std::cout << "Error opening image.ppm" << std::endl;
        return;
    }
    
    
    
    
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    
    // Calculate the image height, and ensure that it's at least 1.
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
    
    // Camera
    
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    auto camera_center = point3(0, 0, 0);
    
    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);
    
    // Calculate the horizontal and vertical delta vectors from pixel to pixel.
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;
    
    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
    - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    
    

    //frame buffer
    std::vector<color> frame_buffer(image_width * image_height);
    
    
    image_file << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    //iterating through each pixel getting the correct color and then storing it to frame buffer.
    //the loop is flattened for better parallizing opportunity.
    
    for (int idx = 0;idx < image_width * image_height;idx++) {
        
        int i = idx % image_width;
        int j = idx / image_width;
        std::clog << "\rScanlines Remaining : "<<(image_height - j) << " " << std::flush;

        auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
        auto ray_direction = pixel_center - camera_center;
        ray r(camera_center, ray_direction);

        color pixel_color = ray_color(r);           
        frame_buffer[idx] = pixel_color;     
    }


    //writing the color to the image file.
    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            int idx = j * image_width + i;
            write_color(image_file, frame_buffer[idx]);
        }
    }

    image_file.close();
    std::clog << "\rDone. \n";
}



int main()
{

    {
        MEASURE_PERF("RayTracing")
        ray_trace();
    }
    
    return 0;

}