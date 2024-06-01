#include <libcamera/camera_manager.h>

int
main(int /*argc*/, char * /*argv*/[])
{
  libcamera::CameraManager camera_manager;
  std::shared_ptr<libcamera::Camera> camera;

  camera_manager.start();
  camera = camera_manager.cameras().at(0);
  // camera.reset(); // Why do we have to reset the shared_ptr manually?
  camera_manager.stop(); // AddressSanitizer: 15617 byte(s) leaked in 193 allocation(s).

  return EXIT_SUCCESS;
}
