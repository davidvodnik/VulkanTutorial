#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;

class HelloTriangleApplication {
public:
	void Run() {
		InitWindow();
		InitVulkan();
		MainLoop();
		Cleanup();
	}

private:
	void InitWindow() {
		glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_FALSE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	void InitVulkan() {
		CreateInstance();
	}

	void CreateInstance() {
		VkApplicationInfo app_info = {};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = "Vulkan Tutorial Triangle";
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.pEngineName = "No Engine";
		app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo create_info = {};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;

		uint32_t glfw_extension_count = 0;
		const char** glfw_extensions;
		glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);
		create_info.enabledExtensionCount = glfw_extension_count;
		create_info.ppEnabledExtensionNames = glfw_extensions;

		create_info.enabledLayerCount = 0;

		VkResult result = vkCreateInstance(&create_info, nullptr, &instance);

		// print available extensions
		uint32_t extension_count = 0;
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, nullptr);
		std::vector<VkExtensionProperties> extensions(extension_count);
		vkEnumerateInstanceExtensionProperties(nullptr, &extension_count, extensions.data());
		std::cout << "available extensions:" << std::endl;
		for (const auto& extension : extensions) {
			std::cout << "\t" << extension.extensionName << std::endl;
		}
	}

	void MainLoop() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	void Cleanup() {
		vkDestroyInstance(instance, nullptr);
		
		glfwDestroyWindow(window);

		glfwTerminate();
	}

	GLFWwindow* window;
	VkInstance instance;
};

int main() {
	HelloTriangleApplication app;

	app.Run();

	return 0;
}