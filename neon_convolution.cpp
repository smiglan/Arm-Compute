#include "arm_compute/runtime/NEON/NEFunctions.h"
#include "arm_compute/runtime/Tensor.h"

#include "arm_compute/core/Types.h"
#include "utils/Utils.h"

using namespace arm_compute;
using namespace utils;

/** Gaussian 3x3 matrix
 */




int main(int argc, const char **argv)
{
        const std::array<int16_t, 9> gaussian3x3 =
{		
		1, 2, 1,
		2, 4, 2,
		1, 2, 1
			};
        constexpr unsigned int width = 6;
		constexpr unsigned int height = 6;
		
		uint8_t* src_data;

		Image input{};
         
        Image tmp{};
		NEConvolution3x3 conv3x3{};
		src_data = new uint8_t[width * height];

            for(unsigned int h = 0; h < height; h++)
            {
                for(unsigned int w = 0; w < width; w++)
                {
                    src_data[ h * width + w] = static_cast<uint8_t>( 13 * h + 17 * w);
                }
            }
        

         

        const TensorShape shape(width, height);

		input.allocator()->init(TensorInfo(shape, 1, DataType::U8));
		tmp.allocator()->init(*input.info());
       
        conv3x3.configure(&input, &tmp, gaussian3x3.data(), 0 /* Let arm_compute calculate the scale */, BorderMode::UNDEFINED);

        tmp.allocator()->allocate();
		input.allocator()->allocate();


        Window input_window;
		input_window.use_tensor_dimensions(input.info()->tensor_shape());
		Iterator input_it(&input, input_window);
		execute_window_loop(input_window, [&](const Coordinates & id)
        {
            //std::cout << "Setting item [" << id.x() << "," << id.y() << "," << id.z() << "]\n";
            *reinterpret_cast<uint8_t *>(input_it.ptr()) = src_data[ id.y() * width + id.x()];
        },
        input_it);


        conv3x3.run();
        input.print(std::cout);
        tmp.print(std::cout);

        
        

  
    }    

