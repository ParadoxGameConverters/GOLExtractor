#ifndef GOLEXTRACTOR_H
#define GOLEXTRACTOR_H
#include "CoatsOfArms/CoatsOfArms.h"
#include "FlagFoundry/FlagFoundry.h"
#include "Magick++.h"
#include "NamedColors/NamedColors.h"

class GOLExtractor
{
  public:
	void extractGarments(const std::string& filePath);

  private:
	void primeLaFabricaDeColor(const std::string& gamePath);
	void loadCoats(const std::string& gamePath);

	NamedColors namedColors;
	CoatsOfArms coats;
	FlagFoundry flagFoundry;
};

#endif // GOLEXTRACTOR_H