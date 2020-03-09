#pragma once
#include <libglw/Shaders.h>
namespace gl
{
    namespace get
    {
        enum Compute
        {
            MaxWorkgroupCount = GL_MAX_COMPUTE_WORK_GROUP_COUNT,
            MaxWorkgroupInvocation = GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS,
            MaxWorkgroupSize = GL_MAX_COMPUTE_WORK_GROUP_SIZE,
            MaxSharedMemorySize = GL_MAX_COMPUTE_SHARED_MEMORY_SIZE,
            MaxUniformComponents = GL_MAX_COMPUTE_UNIFORM_COMPONENTS,
            MaxAtomicCounterBuffer = GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS,
            MaxAtomicCounter = GL_MAX_COMPUTE_ATOMIC_COUNTERS,
            MaxCombinedComputeUniformComponents = GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS,
            WorkgroupSize = GL_COMPUTE_WORK_GROUP_SIZE,
            UniformBlockRef = GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER,
            AtomicCounterBufferRef = GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER,
            MaxUniformBlocks = GL_MAX_COMPUTE_UNIFORM_BLOCKS,
            MaxTextureImageUnits = GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS,
            MaxImageUniforms = GL_MAX_COMPUTE_IMAGE_UNIFORMS
        };
    }
    namespace detail
    {
        template <typename T>
        inline void Get(GLenum pname, T * params);
        template <>
        inline void Get(GLenum pname, GLboolean * params)
        {glGetBooleanv(pname, params);}
        template <>
        inline void Get(GLenum pname, GLdouble * params)
        {glGetDoublev(pname, params);}
        template <>
        inline void Get(GLenum pname, GLfloat * params)
        {glGetFloatv(pname, params);}
        template <>
        inline void Get(GLenum pname, GLint * params)
        {glGetIntegerv(pname, params);}
        template <>
        inline void Get(GLenum pname, GLint64 * params)
        {glGetInteger64v(pname, params);}

        template <typename T>
        inline void GetIndex(GLenum pname, GLuint idx, T * params);
        template <>
        inline void GetIndex(GLenum pname, GLuint idx, GLboolean * params)
        {glGetBooleani_v(pname,idx,params);}
        template <>
        inline void GetIndex(GLenum pname, GLuint idx, GLint * params)
        {glGetIntegeri_v(pname,idx,params);}
        template <>
        inline void GetIndex(GLenum pname, GLuint idx, GLfloat * params)
        {glGetFloati_v(pname,idx,params);}
        template <>
        inline void GetIndex(GLenum pname, GLuint idx, GLdouble * params)
        {glGetDoublei_v(pname,idx,params);}
        template <>
        inline void GetIndex(GLenum pname, GLuint idx, GLint64 * params)
        {glGetInteger64i_v(pname,idx,params);}
    }
    template <typename T, int GN>
    T Get()
    {
        T res=1;
        detail::Get<T>(GN, &res);
        return res;
    }
    template <typename T, int GN>
    T Get(uint32_t idx)
    {
        T res;
        detail::GetIndex<T>(GN, idx, &res);
        return res;
    }
    namespace sl
    {
        class ComputeProgram : public Program
        {
        public:
            void dispatch(glm::ivec3 num_groups)
            {
                use();
                glDispatchCompute(num_groups.x, num_groups.y, num_groups.z);
            }
            void dispatchIndirect(glm::ivec3 num_groups)
            {
                use();
                glDispatchComputeIndirect(reinterpret_cast<GLintptr>(&num_groups.x));
            }
            template <TypeShader type>
			void attachShader(Shader<type>& shader)
			{
				static_assert(false, "Only compute shader allowed.");
			}
            template <>
			void attachShader(Shader<Compute>& shader)
			{
				if (isReference())
					throw std::runtime_error("Program reference not accessible for attachment.");
				if (!exists())
					throw std::runtime_error("Compute program not initialized.");
				glAttachShader(id(), shader.id());
			}
            static glm::ivec3 GetMaxWorkgroupCount()
            {
                return {
                    Get<GLint, gl::get::Compute::MaxWorkgroupCount>(0),
                    Get<GLint, gl::get::Compute::MaxWorkgroupCount>(1),
                    Get<GLint, gl::get::Compute::MaxWorkgroupCount>(2)
                };
                return {};
            }
            static glm::ivec3 GetMaxWorkgroupSize()
            {
                return {
                    Get<GLint, gl::get::Compute::MaxWorkgroupSize>(0),
                    Get<GLint, gl::get::Compute::MaxWorkgroupSize>(1),
                    Get<GLint, gl::get::Compute::MaxWorkgroupSize>(2)
                };
                return {};
            }
        };
    } // namespace sl
}// namespace gl

