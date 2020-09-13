#include "arm_compute/runtime/NEON/NEFunctions.h"
#include "arm_compute/core/Types.h"
#include "utils/Utils.h"
#include "utils/ImageLoader.h"

using namespace arm_compute;
using namespace utils;

int main(int argc, const char **argv)
{
    constexpr unsigned int width = 6;
    constexpr unsigned int height = 6;
	uint8_t* src_data;
	Image input{};

    Image gaus3x3_img;
    src_data = new uint8_t[width * height ];

            for(unsigned int h = 0; h < height; h++)
            {
                for(unsigned int w = 0; w < width; w++)
                {
                    src_data[ h * width + w] = static_cast<uint8_t>(13 * h + 17 * w);
                }
            }
        
   

    
    const TensorShape shape(width, height);
    input.allocator()->init(TensorInfo(shape, 1, DataType::U8));
    gaus3x3_img.allocator()->init(TensorInfo(shape, 1, DataType::U8));

    NEGaussian3x3             gaus3x3;


    gaus3x3.configure(&input, &gaus3x3_img, BorderMode::REPLICATE);


    gaus3x3_img.allocator()->allocate();
    input.allocator()->allocate();

   

	Window input_window;
    input_window.use_tensor_dimensions(input.info()->tensor_shape());
    Iterator input_it(&input, input_window);
	execute_window_loop(input_window, [&](const Coordinates & id)
        {
            //std::cout << "Setting item [" << id.x() << "," << id.y() << "," << id.z() << "]\n";
            *reinterpret_cast<uint8_t *>(input_it.ptr()) = src_data[id.y() * width + id.x()];
        },
        input_it);

    gaus3x3.run();
    
    input.print(std::cout);
	gaus3x3_img.print(std::cout);

}
