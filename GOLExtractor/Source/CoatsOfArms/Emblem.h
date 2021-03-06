#ifndef EMBLEM_H
#define EMBLEM_H
#include "Color.h"
#include "EmblemInstance.h"
#include "Parser.h"
extern commonItems::Color::Factory laFabricaDeColor;

class Emblem: commonItems::parser
{
  public:
	Emblem() = default;
	Emblem(std::istream& theStream,
		 const std::optional<commonItems::Color>& color1,
		 const std::optional<commonItems::Color>& color2,
		 const std::optional<commonItems::Color>& color3);

	[[nodiscard]] const auto& getTexture() const { return texture; }
	[[nodiscard]] const auto& getColor1() const { return color1; }
	[[nodiscard]] const auto& getColor2() const { return color2; }
	[[nodiscard]] const auto& getColor3() const { return color3; }
	[[nodiscard]] const auto& getMask() const { return mask; }
	[[nodiscard]] const auto& getInstances() const { return instances; }

  private:
	void registerKeys();

	std::optional<std::string> texture;
	std::optional<commonItems::Color> color1; // mask: 0, 0, 128 - blueish
	std::optional<commonItems::Color> color2; // mask: 0, 255, 128 - greenish
	std::optional<commonItems::Color> color3; // mask: 255, 0, 128 - unsupported by PDX, must render to white!
	std::vector<int> mask;
	std::vector<EmblemInstance> instances;
	std::map<std::string, std::string> macros; // translates @something into 0.22 or similar.
	std::optional<commonItems::Color> parentColor1;
	std::optional<commonItems::Color> parentColor2;
	std::optional<commonItems::Color> parentColor3;
};

#endif // EMBLEM_H
