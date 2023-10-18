/// @ref core
/// @file glm/detail/type_tvec3.inl

namespace glm
{

#	ifdef GLM_STATIC_CONST_MEMBERS
	template <typename T, precision P>
	const tvec3<T, P> tvec3<T, P>::ZERO(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));

	template <typename T, precision P>
	const tvec3<T, P> tvec3<T, P>::X(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));

	template <typename T, precision P>
	const tvec3<T, P> tvec3<T, P>::Y(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));

	template <typename T, precision P>
	const tvec3<T, P> tvec3<T, P>::Z(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));

	template <typename T, precision P>
	const tvec3<T, P> tvec3<T, P>::XY(static_cast<T>(1), static_cast<T>(1), static_cast<T>(0));

	template <typename T, precision P>
	const tvec3<T, P> tvec3<T, P>::XZ(static_cast<T>(1), static_cast<T>(0), static_cast<T>(1));

	template <typename T, precision P>
	const tvec3<T, P> tvec3<T, P>::YZ(static_cast<T>(0), static_cast<T>(1), static_cast<T>(1));

	template <typename T, precision P>
	const tvec3<T, P> tvec3<T, P>::XYZ(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
#	endif
	// -- Implicit basic constructors --

#	if !GLM_HAS_DEFAULTED_FUNCTIONS || !defined(GLM_FORCE_NO_CTOR_INIT)
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3()
#			ifndef GLM_FORCE_NO_CTOR_INIT 
				: m_x(0), m_y(0), z(0)
#			endif
		{}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

#	if !GLM_HAS_DEFAULTED_FUNCTIONS
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(tvec3<T, P> const & v)
			: x(v.x), y(v.y), z(v.z)
		{}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

	template <typename T, precision P>
	template <precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(tvec3<T, Q> const & v)
		: m_x(v.m_x), m_y(v.m_y), z(v.z)
	{}

	// -- Explicit basic constructors --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(ctor)
	{}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(T scalar)
		: m_x(scalar), m_y(scalar), z(scalar)
	{}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(T a, T b, T c)
		: m_x(a), m_y(b), z(c)
	{}

	// -- Conversion scalar constructors --

	template <typename T, precision P>
	template <typename A, typename B, typename C>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(A a, B b, C c) :
		m_x(static_cast<T>(a)),
		m_y(static_cast<T>(b)),
		z(static_cast<T>(c))
	{}

	template <typename T, precision P>
	template <typename A, typename B, typename C>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(tvec1<A, P> const & a, tvec1<B, P> const & b, tvec1<C, P> const & c) :
		m_x(static_cast<T>(a)),
		m_y(static_cast<T>(b)),
		z(static_cast<T>(c))
	{}

	// -- Conversion vector constructors --

	template <typename T, precision P>
	template <typename A, typename B, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(tvec2<A, Q> const & a, B b) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(a.m_y)),
		z(static_cast<T>(b))
	{}

	template <typename T, precision P>
	template <typename A, typename B, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(tvec2<A, Q> const & a, tvec1<B, Q> const & b) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(a.m_y)),
		z(static_cast<T>(b.m_x))
	{}

	template <typename T, precision P>
	template <typename A, typename B, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(A a, tvec2<B, Q> const & b) :
		m_x(static_cast<T>(a)),
		m_y(static_cast<T>(b.m_x)),
		z(static_cast<T>(b.m_y))
	{}

	template <typename T, precision P>
	template <typename A, typename B, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(tvec1<A, Q> const & a, tvec2<B, Q> const & b) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(b.m_x)),
		z(static_cast<T>(b.m_y))
	{}

	template <typename T, precision P>
	template <typename U, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(tvec3<U, Q> const & v) :
		m_x(static_cast<T>(v.m_x)),
		m_y(static_cast<T>(v.m_y)),
		z(static_cast<T>(v.z))
	{}

	template <typename T, precision P>
	template <typename U, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec3<T, P>::tvec3(tvec4<U, Q> const & v) :
		m_x(static_cast<T>(v.m_x)),
		m_y(static_cast<T>(v.m_y)),
		z(static_cast<T>(v.z))
	{}

	// -- Component accesses --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER T & tvec3<T, P>::operator[](typename tvec3<T, P>::length_type i)
	{
		assert(i >= 0 && i < this->length());
		return (&m_x)[i];
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER T const & tvec3<T, P>::operator[](typename tvec3<T, P>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
		return (&m_x)[i];
	}

	// -- Unary arithmetic operators --

#	if !GLM_HAS_DEFAULTED_FUNCTIONS
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER tvec3<T, P>& tvec3<T, P>::operator=(tvec3<T, P> const & v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			return *this;
		}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P>& tvec3<T, P>::operator=(tvec3<U, P> const & v)
	{
		this->m_x = static_cast<T>(v.m_x);
		this->m_y = static_cast<T>(v.m_y);
		this->z = static_cast<T>(v.z);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator+=(U scalar)
	{
		this->m_x += static_cast<T>(scalar);
		this->m_y += static_cast<T>(scalar);
		this->z += static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator+=(tvec1<U, P> const & v)
	{
		this->m_x += static_cast<T>(v.m_x);
		this->m_y += static_cast<T>(v.m_x);
		this->z += static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator+=(tvec3<U, P> const & v)
	{
		this->m_x += static_cast<T>(v.m_x);
		this->m_y += static_cast<T>(v.m_y);
		this->z += static_cast<T>(v.z);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator-=(U scalar)
	{
		this->m_x -= static_cast<T>(scalar);
		this->m_y -= static_cast<T>(scalar);
		this->z -= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator-=(tvec1<U, P> const & v)
	{
		this->m_x -= static_cast<T>(v.m_x);
		this->m_y -= static_cast<T>(v.m_x);
		this->z -= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator-=(tvec3<U, P> const & v)
	{
		this->m_x -= static_cast<T>(v.m_x);
		this->m_y -= static_cast<T>(v.m_y);
		this->z -= static_cast<T>(v.z);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator*=(U scalar)
	{
		this->m_x *= static_cast<T>(scalar);
		this->m_y *= static_cast<T>(scalar);
		this->z *= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator*=(tvec1<U, P> const & v)
	{
		this->m_x *= static_cast<T>(v.m_x);
		this->m_y *= static_cast<T>(v.m_x);
		this->z *= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator*=(tvec3<U, P> const & v)
	{
		this->m_x *= static_cast<T>(v.m_x);
		this->m_y *= static_cast<T>(v.m_y);
		this->z *= static_cast<T>(v.z);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator/=(U v)
	{
		this->m_x /= static_cast<T>(v);
		this->m_y /= static_cast<T>(v);
		this->z /= static_cast<T>(v);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator/=(tvec1<U, P> const & v)
	{
		this->m_x /= static_cast<T>(v.m_x);
		this->m_y /= static_cast<T>(v.m_x);
		this->z /= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator/=(tvec3<U, P> const & v)
	{
		this->m_x /= static_cast<T>(v.m_x);
		this->m_y /= static_cast<T>(v.m_y);
		this->z /= static_cast<T>(v.z);
		return *this;
	}

	// -- Increment and decrement operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator++()
	{
		++this->m_x;
		++this->m_y;
		++this->z;
		return *this;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator--()
	{
		--this->m_x;
		--this->m_y;
		--this->z;
		return *this;
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec3<T, P> tvec3<T, P>::operator++(int)
	{
		tvec3<T, P> Result(*this);
		++*this;
		return Result;
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec3<T, P> tvec3<T, P>::operator--(int)
	{
		tvec3<T, P> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator%=(U scalar)
	{
		this->m_x %= scalar;
		this->m_y %= scalar;
		this->z %= scalar;
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator%=(tvec1<U, P> const & v)
	{
		this->m_x %= v.m_x;
		this->m_y %= v.m_x;
		this->z %= v.m_x;
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator%=(tvec3<U, P> const & v)
	{
		this->m_x %= v.m_x;
		this->m_y %= v.m_y;
		this->z %= v.z;
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator&=(U scalar)
	{
		this->m_x &= scalar;
		this->m_y &= scalar;
		this->z &= scalar;
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator&=(tvec1<U, P> const & v)
	{
		this->m_x &= v.m_x;
		this->m_y &= v.m_x;
		this->z &= v.m_x;
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator&=(tvec3<U, P> const & v)
	{
		this->m_x &= v.m_x;
		this->m_y &= v.m_y;
		this->z &= v.z;
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator|=(U scalar)
	{
		this->m_x |= scalar;
		this->m_y |= scalar;
		this->z |= scalar;
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator|=(tvec1<U, P> const & v)
	{
		this->m_x |= v.m_x;
		this->m_y |= v.m_x;
		this->z |= v.m_x;
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator|=(tvec3<U, P> const & v)
	{
		this->m_x |= v.m_x;
		this->m_y |= v.m_y;
		this->z |= v.z;
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator^=(U scalar)
	{
		this->m_x ^= scalar;
		this->m_y ^= scalar;
		this->z ^= scalar;
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator^=(tvec1<U, P> const & v)
	{
		this->m_x ^= v.m_x;
		this->m_y ^= v.m_x;
		this->z ^= v.m_x;
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator^=(tvec3<U, P> const & v)
	{
		this->m_x ^= v.m_x;
		this->m_y ^= v.m_y;
		this->z ^= v.z;
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator<<=(U scalar)
	{
		this->m_x <<= scalar;
		this->m_y <<= scalar;
		this->z <<= scalar;
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator<<=(tvec1<U, P> const & v)
	{
		this->m_x <<= static_cast<T>(v.m_x);
		this->m_y <<= static_cast<T>(v.m_x);
		this->z <<= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator<<=(tvec3<U, P> const & v)
	{
		this->m_x <<= static_cast<T>(v.m_x);
		this->m_y <<= static_cast<T>(v.m_y);
		this->z <<= static_cast<T>(v.z);
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator>>=(U scalar)
	{
		this->m_x >>= static_cast<T>(scalar);
		this->m_y >>= static_cast<T>(scalar);
		this->z >>= static_cast<T>(scalar);
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator>>=(tvec1<U, P> const & v)
	{
		this->m_x >>= static_cast<T>(v.m_x);
		this->m_y >>= static_cast<T>(v.m_x);
		this->z >>= static_cast<T>(v.m_x);
		return *this;
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec3<T, P> & tvec3<T, P>::operator>>=(tvec3<U, P> const & v)
	{
		this->m_x >>= static_cast<T>(v.m_x);
		this->m_y >>= static_cast<T>(v.m_y);
		this->z >>= static_cast<T>(v.z);
		return *this;
	}

	// -- Unary arithmetic operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator+(tvec3<T, P> const & v)
	{
		return v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator-(tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			-v.m_x, 
			-v.m_y, 
			-v.z);
	}

	// -- Binary arithmetic operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator+(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x + scalar,
			v.m_y + scalar,
			v.z + scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator+(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x + scalar.m_x,
			v.m_y + scalar.m_x,
			v.z + scalar.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator+(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar + v.m_x,
			scalar + v.m_y,
			scalar + v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator+(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x + v.m_x,
			scalar.m_x + v.m_y,
			scalar.m_x + v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator+(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x + v2.m_x,
			v1.m_y + v2.m_y,
			v1.z + v2.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator-(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x - scalar,
			v.m_y - scalar,
			v.z - scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator-(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x - scalar.m_x,
			v.m_y - scalar.m_x,
			v.z - scalar.m_x);
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec3<T, P> operator-(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar - v.m_x,
			scalar - v.m_y,
			scalar - v.z);
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec3<T, P> operator-(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x - v.m_x,
			scalar.m_x - v.m_y,
			scalar.m_x - v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator-(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x - v2.m_x,
			v1.m_y - v2.m_y,
			v1.z - v2.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator*(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x * scalar,
			v.m_y * scalar,
			v.z * scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator*(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x * scalar.m_x,
			v.m_y * scalar.m_x,
			v.z * scalar.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator*(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar * v.m_x,
			scalar * v.m_y,
			scalar * v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator*(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x * v.m_x,
			scalar.m_x * v.m_y,
			scalar.m_x * v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator*(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x * v2.m_x,
			v1.m_y * v2.m_y,
			v1.z * v2.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator/(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x / scalar,
			v.m_y / scalar,
			v.z / scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator/(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x / scalar.m_x,
			v.m_y / scalar.m_x,
			v.z / scalar.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator/(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar / v.m_x,
			scalar / v.m_y,
			scalar / v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator/(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x / v.m_x,
			scalar.m_x / v.m_y,
			scalar.m_x / v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator/(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x / v2.m_x,
			v1.m_y / v2.m_y,
			v1.z / v2.z);
	}

	// -- Binary bit operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator%(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x % scalar,
			v.m_y % scalar,
			v.z % scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator%(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x % scalar.m_x,
			v.m_y % scalar.m_x,
			v.z % scalar.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator%(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar % v.m_x,
			scalar % v.m_y,
			scalar % v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator%(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x % v.m_x,
			scalar.m_x % v.m_y,
			scalar.m_x % v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator%(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x % v2.m_x,
			v1.m_y % v2.m_y,
			v1.z % v2.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator&(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x & scalar,
			v.m_y & scalar,
			v.z & scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator&(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x & scalar.m_x,
			v.m_y & scalar.m_x,
			v.z & scalar.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator&(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar & v.m_x,
			scalar & v.m_y,
			scalar & v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator&(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x & v.m_x,
			scalar.m_x & v.m_y,
			scalar.m_x & v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator&(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x & v2.m_x,
			v1.m_y & v2.m_y,
			v1.z & v2.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator|(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x | scalar,
			v.m_y | scalar,
			v.z | scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator|(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x | scalar.m_x,
			v.m_y | scalar.m_x,
			v.z | scalar.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator|(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar | v.m_x,
			scalar | v.m_y,
			scalar | v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator|(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x | v.m_x,
			scalar.m_x | v.m_y,
			scalar.m_x | v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator|(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x | v2.m_x,
			v1.m_y | v2.m_y,
			v1.z | v2.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator^(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x ^ scalar,
			v.m_y ^ scalar,
			v.z ^ scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator^(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x ^ scalar.m_x,
			v.m_y ^ scalar.m_x,
			v.z ^ scalar.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator^(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar ^ v.m_x,
			scalar ^ v.m_y,
			scalar ^ v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator^(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x ^ v.m_x,
			scalar.m_x ^ v.m_y,
			scalar.m_x ^ v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator^(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x ^ v2.m_x,
			v1.m_y ^ v2.m_y,
			v1.z ^ v2.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator<<(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x << scalar,
			v.m_y << scalar,
			v.z << scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator<<(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x << scalar.m_x,
			v.m_y << scalar.m_x,
			v.z << scalar.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator<<(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar << v.m_x,
			scalar << v.m_y,
			scalar << v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator<<(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x << v.m_x,
			scalar.m_x << v.m_y,
			scalar.m_x << v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator<<(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x << v2.m_x,
			v1.m_y << v2.m_y,
			v1.z << v2.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator>>(tvec3<T, P> const & v, T scalar)
	{
		return tvec3<T, P>(
			v.m_x >> scalar,
			v.m_y >> scalar,
			v.z >> scalar);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator>>(tvec3<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec3<T, P>(
			v.m_x >> scalar.m_x,
			v.m_y >> scalar.m_x,
			v.z >> scalar.m_x);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator>>(T scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar >> v.m_x,
			scalar >> v.m_y,
			scalar >> v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator>>(tvec1<T, P> const & scalar, tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			scalar.m_x >> v.m_x,
			scalar.m_x >> v.m_y,
			scalar.m_x >> v.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<T, P> operator>>(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return tvec3<T, P>(
			v1.m_x >> v2.m_x,
			v1.m_y >> v2.m_y,
			v1.z >> v2.z);
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec3<T, P> operator~(tvec3<T, P> const & v)
	{
		return tvec3<T, P>(
			~v.m_x,
			~v.m_y,
			~v.z);
	}

	// -- Boolean operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool operator==(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return (v1.m_x == v2.m_x) && (v1.m_y == v2.m_y) && (v1.z == v2.z);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool operator!=(tvec3<T, P> const & v1, tvec3<T, P> const & v2)
	{
		return (v1.m_x != v2.m_x) || (v1.m_y != v2.m_y) || (v1.z != v2.z);
	}

	template <precision P>
	GLM_FUNC_QUALIFIER tvec3<bool, P> operator&&(tvec3<bool, P> const & v1, tvec3<bool, P> const & v2)
	{
		return tvec3<bool, P>(v1.m_x && v2.m_x, v1.m_y && v2.m_y, v1.z && v2.z);
	}

	template <precision P>
	GLM_FUNC_QUALIFIER tvec3<bool, P> operator||(tvec3<bool, P> const & v1, tvec3<bool, P> const & v2)
	{
		return tvec3<bool, P>(v1.m_x || v2.m_x, v1.m_y || v2.m_y, v1.z || v2.z);
	}
}//namespace glm
