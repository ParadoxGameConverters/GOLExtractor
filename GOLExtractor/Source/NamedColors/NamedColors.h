#ifndef NAMED_COLORS_H
#define NAMED_COLORS_H
#include "Color.h"
#include "Parser.h"
extern commonItems::Color::Factory laFabricaDeColor;

class NamedColors: commonItems::parser
{
  public:
	NamedColors() = default;
	void loadColors(std::istream& theStream);
	void loadColors(const std::string& filepath);

  private:
	void registerKeys();
};

#endif // NAMED_COLORS_H