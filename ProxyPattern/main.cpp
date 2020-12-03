#include <iostream>
#include <string>
#include <memory>


class IProgram
{
public:
	virtual void execute() = 0;
	virtual ~IProgram() noexcept = default;
};

class Program
	:
	public IProgram
{
	const std::wstring m_name;
public:
	Program( const std::wstring& name )
		:
		m_name( name )
	{

	}
	~Program() noexcept = default;
	Program( const Program& rhs )
		:
		m_name{rhs.m_name}
	{}
	Program( Program&& rhs ) noexcept
		:
		m_name{std::move( rhs.m_name )}
	{}

	void execute() override
	{
		std::wcout << L"Executing program..." << L'\n';
	}

	std::wstring getName() const noexcept
	{
		return m_name;
	}
};

// Proxy class
class ProxyProgram
{
	std::unique_ptr<Program> m_program;
public:
	ProxyProgram( Program&& program )
		:
		m_program{std::make_unique<Program>( program ) }
	{

	}

	ProxyProgram( const ProxyProgram& rhs ) = delete;
	ProxyProgram( ProxyProgram&& rhs ) noexcept
		:
		m_program{ std::move( rhs.m_program ) }
	{}

	void execute()
	{
		std::wcout << L"Proxy executes the Program "
			<< m_program->getName()
			<< L'\n';
	}

	Program* getProgram() const noexcept
	{
		return m_program.get();
	}
};

// Const Proxy class (trick)
class ProxyProgramConst
{
	ProxyProgram m_proxy;
public:
	ProxyProgramConst( ProxyProgram& pp )
		:
		m_proxy{std::move( pp )}
	{}

	// use only const functions to avoid modifying the Program (target object)

	void execute() const noexcept
	{
		std::wcout << L"Const Proxy executes the Program "
			<< m_proxy.getProgram()->getName()
			<< L" promising not to modify it under any circumstances!"
			<< L'\n';
	}
};


int main()
{
	Program program{L"CCleaner"};

	ProxyProgram proxyProgram{std::move( program )};

	proxyProgram.execute();

	//program.execute();	// it will work in this case, but:
	// 1. the intent in this example is to use the ProxyProgram object to interact with
	//		the target Program object ("program")
	// 2. you should never use an object after it has been moved anyway

	// bonus:
	ProxyProgramConst constProxy{proxyProgram};
	constProxy.execute();
	
	std::system( "pause" );
	return 0;
}
