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
	const std::string m_name;
public:
	Program( const std::string& name )
		:
		m_name( name )
	{

	}

	~Program() noexcept = default;

	Program( const Program& rhs )
		:
		m_name{rhs.m_name}
	{

	}

	Program( Program&& rhs ) noexcept
		:
		m_name{std::move( rhs.m_name )}
	{

	}

	void execute() override
	{
		std::cout << "Executing program..." << '\n';
	}

	std::string getName() const noexcept
	{
		return m_name;
	}
};

// Proxy class
class ProxyProgram
{
	std::unique_ptr<Program> m_pProgram;
public:
	ProxyProgram( Program&& program )
		:
		m_pProgram{std::make_unique<Program>( program ) }
	{

	}

	ProxyProgram( const ProxyProgram& rhs ) = delete;
	ProxyProgram( ProxyProgram&& rhs ) noexcept
		:
		m_pProgram{std::move( rhs.m_pProgram )}
	{

	}

	void execute()
	{
		std::cout << "Proxy executes the Program "
			<< m_pProgram->getName()
			<< '\n';
	}

	Program* getProgram() const noexcept
	{
		return m_pProgram.get();
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
	{

	}

	// use only const functions to avoid modifying the Program (target object)
	void execute() const noexcept
	{
		std::cout << "Const Proxy executes the Program "
			<< m_proxy.getProgram()->getName()
			<< " promising not to modify it under any circumstances!"
			<< '\n';
	}
};


int main()
{
	Program program{"CCleaner"};

	ProxyProgram proxyProgram{std::move( program )};

	proxyProgram.execute();

	//program.execute();	// it will work in this case, but:
	// 1. the intent in this example is to use the ProxyProgram object to interact with
	//		the target Program object ("program")
	// 2. you should never use an object after it has been moved anyway

	// bonus:
	ProxyProgramConst constProxy{proxyProgram};
	constProxy.execute();
	
#if defined _DEBUG && !defined NDEBUG
	while ( !getchar() );
#endif
	return EXIT_SUCCESS;
}