/// @ref core
/// @file glm/detail/type_tvec4.inl

namespace glm{
namespace detail
{
	template <typename T>
	struct is_int
	{
		enum test {value = 0};
	};

	template <>
	struct is_int<uint32>
	{
		enum test {value = ~0};
	};

	template <>
	struct is_int<int32>
	{
		enum test {value = ~0};
	};

	template <>
	struct is_int<uint64>
	{
		enum test {value = ~0};
	};

	template <>
	struct is_int<int64>
	{
		enum test {value = ~0};
	};

	template <typename T, precision P, bool Aligned>
	struct compute_vec4_add
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x + b.m_x, a.m_y + b.m_y, a.z + b.z, a.w + b.w);
		}
	};

	template <typename T, precision P, bool Aligned>
	struct compute_vec4_sub
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x - b.m_x, a.m_y - b.m_y, a.z - b.z, a.w - b.w);
		}
	};

	template <typename T, precision P, bool Aligned>
	struct compute_vec4_mul
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x * b.m_x, a.m_y * b.m_y, a.z * b.z, a.w * b.w);
		}
	};

	template <typename T, precision P, bool Aligned>
	struct compute_vec4_div
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x / b.m_x, a.m_y / b.m_y, a.z / b.z, a.w / b.w);
		}
	};

	template <typename T, precision P, bool Aligned>
	struct compute_vec4_mod
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x % b.m_x, a.m_y % b.m_y, a.z % b.z, a.w % b.w);
		}
	};

	template <typename T, precision P, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_and
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x & b.m_x, a.m_y & b.m_y, a.z & b.z, a.w & b.w);
		}
	};

	template <typename T, precision P, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_or
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x | b.m_x, a.m_y | b.m_y, a.z | b.z, a.w | b.w);
		}
	};

	template <typename T, precision P, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_xor
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x ^ b.m_x, a.m_y ^ b.m_y, a.z ^ b.z, a.w ^ b.w);
		}
	};

	template <typename T, precision P, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_shift_left
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x << b.m_x, a.m_y << b.m_y, a.z << b.z, a.w << b.w);
		}
	};

	template <typename T, precision P, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_shift_right
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & a, tvec4<T, P> const & b)
		{
			return tvec4<T, P>(a.m_x >> b.m_x, a.m_y >> b.m_y, a.z >> b.z, a.w >> b.w);
		}
	};

	template <typename T, precision P, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_equal
	{
		GLM_FUNC_QUALIFIER static bool call(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
		{
			return (v1.m_x == v2.m_x) && (v1.m_y == v2.m_y) && (v1.z == v2.z) && (v1.w == v2.w);
		}
	};

	template <typename T, precision P, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_nequal
	{
		GLM_FUNC_QUALIFIER static bool call(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
		{
			return (v1.m_x != v2.m_x) || (v1.m_y != v2.m_y) || (v1.z != v2.z) || (v1.w != v2.w);
		}
	};

	template <typename T, precision P, int IsInt, std::size_t Size, bool Aligned>
	struct compute_vec4_bitwise_not
	{
		GLM_FUNC_QUALIFIER static tvec4<T, P> call(tvec4<T, P> const & v)
		{
			return tvec4<T, P>(~v.m_x, ~v.m_y, ~v.z, ~v.w);
		}
	};
}//namespace detail

	// -- Implicit basic constructors --

#	if !GLM_HAS_DEFAULTED_FUNCTIONS || !defined(GLM_FORCE_NO_CTOR_INIT)
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR_SIMD tvec4<T, P>::tvec4()
#			ifndef GLM_FORCE_NO_CTOR_INIT
				: m_x(0), m_y(0), z(0), w(0)
#			endif
		{}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

#	if !GLM_HAS_DEFAULTED_FUNCTIONS
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER GLM_CONSTEXPR_SIMD tvec4<T, P>::tvec4(tvec4<T, P> const & v)
			: x(v.x), y(v.y), z(v.z), w(v.w)
		{}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

	template <typename T, precision P>
	template <precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_SIMD tvec4<T, P>::tvec4(tvec4<T, Q> const & v)
		: m_x(v.m_x), m_y(v.m_y), z(v.z), w(v.w)
	{}

	// -- Explicit basic constructors --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_SIMD tvec4<T, P>::tvec4(ctor)
	{}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_SIMD tvec4<T, P>::tvec4(T scalar)
		: m_x(scalar), m_y(scalar), z(scalar), w(scalar)
	{}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_SIMD tvec4<T, P>::tvec4(T a, T b, T c, T d)
		: m_x(a), m_y(b), z(c), w(d)
	{}

	// -- Conversion scalar constructors --

	template <typename T, precision P>
	template <typename A, typename B, typename C, typename D>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_SIMD tvec4<T, P>::tvec4(A a, B b, C c, D d) :
		m_x(static_cast<T>(a)),
		m_y(static_cast<T>(b)),
		z(static_cast<T>(c)),
		w(static_cast<T>(d))
	{}

	template <typename T, precision P>
	template <typename A, typename B, typename C, typename D>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec1<A, P> const & a, tvec1<B, P> const & b, tvec1<C, P> const & c, tvec1<D, P> const & d) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(b.m_x)),
		z(static_cast<T>(c.m_x)),
		w(static_cast<T>(d.m_x))
	{}

	// -- Conversion vector constructors --

	template <typename T, precision P>
	template <typename A, typename B, typename C, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec2<A, Q> const & a, B b, C c) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(a.m_y)),
		z(static_cast<T>(b)),
		w(static_cast<T>(c))
	{}

	template <typename T, precision P>
	template <typename A, typename B, typename C, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec2<A, Q> const & a, tvec1<B, Q> const & b, tvec1<C, Q> const & c) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(a.m_y)),
		z(static_cast<T>(b.m_x)),
		w(static_cast<T>(c.m_x))
	{}

	template <typename T, precision P>
	template <typename A, typename B, typename C, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(A s1, tvec2<B, Q> const & v, C s2) :
		m_x(static_cast<T>(s1)),
		m_y(static_cast<T>(v.m_x)),
		z(static_cast<T>(v.m_y)),
		w(static_cast<T>(s2))
	{}

	template <typename T, precision P>
	template <typename A, typename B, typename C, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec1<A, Q> const & a, tvec2<B, Q> const & b, tvec1<C, Q> const & c) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(b.m_x)),
		z(static_cast<T>(b.m_y)),
		w(static_cast<T>(c.m_x))
	{}

	template <typename T, precision P>
	template <typename A, typename B, typename C, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(A s1, B s2, tvec2<C, Q> const & v) :
		m_x(static_cast<T>(s1)),
		m_y(static_cast<T>(s2)),
		z(static_cast<T>(v.m_x)),
		w(static_cast<T>(v.m_y))
	{}

	template <typename T, precision P>
	template <typename A, typename B, typename C, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec1<A, Q> const & a, tvec1<B, Q> const & b, tvec2<C, Q> const & c) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(b.m_x)),
		z(static_cast<T>(c.m_x)),
		w(static_cast<T>(c.m_y))
	{}

	template <typename T, precision P>
	template <typename A, typename B, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec3<A, Q> const & a, B b) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(a.m_y)),
		z(static_cast<T>(a.z)),
		w(static_cast<T>(b))
	{}

	template <typename T, precision P>
	template <typename A, typename B, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec3<A, Q> const & a, tvec1<B, Q> const & b) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(a.m_y)),
		z(static_cast<T>(a.z)),
		w(static_cast<T>(b.m_x))
	{}

	template <typename T, precision P>
	template <typename A, typename B, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(A a, tvec3<B, Q> const & b) :
		m_x(static_cast<T>(a)),
		m_y(static_cast<T>(b.m_x)),
		z(static_cast<T>(b.m_y)),
		w(static_cast<T>(b.z))
	{}

	template <typename T, precision P>
	template <typename A, typename B, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec1<A, Q> const & a, tvec3<B, Q> const & b) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(b.m_x)),
		z(static_cast<T>(b.m_y)),
		w(static_cast<T>(b.z))
	{}

	template <typename T, precision P>
	template <typename A, typename B, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec2<A, Q> const & a, tvec2<B, Q> const & b) :
		m_x(static_cast<T>(a.m_x)),
		m_y(static_cast<T>(a.m_y)),
		z(static_cast<T>(b.m_x)),
		w(static_cast<T>(b.m_y))
	{}

	template <typename T, precision P>
	template <typename U, precision Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR_CTOR tvec4<T, P>::tvec4(tvec4<U, Q> const & v) :
		m_x(static_cast<T>(v.m_x)),
		m_y(static_cast<T>(v.m_y)),
		z(static_cast<T>(v.z)),
		w(static_cast<T>(v.w))
	{}

	// -- Component accesses --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER T & tvec4<T, P>::operator[](typename tvec4<T, P>::length_type i)
	{
		assert(i >= 0 && i < this->length());
		return (&m_x)[i];
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER T const & tvec4<T, P>::operator[](typename tvec4<T, P>::length_type i) const
	{
		assert(i >= 0 && i < this->length());
		return (&m_x)[i];
	}

	// -- Unary arithmetic operators --

#	if !GLM_HAS_DEFAULTED_FUNCTIONS
		template <typename T, precision P>
		GLM_FUNC_QUALIFIER tvec4<T, P>& tvec4<T, P>::operator=(tvec4<T, P> const & v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;
			return *this;
		}
#	endif//!GLM_HAS_DEFAULTED_FUNCTIONS

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P>& tvec4<T, P>::operator=(tvec4<U, P> const & v)
	{
		this->m_x = static_cast<T>(v.m_x);
		this->m_y = static_cast<T>(v.m_y);
		this->z = static_cast<T>(v.z);
		this->w = static_cast<T>(v.w);
		return *this;
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator+=(U scalar)
	{
		return (*this = detail::compute_vec4_add<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator+=(tvec1<U, P> const & v)
	{
		return (*this = detail::compute_vec4_add<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v.m_x)));
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator+=(tvec4<U, P> const & v)
	{
		return (*this = detail::compute_vec4_add<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator-=(U scalar)
	{
		return (*this = detail::compute_vec4_sub<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator-=(tvec1<U, P> const & v)
	{
		return (*this = detail::compute_vec4_sub<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v.m_x)));
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator-=(tvec4<U, P> const & v)
	{
		return (*this = detail::compute_vec4_sub<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator*=(U scalar)
	{
		return (*this = detail::compute_vec4_mul<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator*=(tvec1<U, P> const & v)
	{
		return (*this = detail::compute_vec4_mul<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v.m_x)));
	}

	template <typename T, precision P>
	template <typename U>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator*=(tvec4<U, P> const & v)
	{
		return (*this = detail::compute_vec4_mul<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator/=(U scalar)
	{
		return (*this = detail::compute_vec4_div<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator/=(tvec1<U, P> const & v)
	{
		return (*this = detail::compute_vec4_div<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v.m_x)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator/=(tvec4<U, P> const & v)
	{
		return (*this = detail::compute_vec4_div<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	// -- Increment and decrement operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator++()
	{
		++this->m_x;
		++this->m_y;
		++this->z;
		++this->w;
		return *this;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator--()
	{
		--this->m_x;
		--this->m_y;
		--this->z;
		--this->w;
		return *this;
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec4<T, P> tvec4<T, P>::operator++(int)
	{
		tvec4<T, P> Result(*this);
		++*this;
		return Result;
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec4<T, P> tvec4<T, P>::operator--(int)
	{
		tvec4<T, P> Result(*this);
		--*this;
		return Result;
	}

	// -- Unary bit operators --

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator%=(U scalar)
	{
		return (*this = detail::compute_vec4_mod<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator%=(tvec1<U, P> const& v)
	{
		return (*this = detail::compute_vec4_mod<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator%=(tvec4<U, P> const& v)
	{
		return (*this = detail::compute_vec4_mod<T, P, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator&=(U scalar)
	{
		return (*this = detail::compute_vec4_and<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator&=(tvec1<U, P> const & v)
	{
		return (*this = detail::compute_vec4_and<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator&=(tvec4<U, P> const & v)
	{
		return (*this = detail::compute_vec4_and<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator|=(U scalar)
	{
		return (*this = detail::compute_vec4_or<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator|=(tvec1<U, P> const & v)
	{
		return (*this = detail::compute_vec4_or<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator|=(tvec4<U, P> const & v)
	{
		return (*this = detail::compute_vec4_or<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator^=(U scalar)
	{
		return (*this = detail::compute_vec4_xor<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator^=(tvec1<U, P> const & v)
	{
		return (*this = detail::compute_vec4_xor<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator^=(tvec4<U, P> const & v)
	{
		return (*this = detail::compute_vec4_xor<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator<<=(U scalar)
	{
		return (*this = detail::compute_vec4_shift_left<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator<<=(tvec1<U, P> const & v)
	{
		return (*this = detail::compute_vec4_shift_left<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator<<=(tvec4<U, P> const & v)
	{
		return (*this = detail::compute_vec4_shift_left<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator>>=(U scalar)
	{
		return (*this = detail::compute_vec4_shift_right<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(scalar)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator>>=(tvec1<U, P> const & v)
	{
		return (*this = detail::compute_vec4_shift_right<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	template <typename T, precision P>
	template <typename U> 
	GLM_FUNC_QUALIFIER tvec4<T, P> & tvec4<T, P>::operator>>=(tvec4<U, P> const & v)
	{
		return (*this = detail::compute_vec4_shift_right<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(*this, tvec4<T, P>(v)));
	}

	// -- Unary constant operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator+(tvec4<T, P> const & v)
	{
		return v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator-(tvec4<T, P> const & v)
	{
		return tvec4<T, P>(0) -= v;
	}

	// -- Binary arithmetic operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator+(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) += scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator+(tvec4<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec4<T, P>(v1) += v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator+(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(v) += scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator+(tvec1<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v2) += v1;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator+(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) += v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator-(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) -= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator-(tvec4<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec4<T, P>(v1) -= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator-(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(scalar) -= v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator-(tvec1<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1.m_x) -= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator-(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) -= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator*(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) *= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator*(tvec4<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec4<T, P>(v1) *= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator*(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(v) *= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator*(tvec1<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v2) *= v1;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator*(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) *= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator/(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) /= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator/(tvec4<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec4<T, P>(v1) /= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator/(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(scalar) /= v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator/(tvec1<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1.m_x) /= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator/(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) /= v2;
	}

	// -- Binary bit operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator%(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) %= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator%(tvec4<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec4<T, P>(v1) %= v2.m_x;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator%(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(scalar) %= v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator%(tvec1<T, P> const & scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(scalar.m_x) %= v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator%(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) %= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator&(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) &= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator&(tvec4<T, P> const & v, tvec1<T, P> const & scalar)
	{
		return tvec4<T, P>(v) &= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator&(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(scalar) &= v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator&(tvec1<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1.m_x) &= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator&(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) &= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator|(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) |= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator|(tvec4<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec4<T, P>(v1) |= v2.m_x;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator|(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(scalar) |= v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator|(tvec1<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1.m_x) |= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator|(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) |= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator^(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) ^= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator^(tvec4<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec4<T, P>(v1) ^= v2.m_x;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator^(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(scalar) ^= v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator^(tvec1<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1.m_x) ^= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator^(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) ^= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator<<(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) <<= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator<<(tvec4<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec4<T, P>(v1) <<= v2.m_x;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator<<(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(scalar) <<= v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator<<(tvec1<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1.m_x) <<= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator<<(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) <<= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator>>(tvec4<T, P> const & v, T scalar)
	{
		return tvec4<T, P>(v) >>= scalar;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator>>(tvec4<T, P> const & v1, tvec1<T, P> const & v2)
	{
		return tvec4<T, P>(v1) >>= v2.m_x;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator>>(T scalar, tvec4<T, P> const & v)
	{
		return tvec4<T, P>(scalar) >>= v;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator>>(tvec1<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1.m_x) >>= v2;
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<T, P> operator>>(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return tvec4<T, P>(v1) >>= v2;
	}

	template <typename T, precision P> 
	GLM_FUNC_QUALIFIER tvec4<T, P> operator~(tvec4<T, P> const & v)
	{
		return detail::compute_vec4_bitwise_not<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(v);
	}

	// -- Boolean operators --

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool operator==(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return detail::compute_vec4_equal<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(v1, v2);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER bool operator!=(tvec4<T, P> const & v1, tvec4<T, P> const & v2)
	{
		return detail::compute_vec4_nequal<T, P, detail::is_int<T>::value, sizeof(T) * 8, detail::is_aligned<P>::value>::call(v1, v2);
	}

	template <precision P>
	GLM_FUNC_QUALIFIER tvec4<bool, P> operator&&(tvec4<bool, P> const & v1, tvec4<bool, P> const & v2)
	{
		return tvec4<bool, P>(v1.m_x && v2.m_x, v1.m_y && v2.m_y, v1.z && v2.z, v1.w && v2.w);
	}

	template <precision P>
	GLM_FUNC_QUALIFIER tvec4<bool, P> operator||(tvec4<bool, P> const & v1, tvec4<bool, P> const & v2)
	{
		return tvec4<bool, P>(v1.m_x || v2.m_x, v1.m_y || v2.m_y, v1.z || v2.z, v1.w || v2.w);
	}
}//namespace glm

#if GLM_ARCH != GLM_ARCH_PURE && GLM_HAS_ALIGNED_TYPE
#	include "type_vec4_simd.inl"
#endif
