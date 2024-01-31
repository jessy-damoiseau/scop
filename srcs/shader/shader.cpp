#include <shader/shader.hpp>

Shader::Shader(const std::string& dirPath){
	_id = glCreateProgram();
	for (auto const& dir_entry : std::filesystem::directory_iterator(dirPath)){
		if (dir_entry.is_regular_file()){
			const std::string& filePath = dir_entry.path();
			const std::string& filename = dir_entry.path().filename();
			if (filename.find("vertex_shader") != std::string::npos){
				GLuint vertexShader = compileShader(filePath, GL_VERTEX_SHADER, "VERTEX");
				glAttachShader(_id, vertexShader);
				glDeleteShader(vertexShader);
			} else if (filename.find("fragment_shader") != std::string::npos){
				GLuint fragmentShader = compileShader(filePath, GL_FRAGMENT_SHADER, "FRAGMENT");
				glAttachShader(_id, fragmentShader);
				glDeleteShader(fragmentShader);
			} else if (filename.find("geometry_shader") != std::string::npos){
				GLuint geometryShader = compileShader(filePath, GL_GEOMETRY_SHADER, "GEOMETRY");
				glAttachShader(_id, geometryShader);
				glDeleteShader(geometryShader);
			}
		}
	}
	glLinkProgram(_id);
	checkCompileErrors(_id, "PROGRAM");
}

Shader::~Shader(){
	glDeleteProgram(_id);
}

u_int Shader::compileShader(const std::string& filePath, GLenum type, const std::string& fileType){
	std::ifstream file;
	std::string shaderCode;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(filePath);
		std::stringstream content;
		content << file.rdbuf();
		file.close();
		shaderCode = content.str();
	}
	catch (std::ifstream::failure& e){
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
	}
	const char *cShaderCode = shaderCode.c_str();
	u_int shaderId = glCreateShader(type);
	glShaderSource(shaderId, 1, &cShaderCode, nullptr);
    glCompileShader(shaderId);
	checkCompileErrors(shaderId, fileType);
	return shaderId;
}

void Shader::use() const{
	glUseProgram(_id);
}

void Shader::setBool(const std::string &name, bool value) const{         
    glUniform1i(glGetUniformLocation(_id, name.c_str()), (int)value); 
}

void Shader::setInt(const std::string &name, int value) const{ 
    glUniform1i(glGetUniformLocation(_id, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const{ 
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value); 
}

void Shader::setUInt(const std::string &name, unsigned int value) const{ 
    glUniform1f(glGetUniformLocation(_id, name.c_str()), value); 
} 

unsigned int Shader::get_id() const { 
	return _id;
}


void Shader::checkCompileErrors(unsigned int shader, const std::string& type){
	int success;
	char infoLog[1024];
	if (type != "PROGRAM"){
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success){
			glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success){
			glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

void Shader::setMat4(const std::string &name, matrix4 matrix) const {
	glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, matrix.get_value());
}


