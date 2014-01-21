#ifndef _SYSTEM
# define _SYSTEM
#include <string> 

class SolarSystem
{
public:
	SolarSystem(void);
    SolarSystem(SolarSystem &);
	~SolarSystem(void);
    SolarSystem & operator=(SolarSystem &);

	const std::string & date(void);
	void	date(const std::string &);
	int		nbAstre(void);
	void	nbAstre(int);
	int		astres(void);
	const std::string & retAstres(int);
	void	astres(int);
	void	astres(int, const std::string &);
	const std::string & materials(void);
	void	materials(const std::string &);
private:
	std::string _date;
	int			_nbAstre;
	std::string * _astres;
	std::string _materials;
};

#endif

