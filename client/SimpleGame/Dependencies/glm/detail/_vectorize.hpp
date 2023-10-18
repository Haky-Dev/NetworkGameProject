/// @ref core
/// @file glm/detail/_vectorize.hpp

#pragma once

#include "type_vec1.hpp"
#include "type_vec2.hpp"
#include "type_vec3.hpp"
#include "type_vec4.hpp"

namespace glm{
namespace detail
{
	template <typename R, typename T, precision P, template <typename, precision> class vecType>
	struct functor1{};

	template <typename R, typename T, precision P>
	struct functor1<R, T, P, tvec1>
	{
		GLM_FUNC_QUALIFIER static tvec1<R, P> call(R (*Func) (T m_x), tvec1<T, P> const & v)
		{
			return tvec1<R, P>(Func(v.m_x));
		}
	};

	template <typename R, typename T, precision P>
	struct functor1<R, T, P, tvec2>
	{
		GLM_FUNC_QUALIFIER static tvec2<R, P> call(R (*Func) (T m_x), tvec2<T, P> const & v)
		{
			return tvec2<R, P>(Func(v.m_x), Func(v.m_y));
		}
	};

	template <typename R, typename T, precision P>
	struct functor1<R, T, P, tvec3>
	{
		GLM_FUNC_QUALIFIER static tvec3<R, P> call(R (*Func) (T m_x), tvec3<T, P> const & v)
		{
			return tvec3<R, P>(Func(v.m_x), Func(v.m_y), Func(v.z));
		}
	};

	template <typename R, typename T, precision P>
	struct functor1<R, T, P, tvec4>
	{
		GLM_FUNC_QUALIFIER static tvec4<R, P> call(R (*Func) (T m_x), tvec4<T, P> const & v)
		{
			return tvec4<R, P>(Func(v.m_x), Func(v.m_y), Func(v.z), Func(v.w));
		}
	};

	template <typename T, precision P, template <typename, precision> class vecType>
	struct functor2{};

	template <typename T, precision P>
	struct functor2<T, P, tvec1>
	{
		GLM_FUNC_QUALIFIER static tvec1<T, P> call(T (*Func) (T m_x, T m_y), tvec1<T, P> const & a, tvec1<T, P> const & b)
		{
			return tvec1<T, P>(Func(a.m_x, b.m_x));
		}
	};

	template <typename T, precision P>
	struct functor2<T, P, tvec2>
	{
		GLM_FUNC_QUALIFIER static tvec2<T, P> call(T (*Func) (T m_x, T m_y), tvec2<T, P> const & a, tvec2<T, P> const & b)
		{
			return tvec2<T, P>(Func(a.m_x, b.m_x), Func(a.m_y, b.m_y));
		}
	};

	template <typename T, precision P>
	struct functor2<T, P, tvec3>
	{
		GLM_FUNC_QUALIFIER static tvec3<T, P> call(T (*Func) (T m_x, T m_y), tvec3<T, P> const & a, tvec3<T, P> const & b)
		{
			return tvec3<T, P>(Func(a.m_x, b.m_x), Func(a.m_y, b.m_y), Func(a.z, b.z));
		}
	};

	template <typename T, precision P>
	struct functor2<T, P, tvec4>
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(T (*Func) (T m_x, T m_y), tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(Func(a.m_x, b.m_x), Func(a.m_y, b.m_y), Func(a.z, b.z), Func(a.w, b.w));
		}
	};

	template <typename T, precision P, template <typename, precision> class vecType>
	struct functor2_vec_sca{};

	template <typename T, precision P>
	struct functor2_vec_sca<T, P, tvec1>
	{
		GLM_FUNC_QUALIFIER static tvec1<T, P> call(T (*Func) (T m_x, T m_y), tvec1<T, P> const & a, T b)
		{
			return tvec1<T, P>(Func(a.m_x, b));
		}
	};

	template <typename T, precision P>
	struct functor2_vec_sca<T, P, tvec2>
	{
		GLM_FUNC_QUALIFIER static tvec2<T, P> call(T (*Func) (T m_x, T m_y), tvec2<T, P> const & a, T b)
		{
			return tvec2<T, P>(Func(a.m_x, b), Func(a.m_y, b));
		}
	};

	template <typename T, precision P>
	struct functor2_vec_sca<T, P, tvec3>
	{
		GLM_FUNC_QUALIFIER static tvec3<T, P> call(T (*Func) (T m_x, T m_y), tvec3<T, P> const & a, T b)
		{
			return tvec3<T, P>(Func(a.m_x, b), Func(a.m_y, b), Func(a.z, b));
		}
	};

	template <typename T, precision P>
	struct functor2_vec_sca<T, P, tvec4>
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(T (*Func) (T m_x, T m_y), tvec4<T, P> const & a, T b)
		{
			return tvec4<T, P>(Func(a.m_x, b), Func(a.m_y, b), Func(a.z, b), Func(a.w, b));
		}
	};
}//namespace detail
}//namespace glm
