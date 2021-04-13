#ifndef CK3_COATOFARMS_H
#define CK3_COATOFARMS_H
#include "Color.h"
#include "Emblem.h"
#include "Parser.h"
extern commonItems::Color::Factory laFabricaDeColor;

class CoatOfArms: commonItems::parser
{
  public:
	CoatOfArms() = default;
	CoatOfArms(std::istream& theStream, const std::string& coaID);

	[[nodiscard]] auto getID() const { return ID; }
	[[nodiscard]] const auto& getPattern() const { return pattern; }
	[[nodiscard]] const auto& getColor1() const { return color1; }
	[[nodiscard]] const auto& getColor2() const { return color2; }
	[[nodiscard]] const auto& getColor3() const { return color3; }
	[[nodiscard]] const auto& getTexturedEmblems() const { return texturedEmblems; }
	[[nodiscard]] const auto& getColoredEmblems() const { return coloredEmblems; }
	[[nodiscard]] const auto& getSubs() const { return subs; }
	[[nodiscard]] const auto& getInstances() const { return instances; }
	[[nodiscard]] const auto& getParent() const { return parent; }

	void loadParent(const std::pair<std::string, std::shared_ptr<CoatOfArms>>& theParent) { parent = theParent; }

  private:
	void registerKeys();

	std::string ID;
	std::optional<std::string> pattern;
	std::optional<commonItems::Color> color1; // mask: 255, 0, 0 - red
	std::optional<commonItems::Color> color2; // mask: 255, 255, 0 - yellow
	std::optional<commonItems::Color> color3; // mask: 255, 255, 255 - white
	std::vector<Emblem> texturedEmblems;
	std::vector<Emblem> coloredEmblems;
	std::vector<std::shared_ptr<CoatOfArms>> subs;										// These are sub-coatsofarms. They are recursive!
	std::vector<EmblemInstance> instances;													// Used to position sub-coats.
	std::optional<std::pair<std::string, std::shared_ptr<CoatOfArms>>> parent; // Used for recursive external flags.
	std::map<std::string, std::string> macros; // translates @something into 0.22 or similar.
};

#endif // CK3_COATOFARMS_H
