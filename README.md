# Arm-Compute
This repository contains code for utilizing Arm-Compute library for convolution and gaussian functions and converting a C++ array to arm compute tensor object.
<h1> Profiling Results </h1> 

Number of iterations: 1000\
Library: OpenCV

Canny Edge | Without Replacement | With Replacement 
--- | --- | ---
Average | 0.1050 | 0.1022 
Maximum | 0.1534 | 0.3428 
Minimum | 0.0735 | 0.0743

Gaussian filter | Without Replacement | With Replacement 
--- | --- | ---
Average | 0.0372 | 0.0390 
Maximum | 0.1154 | 0.4479 
Minimum | 0.0206 | 0.0224

Library: Arm Compute (Tested on Raspberry Pi)

Canny Edge | Without Replacement | With Replacement 
--- | --- | ---
Average | 0.6809 | 0.3804 
Maximum | 0.9222 | 0.4629 
Minimum | 0.6223 | 0.3479

Gaussian filter | Without Replacement | With Replacement 
--- | --- | ---
Average | 0.1361 | 0.0583 
Maximum | 0.2050 | 1.3385 
Minimum | 0.1274 | 0.0449

