#ifndef DBI__ANY_H
#define DBI__ANY_H

#include <algorithm>
#include <typeinfo>

namespace DBI
{
	class Any
	{
	public:
		Any()
			: content(nullptr) 
		{
		}

		template<typename ValueType>
		Any(const ValueType &value)
			: content(new Holder<ValueType>(value))
		{
		}

		Any(const Any &other)
			: content(other.content ? other.content->clone() : 0)
		{
		}
		
		~Any()
		{
			if(content)
				delete content;
		}

		Any& swap(Any &rhs)
		{
			std::swap(content, rhs.content);
			return *this;
		}

		template<typename ValueType>
		Any& operator=(const ValueType &rhs)
		{
			Any(rhs).swap(*this);
			return *this;
		}

		Any& operator=(Any rhs)
		{
			rhs.swap(*this);
			return *this;
		}

		bool empty() const
		{
			return !content;
		}

		const std::type_info& type() const
		{
			return content ? content->type() : typeid(void);
		}

		class Placeholder
		{
		public:
			virtual ~Placeholder()
			{
			}

			virtual const std::type_info& type() const = 0;
			virtual Placeholder* clone() const = 0;
		};


		template<typename ValueType>
		class Holder : public Placeholder
		{
		public:
			Holder(const ValueType &value)
				: held(value)
			{
			}

			virtual const std::type_info& type() const
			{
				return typeid(ValueType);
			}

			virtual Placeholder* clone() const
			{
				return new Holder(held);
			}

			 ValueType held;

		private:
			Holder& operator=(const Holder&);
		};

	private:
		template<typename ValueType>
		friend ValueType* any_cast(Any*);

		template<typename ValueType>
		friend ValueType* unsafe_any_cast(Any*);

		Placeholder* content;
	};

	class bad_any_cast : public std::bad_cast
	{
	public:
		virtual const char * what() const throw()
		{
			return "DBI::bad_any_cast: failed conversion using DBI::any_cast";
		}
	};

	template<typename ValueType>
	ValueType* any_cast(Any* operand)
	{
		return operand && 
			operand->type() == typeid(ValueType) ? &static_cast<Any::Holder<ValueType>*>(operand->content)->held : nullptr;
	}

	template<typename ValueType>
	inline const ValueType* any_cast(const Any* operand)
	{
		return any_cast<ValueType>(const_cast<Any*>(operand));
	}

	template<typename ValueType>
	ValueType any_cast(Any& operand)
	{
		typedef typename std::remove_reference<ValueType>::type nonref;
		nonref* result = any_cast<nonref>(&operand);
		if(!result)
			throw bad_any_cast();
		return *result;
	}
	
	template<typename ValueType>
	inline ValueType any_cast(const Any& operand)
	{
		typedef typename std::remove_reference<ValueType>::type nonref;
		return any_cast<const nonref&>(const_cast<Any&>(operand));
	}

	template<typename ValueType>
	inline ValueType* unsafe_any_cast(Any* operand)
	{
		return &static_cast<Any::Holder<ValueType>*>(operand->content)->held;
	}

	template<typename ValueType>
	inline const ValueType* unsafe_any_cast(const Any* operand)
	{
		return unsafe_any_cast<ValueType>(const_cast<Any*>(operand));
	}
}

#endif
