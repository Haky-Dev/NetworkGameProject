/// @ref core
/// @file glm/detail/func_exponential.inl

#include "func_vector_relational.hpp"
#include "_vectorize.hpp"
#include <limits>
#include <cmath>
#include <cassert>

namespace glm{
namespace detail
{
#	if GLM_HAS_CXX11_STL
		using std::log2;
#	else
		template <typename genType>
		genType log2(genType Value)
		{
			return std::log(Value) * static_cast<genType>(1.4426950408889634073599246810019);
		}
#	endif

	template <typename T, precision P, template <class, precision> class vecType, bool isFloat, bool Aligned>
	struct compute_log2
	{
		GLM_FUNC_QUALIFIER static vecType<T, P> call(vecType<T, P> const & vec)
		{
			return detail::functor1<T, T, P, vecType>::call(log2, vec);
		}
	};

	template <template <class, precision> class vecType, typename T, precision P, bool Aligned>
	struct compute_sqrt
	{
		GLM_FUNC_QUALIFIER static vecType<T, P> call(vecType<T, P> const & m_x)
		{
			return detail::functor1<T, T, P, vecType>::call(std::sqrt, m_x);
		}
	};

	template <template <class, precision> class vecType, typename T, precision P, bool Aligned>
	struct compute_inversesqrt
	{
		GLM_FUNC_QUALIFIER static vecType<T, P> call(vecType<T, P> const & m_x)
		{
			return static_cast<T>(1) / sqrt(m_x);
		}
	};
		
	template <template <class, precision> class vecType, bool Aligned>
	struct compute_inversesqrt<vecType, float, lowp, Aligned>
	{
		GLM_FUNC_QUALIFIER static vecType<float, lowp> call(vecType<float, lowp> const & m_x)
		{
			vecType<float, lowp> tmp(m_x);
			vecType<float, lowp> xhalf(tmp * 0.5f);
			vecType<uint, lowp>* p = reinterpret_cast<vecType<uint, lowp>*>(const_cast<vecType<float, lowp>*>(&m_x));
			vecType<uint, lowp> i = vecType<uint, lowp>(0x5f375a86) - (*p >> vecType<uint, lowp>(1));
			vecType<float, lowp>* ptmp = reinterpret_cast<vecType<float, lowp>*>(&i);
			tmp = *ptmp;
			tmp = tmp * (1.5f - xhalf * tmp * tmp);
			return tmp;
		}
	};
}//namespace detail

	// pow
	using std::pow;
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<T, P> pow(vecType<T, P> const & base, vecType<T, P> const & exponent)
	{
		return detail::functor2<T, P, vecType>::call(pow, base, exponent);
	}

	// exp
	using std::exp;
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<T, P> exp(vecType<T, P> const & m_x)
	{
		return detail::functor1<T, T, P, vecType>::call(exp, m_x);
	}

	// log
	using std::log;
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<T, P> log(vecType<T, P> const & m_x)
	{
		return detail::functor1<T, T, P, vecType>::call(log, m_x);
	}

	//exp2, ln2 = 0.69314718055994530941723212145818f
	template <typename genType>
	GLM_FUNC_QUALIFIER genType exp2(genType m_x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<genType>::is_iec559, "'exp2' only accept floating-point inputs");

		return std::exp(static_cast<genType>(0.69314718055994530941723212145818) * m_x);
	}

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<T, P> exp2(vecType<T, P> const & m_x)
	{
		return detail::functor1<T, T, P, vecType>::call(exp2, m_x);
	}

	// log2, ln2 = 0.69314718055994530941723212145818f
	template <typename genType>
	GLM_FUNC_QUALIFIER genType log2(genType m_x)
	{
		return log2(tvec1<genType>(m_x)).m_x;
	}

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<T, P> log2(vecType<T, P> const & m_x)
	{
		return detail::compute_log2<T, P, vecType, std::numeric_limits<T>::is_iec559, detail::is_aligned<P>::value>::call(m_x);
	}

	// sqrt
	using std::sqrt;
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<T, P> sqrt(vecType<T, P> const & m_x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'sqrt' only accept floating-point inputs");
		return detail::compute_sqrt<vecType, T, P, detail::is_aligned<P>::value>::call(m_x);
	}

	// inversesqrt
	template <typename genType>
	GLM_FUNC_QUALIFIER genType inversesqrt(genType m_x)
	{
		return static_cast<genType>(1) / sqrt(m_x);
	}
	
	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<T, P> inversesqrt(vecType<T, P> const & m_x)
	{
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'inversesqrt' only accept floating-point inputs");
		return detail::compute_inversesqrt<vecType, T, P, detail::is_aligned<P>::value>::call(m_x);
	}
}//namespace glm

#if GLM_ARCH != GLM_ARCH_PURE && GLM_HAS_UNRESTRICTED_UNIONS
#	include "func_exponential_simd.inl"
#endif

