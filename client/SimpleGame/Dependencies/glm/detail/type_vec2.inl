/// @ref core
/// @file glm/core/type_tvec2.inl

namespace glm
{
#	ifdef GLM_STATIC_CONST_MEMBERS
	template <typename T, precision P>
	const tvec2<T, P> tvec2<T, P>::ZERO(static_cast<T>(0), static_cast<T>(0));

	template <typename T, precision P>
	const tvec2<T, P> tvec2<T, P>::X(static_cast<T>(1), static_cast<T>(0));

	template <typename T, precision P>
	const tvec2<T, P> tvec2<T, P>::Y(static_cast<T>(0), static_cast<T>(1));

	template <typename T, precision P>
	const tvec2<T, P> tvec2<T, P>::XY(static_cast<T>(1), static_cast<T>(1));
#	endif
	// -- Implicit basic constructors --

#	if !GLM_HAS_DEFAULTED_FUNCTIONS || !defined(GLM_FORCE_NO_CTOR_INIT)
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2()
#			ifndef GLM_FORCE_NO_CTOR_INIT
				: m_x(0), m_y(0)
#			endif
		{}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

#	if !GLM_HAS_DEFAULTED_FUNCTIONS
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(tvec2<T, P> const & v)
			: x(v.x), y(v.y)
		{}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

	template <typename T, precision P>
	template <precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(tvec2<T, Q> const & v)
		: m_x(v.m_x), m_y(v.m_y)
	{}

	// -- Explicit basic constructors --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(ctor)
	{}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(T scalar)
		: m_x(scalar), m_y(scalar)
	{}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(T s1, T s2)
		: m_x(s1), m_y(s2)
	{}

	// -- Conversion scalar constructors --

	template <typename T, precision P>
	template <typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(A a, B b)
		: m_x(static_cast<T>(a))
		, m_y(static_cast<T>(b))
	{}

	template <typename T, precision P>
	template <typename A, typename B>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(tvec1<A, P> const & a, tvec1<B, P> const & b)
		: m_x(static_cast<T>(a.m_x))
		, m_y(static_cast<T>(b.m_x))
	{}

	// -- Conversion vector constructors --

	template <typename T, precision P>
	template <typename U, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(tvec2<U, Q> const & v)
		: m_x(static_cast<T>(v.m_x))
		, m_y(static_cast<T>(v.m_y))
	{}

	template <typename T, precision P>
	template <typename U, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(tvec3<U, Q> const & v)
		: m_x(static_cast<T>(v.m_x))
		, m_y(static_cast<T>(v.m_y))
	{}

	template <typename T, precision P>
	template <typename U, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec2<T, P>::tvec2(tvec4<U, Q> const & v)
		: m_x(static_cast<T>(v.m_x))
		, m_y(static_cast<T>(v.m_y))
	{}

	// -- Component accesses --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER T & tvec2<T, P>::operator[](typename tvec2<T, P>::length_type i)
	{
		assert(i >= 0 && i < this->length());
		return (&m_x)[i];
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER T const & tvec2<T, P>::operator[](typename tvec2<T, P>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
		return (&m_x)[i];
	}

	// -- Unary arithmetic operators --

#	if !GLM_HAS_DEFAULTED_FUNCTIONS
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator=(tvec2<T, P> const & v)
		{
			this->x = v.x;
			this->y = v.y;
			return *this;
		}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator=(tvec2<U, P> const & v)
	{
		this->m_x = static_cast<T>(v.m_x);
		this->m_y = static_cast<T>(v.m_y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator+=(U scalar)
	{
		this->m_x += static_cast<T>(scalar);
		this->m_y += static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator+=(tvec1<U, P> const & v)
	{
		this->m_x += static_cast<T>(v.m_x);
		this->m_y += static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator+=(tvec2<U, P> const & v)
	{
		this->m_x += static_cast<T>(v.m_x);
		this->m_y += static_cast<T>(v.m_y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator-=(U scalar)
	{
		this->m_x -= static_cast<T>(scalar);
		this->m_y -= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator-=(tvec1<U, P> const & v)
	{
		this->m_x -= static_cast<T>(v.m_x);
		this->m_y -= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator-=(tvec2<U, P> const & v)
	{
		this->m_x -= static_cast<T>(v.m_x);
		this->m_y -= static_cast<T>(v.m_y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator*=(U scalar)
	{
		this->m_x *= static_cast<T>(scalar);
		this->m_y *= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator*=(tvec1<U, P> const & v)
	{
		this->m_x *= static_cast<T>(v.m_x);
		this->m_y *= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator*=(tvec2<U, P> const & v)
	{
		this->m_x *= static_cast<T>(v.m_x);
		this->m_y *= static_cast<T>(v.m_y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator/=(U scalar)
	{
		this->m_x /= static_cast<T>(scalar);
		this->m_y /= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator/=(tvec1<U, P> const & v)
	{
		this->m_x /= static_cast<T>(v.m_x);
		this->m_y /= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator/=(tvec2<U, P> const & v)
	{
		this->m_x /= static_cast<T>(v.m_x);
		this->m_y /= static_cast<T>(v.m_y);
		return *this;
	}

	// -- Increment and decrement operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator++()
	{
		++this->m_x;
		++this->m_y;
		return *this;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator--()
	{
		--this->m_x;
		--this->m_y;
		return *this;
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec2<T, P> tvec2<T, P>::operator++(int)
	{
		tvec2<T, P> Result(*this);
		++*this;
		return Result;
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec2<T, P> tvec2<T, P>::operator--(int)
	{
		tvec2<T, P> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator%=(U scalar)
	{
		this->m_x %= static_cast<T>(scalar);
		this->m_y %= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator%=(tvec1<U, P> const & v)
	{
		this->m_x %= static_cast<T>(v.m_x);
		this->m_y %= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator%=(tvec2<U, P> const & v)
	{
		this->m_x %= static_cast<T>(v.m_x);
		this->m_y %= static_cast<T>(v.m_y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator&=(U scalar)
	{
		this->m_x &= static_cast<T>(scalar);
		this->m_y &= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator&=(tvec1<U, P> const & v)
	{
		this->m_x &= static_cast<T>(v.m_x);
		this->m_y &= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator&=(tvec2<U, P> const & v)
	{
		this->m_x &= static_cast<T>(v.m_x);
		this->m_y &= static_cast<T>(v.m_y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator|=(U scalar)
	{
		this->m_x |= static_cast<T>(scalar);
		this->m_y |= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator|=(tvec1<U, P> const & v)
	{
		this->m_x |= static_cast<T>(v.m_x);
		this->m_y |= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator|=(tvec2<U, P> const & v)
	{
		this->m_x |= static_cast<T>(v.m_x);
		this->m_y |= static_cast<T>(v.m_y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator^=(U scalar)
	{
		this->m_x ^= static_cast<T>(scalar);
		this->m_y ^= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator^=(tvec1<U, P> const & v)
	{
		this->m_x ^= static_cast<T>(v.m_x);
		this->m_y ^= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator^=(tvec2<U, P> const & v)
	{
		this->m_x ^= static_cast<T>(v.m_x);
		this->m_y ^= static_cast<T>(v.m_y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator<<=(U scalar)
	{
		this->m_x <<= static_cast<T>(scalar);
		this->m_y <<= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator<<=(tvec1<U, P> const & v)
	{
		this->m_x <<= static_cast<T>(v.m_x);
		this->m_y <<= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator<<=(tvec2<U, P> const & v)
	{
		this->m_x <<= static_cast<T>(v.m_x);
		this->m_y <<= static_cast<T>(v.m_y);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator>>=(U scalar)
	{
		this->m_x >>= static_cast<T>(scalar);
		this->m_y >>= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator>>=(tvec1<U, P> const & v)
	{
		this->m_x >>= static_cast<T>(v.m_x);
		this->m_y >>= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec2<T, P> & tvec2<T, P>::operator>>=(tvec2<U, P> const & v)
	{
		this->m_x >>= static_cast<T>(v.m_x);
		this->m_y >>= static_cast<T>(v.m_y);
		return *this;
	}

	// -- Unary arithmetic operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec2<T, P> const & v)
	{
		return v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			-v.m_x, 
			-v.m_y);
	}

	// -- Binary arithmetic operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x + scalar,
			v.m_y + scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x + v2.m_x,
			v1.m_y + v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar + v.m_x,
			scalar + v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x + v2.m_x,
			v1.m_x + v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator+(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x + v2.m_x,
			v1.m_y + v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x - scalar,
			v.m_y - scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x - v2.m_x,
			v1.m_y - v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar - v.m_x,
			scalar - v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x - v2.m_x,
			v1.m_x - v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator-(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x - v2.m_x,
			v1.m_y - v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x * scalar,
			v.m_y * scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x * v2.m_x,
			v1.m_y * v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar * v.m_x,
			scalar * v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x * v2.m_x,
			v1.m_x * v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator*(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x * v2.m_x,
			v1.m_y * v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x / scalar,
			v.m_y / scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x / v2.m_x,
			v1.m_y / v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar / v.m_x,
			scalar / v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x / v2.m_x,
			v1.m_x / v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator/(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x / v2.m_x,
			v1.m_y / v2.m_y);
	}

	// -- Binary bit operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x % scalar,
			v.m_y % scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x % v2.m_x,
			v1.m_y % v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar % v.m_x,
			scalar % v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x % v2.m_x,
			v1.m_x % v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator%(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x % v2.m_x,
			v1.m_y % v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x & scalar,
			v.m_y & scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x & v2.m_x,
			v1.m_y & v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar & v.m_x,
			scalar & v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x & v2.m_x,
			v1.m_x & v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator&(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x & v2.m_x,
			v1.m_y & v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x | scalar,
			v.m_y | scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x | v2.m_x,
			v1.m_y | v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar | v.m_x,
			scalar | v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x | v2.m_x,
			v1.m_x | v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator|(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x | v2.m_x,
			v1.m_y | v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x ^ scalar,
			v.m_y ^ scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x ^ v2.m_x,
			v1.m_y ^ v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar ^ v.m_x,
			scalar ^ v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x ^ v2.m_x,
			v1.m_x ^ v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator^(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x ^ v2.m_x,
			v1.m_y ^ v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x << scalar,
			v.m_y << scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x << v2.m_x,
			v1.m_y << v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar << v.m_x,
			scalar << v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x << v2.m_x,
			v1.m_x << v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator<<(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x << v2.m_x,
			v1.m_y << v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(tvec2<T, P> const & v, T scalar)
	{
		return tvec2<T, P>(
			v.m_x >> scalar,
			v.m_y >> scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(tvec2<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x >> v2.m_x,
			v1.m_y >> v2.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(T scalar, tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			scalar >> v.m_x,
			scalar >> v.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(tvec1<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x >> v2.m_x,
			v1.m_x >> v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator>>(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return tvec2<T, P>(
			v1.m_x >> v2.m_x,
			v1.m_y >> v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<T, P> operator~(tvec2<T, P> const & v)
	{
		return tvec2<T, P>(
			~v.m_x,
			~v.m_y);
	}

	// -- Boolean operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool operator==(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return (v1.m_x == v2.m_x) && (v1.m_y == v2.m_y);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool operator!=(tvec2<T, P> const & v1, tvec2<T, P> const & v2)
	{
		return (v1.m_x != v2.m_x) || (v1.m_y != v2.m_y);
	}

	template <precision P>
	GLM_FUNC_QUALIFIER tvec2<bool, P> operator&&(tvec2<bool, P> const & v1, tvec2<bool, P> const & v2)
	{
		return tvec2<bool, P>(v1.m_x && v2.m_x, v1.m_y && v2.m_y);
	}

	template <precision P>
	GLM_FUNC_QUALIFIER tvec2<bool, P> operator||(tvec2<bool, P> const & v1, tvec2<bool, P> const & v2)
	{
		return tvec2<bool, P>(v1.m_x || v2.m_x, v1.m_y || v2.m_y);
	}
}//namespace glm
