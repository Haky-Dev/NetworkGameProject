/// @ref simd
/// @file glm/simd/experimental.h

#pragma once

#include "platform.h"

#if GLM_ARCH & GLM_ARCH_SSE2_BIT

GLM_FUNC_QUALIFIER glm_vec4 glm_vec1_sqrt_lowp(glm_vec4 m_x)
{
	return _mm_mul_ss(_mm_rsqrt_ss(m_x), m_x);
}

GLM_FUNC_QUALIFIER glm_vec4 glm_vec4_sqrt_lowp(glm_vec4 m_x)
{
	return _mm_mul_ps(_mm_rsqrt_ps(m_x), m_x);
}

#endif//GLM_ARCH & GLM_ARCH_SSE2_BIT
