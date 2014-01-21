#include "System.h"

SolarSystem::SolarSystem(void)
	: _date(), _nbAstre(0), _astres(NULL)
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
    _materials = solar.materials();
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

int		SolarSystem::astres()
{
	return _nbAstre;
}

void	SolarSystem::astres(int nb)
{
	_astres = new std::string[nb];
}

const std::string & SolarSystem::retAstres(int i)
{
	return _astres[i];
}

void	SolarSystem::astres(int nb, const std::string & astre)
{
	_astres[nb] = astre;
}

const std::string & SolarSystem::materials(void)
{
	return _materials;
}

void	SolarSystem::materials(const std::string & materials)
{
	_materials = materials;
}
