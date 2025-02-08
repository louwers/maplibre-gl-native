#include "maplibre-native/include/tile_server_options.h"
#include "maplibre-native/include/map_renderer.h"
#include "maplibre-native/src/lib.rs.h"

namespace ml {
namespace bridge {

std::vector<uint8_t> stringToByteVector(const std::string& input) {
    // Construct a vector of uint8_t from the string’s data
    return std::vector<uint8_t>(input.begin(), input.end());
}

std::vector<uint8_t> MapRenderer::render() {
    // Setup frontend and map
    HeadlessFrontend frontend(size, pixelRatio);

    auto tileServerOptions = TileServerOptions::MapTilerConfiguration();
    ResourceOptions resourceOptions;
    resourceOptions.withCachePath(cachePath).withAssetPath(assetRoot).withApiKey(apiKey).withTileServerOptions(
        tileServerOptions);

    Map map(frontend,
            MapObserver::nullObserver(),
            MapOptions().withMapMode(mapMode).withSize(size).withPixelRatio(pixelRatio),
            resourceOptions);

    // Handle style URL
    if (styleUrl.find("://") == std::string::npos) {
        styleUrl = "file://" + styleUrl;
    }

    // Load style and set camera
    map.getStyle().loadURL("https://demotiles.maplibre.org/style.json");
    map.jumpTo(cameraOptions);

    // Set debug flags
    if (debugFlags != MapDebugOptions::NoDebug) {
        map.setDebug(debugFlags);
    }

    // Render and encode
    auto image = frontend.render(map).image;
    return stringToByteVector(encodePNG(image));
}

} // namespace bridge
} // namespace ml
