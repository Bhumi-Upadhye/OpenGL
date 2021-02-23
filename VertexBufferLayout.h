#pragma once
 #include <vector>
#include "Renderer.h"
//#include <GL/glew.h>
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	
	unsigned char  normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:        return 4;
		case GL_UNSIGNED_INT:  return 4;
		case GL_UNSIGNED_BYTE:  return 1;
	
		
		}
		ASSERT(false);
		return 0;
	}

};
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;

public:
	VertexBufferLayout()
		:m_Stride(0){}
	
	template <typename t>

		void  push(unsigned int count)
	{
			static_assert(false);
	}

		template<>
		void push <float>(unsigned int count)
		{
			m_Elements.push_back({GL_FLOAT,count,GL_FALSE});
			//m_Stride += sizeof(GLfloat);
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}



		template<>
		void push <unsigned int>(unsigned int count)
		{
			m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
			//m_Stride += sizeof(GLuint);
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		}




		template<>
		void push <unsigned char>(unsigned int count)
		{
			m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE});
			//m_Stride += sizeof(GLbyte);
			m_Stride +=count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

};

