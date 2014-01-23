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
    int     nbMaterial(void);
    void    nbMaterial(int);
	int		astres(void);
    const   std::string & retAstres(int);
    const   std::string & retMaterial(int i);
	void	astres(int);
	void	astres(int, const std::string &);
    const   std::string & materials(int i);
    void	materials(int nb, const std::string &);
private:
	std::string _date;
	int			_nbAstre;
    int         _nbMaterial;
	std::string * _astres;
    std::string *_materials;
};

#endif

