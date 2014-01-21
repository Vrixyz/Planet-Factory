#ifndef _JSONFILEMANAGER
#define _JSONFILEMANAGER
#include <fstream>
#include <string> 
#include <iostream>
#include <sstream>
#include "Jansson.h"
#include "System.h"


enum jsonType
{
    J_SYSTEM,
    J_STAR,
    J_PLANET,
    J_GAZ,
    J_ASTE,
    J_CONF
};

class jsonFileManager
{
public:
	jsonFileManager(const std::string &);
	~jsonFileManager(void);
	int		write(const std::string &);
	
	template <class T>
	T & parse(jsonType type)
	{
		if (!_isReadable())
		{
			std::cout << "No readable" << std::endl;
			exit(1);
		}
        std::cout << "test" << std::endl;
        if(_read())
        {
            std::cout << "Read: error." <<std::endl;
            exit(1);
        }
        std::cout << "buffer : " << _text.c_str() <<std::endl;
		switch (type)
		{
            case J_SYSTEM :
				SolarSystem * solarSystem = new SolarSystem();
				if ((_parseSystem(solarSystem)) == 0)//<SolarSystem>
					return *solarSystem;
            /*case J_STAR : return _parseSystem();
            case J_PLANET : return _parseSystem();
            case J_GAZ : return _parseSystem();
            case J_ASTE : return _parseSystem();
            case J_CONF : return _parseSystem();*/
		}
        std::cout << "Error parsing" << std::endl;
		exit (1);
	}

	template <class T>
	int write(T t, jsonType type)
	{		
		if (!_isReadable())
		{
			std::cout << "No readable" << std::endl;
			exit(1);
		}
		switch (type)
		{
            case J_SYSTEM :
                return _writeSystem(t);
            /*case J_STAR : return _parseSystem();
            case J_PLANET : return _parseSystem();
            case J_GAZ : return _parseSystem();
            case J_ASTE : return _parseSystem();
            case J_CONF : return _parseSystem();*/
		}
        std::cout << "Error writing" << std::endl;
		exit (1);
	}

	void	fileName(const std::string &);
	const	std::string & fileName(void);
	void	text(const std::string &);
	const	std::string & text(void);

private:
	std::string _fileName;
	std::string _text;

	bool	_isReadable(void);
	int		_read(void);
	int		_write(void);
	int		_parseSystem(SolarSystem *);
	int		_writeSystem(const SolarSystem &);

};

#endif
