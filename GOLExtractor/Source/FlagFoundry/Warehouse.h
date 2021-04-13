#ifndef EU4_WAREHOUSE_H
#define EU4_WAREHOUSE_H
#include <set>

#include "Color.h"
#include "Magick++.h"
#include "Recolorer.h"

class CoatOfArms;
class Emblem;
struct coloredImage
{
	std::optional<commonItems::Color> color1;
	std::optional<commonItems::Color> color2;
	std::optional<commonItems::Color> color3;
	std::string patternName;
	Magick::Image imageData;
	bool operator==(const coloredImage& rhs);
};

class Warehouse
{
  public:
	void loadImageFolders(const std::set<std::string>& sources) { imageFolders = sources; }
	void storeCoA(const std::string& ID, Magick::Image image) { coaStorage.insert(std::pair(ID, image)); }
	[[nodiscard]] std::pair<bool, Magick::Image> getCoA(const std::string& ID);

	[[nodiscard]] std::pair<Magick::Image, Magick::Image> getPattern(const CoatOfArms& coa); // colored/RAW (original) pattern
	[[nodiscard]] std::vector<std::pair<Emblem, Magick::Image>> getColoredTextures(const std::vector<Emblem>& emblems);
	[[nodiscard]] std::vector<std::pair<Emblem, Magick::Image>> getTexturedTextures(const std::vector<Emblem>& emblems);

  private:
	[[nodiscard]] std::vector<std::pair<Emblem, Magick::Image>> getTextures(const std::vector<Emblem>& emblems, const std::string& directoryName);

	std::set<std::string> imageFolders;

	std::map<std::string, Magick::Image> basePatterns; // these are raw background patterns and textured emblems
	std::map<std::string, Magick::Image> baseTextures; // these are raw colored emblems

	std::vector<coloredImage> patternStorage;	 // Storage for crafted CoA patterns, which are RGB solids
	std::vector<coloredImage> texturedStorage; // Storage for crafted colored emblems that use RGBA textures
	std::vector<coloredImage> coloredStorage;	 // Storage for crafted colored emblems, which are RGB solids

	std::map<std::string, Magick::Image> coaStorage; // Storage for finished CoAs to be used as parents in other CoAs

	Recolorer recolorer;
};

#endif // EU4_WAREHOUSE_H