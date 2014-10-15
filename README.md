# OpenCL Video

A simple project to use video and pass them to OpenCL. The idea is to open a
video or a webcam and then pass the video to OpenCL and use a predefined kernel
on every pixel of the video and render it to the screen. It uses cmake and
C++11.

## Example

Here is an example call using a movie from the blender foundation.

```
> ./OpenCL_Video -i ~/Movies/big_buck_bunny_480p_surround-fix.avi -c ./sources/painter.cl
```

[painter example](https://raw.githubusercontent.com/anirul/OpenCL_Video/master/pictures/big_bunny_painter.png)

## Dependencies

You may need these dependencies to compile and use this:

- OpenCL
- OpenGL
- GLUT
- OpenCV
- boost
  - program_options
  - filesystem
  - system
  - date_time
  - chrono

## Build

```
> git clone git@github.com:anirul/OpenCL_Video.git
> cd OpenCL_Video
> mkdir build
> cd build
> cmake ..
> make
```

## Usage

```
> ./OpenCL_Video -h
Allowed options:
  -h [ --help ]            produce help message
  -i [ --input-video ] arg input video file
  -c [ --input-cl ] arg    input cl file
  --cpu                    OpenCL with CPU
  -d [ --device ] arg      OpenCL device
  -b [ --black-white ]     black and white mode
```
