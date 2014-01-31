#include "System.h"

SolarSystem::SolarSystem(void)
    : _date(), _nbAstre(0), _astres(NULL), _nbMaterial(0), _materials()
{
}

SolarSystem::SolarSystem(SolarSystem & solar)
{
    int		i;

    _date = solar.date();
    _nbAstre = solar.nbAstre();
    _astres = new std::string[_nbAstre];
    for (i = 0; i < _nbAstre; i++)
        _astres[i] = solar.retAstres(i);
    _nbMaterial = solar.nbMaterial();
    //_materials = new std::vector<Component>;
    //for (std::vector<Component>::iterator it = solar.materials().begin(); it != solar.materials().end(); ++it)
    //    _materials.push_back(*it);
    _materials = solar.materials();
}

SolarSystem::~SolarSystem(void)
{
}

SolarSystem & SolarSystem::operator=(SolarSystem & solar)
{
	int		i;

    _date = solar.date();
    _nbAstre = solar.nbAstre();
	_astres = new std::string[_nbAstre];
	for (i = 0; i < _nbAstre; i++)
        _astres[i] = solar.retAstres(i);
    _nbMaterial = solar.nbMaterial();

    //for (std::vector<Component>::iterator it = solar.materials().begin(); it != solar.materials().end(); ++it)
   //     _materials.push_back(*it);


    _materials = solar.materials();
    /**_materials = new std::string[_nbMaterial];
    for (i = 0; i < _nbMaterial; i++)
        _materials[i] = solar.retMaterial(i);**/
	return *this;
}

const std::string & SolarSystem::date(void)
{
	return _date;
}

void	SolarSystem::date(const std::string & date)
{
	_date = date;
}

int		SolarSystem::nbAstre(void)
{
	return _nbAstre;
}

void	SolarSystem::nbAstre(int nbAstre)
{
	_nbAstre = nbAstre;
}

int     SolarSystem::nbMaterial(void)
{
    return _nbMaterial;
}

void    SolarSystem::nbMaterial(int i)
{
    _nbMaterial = i;
}

void	SolarSystem::astres(int nb)
{
	_astres = new std::string[nb];
}

const std::string & SolarSystem::retAstres(int i)
{
	return _astres[i];
}

Component SolarSystem::retMaterial(int i)
{
    return _materials[i];
}

void	SolarSystem::astres(int nb, const std::string & astre)
{
	_astres[nb] = astre;
}
void	SolarSystem::materials(Component * component)
{
    _materials.push_back(*component);
}


std::vector<Component> SolarSystem::materials(void)
{
    return _materials;
}
