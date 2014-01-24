#ifndef _SYSTEM
# define _SYSTEM
#include <string>
#include <vector>

#include "Component.hpp"

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
    const   std::string & retAstres(int);
    Component retMaterial(int i);
    void	astres(int);
    void	astres(int, const std::string &);
    void	materials(Component *);
    std::vector<Component> materials(void);
private:
	std::string _date;
	int			_nbAstre;
    int         _nbMaterial;

	std::string * _astres;
    std::vector<Component> _materials;
};

#endif

