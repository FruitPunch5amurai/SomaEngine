#include "somapch.hpp"
#include "platform/opengl/OpenGLShader.hpp"
#include <glad/glad.h>
#include "core/Logger.hpp"
#include <platform/opengl/OpenGLBuffer.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace SOMA_ENGINE {
	static bool addShader(GLuint shaderProgram, const SOMA_String& text, GLenum type,
		SOMA_Array<GLuint>* shaders);
	static bool checkShaderError(GLuint shader, int flag,
		bool isProgram, const SOMA_String& errorMessage);
	static void addAllAttributes(GLuint program, const SOMA_String& vertexShaderText, uint32 version);
	static void addShaderUniforms(GLuint shaderProgram, const SOMA_String& shaderText,
		Map<SOMA_String, GLint>& uniformMap, Map<SOMA_String, GLint>& uniformBinding, Map<SOMA_String, GLint>& samplerMap);

	OpenGLShader::OpenGLShader(const SOMA_String& filepath)
	{
		SOMA_String shaderText;
		StringFuncs::loadTextFileWithIncludes(shaderText, filepath, "#include");
		m_name = StringFuncs::getFileName(filepath);
		m_id = glCreateProgram();

		if (m_id == 0)
		{
			DEBUG_LOG(LOG_TYPE_RENDERER, LOG_ERROR, "Error creating shader program\n");
			//return (uint32)-1;
		}

		SOMA_String version = GetShaderVersion();
		SOMA_String vertexShaderText = "#version " + version +
			"\n#define VS_BUILD\n#define GLSL_VERSION " + version + "\n" + shaderText;
		SOMA_String fragmentShaderText = "#version " + version +
			"\n#define FS_BUILD\n#define GLSL_VERSION " + version + "\n" + shaderText;

		SOMA_ENGINE::ShaderProgram programData;
		if (!addShader(m_id, vertexShaderText, GL_VERTEX_SHADER,
			&programData.shaders)) {
			//return (uint32)-1;
		}
		if (!addShader(m_id, fragmentShaderText, GL_FRAGMENT_SHADER,
			&programData.shaders)) {
			//return (uint32)-1;
		}

		glLinkProgram(m_id);
		if (checkShaderError(m_id, GL_LINK_STATUS,
			true, "Error linking shader program")) {
			//return (uint32)-1;
		}

		glValidateProgram(m_id);
		if (checkShaderError(m_id, GL_VALIDATE_STATUS,
			true, "Invalid shader program")) {
			//return (uint32)-1;
		}

		addAllAttributes(m_id, vertexShaderText, GetVersion());
		addShaderUniforms(m_id, shaderText, programData.uniformMap, programData.uniformBinding,
			programData.samplerMap);

		m_shaderProgramMap[m_id] = programData;
	}
	OpenGLShader::OpenGLShader(const SOMA_String& name, const SOMA_String& filepath)
	{
		SOMA_String shaderText;
		StringFuncs::loadTextFileWithIncludes(shaderText, filepath, "#include");
		m_name = name;

		m_id = glCreateProgram();

		if (m_id == 0)
		{
			DEBUG_LOG(LOG_TYPE_RENDERER, LOG_ERROR, "Error creating shader program\n");
			//return (uint32)-1;
		}

		SOMA_String version = GetShaderVersion();
		SOMA_String vertexShaderText = "#version " + version +
			"\n#define VS_BUILD\n#define GLSL_VERSION " + version + "\n" + shaderText;
		SOMA_String fragmentShaderText = "#version " + version +
			"\n#define FS_BUILD\n#define GLSL_VERSION " + version + "\n" + shaderText;

		SOMA_ENGINE::ShaderProgram programData;
		if (!addShader(m_id, vertexShaderText, GL_VERTEX_SHADER,
			&programData.shaders)) {
			//return (uint32)-1;
		}
		if (!addShader(m_id, fragmentShaderText, GL_FRAGMENT_SHADER,
			&programData.shaders)) {
			//return (uint32)-1;
		}

		glLinkProgram(m_id);
		if (checkShaderError(m_id, GL_LINK_STATUS,
			true, "Error linking shader program")) {
			//return (uint32)-1;
		}

		glValidateProgram(m_id);
		if (checkShaderError(m_id, GL_VALIDATE_STATUS,
			true, "Invalid shader program")) {
			//return (uint32)-1;
		}

		addAllAttributes(m_id, vertexShaderText, GetVersion());
		addShaderUniforms(m_id, shaderText, programData.uniformMap, programData.uniformBinding,
			programData.samplerMap);

		m_shaderProgramMap[m_id] = programData;
	}
	OpenGLShader::~OpenGLShader()
	{
		if (m_id == 0) {
			return;
		}
		Map<uint32, ShaderProgram>::iterator programIt = m_shaderProgramMap.find(m_id);
		if (programIt == m_shaderProgramMap.end()) {
			return;
		}
		const struct ShaderProgram* shaderProgram = &programIt->second;

		for (SOMA_Array<uint32>::const_iterator it = shaderProgram->shaders.begin();
			it != shaderProgram->shaders.end(); ++it)
		{
			glDetachShader(m_id, *it);
			glDeleteShader(*it);
		}
		glDeleteProgram(m_id);
		m_shaderProgramMap.erase(programIt);
	}
	void OpenGLShader::Bind() const
	{
		glUseProgram(m_id);
	}
	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}
	void OpenGLShader::BindUniformBuffer(const SOMA_String& uniformBufferName,
		SOMA_ENGINE::UniformBuffer* buffer)
	{
		OpenGLUniformBuffer* b  = (OpenGLUniformBuffer*)(buffer);	// TODO: May have to change this later
		glBindBufferBase(GL_UNIFORM_BUFFER,
			m_shaderProgramMap.at(m_id).uniformBinding.at(uniformBufferName),
			b->GetId());

		m_shaderProgramMap.at(m_id).uniformBufferIds[uniformBufferName] = b->GetId();
	}
	void OpenGLShader::UploadUniformBuffer(const SOMA_String& uniformName, const void* data, uint32 dataSize, uint32 offset) const
	{
		int32 id = m_shaderProgramMap.at(m_id).uniformBufferIds.at(uniformName);

		glBindBuffer(GL_UNIFORM_BUFFER, id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, dataSize, data);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
	void OpenGLShader::UploadInt(const SOMA_String& uniformName, const int& value) const
	{
		GLint location = glGetUniformLocation(m_id, uniformName.c_str());
		glUniform1i(location, value);
	}
	void OpenGLShader::UploadFloat4(const SOMA_String& uniformName, const glm::vec4& value) const
	{
		GLint location = glGetUniformLocation(m_id, uniformName.c_str());
		glUniform4f(location, value.x,value.y,value.z,value.w);
	}
	void OpenGLShader::UploadFloat3(const SOMA_String& uniformName, const glm::vec3& value) const
	{
		GLint location = glGetUniformLocation(m_id, uniformName.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	void OpenGLShader::UploadMat4(const SOMA_String& uniformName, const glm::mat4& value) const
	{
		GLint location = glGetUniformLocation(m_id, uniformName.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	SOMA_String OpenGLShader::GetShaderVersion()
	{
		if (!m_shaderVersion.empty()) {
			return m_shaderVersion;
		}

		uint32 version = GetVersion();

		if (version >= 330) {
			m_shaderVersion = StringFuncs::toString(version);
		}
		else if (version >= 320) {
			m_shaderVersion = "150";
		}
		else if (version >= 310) {
			m_shaderVersion = "140";
		}
		else if (version >= 300) {
			m_shaderVersion = "130";
		}
		else if (version >= 210) {
			m_shaderVersion = "120";
		}
		else if (version >= 200) {
			m_shaderVersion = "110";
		}
		else {
			int32 majorVersion = version / 100;
			int32 minorVersion = (version / 10) % 10;
			DEBUG_LOG(LOG_TYPE_RENDERER, LOG_ERROR,
				"Error: OpenGL Version %d.%d does not support shaders.\n",
				majorVersion, minorVersion);
			return "";
		}

		return m_shaderVersion;
	}
	uint32 OpenGLShader::GetVersion()
	{
		if (m_version != 0) {
			return m_version;
		}

		int32 majorVersion;
		int32 minorVersion;

		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

		m_version = (uint32)(majorVersion * 100 + minorVersion * 10);
		return m_version;
	}

	static bool addShader(GLuint shaderProgram, const SOMA_String& text, GLenum type,
		SOMA_Array<GLuint>* shaders)
	{
		GLuint shader = glCreateShader(type);

		if (shader == 0)
		{
			SOMA_CORE_ERROR("Error creating shader type {0}", shader);
			return false;
		}

		const GLchar* p[1];
		p[0] = text.c_str();
		GLint lengths[1];
		lengths[0] = (GLint)text.length();

		glShaderSource(shader, 1, p, lengths);
		glCompileShader(shader);

		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar InfoLog[1024];

			glGetShaderInfoLog(shader, 1024, NULL, InfoLog);
			SOMA_CORE_ERROR("Error compiling shader type {0}: {1}", shader, InfoLog);
			glDeleteShader(shader);
			return false;
		}

		glAttachShader(shaderProgram, shader);
		shaders->push_back(shader);
		return true;
	}
	static bool checkShaderError(GLuint shader, int flag,
		bool isProgram, const SOMA_String& errorMessage)
	{
		GLint success = 0;
		GLchar error[1024] = { 0 };

		if (isProgram) {
			glGetProgramiv(shader, flag, &success);
		}
		else {
			glGetShaderiv(shader, flag, &success);
		}

		if (!success) {
			if (isProgram) {
				glGetProgramInfoLog(shader, sizeof(error), NULL, error);
			}
			else {
				glGetShaderInfoLog(shader, sizeof(error), NULL, error);
			}

			DEBUG_LOG(LOG_TYPE_RENDERER, LOG_ERROR, "%s: '%s'\n", errorMessage.c_str(), error);
			return true;
		}
		return false;
	}
	static void addAllAttributes(GLuint program, const SOMA_String& vertexShaderText, uint32 version)
	{
		if (version >= 320) {
			// Layout is enabled. Return.
			return;
		}

		// FIXME: This code assumes attributes are listed in order, which isn't
		// true for all compilers. It's safe to ignore for now because OpenGL versions
		// requiring this aren't being used.
		GLint numActiveAttribs = 0;
		GLint maxAttribNameLength = 0;

		glGetProgramiv(program, GL_ACTIVE_ATTRIBUTES, &numActiveAttribs);
		glGetProgramiv(program, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttribNameLength);

		//	DEBUG_LOG_TEMP2("Adding attributes!");
		//	DEBUG_LOG_TEMP("%i %i", numActiveAttribs, maxAttribNameLength);
		//Array<GLchar> nameData(maxAttribNameLength);
		//for (GLint attrib = 0; attrib < numActiveAttribs; ++attrib) {
		//	GLint arraySize = 0;
		//	GLenum type = 0;
		//	GLsizei actualLength = 0;

		//	glGetActiveAttrib(program, attrib, nameData.size(),
		//		&actualLength, &arraySize, &type, &nameData[0]);
		//	glBindAttribLocation(program, attrib, (char*)&nameData[0]);
		//	//		DEBUG_LOG_TEMP2("Adding attribute!");
		//	//		DEBUG_LOG_TEMP("%s: %d", (char*)&nameData[0], attrib);
		//}
	}

	static void addShaderUniforms(GLuint shaderProgram, const SOMA_String& shaderText,
		Map<SOMA_String, GLint>& uniformMap, Map<SOMA_String, GLint>& uniformBinding,
		Map<SOMA_String, GLint>& samplerMap)
	{
		GLint numBlocks;
		uint32 binding = 0;
		glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORM_BLOCKS, &numBlocks);
		for (int32 block = 0; block < numBlocks; ++block) {
			GLint nameLen;
			glGetActiveUniformBlockiv(shaderProgram, block,
				GL_UNIFORM_BLOCK_NAME_LENGTH, &nameLen);

			SOMA_Array<GLchar> name(nameLen);
			glGetActiveUniformBlockName(shaderProgram, block, nameLen, NULL, &name[0]);
			SOMA_String uniformBlockName((char*)&name[0], nameLen - 1);
			uniformMap[uniformBlockName] = glGetUniformBlockIndex(shaderProgram, &name[0]);
			glUniformBlockBinding(shaderProgram, glGetUniformBlockIndex(shaderProgram, &name[0]), 
				binding);
			uniformBinding[uniformBlockName] = glGetUniformBlockIndex(shaderProgram, &name[0]);
			binding++;
		}
		glActiveTexture(GL_TEXTURE0);
		glActiveTexture(GL_TEXTURE1);
		GLint numUniforms = 0;
		glGetProgramiv(shaderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);

		// Would get GL_ACTIVE_UNIFORM_MAX_LENGTH, but buggy on some drivers
		SOMA_Array<GLchar> uniformName(256);
		for (int32 uniform = 0; uniform < numUniforms; ++uniform) {
			GLint arraySize = 0;
			GLenum type = 0;
			GLsizei actualLength = 0;
			glGetActiveUniform(shaderProgram, uniform, uniformName.size(),
				&actualLength, &arraySize, &type, &uniformName[0]);
			if (type != GL_SAMPLER_2D) {
				continue;
			}
			SOMA_String name((char*)&uniformName[0], actualLength);
			SOMA_CORE_DEBUG(name);
			samplerMap[name] = glGetUniformLocation(shaderProgram, (char*)&uniformName[0]);
		}
	}
}