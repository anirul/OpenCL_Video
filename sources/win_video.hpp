#ifndef WIN_VIDEO_HEADER_DEFINED
#define WIN_VIDEO_HEADER_DEFINED

#include <vector>
#include <string>
#include <functional>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "cl_video.hpp"
#include "glut_win.hpp"

class win_video : public i_win {
private:
	std::pair<unsigned int, unsigned int> range_;
	std::vector<char> current_image_;
	cl_video* video_;
	bool color_;
	bool gpu_;
	unsigned int device_;
	unsigned int texture_id_;
	std::string cl_file_;
	boost::posix_time::time_duration best_time_;
	std::function<bool (std::vector<char>&)> callback_;
public:
	// constructor
	// 		size 			: frame size
	//		initial_image	: initial image
	//		callback		: get next frame (return false no more frames)
	//		cl_file			: file with the OpenCL code
	//		gpu				: force GPU else CPU
	//		device			: witch device (in case many)
	win_video(const std::pair<unsigned int, unsigned int>& size,
			  const std::vector<char> initial_image,
			  std::function<bool (std::vector<char>&)> callback,
			  const std::string& cl_file,
			  bool color = false,
			  bool gpu = true,
			  unsigned int device = 0);
	virtual ~win_video();
public:
	// inherited from the i_win interface
	virtual void init();
	virtual void display();
	virtual void idle();
	virtual void reshape(int w, int h);
	virtual void mouse_event(int button, int state, int x, int y);
	virtual void mouse_move(int x, int y);
	virtual void keyboard(unsigned char key, int x, int y);
	virtual void finish();
};

#endif // WIN_VIDEO_HEADER_DEFINED