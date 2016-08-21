#pragma once

namespace DBI
{

	class ResultSet;

	class StatementHandle
	{
	public:
		StatementHandle() { }
		virtual ~StatementHandle() { }
	
		std::unique_ptr<ResultSet> Execute() {
			return InternalExecute();
		}

		template<typename T, typename... Args>
		std::unique_ptr<ResultSet> Execute(T value, Args... args)
		{
			BindArg(value, 1);
			return _Execute(2, args...);
		}

	protected:
		std::unique_ptr<ResultSet> _Execute(int i) {
			return InternalExecute();
		}

		template<typename T, typename... Args>
		std::unique_ptr<ResultSet> _Execute(int i, T value, Args... args)
		{
			BindArg(value, i);
			return _Execute(i + 1, args...);
		}

		virtual void BindArg(bool v, int i) = 0;
		virtual void BindArg(int8_t v, int i) = 0;
		virtual void BindArg(uint8_t v, int i) = 0;
		virtual void BindArg(int16_t v, int i) = 0;
		virtual void BindArg(uint16_t v, int i) = 0;
		virtual void BindArg(int32_t v, int i) = 0;
		virtual void BindArg(uint32_t v, int i) = 0;
		virtual void BindArg(int64_t v, int i) = 0;
		virtual void BindArg(uint64_t v, int i) = 0;
		virtual void BindArg(float v, int i) = 0;
		virtual void BindArg(double v, int i) = 0;
		virtual void BindArg(const std::string &v, int i) = 0;
		virtual void BindArg(const char *v, int i) = 0;
		virtual void BindArg(std::nullptr_t v, int i) = 0;
		virtual std::unique_ptr<ResultSet> InternalExecute() = 0;
	};

}

