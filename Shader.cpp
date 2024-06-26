#include "Shader.h"

Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
	isWireframed = false;

	std::string vertexCode = getFileContents(vertexFile);
	std::string fragmentCode = getFileContents(fragmentFile);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	//create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//give it the shader code
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	//compile it
	glCompileShader(vertexShader);
	compileErrors(vertexShader, "VERTEX");

	//create fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//give it the shader code
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	//compile it
	glCompileShader(fragmentShader);
	compileErrors(fragmentShader, "FRAGMENT");

	//create the shader program
	ID = glCreateProgram();
	//attatch the shaders
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	compileErrors(ID, "PROGRAM");

	//we are done with the shaders now, they are inside the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::close()
{
	glUseProgram(0);
}

void Shader::deleteProgram()
{
	glDeleteProgram(ID);
}

void Shader::setWireframe(bool mode)
{
	isWireframed = mode;

	if (mode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void Shader::toggleWireframe()
{
	setWireframe(!isWireframed);
}

void Shader::setInt(GLint value, const GLchar* name)
{
	use();

	glUniform1i(glGetUniformLocation(ID, name), value);

	close();
}

void Shader::setFloat(GLfloat value, const GLchar* name)
{
	use();

	glUniform1f(glGetUniformLocation(ID, name), value);

	close();
}

void Shader::setVector2(glm::fvec2 value, const GLchar* name)
{
	use();

	glUniform2fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));

	close();
}

void Shader::setVector3(glm::fvec3 value, const GLchar* name)
{
	use();

	glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));

	close();
}

void Shader::setVector4(glm::fvec4 value, const GLchar* name)
{
	use();

	glUniform4fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));

	close();
}

void Shader::setMatrix3(glm::mat3 value, const GLchar* name, GLboolean transpose)
{
	use();

	glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, transpose, glm::value_ptr(value));

	close();
}

void Shader::setMatrix4(glm::mat4 value, const GLchar* name, GLboolean transpose)
{
	use();

	glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, transpose, glm::value_ptr(value));

	close();
}

void Shader::setPalette(ColorPalette* palette)
{
	use();

	//convert colors to GLuint array

	GLint uPalette[COLOR_COUNT];//shader COLOR COUNT value is hard coded

	int i = 0;
	for (; i < COLOR_COUNT; i++)
	{
		uPalette[i] = (GLint)palette->get(i).rawData();
	}

	//pass to shader
	glUniform1iv(glGetUniformLocation(ID, "palette"), COLOR_COUNT, uPalette);

	close();
}

void Shader::setFaceShades(GLfloat f0, GLfloat f1, GLfloat f2, GLfloat f3)
{
	use();

	GLfloat faces[4] = {
		f0, f1, f2, f3
	};

	glUniform1fv(glGetUniformLocation(ID, "faceShades"), 4, faces);

	close();
}

// Checks if the different Shaders have compiled properly
void Shader::compileErrors(unsigned int shader, const char* type)
{
	// Stores status of compilation
	GLint hasCompiled;
	// Character array to store error message in
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
		if (hasCompiled == GL_FALSE)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
		}
	}
}