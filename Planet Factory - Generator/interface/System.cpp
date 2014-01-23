#include "System.h"

SolarSystem::SolarSystem(void)
    : _date(), _nbAstre(0), _astres(NULL), _nbMaterial(0), _materials(NULL)
{
}

SolarSystem::SolarSystem(SolarSystem & solar)
{
    _date = solar.date();
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
    for (i = 0; i < _nbMaterial; i++)
        _materials[i] = solar.retMaterial(i);
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

int		SolarSystem::astres()
{
	return _nbAstre;
}

void	SolarSystem::astres(int nb)
{
	_astres = new std::string[nb];
}

int		SolarSystem::materials()
{
    return _nbMaterial;
}

void	SolarSystem::materials(int nb)
{
    _materials = new std::string[nb];
}

const std::string & SolarSystem::retAstres(int i)
{
	return _astres[i];
}

const std::string & SolarSystem::retMaterial(int i)
{
    return _materials[i];
}

void	SolarSystem::astres(int nb, const std::string & astre)
{
	_astres[nb] = astre;
}
void	SolarSystem::materials(int nb, const std::string & materials)
{
    _materials[nb] = materials;
}
