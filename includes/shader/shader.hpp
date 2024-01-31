#ifndef SHADER_HPP
#define SHADER_HPP

#include <header.hpp>
#include <filesystem>
#include <math4/math4.hpp>

class Shader {
	public:
		explicit Shader(const std::string&);
		~Shader();

		[[nodiscard]] u_int get_id() const;
		void use() const;
		void setBool(const std::string&, bool) const;
		void setInt(const std::string&, int)const;
		void setFloat(const std::string&, float) const;
		void setMat4(const std::string&, matrix4) const;
		void setUInt(const std::string&, unsigned int) const;
		
	private:
		static u_int compileShader(const std::string&, GLenum, const std::string&);
		static void checkCompileErrors(u_int, const std::string&);
		
		u_int _id;
};

#endif