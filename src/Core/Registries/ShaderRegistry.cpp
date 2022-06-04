#include "ShaderRegistry.h"

lucy::ShaderRegistry::~ShaderRegistry() {
	for (auto& pair: shader_registry) {
		delete(pair.second);
	}
}

lgl::Shader* lucy::ShaderRegistry::GetShader(uint32_t flags, lucy::Registry* registry) {
	using namespace lucy::Component;

	int point_light = 0;
	int dir_light = 0;

	for (auto& entity : registry->view<Tag, Transform, Light>()) {
		auto& light = registry->get<Light>(entity);

		if (!light.active) continue;

		if (light.active) {
			if (light.mode == Point) point_light++;
			if (light.mode == Directional) dir_light++;
		}
	}

	return RegisterShader(flags, point_light, dir_light);
}

void lucy::ShaderRegistry::AddShader(lgl::Shader* shader) {
	shader_registry[shader->name] = shader;
}

lgl::Shader* lucy::ShaderRegistry::GetShader(std::string name) {
	return shader_registry[name];
}

void replace_first(std::string& s, std::string const& toReplace, std::string const& replaceWith) {
    size_t pos = s.find(toReplace);
    if (pos == std::string::npos) return;

    s.replace(pos, toReplace.length(), replaceWith);
}

lgl::Shader* lucy::ShaderRegistry::RegisterShader(uint32_t shader_flags, int point_light, int dir_light) {
	std::string id = std::to_string(shader_flags) + '_' + std::to_string(dir_light) + '_' + std::to_string(point_light);

	if (shader_registry.find(id) == shader_registry.end()) {
		std::string vertexshader = read_file("D:\\C++\\Lucy Framework V2\\src\\Core\\Renderer\\Shaders\\default.vs");
		std::string fragmentshader = read_file("D:\\C++\\Lucy Framework V2\\src\\Core\\Renderer\\Shaders\\pbr.fs");

		replace_first(fragmentshader, "#define SET_LOGIC", SetLogic(point_light, dir_light));
		replace_first(fragmentshader, "#define SET_UNIFORMS", SetUniforms(point_light, dir_light));
		replace_first(fragmentshader, "#define SET_FUNCTIONS", SetFunctions(point_light, dir_light));

		// std::cout << fragmentshader << '\n';

		shader_registry[id] = new lgl::Shader(id, vertexshader, fragmentshader, false);
	}

	return shader_registry[id];
}

std::string lucy::ShaderRegistry::SetUniforms(int point_light, int dir_light) {
	std::string uniforms;

	for (int i = 0; i < point_light; i++)
		uniforms += "uniform Light point_light" + std::to_string(i) + ";\n";
	for (int i = 0; i < dir_light; i++)
		uniforms += "uniform Light dir_light" + std::to_string(i) + ";\n";

	return uniforms;
}

std::string lucy::ShaderRegistry::SetFunctions(int point_light, int dir_light) {
	std::string functions;

	functions += "#define LIGHTING_ENABLE\n";

	return functions;
}

std::string lucy::ShaderRegistry::SetLogic(int point_light, int dir_light) {
	std::string logic;

	for (int i = 0; i < point_light; i++)
		logic += "	Lo += PointCalculatePBR(N, V, point_light" + std::to_string(i) + ".position, point_light" + std::to_string(i) + ".color);\n";
	for (int i = 0; i < dir_light; i++)
		logic += "	Lo += DirCalculatePBR(N, V, dir_light" + std::to_string(i) + ".position, dir_light" + std::to_string(i) + ".direction, dir_light" + std::to_string(i) + ".color);\n";

	return logic;
}
