#include "OCL_manager.hpp"

OCL_manager::OCL_manager() {
    init_cl("", "");
    addKernelFiles("kernel/header.cl");
    addKernelFiles("kernel/init.cl");
    addKernelFiles("kernel/update.cl");
    buildKernelProgram();
}

void        OCL_manager::init_cl(const std::string & defPlatName, const std::string & defDevName) {


    platform = getPlatform(defPlatName);
	device = getDevice(platform, defDevName);

    CGLContextObj     kCGLContext     = CGLGetCurrentContext();
    CGLShareGroupObj  kCGLShareGroup  = CGLGetShareGroup(kCGLContext);

    cl_context_properties properties[] = {
      CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
      (cl_context_properties) kCGLShareGroup,
      0
    };

    try
	{
		context = cl::Context(device, properties);
		queue = cl::CommandQueue(context, device);
	}
	catch (const cl::Error & e)
	{
		printf(
			"Error while creating the CL context: %s returned %i.\n",
			e.what(),
			e.err()
		);
	}
}

cl::Platform	OCL_manager::getPlatform(const std::string & defaultName) {
	std::vector<cl::Platform>	platforms;
	std::vector<std::string>	choices;
	size_t						platformID;

	cl::Platform::get(&platforms);

	choices.resize(platforms.size());

	std::transform(
		platforms.cbegin(), platforms.cend(),
		choices.begin(),
		getPlatformName
	);

	if (defaultName.empty())
	{
		platformID = 0;
		// platformID = promptChoice(
		// 	"Available OpenCL platforms on this computer:",
		// 	"Which platform do you want to use ? ",
		// 	choices
		// );
	}
	else
	{
		const auto occ = std::find(choices.cbegin(), choices.cend(), defaultName);

		if (occ == choices.cend())
			printf("The platform \"%s\" does not exist.\n", defaultName.c_str());

		platformID = occ - choices.cbegin();
	}

	return platforms[platformID];
}

std::string	    OCL_manager::getPlatformName(const cl::Platform & platform) {
	return platform.getInfo<CL_PLATFORM_NAME>();
}

cl::Device		OCL_manager::getDevice(const cl::Platform & platform, const std::string & defaultName) {
	std::vector<cl::Device>		devices;
	std::vector<std::string>	choices;
	size_t						deviceID;

	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);

	choices.resize(devices.size());

	std::transform(
		devices.cbegin(), devices.cend(),
		choices.begin(),
		getDeviceName
	);

	if (defaultName.empty())
	{
		// printf("-----\n");
		deviceID = 1;
		// deviceID = promptChoice(
		// 	"Available OpenCL platforms on this computer:",
		// 	"Which platform do you want to use ? ",
		// 	choices
		// );
	}
	else
	{
		const auto occ = std::find(choices.cbegin(), choices.cend(), defaultName);

		if (occ == choices.cend())
			printf("The device \"%s\" does not exist.\n", defaultName.c_str());

		deviceID = occ - choices.cbegin();
	}

	return devices[deviceID];
}

std::string	    OCL_manager::getDeviceName(const cl::Device & device)
{
	return device.getInfo<CL_DEVICE_NAME>();
}

int		    OCL_manager::promptChoice(
	const std::string & questionText,
	const std::string & answerText,
	const std::vector<std::string> & choices
) {
	unsigned	i = 1;
	std::string	answer;

	std::cout << questionText << std::endl;

	for (const auto choice : choices)
	{
		std::cout
			<< "  " << i << ". "
			<< choice
			<< std::endl;
		++i;
	}

	std::cout << std::endl;

	do
	{
		std::cout << answerText;
	} while (std::getline(std::cin, answer) && !isAnswerCorrect(choices, answer));

	return atoi(answer.c_str()) - 1;
}

bool		OCL_manager::isAnswerCorrect(const std::vector<std::string> & choices, const std::string & answer) {
	int		n = atoi(answer.c_str());
	return (n > 0 && n <= choices.size());
}

void        OCL_manager::addKernelFiles(const std::string path) {

    std::ifstream		file(path.c_str(), std::ios::in);
	std::stringstream	ss;

	if (!file.good())
		printf("The script file \"%s\" cannot be opened.\n", path.c_str());

	ss << file.rdbuf();
	std::string code = ss.str();
	sources.push_back({ strdup(code.c_str()), code.size() });

}

void    OCL_manager::buildKernelProgram() {

    program = cl::Program(context, sources);

	try
	{
		program.build({ device });
	}
	catch (const cl::Error & e)
	{
		(void)e;
		printf("%s\n", program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device).c_str());
	}
}

cl::Platform		OCL_manager::getPlatform() const {
	return this->platform;
}

cl::Device		OCL_manager::getDevice() const {
	return this->device;
}

cl::CommandQueue		OCL_manager::getQueue() {
	return this->queue;
}

std::ostream &		operator<<(std::ostream & os, const OCL_manager & cl)
{
	os
		<< "Using platform "
		<< cl.getPlatform().getInfo<CL_PLATFORM_NAME>()
		<< std::endl
		<< "Using device "
		<< cl.getDevice().getInfo<CL_DEVICE_NAME>();

	return os;
}

OCL_manager::~OCL_manager() {}
