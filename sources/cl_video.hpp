#ifndef CL_VIDEO_HEADER_DEFINED
#define CL_VIDEO_HEADER_DEFINED

#include <string>

#include <CL/cl.hpp>

class cl_video {
private:
	cl::Image2D cl_image_input_;
	cl::Image2D cl_image_output_;
	cl::CommandQueue queue_;
	cl::Program program_;
	cl::Kernel kernel_;
	std::vector<cl::Device> devices_;
	cl::Context context_;
	unsigned int device_used_;
	cl_int err_;
	cl::Event event_;
	unsigned int mdx_;
	unsigned int mdy_;
	unsigned int nb_col_;
	unsigned int total_size_;
	cl::size_t<3> origin_;
	cl::size_t<3> region_;
public:
	cl_video(bool gpu, unsigned int device);
	virtual ~cl_video();
public:
	void init(const std::string& cl_file);
	void setup(const std::pair<unsigned int, unsigned int>& s,
			   unsigned int nb_col);
	void prepare(const std::vector<char>& input);
	boost::posix_time::time_duration run(std::vector<char>& output);
};

#endif // CL_VIDEO_HEADER_DEFINED